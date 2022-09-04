#include "options.h"
#include "back.h"
#include "include/nlohmann/json.hpp" //nlohmann json
#include <curl/curl.h> //libcurl
#include <cstdlib> //memcpy(), realloc(), malloc(), free()
#include <iostream>
#include <fstream>

//references: 
//https://curl.se/libcurl/c/getinmemory.html
//https://curl.se/libcurl/c/simple.html
//https://json.nlohmann.me/api/basic_json/parse/
//https://json.nlohmann.me/api/basic_json/dump/

struct MemoryStruct {
    public:
        char *memory{};
        std::size_t size;
};

//callback function for url
std::size_t curlWriteCallback(void *dataContents, const std::size_t size, const std::size_t nmemb, void *data) {
    std::size_t realSize = size * nmemb;

    //MemoryStruct object, casting data ptr to MemoryStruct
    MemoryStruct *mem = (MemoryStruct*) data;

    //reallocate block of memory
    char *ptr = static_cast<char*>(std::realloc(mem->memory, mem->size + realSize + 1));

    //check if the block of memory doesn't have enough memory
    //when there is not enough memory, the ptr of the memory block won't be freed and realloc() returns a null pointer
    if(!ptr) {
        std::cout << "Not enough memory for reallocation. realloc() returned a NULL pointer." << '\n';
        return 0;
    }

    //memory takes value of ptr
    mem->memory = ptr;
    //copy the chunk of memory into the dataContents pointer, taking in realSize (size * nmemb) number of bytes to copy
    std::memcpy(&(mem->memory[mem->size]), dataContents, realSize);
    //value of size is size + realSize
    mem->size += realSize;
    //value of memory at index size is 0 (no memory)
    mem->memory[mem->size] = 0;

    //return value of realSize 
    return realSize;
}

//apod fetch
void curlNasaApod() {   
    //grab api key
    std::string key{};

    std::ifstream apiKey("./src/key.txt");

    std::getline(apiKey, key);
    
    //create concatenated url
    std::string url = "https://api.nasa.gov/planetary/apod?api_key=" + key;

    //curl objects
    CURL *curl;
    CURLcode res;
    
    //MemoryStruct object
    MemoryStruct chunk;

    chunk.memory = static_cast<char*>(malloc(1)); //byte allocation size will increase via realloc() of the char ptr
    chunk.size = 0; //size of memory is 0, meaning no memory

    curl_global_init(CURL_GLOBAL_ALL);

    //initialize libcurl easy init
    curl = curl_easy_init();

    if(curl) {
        //set curl easy handle url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        //set curl callback function 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);

        //our url that is redirected will be followed by libcurl 
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        //pass chunk object (MemoryStruct) to the callback function (curlWriteCallback)
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

        //perform the request of our url
        //res will hold our return code
        res = curl_easy_perform(curl);

        //check if the return code of res is an error code
        //if true, print error
        //else, do operations regardomg the data contents from the memory block (chunk.memory)
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n' << std::flush;
        } else {
            //parse chars from memory as json string value
            auto jsonParse = nlohmann::json::parse(chunk.memory);
            
            //create a json object from parsed json string
            nlohmann::json jsonObject = jsonParse; 

            //output parsed json to file
            std::ofstream apod("./src/json-out/apod.json");
            apod << jsonObject.dump(4);

            //output parsed json to terminal
            std::cout << jsonObject.dump(4) << '\n' << std::flush; //output prettified parsed json string
        }

        //cleanup curl
        curl_easy_cleanup(curl);

        //free previous allocated memory from malloc/realloc
        free(chunk.memory);

        //cleanup global 
        curl_global_cleanup();
    }

    //call backMenu()
    backMenu();
}

//asteroid neow feed fetch
void curlNasaAsteroidsNeoWFeed() {
    std::string key{};

    std::ifstream apiKey("./src/key.txt");

    std::getline(apiKey, key);

    //url
    std::string initUrl = "https://api.nasa.gov/neo/rest/v1/feed?";
    std::string startDate = "start_date=";
    std::string startDateVal{};
    std::string endDate = "&end_date";
    std::string endDateVal{};
    std::string initApiKey = "&api_key=";

    //take input (start_date)
    std::cout << "start_date (YYYY-MM-DD): " << startDateVal;
    std::cin.clear();
    std::cin >> startDateVal;

    //take input (end_date)
    std::cout << "end_date (YYYY-MM-DD): " << endDateVal;
    std::cin.clear();
    std::cin >> endDateVal;

    std::string url = initUrl + startDate + startDateVal + endDate + endDateVal + initApiKey + key; 

    CURL *curl;
    CURLcode res;

    MemoryStruct chunk;

    chunk.memory = static_cast<char*>(malloc(1));
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n' << std::flush;
        } else {
            auto jsonParse = nlohmann::json::parse(chunk.memory);

            nlohmann::json jsonObject = jsonParse;

            //parsed json to file
            std::ofstream neoFeed("./src/json-out/neofeed.json");
            neoFeed << jsonObject.dump(4);

            //parsed json to terminal
            std::cout << jsonObject.dump(4) << '\n' << std::flush;
        }
    }

    curl_easy_cleanup(curl);

    free(chunk.memory);
    
    curl_global_cleanup();

    backMenu();
}

//donki sep fetch
void curlNasaDonkiSep() {
    std::string key{};

    std::ifstream apiKey("./src/key.txt");

    std::getline(apiKey, key);

    std::string initUrl = "https://api.nasa.gov/DONKI/SEP?";
    std::string startDate = "startDate=";
    std::string startDateVal{};
    std::string endDate = "&endDate=";
    std::string endDateVal{};
    std::string initApiKey = "&api_key=";

    std::cout << "start_date (YYYY-MM-DD): " << startDateVal << "";
    std::cin.clear();
    std::cin >> startDateVal;

    std::cout << "end_date (YYYY-MM-DD): " << endDateVal << "";
    std::cin.clear();
    std::cin >> endDateVal;

    std::string url = initUrl + startDate + startDateVal + endDate + endDateVal + initApiKey + key;

    CURL *curl;
    CURLcode res;

    MemoryStruct chunk;

    chunk.memory = static_cast<char*>(malloc(1));
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n' << std::flush;
        } else {
            auto jsonParse = nlohmann::json::parse(chunk.memory);

            nlohmann::json jsonObject = jsonParse;

            std::ofstream donkiSep("./src/json-out/donkisep.json");

            donkiSep << jsonObject.dump(4);

            std::cout << jsonObject.dump(4) << '\n' << std::flush;
        }
    }

    curl_easy_cleanup(curl);

    free(chunk.memory);

    curl_global_cleanup();

    backMenu();
}