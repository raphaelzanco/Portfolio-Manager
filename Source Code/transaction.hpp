#include <iostream>
#include <string>
#include "transactionType.hpp"
#include "json.hpp"

#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

class Transaction
{
    private:
        std::string tickerSymbol;
        std::string date;
        std::string currency;

        public:
            Transaction() = default;
            Transaction(std::string& tickerSymbol, std::string& date, std::string& currency) 
                : tickerSymbol(tickerSymbol), date(date), currency(currency) {};
         
            Transaction(const Transaction&) = default;
            Transaction& operator=(const Transaction&) = default;
            Transaction(Transaction&&) = default;
            Transaction& operator=(Transaction&&) = default;

            virtual ~Transaction() = default;

            std::string getDate() const;
            std::string getTickerSymbol() const;
            std::string getCurrency() const;

            friend std::ostream& operator<<(std::ostream& os, const Transaction& tx);
            virtual Operation::TransactionType getTransactionType() const = 0;
            virtual void printTransaction(std::ostream& os) const = 0;
            friend void from_json(const nlohmann::json& j, Transaction& t);
};

#endif