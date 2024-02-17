#include "StockTrade.h"
#include <iostream>
#include <string>

using namespace std;
// Default Constructor

StockTrade::StockTrade()
{
    setName("Default");
    setId(0);
    setAge(0);
    setBalance(1000);
    setQuantity(100);
}

// Overloaded Constructor
StockTrade::StockTrade(string Name, int id, int age, double b, double q)
{
    setName(Name);
    setId(id);
    setAge(age);
    setBalance(b);
    setQuantity(q);
}

//SETTERS
void StockTrade::setName(string Names)
{
    Name = Names;
}
void StockTrade::setId(int ids)
{
    id = ids;
}
void StockTrade::setAge(int ages)
{
    age = ages;
}
void StockTrade::setBalance(double b)
{
    balance = b;
}
void StockTrade::setQuantity(double q)
{
    quantity = q;
}


//GETTERS
string StockTrade::getName() const
{
    return Name;
}
int StockTrade::getId() const
{
    return id;
}
int StockTrade::getAge() const
{
    return age;
}
double StockTrade::getBalance() const
{
    return balance;
}
double StockTrade::getQuantity() const
{
    return quantity;
}


//show info
void StockTrade::showInfo() const
{
    cout << "Purchaser Name: " << getName() << endl;
    cout << "Purchaser Id: " << getId() << endl;
    cout << "Purchaser Age: " << getAge() << endl;
    cout << "Balance Is: $" << getBalance() << endl;
    cout << "Number Of Stocks: " << getQuantity() << endl;
    cout << endl;
}
