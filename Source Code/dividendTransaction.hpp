#include <iostream>
#include <string>
#include "transaction.hpp"
#include "json.hpp"

#ifndef DIVIDENDTRANSACTION_HPP
#define DIVIDENDTRANSACTION_HPP

class DividendTransaction : public Transaction
{
    private:
        double dividendPerShare;
        double heldShares;
        double totalDividend;
    
        public:
             DividendTransaction() = default;
            DividendTransaction(double dividendPerShare, double heldShares, double totalDividend, std::string& tickerSymbol, std::string& date, std::string& currency)
                : dividendPerShare(dividendPerShare), heldShares(heldShares), totalDividend(totalDividend), Transaction(tickerSymbol, date, currency) {};

            DividendTransaction(const DividendTransaction&) = default;
            DividendTransaction& operator=(const DividendTransaction&) = default;
            DividendTransaction(DividendTransaction&&) = default;
            DividendTransaction& operator=(DividendTransaction&&) = default;

            ~DividendTransaction() = default;
            
            double getDividendPerShare() const;
            double getHeldShares() const;
            double getTotalDividend() const;

            Operation::TransactionType getTransactionType() const override;
            void printTransaction(std::ostream& os) const override;
            friend void from_json(const nlohmann::json& j, DividendTransaction& d);
};

#endif