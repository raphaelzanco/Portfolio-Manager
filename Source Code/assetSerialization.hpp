#include "asset.hpp"
#include "json.hpp"

#ifndef ASSET_SERIALIZATION_HPP
#define ASSET_SERIALIZATION_HPP

inline void to_json(nlohmann::json& j, const Asset& a)
{
        j = nlohmann::json{
        {"tickerSymbol", a.getTickerSymbol()},
        {"assetClass", a.getAssetClass()},
        {"currency", a.getCurrency()},
        {"heldShares", a.getHeldShares()},
        {"averagePrice", a.getAveragePrice()},
        {"dividendReceived", a.getDividendReceived()}
    };
}

inline void from_json(const nlohmann::json& j, Asset& a)
{
    j.at("tickerSymbol").get_to(a.tickerSymbol);
    j.at("assetClass").get_to(a.assetClass);
    j.at("currency").get_to(a.currency);
    j.at("heldShares").get_to(a.heldShares);
    j.at("averagePrice").get_to(a.averagePrice);
    j.at("dividendReceived").get_to(a.dividendReceived);
}

// --- Smart Pointer Serialization for Asset ---

inline void to_json(nlohmann::json& j, const std::unique_ptr<Asset>& a) 
{
    if (a) 
    {
        to_json(j, *a);
    } 
    else 
    {
        j = nullptr;
    }
}

inline void from_json(const nlohmann::json& j, std::unique_ptr<Asset>& a) 
{
    if (j.is_null()) 
    {
        a = nullptr;
    } 
    else 
    {
        a = std::make_unique<Asset>(j.get<Asset>());
    }
}
#endif