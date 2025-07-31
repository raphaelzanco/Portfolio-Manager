#include <iostream>
#include "portfolio.hpp"
#include "menu.hpp"
#include "iCommand.hpp"

#ifndef MANAGEASSETCOMMAND_HPP
#define MANAGEASSETCOMMAND_HPP

class ManageAssetCommand : public ICommand
{
    private:
        Portfolio& portfolio;
        Menu& menu;
    
    public:
        ManageAssetCommand(Portfolio& p, Menu& m): portfolio(p), menu(m) {};
        ~ManageAssetCommand() = default;

        void execute() override;
        void addAsset();
        void deleteAsset();
        void editAsset();
        void viewAssets();
        void printMenu();
};


#endif