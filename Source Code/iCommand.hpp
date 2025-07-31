#include <iostream>
#include "portfolio.hpp"

#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

class ICommand
{   
        public:
            ICommand() {};
            virtual ~ICommand() = default;

            virtual void execute() = 0;
};

#endif