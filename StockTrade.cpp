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
    setbuying(100);
    setselling(100);
}

// Overloaded Constructor
StockTrade::StockTrade(string Name, int id, int age, double nl, double hl)
{
    setName(Name);
    setId(id);
    setAge(age);
    setbuying(nl);
    setselling(hl);
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
void StockTrade::setbuying(double hs)
{
    buying = hs;
}
void StockTrade::setselling(double nl)
{
    selling = nl;
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
double StockTrade::getbuying() const
{
    return buying;
}
double StockTrade::getselling() const
{
    return selling;
}

//show info
void StockTrade::showInfo() const
{
    cout << "Purchaser Name: " << getName() << endl;
    cout << "Purchaser Id: " << getId() << endl;
    cout << "Purchaser Age: " << getAge() << endl;
    cout << "Purchaser buying power: " << getbuying() << endl;
    cout << "Purchaser selling power: " << getselling() << endl;
    cout << endl;
}
