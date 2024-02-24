#pragma once
#include <iostream>
#include <string>

using namespace std;

class StockTrade
{
private:
    string Name;
    int id;
    string symbol;
    double price;

public:
    StockTrade();
    StockTrade(string, int, string, double);

    // SETTERS
    void setStockTrade(string);
    void setTradeID(int);
    void setStockSymbol(string);
    void setStockPrice(double);
    

    // GETTERS
    string getStockTrade() const;
    int getTradeID() const;
    string getStockSymbol() const;
    double getStockPrice() const;

    // EXTRA
    void showInfo() const;

};
