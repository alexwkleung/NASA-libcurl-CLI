#include "back.h"
#include "options.h"
#include "include/termstylist.h"
#include <iostream>

void backMenu() {
    std::string backMenuOpt{};

    std::cout << '\n' << termstylist::FG_White << "Type " << termstylist::FG_Yellow << "back" << termstylist::FG_Default << " to go back to the main menu." << backMenuOpt << '\n';

    std::cin >> backMenuOpt;

    if(backMenuOpt == "back") {
        options();
    } else if(backMenuOpt != "back") {
        std::cin.clear();

        std::cout << termstylist::FG_LightRed << "Invalid input. Try again." << termstylist::FG_Default << '\n';
        
        backMenu();
    }
}