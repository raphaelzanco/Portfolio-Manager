#ifndef TRANSACTIONTYPE_HPP
#define TRANSACTIONTYPE_HPP

namespace Operation
{
    enum class TransactionType
    {
        Buy,
        Sell,
        Dividend,
        Movement //represents both Buy and Sell
    };

    inline std::ostream& operator<<(std::ostream& os, const TransactionType& type)
    {
        switch(type)
        {
            case TransactionType::Buy: 
                os << "Buy";
                break;
            
            case TransactionType::Dividend:
                os << "Dividend";
                break;
            
            case TransactionType::Sell:
                os << "Sell";
                break;
            
            default:
                os << "Undefined";
        }

        return os;
    }
}

#endif