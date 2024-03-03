// TradeRecord.h
#pragma once
#include <vector>
#include <string>
#include <tuple>

class TradeRecord {
private:
    using Trade = std::tuple<std::string, int, std::string, double, std::string, int>; 
    std::vector<Trade> trades;

public:
    void addTrade(const std::string& stockSymbol, int stockglobalid, const std::string& stockTradeName, double price, const std::string& status, int UserID);

    // Function to get the number of trades
    int getNumberOfTrades() const;

    // Function to get a specific trade
    Trade getTrade(int index) const;

    //function to display
    void displayTrades() const;
};
