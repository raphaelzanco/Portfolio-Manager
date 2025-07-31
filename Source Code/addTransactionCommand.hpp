#include <iostream>
#include "portfolio.hpp"
#include "menu.hpp"
#include "iCommand.hpp"

#ifndef ADDTRANSACTIONCOMMAND_HPP
#define ADDTRANSACTIONCOMMAND_HPP

class AddTransactionCommand : public ICommand
{
    private:
        Portfolio& portfolio;
        Menu& menu;
    
        public:
            AddTransactionCommand(Portfolio& p, Menu& m): portfolio(p), menu(m) {};
            ~AddTransactionCommand() = default;

            void execute() override;
            void purchaseTransaction();
            void sellingTransaction();
            void dividendTransaction();
            void printMenu();
};

#endif