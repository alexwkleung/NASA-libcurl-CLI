#include "include/termstylist.h" //termstylist
#include "back.h"
#include "options.h"
#include <iostream>

void options();

void backMenu() {
    std::string backMenuOpt{};

    std::cout << '\n' << termstylist::FG_White << "Type " << termstylist::FG_Yellow << "back" << termstylist::FG_White << " to go back to the main menu." << backMenuOpt << termstylist::FG_Default << '\n';

    std::cin >> backMenuOpt;

    if(backMenuOpt == "back") {
        options();
    } else if(backMenuOpt != "back") {
        std::cin.clear();

        std::cout << termstylist::FG_LightRed << "Invalid input. Try again." << termstylist::FG_Default << '\n';
        
        backMenu();
    }
}