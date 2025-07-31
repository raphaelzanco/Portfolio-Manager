#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <iomanip>

#include "portfolio.hpp"
#include "asset.hpp"
#include "transactionType.hpp"
#include "transaction.hpp"
#include "purchaseTransaction.hpp"
#include "sellingTransaction.hpp"
#include "dividendTransaction.hpp"

bool Portfolio::checkValidDate(std::string& date)
{
    std::stringstream ss(date);
    int year, month, day;

    //variables to consume hyphens
    char h1, h2; 

    ss >> year >> h1 >> month >> h2 >> day;
    if (ss.fail() || h1 != '-' || h2 != '-' || !(ss.eof()))
    {
        return false;
    }

    if (month <= 0 || month > 12 || day <= 0 || day > 31)
    {
        return false;
    }

    return true;
}

bool Portfolio::isRegisteredAsset(std::string& tickerSymbol)
{
    auto it = this->heldAsset.find(tickerSymbol);
    if (it != this->heldAsset.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Portfolio::registerPurchaseTransaction(std::string& tickerSymbol, double numShares, double price)
{
    std::string date, currency;

    std::cout << "Insert Purchase Date (YYYY-MM-DD): ";

    while(std::getline(std::cin, date))
    {
        if (checkValidDate(date))
        {
            break;
        }

        std::cout << std::endl << "Invalid date. Use the format YYY-MM-DD" << std::endl;
        std::cout << "Insert Purchase Date (YYYY-MM-DD): ";
    }

    std::cout << "Insert Transaction Currency (e.g USD, BRL): ";
    std::getline(std::cin, currency);
    std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);


    std::unique_ptr<Transaction> purchaseTransaction = std::make_unique<PurchaseTransaction>(price, numShares, tickerSymbol, date, currency);

    this->transactionHistory.push_back(std::move(purchaseTransaction));
}

void Portfolio::registerSellingTransaction(std::string& tickerSymbol, double numShares, double price, double tickerAveragePrice)
{
    std::string date, currency;
    double profitMargin = (price - tickerAveragePrice)*100;

    std::cout << "Insert Purchase Date (YYYY-MM-DD): ";

    while(std::getline(std::cin, date))
    {
        if (checkValidDate(date))
        {
            break;
        }

        std::cout << std::endl << "Invalid date. Use the format YYY-MM-DD" << std::endl;
        std::cout << "Insert Purchase Date (YYYY-MM-DD): ";
    }

    std::cout << std::endl << "Insert Transaction Currency (e.g USD, BRL): ";
    std::getline(std::cin, currency);
    std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);

    std::unique_ptr<Transaction> sellingTransaction = std::make_unique<SellingTransaction>(profitMargin, price, numShares, tickerSymbol, date, currency);

    this->transactionHistory.push_back(std::move(sellingTransaction));
}

void Portfolio::registerDividendTransaction(std::string& tickerSymbol, double dividendPerShare, double heldShares, double totalDividend)
{
    std::string date, currency;

    std::cout << "Insert Purchase Date (YYYY-MM-DD): ";

    while(std::getline(std::cin, date))
    {
        if (checkValidDate(date))
        {
            break;
        }

        std::cout << std::endl << "Invalid date. Use the format YYY-MM-DD" << std::endl;
        std::cout << "Insert Purchase Date (YYYY-MM-DD): ";
    }

    std::cout << std::endl << "Insert Transaction Currency (e.g USD, BRL): ";
    std::getline(std::cin, currency);
    std::transform(currency.begin(), currency.end(), currency.begin(), ::toupper);

    std::unique_ptr<Transaction> purchaseTransaction = std::make_unique<DividendTransaction>(dividendPerShare, heldShares, totalDividend, tickerSymbol, date, currency);

    this->transactionHistory.push_back(std::move(purchaseTransaction));
}

int Portfolio::getTotalAssets()
{
    return this->heldAsset.size();
}

int Portfolio::getTotalTransactions()
{
    return this->transactionHistory.size();
}

int Portfolio::getTotalCurrencies()
{
    std::set<std::string> currencies;

    for (auto const& [tickerSymbol, asset]: this->heldAsset)
    {
        currencies.insert(asset->getAssetClass());
    }

    return currencies.size();
}

