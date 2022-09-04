#include "include/termstylist.h" //termstylist
#include "options.h"
#include "nasa.h"
#include <iostream>
#include <string>

void options() {
    std::cout << '\n' << termstylist::FG_Cyan << "NASA-libcurl-CLI" << termstylist::FG_Default << '\n';
    std::cout << "=================" << '\n';

    std::cout << termstylist::FG_White << "1) NASA APOD (" << termstylist::FG_Yellow << "apod" << termstylist::FG_Default << ")" << '\n';
    std::cout << termstylist::FG_White << "2) NASA Asteroids - NeoW Feed (" << termstylist::FG_Yellow << "asteroids" << termstylist::FG_Default << ")" << '\n';
    std::cout << termstylist::FG_White << "3) exit" << termstylist::FG_Default << '\n';
    
    std::string option{};
    
    std::cin >> option;

    if(option == "apod") {
        curlNasaApod();
    }

    if(option == "asteroids") {
        curlNasaAsteroidsNeoWFeed();
    }

    if(option == "exit") {
        std::cout << termstylist::FG_LightGreen << "Exiting..." << termstylist::FG_Default << '\n';
        exit(0);
    }

    if(option != "apod" || option != "asteroids" || option != "exit") {
        std::cout << termstylist::FG_LightRed << "Invalid input. Try again." << '\n';

        options();
    }
}