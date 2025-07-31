#include <iostream>
#include <string>
#include "json.hpp"

#ifndef ASSET_HPP
#define ASSET_HPP

class Asset
{
    private:
        std::string tickerSymbol;
        std::string assetClass;
        std::string currency;
        double heldShares;
        double averagePrice;
        double dividendReceived;
    
    public:
        Asset() = default;
        Asset(std::string& tickerSymbol, std::string& assetClass, std::string& currency)
            : tickerSymbol(tickerSymbol), assetClass(assetClass), currency(currency), heldShares(0), averagePrice(0), dividendReceived(0) {};

        Asset(std::string& tickerSymbol, std::string& assetClass, std::string& currency, double heldShares, double averagePrice, double dividendReceived)
            : tickerSymbol(tickerSymbol), assetClass(assetClass), currency(currency), heldShares(heldShares), averagePrice(averagePrice), dividendReceived(dividendReceived) {};
        
        Asset(const Asset&) = default;
        Asset& operator=(const Asset&) = default;
        Asset(Asset&&) = default;
        Asset& operator=(Asset&&) = default;

        ~Asset() = default;

        std::string getTickerSymbol() const;
        std::string getAssetClass() const;
        std::string getCurrency() const;
        double getHeldShares() const;
        double getAveragePrice() const;
        double getDividendReceived() const;

        void setTickerSymbol(std::string newTickerSymbol);
        void setAssetClass(std::string newAssetClass);
        void setCurrency(std::string newCurrency);

        bool purchaseShares(double numShares, double price);
        bool sellShares(double numShares, double price);
        bool payDividend(double totalDividend, double heldShares);

        friend std::ostream& operator<<(std::ostream& os, const Asset& asset);
        friend void from_json(const nlohmann::json& j, Asset&a);
};

#endif