void Portfolio::makePurchase(std::string& tickerSymbol, double numShares, double price)
{
    if (isRegisteredAsset(tickerSymbol))
    {
        if (this->heldAsset[tickerSymbol]->purchaseShares(numShares, price))
        {
            registerPurchaseTransaction(tickerSymbol, numShares, price);
            std::cout << std::endl << "Successfully purchased " << numShares << " shares of " << tickerSymbol;
        }
        return;
    }

    std::cout << "Your portifolio doesn't know an Asset named " << tickerSymbol;
    return;
}

void Portfolio::makeSelling(std::string& tickerSymbol, double numShares, double price) 
{
    if (isRegisteredAsset(tickerSymbol))
    {
        if (this->heldAsset[tickerSymbol]->sellShares(numShares, price))
        {
            registerSellingTransaction(tickerSymbol, numShares, price, this->heldAsset[tickerSymbol]->getAveragePrice());
            std::cout << "Successfully sold " << numShares << " shares of " << tickerSymbol << " for $" << price << " each." << std::endl;
        }
        return;
    }

    std::cout << "Your portifolio doesn't know an Asset named " << tickerSymbol;
    return;
}

void Portfolio::receiveDividend(std::string& tickerSymbol, double dividendPerShare, double heldShares, double totalDividend)
{
    if (isRegisteredAsset(tickerSymbol))
    {
        if (this->heldAsset[tickerSymbol]->payDividend(totalDividend, heldShares))
         {
            registerDividendTransaction(tickerSymbol, dividendPerShare, heldShares, totalDividend);
            std::cout << "Successfully received $" << totalDividend << " from " << tickerSymbol << " for $" << dividendPerShare << " each share." << std::endl;
        }
        return;
    }
    std::cout << "Your portifolio doesn't know an Asset named " << tickerSymbol;
    return;
}

bool Portfolio::addAsset(std::string& tickerSymbol, std::string& assetClass, std::string& currency)
{
    //inserted will be false if an asset with the same "tickerSymbol" already exists inside the map
    auto const& [iterator, inserted] = this->heldAsset.emplace(tickerSymbol,std::make_unique<Asset>(tickerSymbol, assetClass, currency));

    if (inserted == false)
    {
        std::cout << "The portfolio already has an asset called " << tickerSymbol << std::endl;
        return false;
    }

    return true;
}

Asset* Portfolio::getAsset(std::string& tickerSymbol)
{
    auto it = this->heldAsset.find(tickerSymbol);

    if (it != this->heldAsset.end())
    {
        return it->second.get();
    }

    return nullptr;
}

bool Portfolio::deleteAsset(std::string& tickerSymbol)
{
    if (this->heldAsset.erase(tickerSymbol) > 0)
    {
        std::cout << "Successfully deleted 1 asset called " << tickerSymbol << std::endl;
        return true; 
    }

    std::cout << "Your portfolio doesn't have an asset called " << tickerSymbol << std::endl;
    return false;

}

void Portfolio::printPortfolio() 
{
    double totalAllocation = 0;
    std::map<std::string, std::map<std::string, std::vector<const Asset*>>> groupedAssets;

    for (auto const& [tickerSymbol, asset]: this->heldAsset) 
    {
        if (asset->getAveragePrice() > 0 && asset->getHeldShares() > 0)
        {
            groupedAssets[asset->getCurrency()][asset->getAssetClass()].push_back(asset.get());
        }
    }

    if (groupedAssets.empty() == true)
    {
        std::cout << "Your portfolio doesn't have any Assets with holded shares." << std::endl;
        return;
    }

    for (const auto& [currency, assetsMap] : groupedAssets)
    {
        std::cout << std::endl <<"[Currency: " << currency << "]" << std::endl;
        
        for (const auto& [assetClassType, assetList] : assetsMap)
        {
            std::cout << std::endl << "→ " << assetClassType << "s" << std::endl;

            for (const Asset* asset : assetList)
            {
                totalAllocation += (asset->getAveragePrice())*(asset->getHeldShares());
                std::cout << *asset << std::endl << std::endl;
            }
            std::cout << std::endl << "Total Allocation: " << totalAllocation << std::endl <<std::endl;
            totalAllocation = 0;
        }
    }
}

