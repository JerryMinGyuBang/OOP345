#include "StockTrade.h"
#include <iostream>
#include <string>

using namespace std;
// Default Constructor

StockTrade::StockTrade()
{
    setStockTrade("Default");
    setTradeID(0);
    setStockSymbol("Default");
    setStockPrice(100);
}

// Overloaded Constructor
StockTrade::StockTrade(string Name, int id, string symbol, double price)
{
    setStockTrade(Name);
    setTradeID(id);
    setStockSymbol(symbol);
    setStockPrice(price);
}

//SETTERS
void StockTrade::setStockTrade(string Names)
{
    Name = Names;
}
void StockTrade::setTradeID(int ids)
{
    id = ids;
}
void StockTrade::setStockSymbol(string symbols)
{
    symbol = symbols;
}
void StockTrade::setStockPrice(double prices)
{
    price = prices;
}

//GETTERS
string StockTrade::getStockTrade() const
{
    return Name;
}
int StockTrade::getTradeID() const
{
    return id;
}
string StockTrade::getStockSymbol() const
{
    return symbol;
}
double StockTrade::getStockPrice() const
{
    return price;
}

//show info
void StockTrade::showInfo() const
{
    cout << "Stock Trade is: " << getStockTrade() << endl;
    cout << "Trade ID: " << getTradeID() << endl;
    cout << "StockSymbol: " << getStockSymbol() << endl;
    cout << "StockSymbol Price is: " << getStockPrice() << endl;
    cout << endl;
}
