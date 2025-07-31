#include <iostream>
#include <string>
#include "movementTransaction.hpp"
#include "transactionType.hpp"
#include "json.hpp"

#ifndef SELLINGTRANSACTION_HPP
#define SELLINGTRANSACTION_HPP

class SellingTransaction : public MovementTransaction
{
    private:
        double profitMargin;
    
    public:
         SellingTransaction() = default;
        SellingTransaction(double profitMargin, double pricePerShare, double tradedShares, std::string& tickerSymbol, std::string& date, std::string& currency)
        :   profitMargin(profitMargin), MovementTransaction(pricePerShare, tradedShares, tickerSymbol, date, currency) {};
       
        SellingTransaction(const SellingTransaction&) = default;
        SellingTransaction& operator=(const SellingTransaction&) = default;
        SellingTransaction(SellingTransaction&&) = default;
        SellingTransaction& operator=(SellingTransaction&&) = default;

        ~SellingTransaction() = default;


        double getProfitMargin() const;

        Operation::TransactionType getTransactionType() const override;
        void printTransaction(std::ostream& os) const override;
        friend void from_json(const nlohmann::json& j, SellingTransaction& s);
};

#endif