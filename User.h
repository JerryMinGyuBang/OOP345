#pragma once
#include <iostream>
#include <string>

class User
{
private:
    std::string Name;
    int id;
    int age;
    double balance;
    double quantity;

public:
    User();
    User(std::string, int, int, double, double);

    // SETTERS
    void setName(std::string);
    void setId(int);
    void setAge(int);
    void setBalance(double);
    void setQuantity(double);


    // GETTERS
    std::string getName() const;
    int getId() const;
    int getAge() const;
    double getBalance() const;
    double getQuantity() const;


    // EXTRA
    void showInfo() const;

};
