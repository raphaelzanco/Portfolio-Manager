#include <iostream>
#include <string>
#include "movementTransaction.hpp"
#include "transactionType.hpp"
#include "json.hpp"

#ifndef PURCHASETRANSACTION_HPP
#define PURCHASETRANSACTION_HPP

class PurchaseTransaction : public MovementTransaction
{
    public:
        PurchaseTransaction() = default;
        PurchaseTransaction(double pricePerShare, double tradedShares, std::string& tickerSymbol, std::string& date, std::string& currency)
        :   MovementTransaction(pricePerShare, tradedShares, tickerSymbol, date, currency) {};

        PurchaseTransaction(const PurchaseTransaction&) = default;
        PurchaseTransaction& operator=(const PurchaseTransaction&) = default;
        PurchaseTransaction(PurchaseTransaction&&) = default;
        PurchaseTransaction& operator=(PurchaseTransaction&&) = default;

        ~PurchaseTransaction() = default;

        Operation::TransactionType getTransactionType() const override;
        void printTransaction(std::ostream& os) const override;
        friend void from_json(const nlohmann::json& j, PurchaseTransaction& p);
};

#endif