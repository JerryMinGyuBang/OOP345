#include "User.h"
#include <iostream>
#include <string>

// Default Constructor
User::User()
{
    setName("Default");
    setId(0);
    setAge(0);
    setBalance(1000);
    setQuantity(100);
}

// Overloaded Constructor
User::User(std::string Name, int id, int age, double b, double q)
{
    setName(Name);
    setId(id);
    setAge(age);
    setBalance(b);
    setQuantity(q);
}

//SETTERS
void User::setName(std::string Names)
{
    Name = Names;
}
void User::setId(int ids)
{
    id = ids;
}
void User::setAge(int ages)
{
    age = ages;
}
void User::setBalance(double b)
{
    balance = b;
}
void User::setQuantity(double q)
{
    quantity = q;
}


//GETTERS
std::string User::getName() const
{
    return Name;
}
int User::getId() const
{
    return id;
}
int User::getAge() const
{
    return age;
}
double User::getBalance() const
{
    return balance;
}
double User::getQuantity() const
{
    return quantity;
}


//show info
void User::showInfo() const
{
    std::cout << "Purchaser Name: " << getName() << std::endl;
    std::cout << "Purchaser Id: " << getId() << std::endl;
    std::cout << "Purchaser Age: " << getAge() << std::endl;
    std::cout << "Balance Is: $" << getBalance() << std::endl;
    std::cout << "Number Of Stocks: " << getQuantity() << std::endl;
    std::cout << std::endl;
}
