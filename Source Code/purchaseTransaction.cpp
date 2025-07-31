#include <iostream>
#include <string>
#include <iomanip>
#include "purchaseTransaction.hpp"
#include "transactionType.hpp"

Operation::TransactionType PurchaseTransaction::getTransactionType() const
{
    return Operation::TransactionType::Buy;
}

void PurchaseTransaction::printTransaction(std::ostream& os) const
{
    //TODO
    // Set formatting for floating-point numbers
    os << std::fixed << std::setprecision(2);

    os << std::left << std::setw(11) << this->getDate() << "| ";

    os << std::setw(8) << this->getTransactionType() << "| ";

    os << std::setw(8) << this->getTickerSymbol() << "  | ";

    os << std::setw(9) << this->getTradedShares() << "  | ";

    os << std::setw(10) << this->getPricePerShare() << "  | ";

    os << std::setw(9) << "----------- " << "| ";

    os << this->getCurrency() << std::endl;
}