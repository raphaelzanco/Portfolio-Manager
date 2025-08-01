# Portfolio Manager
A portable C++ application made to help you keep track of your finances.

## 📑Table of Content
- [About The Project](#about-the-project)
- [Features](#features)
- [UML - Use Cases Diagram](#uml---use-cases-diagram)
- [UML - Class Diagram](#uml---class-diagram)
- [Getting Started](#getting-started)

## 💡About The Project
Nowadays, investors have access to a large pool of financial products, being able to expose themselves to a large variety of markets (Stocks, Bonds, REITs, ETFs, and so on).
However, even though a diverse portfolio can minimize some risks, it also makes it all the more complex to keep track of.

While a smart investment strategy is key, accurately tracking your transactions, asset distribution, and performance history is crucial for managing risk and planning your next steps.

Tired of cumbersome and error-prone spreadsheets? **Portfolio Manager** was built to simplify asset and multi-portfolio administration, giving you a clear view of your investments without the headache.

## 💼Features
- Manage Multiple Portfolios
  - Create and Load ".json" files
  - Save all changes
    
- Support Multiple Currencies
  - Add assets/transactions from any currency
  - View Converted Portfolio (Currency of Choice)
    
- Manage Assets
  - Add assets from any type or currency 
  - Edit existing assets
  - Delete unwanted assets
  - View assets known to your portfolio
    
- Make Transactions
  - Purchase Transactions
  - Selling Transactions
  - Dividend Transactions
    
- Check Transactions History
  - Purchase, Selling and Dividend Transactions
  - Movement Transactions(Both Purchase and Selling Transactions History)
    
- View Holdings
  - Check all held assets (must have at least one share)
  - Show report sorted by currency and asset class
  - Know exactly how much you have in each currency, investiment class and asset
  - View total units held, average price and dividend received
 
## 🎨UML - Use Cases Diagram
![Use Cases Diagram from UML (also inside one of this repository folder!)](https://github.com/raphaelzanco/Portfolio-Manager/blob/b1a77278778d640eaec2c037a38a2f1a6b9b4224/UML%20Diagrams/Portfolio%20Management%20Use%20Cases.jpg)

## 🖼️UML - Class Diagram
![Class Diagram from UML (also inside one of this repository folder!)](https://github.com/raphaelzanco/Portfolio-Manager/blob/3ecdbb42265f12828dbd09fe8522cab3e39090fd/UML%20Diagrams/Portfolio%20Management%20Classes.jpg)

## 🚀Getting Started
**📌Warning: This program was built and test in a Linux Environment. 
Unexpected behaviours may occur if runned in a Windows System**

First and foremost, download all files inside the "Source Code" folder. Those .hpp and .cpp are files are the classes which compose this application, acting as the heart of the program.

Afterwards, download the shell script "compilePortfolioManager.sh": that will save you a lot of time as it automatically will compile all .cpp files and create an executable called "portfolioManager".
