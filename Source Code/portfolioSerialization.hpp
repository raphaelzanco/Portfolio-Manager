#include "json.hpp"
#include "portfolio.hpp"
#include "transactionSerialization.hpp"
#include "assetSerialization.hpp"

#ifndef PORTFOLIOSERIALIZATION_HPP
#define PORTFOLIOSERIALIZATION_HPP

inline void to_json(nlohmann::json& j, const Portfolio& p) 
{
    j["heldAsset"] = p.heldAsset;
    j["transactionHistory"] = p.transactionHistory;
}

inline void from_json(const nlohmann::json& j, Portfolio& p)
{
    j.at("heldAsset").get_to(p.heldAsset);
    j.at("transactionHistory").get_to(p.transactionHistory);
}

#endif