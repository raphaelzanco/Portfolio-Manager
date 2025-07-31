#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>

#include "iCommand.hpp"
#include "addTransactionCommand.hpp"
#include "portfolio.hpp"
#include "menu.hpp"

void AddTransactionCommand::execute()
{
    int choice;
    printMenu();

    choice = this->menu.chooseOption();

    system("clear");

    switch(choice)
    {
        case 0:
            return;
        
        case 1:
            purchaseTransaction();
            break;
        
        case 2:
            sellingTransaction();
            break;
        
        case 3:
            dividendTransaction();
            break;
    }

    std::cout << std::endl << "Going back to main menu. Press ENTER to continue.";
    getchar();
    system("clear");

    return;
}

void AddTransactionCommand::purchaseTransaction()
{
    std::string tickerSymbol;
    double numShares, price;

    std::cout << "==== Add Purchase Transaction ====" << std::endl << std::endl;

    while(true)
    {
        std::cout << "Enter Ticker Symbol: ";
        std::cin >> tickerSymbol;
        std::transform(tickerSymbol.begin(), tickerSymbol.end(), tickerSymbol.begin(), ::toupper);
        

        if ((this->portfolio.isRegisteredAsset(tickerSymbol)) == true)
        {
            break;
        }
        else
        {
            char loadChoice;
                
            std::cout << std::endl << "Error: Your portfolio doesn't know an asset called " << tickerSymbol << ".";

            while(true)
            {
                std::cout << std::endl << "Do you want to try again (Y/N): ";
                std::cin >> loadChoice;
                if (std::toupper(loadChoice) == 'Y')
                {           
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    break;
                }
                else if (std::toupper(loadChoice) == 'N')
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    return;
                }
                else
                {
                    std::cout << std::endl << "Invalid input. Please enter Y or N." << std::endl;

                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    continue;
                }
            }
        }
    }

    std::cout << "Enter Number of Traded Shares: ";
    std::cin >> numShares;

    std::cout << "Enter Traded Price per Share: ";
    std::cin >> price;
    std::cout << std::endl;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    this->portfolio.makePurchase(tickerSymbol, numShares, price);

    return;
}

void AddTransactionCommand::sellingTransaction()
{
    std::string tickerSymbol;
    double numShares, price;

    std::cout << "==== Add Selling Transaction ====" << std::endl << std::endl;

   while(true)
    {
        std::cout << "Enter Ticker Symbol: ";
        std::cin >> tickerSymbol;
        std::transform(tickerSymbol.begin(), tickerSymbol.end(), tickerSymbol.begin(), ::toupper);
        

        if ((this->portfolio.isRegisteredAsset(tickerSymbol)) == true)
        {
            break;
        }
        else
        {
            char loadChoice;
                
            std::cout << std::endl << "Error: Your portfolio doesn't know an asset called " << tickerSymbol << ".";

            while(true)
            {
                std::cout << std::endl << "Do you want to try again (Y/N): ";
                std::cin >> loadChoice;
                if (std::toupper(loadChoice) == 'Y')
                {           
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    break;
                }
                else if (std::toupper(loadChoice) == 'N')
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    return;
                }
                else
                {
                    std::cout << std::endl << "Invalid input. Please enter Y or N." << std::endl;

                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    continue;
                }
            }
        }
    }

    std::cout << "Enter Number of Traded Shares: ";
    std::cin >> numShares;

    std::cout << "Enter Traded Price per Share: ";
    std::cin >> price;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->portfolio.makeSelling(tickerSymbol, numShares, price);

    return;
}

void AddTransactionCommand::dividendTransaction()
{
    std::string tickerSymbol;
    double dividendPerShare, heldShares, totalDividend;

    std::cout << "==== Add Dividend Transaction ====" << std::endl << std::endl;

    while(true)
    {
        std::cout << "Enter Ticker Symbol: ";
        std::cin >> tickerSymbol;
        std::transform(tickerSymbol.begin(), tickerSymbol.end(), tickerSymbol.begin(), ::toupper);
        

        if ((this->portfolio.isRegisteredAsset(tickerSymbol)) == true)
        {
            break;
        }
        else
        {
            char loadChoice;
                
            std::cout << std::endl << "Error: Your portfolio doesn't know an asset called " << tickerSymbol << ".";

            while(true)
            {
                std::cout << std::endl << "Do you want to try again (Y/N): ";
                std::cin >> loadChoice;
                if (std::toupper(loadChoice) == 'Y')
                {           
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    break;
                }
                else if (std::toupper(loadChoice) == 'N')
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    return;
                }
                else
                {
                    std::cout << std::endl << "Invalid input. Please enter Y or N." << std::endl;

                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    continue;
                }
            }
        }
    }

    std::cout << "Enter Dividend Per Share: ";
    std::cin >> dividendPerShare;

    std::cout << "Enter Number of Shares: ";
    std::cin >> heldShares;

    std::cout << "Enter Total Dividend: ";
    std::cin >> totalDividend;
    std::cout << std::endl;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    this->portfolio.receiveDividend(tickerSymbol, dividendPerShare, heldShares, totalDividend);

    return;
}

void AddTransactionCommand::printMenu()
{
    Menu& menu = this->menu;

    menu.clearOptions();
    menu.setTitle("Add Transaction");
    menu.addOption("Purchase Transaction");
    menu.addOption("Selling Transaction");
    menu.addOption("Dividend Transaction");
    menu.setOptionZero("Go Back");

    system("clear");
    menu.printMenu();
}