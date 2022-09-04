#include "include/termstylist.h" //termstylist
#include "options.h"
#include "nasa.h"
#include <iostream>
#include <string>

void options() {
    std::cout << '\n' << termstylist::FG_Cyan << "NASA-libcurl-CLI" << termstylist::FG_Default << '\n';
    std::cout << "=================" << '\n';

    std::cout << termstylist::FG_White << "1) NASA APOD (" << termstylist::FG_Yellow << "apod" << termstylist::FG_Default << ")" << '\n';
    std::cout << termstylist::FG_White << "2) NASA Asteroids - NeoW Feed (" << termstylist::FG_Yellow << "neo-feed" << termstylist::FG_Default << ")" << '\n';
    std::cout << termstylist::FG_White << "3) NASA DONKI - Solar Energetic Particle (" << termstylist::FG_Yellow << "donki-sep" << termstylist::FG_Default << ")" << '\n';
    std::cout << termstylist::FG_White << "4) exit" << termstylist::FG_Default << '\n';
    
    std::string option{};
    
    //take input for option
    std::cin >> option;

    //apod
    if(option == "apod") {
        curlNasaApod();
    }

    //neo-feed
    if(option == "neo-feed") {
        curlNasaAsteroidsNeoWFeed();
    }

    //donki-sep
    if(option == "donki-sep") {
        curlNasaDonkiSep();
    }
    
    //exit
    if(option == "exit") {
        std::cout << termstylist::FG_LightGreen << "Exiting..." << termstylist::FG_Default << '\n';
        exit(0);
    }

    //check input
    if(option != "apod" || option != "neo-feed" || option != "donki-sep" || option != "exit") {
        std::cout << termstylist::ATTRS_Clear << "";

        std::cout << termstylist::FG_LightRed << "Invalid input. Try again." << '\n';

        options();
    }
}