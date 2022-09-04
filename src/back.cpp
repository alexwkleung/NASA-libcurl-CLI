#include "back.h"
#include "options.h"
#include "include/termstylist.h"
#include <iostream>

void backMenu() {
    std::string backMenuOpt{};

    std::cin >> backMenuOpt;
    
    if(backMenuOpt == "menu") {
        std::cout << termstylist::FG_White << "Type menu to go back." << termstylist::FG_Default << '\n';
        
        options();
    } else if(backMenuOpt != "menu") {
        std::cin.clear();

        std::cout << termstylist::FG_LightRed << "Invalid input. Try again." << termstylist::FG_Default << '\n';
        
        backMenu();
    }
}