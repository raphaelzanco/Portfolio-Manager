#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "asset.hpp"

std::string Asset::getTickerSymbol() const
{ 
    return this->tickerSymbol; 
}

std::string Asset::getAssetClass() const
{
    return this->assetClass; 
}

std::string Asset::getCurrency() const
{ 
    return this->currency; 
}

double Asset::getHeldShares() const
{ 
    return this->heldShares; 
}

double Asset::getAveragePrice() const
{
    return this->averagePrice; 
}

double Asset::getDividendReceived() const
{
    return this->dividendReceived;
}

void Asset::setTickerSymbol(std::string newTickerSymbol)
{
    this->tickerSymbol = newTickerSymbol;
}

void Asset::setAssetClass(std::string newAssetClass)
{
    this->assetClass = newAssetClass;
}

void Asset::setCurrency(std::string newCurrency)
{
    this->currency = newCurrency;
}

bool Asset::purchaseShares(double numShares, double price)
{
    try
    {
        if (numShares <= 0 || price <= 0)
        {
            throw std::invalid_argument("Number of shares and price must be positive and non-zero.");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
    
    if (this->heldShares == 0)
    {
        this->heldShares = numShares;
        this->averagePrice = price;
    }
    else
    {
        double originalValue = (this->heldShares)*(this->averagePrice);
        double newCost = numShares * price; 

        this->heldShares += numShares;
        this->averagePrice = (originalValue+newCost)/(this->heldShares);
    }

    return true;
}

bool Asset::sellShares(double numShares, double price)
{
    try
    {
        if (numShares <= 0 || price <= 0)
        {
            throw std::invalid_argument("Number of shares and price must be positive and non-zero.");
        }
        else if (numShares > (this->heldShares))
        {
            throw std::invalid_argument("Cannot sell more shares than you hold.");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    this->heldShares -= numShares;
    this->averagePrice = (this->heldShares == 0) ? 0 : this->averagePrice;
   
    return true;
}

bool Asset::payDividend(double totalDividend, double heldShares)
{
     try
    {
        if (this->heldShares <= 0 || this->averagePrice <= 0 || heldShares > this->heldShares)
        {
            throw std::invalid_argument("Must have shares to receive dividends. Cannot receive dividends from more shares than you hold.");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    this->dividendReceived += totalDividend;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Asset& asset)
{
   const double totalValue = asset.getHeldShares() * asset.getAveragePrice();

   os << std::left << std::setw(8) << asset.getTickerSymbol() << "| ";
   os << std::setw(3) << asset.getHeldShares() << " units | Avg $";
   os << std::fixed << std::setprecision(2) << asset.getAveragePrice();
   os << " | Dividend Received $" << asset.getDividendReceived() << " | Total $" << totalValue;

   return os;
}