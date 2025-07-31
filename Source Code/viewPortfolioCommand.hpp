#include <iostream>
#include "portfolio.hpp"
#include "menu.hpp"
#include "iCommand.hpp"

#ifndef VIEWPORTFOLIOCOMMAND_HPP
#define VIEWPORTFOLIOCOMMAND_HPP

class ViewPortfolioCommand : public ICommand
{
    private:
        Portfolio& portfolio;
        Menu& menu;
    
    public:
        ViewPortfolioCommand(Portfolio& p, Menu& m): portfolio(p), menu(m) {};
        ~ViewPortfolioCommand() = default;

        void execute() override;
        void printMenu();
};

#endif