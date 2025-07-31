#include <memory>
#include <stdexcept>
#include "json.hpp"

#include "transaction.hpp"
#include "movementTransaction.hpp"
#include "purchaseTransaction.hpp"
#include "sellingTransaction.hpp"
#include "dividendTransaction.hpp"

#ifndef TRANSACTIONSERIALIZATION_HPP
#define TRANSACTIONSERIALIZATION_HPP

// Forward-declaring all functions 
void from_json(const nlohmann::json& j, Transaction& t);
void from_json(const nlohmann::json& j, MovementTransaction& m);
void from_json(const nlohmann::json& j, PurchaseTransaction& p);
void from_json(const nlohmann::json& j, SellingTransaction& s);
void from_json(const nlohmann::json& j, DividendTransaction& d);

// --- SERIALIZATION FUNCTIONS ---

//Transaction
inline void to_json(nlohmann::json& j, const Transaction& t) 
{
    j = nlohmann::json{
        {"tickerSymbol", t.getTickerSymbol()},
        {"date", t.getDate()},
        {"currency", t.getCurrency()}
    };
}

inline void from_json(const nlohmann::json& j, Transaction& t) 
{
    j.at("tickerSymbol").get_to(t.tickerSymbol);
    j.at("date").get_to(t.date);
    j.at("currency").get_to(t.currency);
}

//MovementTransaction
inline void to_json(nlohmann::json& j, const MovementTransaction& m) 
{
    to_json(j, static_cast<const Transaction&>(m));
    j["pricePerShare"] = m.getPricePerShare();
    j["tradedShares"] = m.getTradedShares();
}

inline void from_json(const nlohmann::json& j, MovementTransaction& m) 
{
    from_json(j, static_cast<Transaction&>(m));
    j.at("pricePerShare").get_to(m.pricePerShare);
    j.at("tradedShares").get_to(m.tradedShares);
}

//PurchaseTransaction 
inline void to_json(nlohmann::json& j, const PurchaseTransaction& p) 
{
    to_json(j, static_cast<const MovementTransaction&>(p));
    j["type"] = p.getTransactionType();
}

inline void from_json(const nlohmann::json& j, PurchaseTransaction& p) 
{
    from_json(j, static_cast<MovementTransaction&>(p));
}

//SellingTransaction
inline void to_json(nlohmann::json& j, const SellingTransaction& s) 
{
    to_json(j, static_cast<const MovementTransaction&>(s));
    j["type"] = s.getTransactionType();
    j["profitMargin"] = s.getProfitMargin();
}

inline void from_json(const nlohmann::json& j, SellingTransaction& s) 
{
    from_json(j, static_cast<MovementTransaction&>(s));
    j.at("profitMargin").get_to(s.profitMargin);
}

//DividendTransaction
inline void to_json(nlohmann::json& j, const DividendTransaction& d) 
{
    to_json(j, static_cast<const Transaction&>(d));
    j["type"] = d.getTransactionType();
    j["dividendPerShare"] = d.getDividendPerShare();
    j["heldShares"] = d.getHeldShares();
    j["totalDividends"] = d.getTotalDividend();
}

inline void from_json(const nlohmann::json& j, DividendTransaction& d) 
{
    from_json(j, static_cast<Transaction&>(d));
    j.at("dividendPerShare").get_to(d.dividendPerShare);
    j.at("heldShares").get_to(d.heldShares);
    j.at("totalDividends").get_to(d.totalDividend);
}


// --- POLYMORPHIC DESERIALIZATION ---

NLOHMANN_JSON_SERIALIZE_ENUM( Operation::TransactionType, {
    {Operation::TransactionType::Buy, "buy"},
    {Operation::TransactionType::Sell, "sell"},
    {Operation::TransactionType::Dividend, "dividend"},
})

inline void to_json(nlohmann::json& j, const std::unique_ptr<Transaction>& t)
{
    // If the pointer is null, serialize it as null
    if (!t) 
    {
        j = nullptr;
        return;
    }

    // Using dynamic_cast to find the actual type to call the correct serializer
    if (const auto p = dynamic_cast<const PurchaseTransaction*>(t.get())) 
    {
        j = *p;
    } 
    else if (const auto s = dynamic_cast<const SellingTransaction*>(t.get())) 
    {
        j = *s;
    } 
    else if (const auto d = dynamic_cast<const DividendTransaction*>(t.get())) 
    {
        j = *d;
    } 
}


inline void from_json(const nlohmann::json& j, std::unique_ptr<Transaction>& t) 
{
    auto type = j.at("type").get<Operation::TransactionType>();
    switch (type) {
        case Operation::TransactionType::Buy:
            t = std::make_unique<PurchaseTransaction>(j.get<PurchaseTransaction>());
            break;
        case Operation::TransactionType::Sell:
            t = std::make_unique<SellingTransaction>(j.get<SellingTransaction>());
            break;
        case Operation::TransactionType::Dividend:
            t = std::make_unique<DividendTransaction>(j.get<DividendTransaction>());
            break;
        default:
            throw std::runtime_error("Cannot deserialize: Unknown transaction type.");
    }
}

#endif 