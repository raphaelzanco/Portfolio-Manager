#include <iostream>
#include "portfolio.hpp"
#include "menu.hpp"
#include "iCommand.hpp"

#ifndef VIEWTRANSACTIONSCOMMAND_HPP
#define VIEWTRANSACTIONSCOMMAND_HPP

class ViewTransactionsCommand : public ICommand
{
    private:
        Portfolio& portfolio;
        Menu& menu;
    
        public:
            ViewTransactionsCommand(Portfolio& p, Menu& m): portfolio(p), menu(m) {};
            ~ViewTransactionsCommand() = default;

            void execute() override;
            void printMenu();
};

#endif