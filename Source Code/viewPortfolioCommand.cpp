#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>

#include "iCommand.hpp"
#include "viewPortfolioCommand.hpp"
#include "portfolio.hpp"
#include "menu.hpp"

void ViewPortfolioCommand::execute()
{
    int choice;
    printMenu();

    choice = this->menu.chooseOption();

    system("clear");

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch(choice)
    {
        case 0:
            return;
        
        case 1:
            std::cout << "==== View Current Holdings ====" << std::endl << std::endl;
            this->portfolio.printPortfolio();
            break;
        
        case 2:
            std::cout << "==== Check Converted Portfolio ====" << std::endl << std::endl;
            this->portfolio.printConvertedPortfolio();
            break;
    }

    std::cout << std::endl << "Going back to main menu. Press ENTER to continue.";
    getchar();
    system("clear");

    return;
} 

void ViewPortfolioCommand::printMenu()
{
    Menu& menu = this->menu;

    menu.clearOptions();
    menu.setTitle("View Portfolio");
    menu.addOption("View Current Holdings");
    menu.addOption("Check Converted Portfolio");
    menu.setOptionZero("Go Back");

    system("clear");
    menu.printMenu();
}