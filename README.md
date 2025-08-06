# Portfolio Manager
A portable C++ application made to help you keep track of your finances.

## 📑Table of Content
- [About The Project](#about-the-project)
- [Features](#features)
- [UML - Use Cases Diagram](#uml---use-cases-diagram)
- [UML - Class Diagram](#uml---class-diagram)
- [Getting Started](#getting-started)
- [Walkthrough](#walkthrough)
- [Contact](#contact)

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

Follow the steps bellow to compile and run the program:

**1. Download the files**
   
Download all .hpp and .cpp the inside the "Source Code" folder as well as the shell script "compilePortfolioManager.sh".

The .hpp and .cpp files are the heart of this program ! It won't work without them. The shellscript will help you save time and compile all files into an exacutable one.

**Make sure to place them all in the same directory !**

**2. Go to your directory**

If you didn't open your directory path in your terminal, use the *"cd <directory>"* command to go inside the folder you stored this projects files.

**3. Make the shell script executable**

Run the line ahead to make your shell script executable: *"chmod +x compilePortfolioManager.sh"*.

**4. Compile the program**

Run the shell script with *"./compilePortfolioManager.sh"*. Afterwards, you're expected to receive an executable file called portfolioManager

**5. Run the application**

Once the script finishes, start the program with the command *"./portfolioManager"*.

Now, have a good time !

## 🗺️Walkthrough
**1. Load/Create Portfolio**

Whenever you run the portfolio Manager software you are prompted to either load a .json file (a portfolio) or start a new one.
- Load Existing Portfolio
  - To load an existing potfolio you must insert your .json file name (may not include the ".json" extension).
   If successfully loaded,you will be shown the total number of assets, transactions and unique currencies loaded
- Create a New Portfolio
  - You will be prompteed to name your new portfolio. After exiting the program, you will receive a file of the given name with the ".json" extension

**2. Manage Assets**
  - Add Asset
    - Insert ticker symbol, asset type (e.g stocks, REIT, ETF) and currency to add a new asset
  - Edit Asset
    - Edit asset tycker symbol, type or currency
  - Delete Asset
    - Delete an asset from a given ticker symbol from your portfolio
  - View Assets
    - Show all ticker symbols (assets) known to your portfolio

**3. Add Transactions**
- Purchase Transaction
  - Insert valid ticker symbol (known asset), number of traded shares, price per share, date and transaction currency to register/make a purchase
- Selling Transaction
  - Insert valid ticker symbol (known asset), number of traded shares (cannot be more than already owned), price per share, date and transaction currency to register/make a sale
- Dividend Transaction
  - Insert valid ticker symbol (known asset), dividend per share, number of shares (cannot receive dividend from more shares than owned), total dividend,
date and transaction currency to register/receive dividends

**4. View Transactions History**
- Purchase Transactions
  - Shows date, transaction type, ticker symbol, number of traded shares, unit price and currency
- Selling Transactions
  -Shows date, transaction type, ticker symbol, number of traded shares, unit price, profit/loss ratio and currency
- Movement Transactions
  - Will show both purchase and selling transactions history, together
- Dividend Transactions
  - Shows date, ticker symbol, dividend per share, number of shares part of the dividend distribution, total dividend and currency

 **4. View Portfolio**
 - View Current Holdings
   - Group your assets and show them by currency and asset class type
   - Shows your assets ticker symbol, holded units, average price, dividends received and total invested. Finally,exhibits total allocation for each class per currency
- Check Converted Portfolio (for multi-currency portfolios only)
  - When a portfolio has assets from more than one currency, you can use this functionality
  - First, you will be shown all currencies and total allocation for each
  - Afterwards, you may choose one of those currencies and pass all exchange rates to that one target coin to know your total allocation of all your portfolio/currencies on that one coin

 **5. Exit**
 
 Saves all modifications, updates or create your ".json" portfolio file

## ✉️Contact
Thank you for your interest in the Portfolio Manager project ! I developed it with the goal of creating something impactful for our day-to-day lives.

I welcome any and all feedback. If you encounter a bug, have a suggestion for a new feature, or just want to send a message, please feel free to reach out.

You can contact me at: raphaelzanco@gmail.com

Wish you all the best ! See you on my next project.
