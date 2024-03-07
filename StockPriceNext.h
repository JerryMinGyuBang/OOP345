#include <vector>
#include <cstdlib> 
#include "StockTrade.h" 

class StockPriceNext {
public:
    // modify all stocks from -20 to 20 percent
    static double modifyStockPrice(std::vector<StockTrade>& vect, int h)
    {
        double percentageChange = 0.0;
        if (h > 0 && h <= vect.size()) {
            double currentPrice = vect[h - 1].getStockPrice();
            // generates a random number between -20 and 20
            double randomPercentage = (std::rand() % 41 - 20) / 100.0; 
            double newPrice = currentPrice + currentPrice * randomPercentage;
            vect[h - 1].setStockPrice(newPrice);
            // convert to percentage
            percentageChange = randomPercentage * 100; 
        }
        return percentageChange;
    }
    // buy increases price by 0 - 5 percent
    static double modifyStockPriceBuy(std::vector<StockTrade>& vect, int h)
    {
        double percentageChange = 0.0;
        if (h > 0 && h <= vect.size()) {
            double currentPrice = vect[h - 1].getStockPrice();
            // generates a random number between 0 and 5
            double randomPercentage = (std::rand() % 6) / 100.0;
            double newPrice = currentPrice + currentPrice * randomPercentage;
            vect[h - 1].setStockPrice(newPrice);
            // convert to percentage
            percentageChange = randomPercentage * 100;
        }
        return percentageChange;
    }
    // sell decrease price by 0 - 5 percent
    static double modifyStockPriceSell(std::vector<StockTrade>& vect, int h)
    {
        double percentageChange = 0.0;
        if (h > 0 && h <= vect.size()) {
            double currentPrice = vect[h - 1].getStockPrice();
            // generates a random number between 0 and 5
            double randomPercentage = (std::rand() % 6) / 100.0;
            // decrease the price
            double newPrice = currentPrice - currentPrice * randomPercentage; 
            vect[h - 1].setStockPrice(newPrice);
            // convert to percentage
            percentageChange = randomPercentage * 100;
        }
        return percentageChange;
    }
};
