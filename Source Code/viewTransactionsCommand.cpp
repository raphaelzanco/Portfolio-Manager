#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>

#include "iCommand.hpp"
#include "viewTransactionsCommand.hpp"
#include "portfolio.hpp"
#include "transactionType.hpp"
#include "menu.hpp"

void ViewTransactionsCommand::execute()
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
            std::cout << "==== View Purchase Transaction ====" << std::endl << std::endl;
            this->portfolio.printTransaction(Operation::TransactionType::Buy);
            break;
        
        case 2:
            std::cout << "==== View Selling Transaction ====" << std::endl << std::endl;
            this->portfolio.printTransaction(Operation::TransactionType::Sell);
            break;
        
        case 3:
            std::cout << "==== View Movement Transaction ====" << std::endl << std::endl;
            this->portfolio.printTransaction(Operation::TransactionType::Movement);
            break;
        
        case 4:
            std::cout << "==== View Dividend Transaction ====" << std::endl << std::endl;
            this->portfolio.printTransaction(Operation::TransactionType::Dividend);
            break;
    }

    std::cout << std::endl << "Going back to main menu. Press ENTER to continue.";
    getchar();
    system("clear");

    return;
}

void ViewTransactionsCommand::printMenu()
{
    Menu& menu = this->menu;

    menu.clearOptions();
    menu.setTitle("View Transactions History");
    menu.addOption("Purchase Transactions");
    menu.addOption("Selling Transactions");
    menu.addOption("Movement Transaction (Purchase and Selling)");
    menu.addOption("Dividend Transaction");
    menu.setOptionZero("Go Back");

    system("clear");
    menu.printMenu();
}