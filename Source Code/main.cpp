#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <cctype>
#include <cstdlib>
#include <limits>

#include "json.hpp"
#include "menu.hpp"
#include "asset.hpp"
#include "portfolio.hpp"
#include "portfolioSerialization.hpp"
#include "transactionType.hpp"

#include "iCommand.hpp"
#include "manageAssetCommand.hpp"
#include "addTransactionCommand.hpp"
#include "viewTransactionsCommand.hpp"
#include "viewPortfolioCommand.hpp"

int main()
{
    //Loading and creating a new Portfolio 
    char loadChoice;
    std::string filename;
    std::unique_ptr<Portfolio> portfolio = nullptr;

    system("clear");
    std::cout << "Welcome to Potfolio Manager !" << std::endl << std::endl;

    while(true)
    {
        std::cout << "Do you want to load an existing portfolio file (Y/N): ";
        std::cin >> loadChoice;
        if (std::toupper(loadChoice) == 'Y' || std::toupper(loadChoice) == 'N')
        {
            //Clearing buffer for new inputs
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            break;
        }
        else
        {
            std::cout << std::endl << "Invalid input. Please enter Y or N." << std::endl;

            //Clearing buffer for new inputs
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue;
        }
    }

    if (std::toupper(loadChoice) == 'Y')
    {
        while(true)
        {
            std::cout << "Enter filename: ";
            std::cin >> filename;

            if (filename.length() < 5 || filename.substr(filename.length() - 5) != ".json")
            {
                filename += ".json";
            }

            std::ifstream portfolioFile(filename);

            if (portfolioFile.is_open())
            {
                try
                {
                    //Read from file stream into a json object
                    nlohmann::json j;
                    portfolioFile >> j;

                    portfolio = std::make_unique<Portfolio>(j.get<Portfolio>());

                    std::cout << std::endl << "Successfully loaded portfolio from " << filename << "!" << std::endl;
                    std::cout << "Assets loaded: " << portfolio->getTotalAssets() << std::endl;
                    std::cout << "Transactions loaded: " << portfolio->getTotalTransactions() << std::endl;
                    std::cout << "Currencies loaded: " << portfolio->getTotalCurrencies() << std::endl;
                    break;
                }
                catch(const std::exception& e)
                {
                    std::cerr << "Error: Invalid JSON format in " << filename << ". " << e.what() << std::endl;
                }
            }
            else
            {
                std::cout << "Error: Could not open '" << filename << "'. Please try again." << std::endl;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    else
    {
        portfolio = std::make_unique<Portfolio>(Portfolio());
        std::cout << std::endl << "Let's start a new Portfolio !" << std::endl;
        std::cout << "Give a name to your new Portfolio: ";
        std::cin >> filename;

        if (filename.length() < 5 || filename.substr(filename.length() - 5) != ".json")
            {
                filename += ".json";
            }

        std::cout << std::endl << "Your new Portfolio has been successfully created !";
        std::cout << std::endl << "After managing your portfolio you will receive a file called '" << filename << "'." << std::endl;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << std::endl << "Press ENTER to comtinue";
    std::getchar();
    system("clear");

    //Main Menu
    int choice;
    std::unique_ptr<Menu> menu = std::make_unique<Menu>(Menu("Portfolio Manager"));

    //Building Main Menu options
    menu->addOption("Manage Assets");
    menu->addOption("Add Transactions");
    menu->addOption("View Transactions History");
    menu->addOption("View Portfolio");

    //Sub Menus
    std::unique_ptr<Menu> subMenu = std::make_unique<Menu>(Menu());
    std::map<int, std::unique_ptr<ICommand>> subMenus;

    subMenus.emplace(1, std::make_unique<ManageAssetCommand>(ManageAssetCommand((*portfolio), (*subMenu))));
    subMenus.emplace(2, std::make_unique<AddTransactionCommand>(AddTransactionCommand((*portfolio), (*subMenu))));
    subMenus.emplace(3, std::make_unique<ViewTransactionsCommand>(ViewTransactionsCommand((*portfolio), (*subMenu))));
    subMenus.emplace(4, std::make_unique<ViewPortfolioCommand>(ViewPortfolioCommand((*portfolio), (*subMenu))));

    while (true)
    {
        menu->printMenu();
        choice = menu->chooseOption();

        if (choice == 0)
        {
            nlohmann::json j = *portfolio;
            std::ofstream updatedFile (filename);
            updatedFile << j.dump(4) << std::endl;
            
            system("clear");
            std::cout << "Successfully saved your portfolio on '" << filename << "." << std::endl;
            break;
        }
        else
        {
            subMenus[choice]->execute();
        }
    }
    return 0;
}