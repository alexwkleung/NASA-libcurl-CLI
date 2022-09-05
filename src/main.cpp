#include "nasa.h"
#include "options.h"
#include <iostream>
#include <vector>
#include <string>

void options();

int main(int argc, char **argv) {
    //vector to hold command line arguments 
    std::vector<std::string> args = {argv + 1, argv + argc};

    //iterate over vector using iterator and compare each index to passed argument
    for(std::vector<std::string>::iterator it = args.begin(); it != args.end(); it++) {
        if(*it == "--apod") {
            curlNasaApod();
        } else if(*it == "--neo-feed") {
            curlNasaAsteroidsNeoWFeed();
        } else if(*it == "--donki-sep") {
            curlNasaDonkiSep();
        } else if(*it == "--insight") {
            curlNasaInsight();
        } else if(*it == "--options") {
            options();
        } else {
            return 0;
        }
    }

    return 0;
}