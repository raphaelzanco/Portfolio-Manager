#!/bin/bash

g++ main.cpp \
    menu.cpp \
    asset.cpp \
    transaction.cpp \
    dividendTransaction.cpp \
    movementTransaction.cpp \
    purchaseTransaction.cpp \
    sellingTransaction.cpp \
    portfolio.cpp \
    manageAssetCommand.cpp \
    addTransactionCommand.cpp \
    viewTransactionsCommand.cpp \
    viewPortfolioCommand.cpp \
    -o portfolioManager