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
    double buying;
    double selling;
    double balance;

public:
    StockTrade();
    StockTrade(string, int, int, double,double, double);

    // SETTERS
    void setName(string);
    void setId(int);
    void setAge(int);
    void setbuying(double);
    void setselling(double);
    void setBalance(double);
    

    // GETTERS
    string getName() const;
    int getId() const;
    int getAge() const;
    double getbuying() const;
    double getselling() const;
    double getBalance() const;


    // EXTRA
    void showInfo() const;

};
