#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include "asset.hpp"
#include "transaction.hpp"
#include "transactionType.hpp"
#include "json.hpp"

#ifndef PORTFOLIO_HPP  
#define PORTFOLIO_HPP

class Portfolio
{
    private:
        std::map<std::string, std::unique_ptr<Asset>> heldAsset;
        std::vector<std::unique_ptr<Transaction>> transactionHistory;

        bool checkValidDate(std::string& date); 
        void registerPurchaseTransaction(std::string& tickerSymbol, double numShares, double price);
        void registerSellingTransaction(std::string& tickerSymbol, double numShares, double price, double tickerAveragePrice);
        void registerDividendTransaction(std::string& tickerSymbol, double dividendPerShare, double heldShares, double totalDividend);
    
        public:

            Portfolio() = default;
            Portfolio(std::map<std::string, std::unique_ptr<Asset>> heldAsset, std::vector<std::unique_ptr<Transaction>> transactionHistory) 
                        : heldAsset(std::move(heldAsset)), transactionHistory(std::move(transactionHistory)) {};

            Portfolio(const Portfolio&) = default;
            Portfolio& operator=(const Portfolio&) = default;
            Portfolio(Portfolio&&) = default;
            Portfolio& operator=(Portfolio&&) = default;

            ~Portfolio() = default;

            int getTotalAssets();
            int getTotalTransactions();
            int getTotalCurrencies();

            void makePurchase(std::string& tickerSymbol, double numShares, double price);
            void makeSelling(std::string& tickerSymbol, double numShares, double price);
            void receiveDividend(std::string& tickerSymbol, double dividendPerShare, double heldShares, double totalDividend);

            bool addAsset(std::string& tickerSymbol, std::string& assetClass, std::string& currency); 
            Asset* getAsset(std::string& tickerSymbol); 
            bool deleteAsset(std::string& tickerSymbol);
            bool isRegisteredAsset(std::string& tickerSymbol);

            void printPortfolio();
            void printTransaction(Operation::TransactionType type);
            void printAllTickers();
            void printConvertedPortfolio();

            friend void to_json(nlohmann::json& j, const Portfolio& p);
            friend void from_json(const nlohmann::json& j, Portfolio& p);
};

#endif