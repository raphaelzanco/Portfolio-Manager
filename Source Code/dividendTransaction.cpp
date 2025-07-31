#include <iostream>
#include <iomanip>
#include "transaction.hpp"
#include "transactionType.hpp"
#include "dividendTransaction.hpp"

double DividendTransaction::getDividendPerShare() const
{
    return this->dividendPerShare;
}

double DividendTransaction::getHeldShares() const
{
    return this->heldShares;
}

double DividendTransaction::getTotalDividend() const
{
    return this->totalDividend;
}

Operation::TransactionType DividendTransaction::getTransactionType() const
{
    return Operation::TransactionType::Dividend;
}

void DividendTransaction::printTransaction(std::ostream& os) const
{
    // Set formatting for floating-point numbers 
    os << std::fixed << std::setprecision(2);

    os << std::left << std::setw(11) << this->getDate() << "| ";

    os << std::setw(10) << this->getTickerSymbol() << "| ";

    os << std::setw(19) << this->getDividendPerShare() << "  | ";

    os << std::setw(9) << this->getHeldShares() << "  | ";

    os << std::setw(15) << this->getTotalDividend() << "  | ";

    os << this->getCurrency() << std::endl;
}