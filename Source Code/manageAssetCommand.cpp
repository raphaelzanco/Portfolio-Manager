#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include "portfolio.hpp"
#include "menu.hpp"
#include "iCommand.hpp"
#include "manageAssetCommand.hpp"

void ManageAssetCommand::execute()
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
            addAsset();
            break;
        
        case 2:
            deleteAsset();
            break;
        
        case 3:
            editAsset();
            break;
        
        case 4:
            viewAssets();
            break;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

    std::cout << std::endl << "Going back to main menu. Press ENTER to continue.";
    getchar();
    system("clear");

    return;
}

void ManageAssetCommand::addAsset()
{
    std::string tickerSymbol, assetClass, currency;

    std::cout << "==== Add Asset ====" << std::endl << std::endl;

    while(true)
    {
        std::cout << "Enter Ticker Symbol: ";
        std::cin >> tickerSymbol;
        std::transform(tickerSymbol.begin(), tickerSymbol.end(), tickerSymbol.begin(), ::toupper);
        

        if ((this->portfolio.isRegisteredAsset(tickerSymbol)) == false)
        {
            break;
        }
        else
        {
            //Warning for repeated asset 
            char loadChoice;
                
            std::cout << std::endl << "Error: Your portfolio already know an asset called " << tickerSymbol << ".";

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

    std::cout << "Enter Asset Class (e.g Stock, ETF, Bond, REIT): ";
    std::cin >> assetClass;

    std::cout << "Enter Currency (e.g USD, EUR, BRL): ";
    std::cin >> currency;
    std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);

    bool addAsset = this->portfolio.addAsset(tickerSymbol, assetClass, currency);
    if (addAsset == false)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        std::cout << std::endl << "Going back to main menu. Press ENTER to continue.";
        std::getchar();
        return;
    }

    std::cout << std::endl << "Successfully added asset " << tickerSymbol << " (" << assetClass << ")" << " in " << currency;

    return;
}

void ManageAssetCommand::deleteAsset()
{
    std::string tickerSymbol;

    std::cout << "==== Delete Asset ====" << std::endl << std::endl;

    while(true)
    {
        std::cout << "Enter Ticker Symbol: ";
        std::cin >> tickerSymbol;
        std::transform(tickerSymbol.begin(), tickerSymbol.end(), tickerSymbol.begin(), ::toupper);

        if ((this->portfolio.isRegisteredAsset(tickerSymbol)) == true)
        { 
            break;
        }

        //Warning for unknown asset 
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
    
    this->portfolio.deleteAsset(tickerSymbol);
    return;
}

void ManageAssetCommand::editAsset()
{
    std::string tickerSymbol, changedStr;

    std::cout << "==== Edit Asset ====" << std::endl << std::endl;

    while(true)
    {
        std::cout << "Enter Ticker Symbol: ";
        std::cin >> tickerSymbol;
        std::transform(tickerSymbol.begin(), tickerSymbol.end(), tickerSymbol.begin(), ::toupper);

        if ((this->portfolio.isRegisteredAsset(tickerSymbol)) == true)
        {
            break;
        }

        //Warning for repeated asset 
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

    Asset* asset = this->portfolio.getAsset(tickerSymbol);
    if (asset == nullptr)
    {
        std::cout << std::endl << "Couldn't edit asset called " << tickerSymbol << std::endl;
        return;
    }

    system("clear");

    int choice;
    std::cout << "__Check informations__ " << std::endl;
    std::cout << "Ticker Symbol: " << asset->getTickerSymbol() << std::endl;
    std::cout << "Class: " << asset->getAssetClass() << std::endl;
    std::cout << "Currency: " << asset->getCurrency() << std::endl <<std::endl;

    this->menu.setTitle("Edit Options");
    this->menu.clearOptions();
    this->menu.addOption("Class");
    this->menu.addOption("Currency");
    this->menu.setOptionZero("Back to Manage Asset Menu");

    this->menu.printMenu();
    choice = this->menu.chooseOption();

    switch(choice)
    {
        case 0:
            execute();
            break;
        
        case 1:
            std::cout << std::endl << "Insert new Class: ";
            std::cin >> changedStr;

            asset->setAssetClass(changedStr);
            std::cout << "Successfully changed asset class to " << changedStr << std::endl;
            break;
        
        case 2:
            std::cout << std::endl << "Insert new Currency: ";
            std::cin >> changedStr;
            std::transform(changedStr.begin(), changedStr.end(), changedStr.begin(), ::toupper);

            asset->setCurrency(changedStr);
            std::cout << "Successfully changed asset currency to " << changedStr << std::endl;
            break;
    }

    return;
}

void ManageAssetCommand::viewAssets()
{
    std::cout << "==== View Assets ====" << std::endl << std::endl;
    this->portfolio.printAllTickers();
}

void ManageAssetCommand::printMenu()
{
    Menu& menu = this->menu;

    menu.clearOptions();
    menu.setTitle("Manage Asset");
    menu.addOption("Add Asset");
    menu.addOption("Delete Asset");
    menu.addOption("Edit Asset");
    menu.addOption("View Assets");
    menu.setOptionZero("Go Back");

    system("clear");
    menu.printMenu();
}

