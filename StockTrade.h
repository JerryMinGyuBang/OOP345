#pragma once
#include <iostream>
#include <string>

using namespace std;

class StockTrade
{
private:
    string Name;
    int id;
    int age;
    double balance;
    double quantity;

public:
    StockTrade();
    StockTrade(string, int, int, double, double);

    // SETTERS
    void setName(string);
    void setId(int);
    void setAge(int);
    void setBalance(double);
    void setQuantity(double);
    

    // GETTERS
    string getName() const;
    int getId() const;
    int getAge() const;
    double getBalance() const;
    double getQuantity() const;


    // EXTRA
    void showInfo() const;

};
