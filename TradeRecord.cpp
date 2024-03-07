// TradeRecord.cpp
#include <stdexcept>
#include <iostream>
//including classes
#include "StockTrade.h"
#include "Account.h"
#include "User.h"
#include "TradeRecord.h"

void TradeRecord::addTrade(const std::string& stockSymbol, int stockglobalid, const std::string& stockTradeName, double price, const std::string& status, int UserID)
{
    trades.push_back(std::make_tuple(stockSymbol, stockglobalid, stockTradeName, price, status, UserID));
}

int TradeRecord::getNumberOfTrades() const
{
    return trades.size();
}

TradeRecord::Trade TradeRecord::getTrade(int index) const
{
    if (index >= 0 && index < trades.size()) {
        return trades[index];
    }
    throw std::out_of_range("Index out of range");
}

void TradeRecord::displayTrades() const
{
    std::cout << "Trade Records:" << std::endl;
    for (int i = 0; i < trades.size(); ++i) {
        std::cout << "Trade " << i + 1 << std::endl;
        std::cout << "Stock Symbol: " << std::get<0>(trades[i]) << std::endl;
        std::cout << "Stock Global ID: " << std::get<1>(trades[i]) << std::endl;
        std::cout << "Stock Trade Name: " << std::get<2>(trades[i]) << std::endl;
        std::cout << "Price: " << std::get<3>(trades[i]) << std::endl;
        std::cout << "Status: " << std::get<4>(trades[i]) << std::endl;
        std::cout << "UserID: " << std::get<5>(trades[i]) << std::endl;
        std::cout << "-----------------" << std::endl;
    }
}
