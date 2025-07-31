#include <iostream>
#include <string>
#include "transaction.hpp"
#include "json.hpp"

#ifndef MOVEMENTTRANSACTION_HPP
#define MOVEMENTTRANSACTION_HPP

class MovementTransaction : public Transaction
{
    private:
        double pricePerShare;
        double tradedShares;
    
        public:
            MovementTransaction() = default;
            MovementTransaction(double pricePerShare, double tradedShares, std::string& tickerSymbol, std::string& date, std::string& currency)
                : pricePerShare(pricePerShare), tradedShares(tradedShares), Transaction(tickerSymbol, date, currency) {};

            MovementTransaction(const MovementTransaction&) = default;
            MovementTransaction& operator=(const MovementTransaction&) = default;
            MovementTransaction(MovementTransaction&&) = default;
            MovementTransaction& operator=(MovementTransaction&&) = default;

            virtual ~MovementTransaction() = default;
            
            double getPricePerShare() const;
            double getTradedShares() const;
            friend void from_json(const nlohmann::json& j, MovementTransaction& m);
};

#endif