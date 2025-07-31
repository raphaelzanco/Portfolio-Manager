#include <iostream>
#include "movementTransaction.hpp"

double MovementTransaction::getPricePerShare() const
{
    return this->pricePerShare;
}

double MovementTransaction::getTradedShares() const
{
    return this->tradedShares;
}