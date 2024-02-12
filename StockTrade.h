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

public:
    StockTrade();
    StockTrade(string, int, int, double,double);

    // SETTERS
    void setName(string);
    void setId(int);
    void setAge(int);
    void setbuying(double);
    void setselling(double);
    

    // GETTERS
    string getName() const;
    int getId() const;
    int getAge() const;
    double getbuying() const;
    double getselling() const;


    // EXTRA
    void showInfo() const;

};
