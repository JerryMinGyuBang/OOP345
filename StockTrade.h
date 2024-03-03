#pragma once
#include <iostream>
#include <string>
#include "Account.h"
#include "User.h"
#include "TradeRecord.h"

class StockTrade
{
private:
    std::string Name;
    int id;
    std::string symbol;
    double price;

public:
    StockTrade();
    StockTrade(std::string, int, std::string, double);

    // SETTERS
    void setStockTrade(std::string);
    void setTradeID(int);
    void setStockSymbol(std::string);
    void setStockPrice(double);


    // GETTERS
    std::string getStockTrade() const;
    int getTradeID() const;
    std::string getStockSymbol() const;
    double getStockPrice() const;

    // EXTRA
    void showInfo() const;

};
