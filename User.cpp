#include "User.h"
#include <iostream>
#include <string>
using namespace std;
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
User::User(string Name, int id, int age, double b, double q)
{
    setName(Name);
    setId(id);
    setAge(age);
    setBalance(b);
    setQuantity(q);
}

//SETTERS
void User::setName(string Names)
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
string User::getName() const
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
    cout << "Purchaser Name: " << getName() << endl;
    cout << "Purchaser Id: " << getId() << endl;
    cout << "Purchaser Age: " << getAge() << endl;
    cout << "Balance Is: $" << getBalance() << endl;
    cout << "Number Of Stocks: " << getQuantity() << endl;
    cout << endl;
}
