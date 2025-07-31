#include <iostream>
#include <string>
#include "transaction.hpp"

std::string Transaction::getDate() const
{
    return this->date;
}

std::string Transaction::getTickerSymbol() const
{
    return this->tickerSymbol;
}

std::string Transaction::getCurrency() const
{
    return this->currency;
}

std::ostream& operator<<(std::ostream& os, const Transaction& tx)
{
    tx.printTransaction(os);
    return os;
}
