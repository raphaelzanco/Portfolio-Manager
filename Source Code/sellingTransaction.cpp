#include <iostream>
#include <string>
#include <iomanip>
#include "sellingTransaction.hpp"
#include "transactionType.hpp"

double SellingTransaction::getProfitMargin() const
{
    return this->profitMargin;
}

Operation::TransactionType SellingTransaction::getTransactionType() const
{
    return Operation::TransactionType::Sell;
}

void SellingTransaction::printTransaction(std::ostream& os) const
{
    //TODO
    // Set formatting for floating-point numbers
    os << std::fixed << std::setprecision(2);

    os << std::left << std::setw(11) << this->getDate() << "| ";

    os << std::setw(8) << this->getTransactionType() << "| ";

    os << std::setw(8) << this->getTickerSymbol() << "  | ";

    os << std::setw(9) << this->getTradedShares() << "  | ";

    os << std::setw(10) << this->getPricePerShare() << "  | ";

    os << std::setw(10) << this->getProfitMargin() << "  | ";

    os << this->getCurrency() << std::endl;
}