void Portfolio::printTransaction(Operation::TransactionType type)
{
    int counter = 0;

    if (type != Operation::TransactionType::Buy && type != Operation::TransactionType::Sell 
        && type != Operation::TransactionType::Dividend && type != Operation::TransactionType::Movement)
    {
        std::cout << "Error trying to display Transaction" << std::endl;
        return;
    }
    else
    {
        for (int i = this->transactionHistory.size() - 1; i >= 0; i--)
        {
            auto& transaction = this->transactionHistory[i];

            if (transaction->getTransactionType() == type)
            {
                if (counter == 0 && type != Operation::TransactionType::Dividend)
                {
                    std::cout << "   Date    |" <<  "  Type   |" << "  Ticker   |" << "  Quantity  |" << " Unit Price  |" << " Profit/Loss |" << " Currency ";
                    std::cout << std::endl << std::endl;
                    counter++;
                }
                else if (counter == 0 && type == Operation::TransactionType::Dividend)
                {
                    std::cout << "   Date    |" <<  "  Ticker   |" << "  Dividend Per Share  |" << "  Quantity  |" << " Total Dividends  |" << " Currency ";
                    std::cout << std::endl << std::endl;
                    counter++;
                }

                std::cout << *transaction << std::endl;
            }
            else if (type == Operation::TransactionType::Movement 
                && transaction->getTransactionType() != Operation::TransactionType::Dividend)
            {
                if (counter == 0)
                {
                    std::cout << "   Date    |" <<  "  Type   |" << "  Ticker   |" << "  Quantity  |" << " Unit Price  |" << " Profit/Loss |" << " Currency ";
                    std::cout << std::endl << std::endl;
                    counter++;
                }

                std::cout << *transaction << std::endl;
            }
        }

        if (counter == 0)
        {
            std::cout << "Your portfolio doesn't have any transaction of this type." << std::endl;
        }
        
    }
}

void Portfolio::printAllTickers()
{
    if (this->heldAsset.empty() == true)
    {
        std::cout << "Your portfolio doesn't know any asset yet." << std::endl;
    }
    else
    {
        for (auto const& [tickerSymbol, asset]: this->heldAsset)
        {
            std::cout << tickerSymbol << std::endl;
        }
    }
}

void Portfolio::printConvertedPortfolio()
{
    std::map<std::string, std::vector<Asset*>> groupedAssets;

    for (auto const& [tickerSymbol, asset]: this->heldAsset) 
    {
        if (asset->getAveragePrice() > 0 && asset->getHeldShares() > 0)
        {
            groupedAssets[asset->getCurrency()].push_back(asset.get());
        }
    }

    if (groupedAssets.empty() == true)
    {
        std::cout << "Your portfolio doesn't have any Assets with holded shares." << std::endl;
        return;
    }
    
    double total;
    std::vector<double> totalCurrency;

    std::cout << "__Current Currencies__" << std::endl;
    for (const auto& [currency, asset] : groupedAssets)
    {
        total = 0;
        for (int i = 0; i < asset.size(); i++)
        {
            total += (asset[i]->getAveragePrice() * asset[i]->getHeldShares());
        }
        std::cout << currency << ": $" << total << std::endl;
        totalCurrency.push_back(total);
    }

    if (totalCurrency.size() == 1)
    {
        std::cout << std::endl << "Your portfolio doesn't have more currencies to convert." << std::endl;
        return;
    }
    else
    {
        std::string mainCurrency;
        while (true)
        {
            std::cout << std::endl << "Enter Target Currency: ";
            std::cin >> mainCurrency;
            std::transform(mainCurrency.begin(), mainCurrency.end(), mainCurrency.begin(), ::toupper);

            auto it = groupedAssets.find(mainCurrency);
            if (it != groupedAssets.end())
            {
                std::cout << std::endl << "__Enter Exchange Rates__" << std::endl;
                break;
            }
            else
            {
                std::cout << std::endl << "Error: please, insert valid currency." << std::endl;
                continue;
            }
        }

        int count = 0;
        total = 0;
        for (const auto& [currency, asset] : groupedAssets)
        {
            double currencyRate = 0;
            if (currency != mainCurrency)
            {
                std::cout << currency << " → " << mainCurrency << ": ";
                std::cin >> currencyRate;
                total += totalCurrency[count] * currencyRate;
            }
            else
            {
                total += totalCurrency[count];
            }
            count++;
        }

        std::cout << std::endl << "Your portfolio is worth $" << total << " " << mainCurrency << "." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
}