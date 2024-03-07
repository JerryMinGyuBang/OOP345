#include <map>
#include <vector>

// Stock Class
class Stock {
public:
    int id;
    int quantity;

    // Default constructor
    Stock()
    {
        id = 0;
        quantity = 0;
    }

    // Overloaded Constructor
    Stock(int id, int quantity)
    {
        this->id = id;
        this->quantity = quantity;
    }
};

// Trader class
class Trader { 
public:
    int id;
    std::map<int, Stock> stocks; 

    Trader(int id) : id(id) {} 

    void addStock(int stockId, int quantity)
    {
        stocks[stockId] = Stock(stockId, quantity);
    }
};


