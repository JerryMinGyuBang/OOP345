#pragma once
// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include "StockTrade.h"
using namespace std;

class Account {
	// Account class implementation
public:
	double balance = 0;
	double Purchasefee = 0;
	double sold = 0;
	double 	feecharge = 0;
	double buys = 0;
public:
	Account()
	{
		balance = 0;
		Purchasefee = 100;
		sold = 0;
		feecharge = 100;
		buys = 0;
	}
	Account(double x) : balance{ x }
	{
		if (balance >= 0) {
			balance = 0;
			Purchasefee = 100;
			sold = 0;
			feecharge = 10;
			buys = 0;
		}
		else {
			cout << "Error Message, Balance less than 0" << endl;
		}
	}
	virtual double SoldFee(double m)
	{
		sold = m;
		balance = sold - Purchasefee;
		return balance;
	}
	virtual double buy(double c)
	{
		buys = c;
		balance = buys - feecharge;
		return balance;
	}
	virtual double getfee()
	{
		return Purchasefee;
	}
	double getBalance()
	{
		return balance;
	}
	~Account()
	{
		cout << "base destructor" << endl;
	}
};

class Sell : public Account {

public:
	Sell()
	{
		Purchasefee = 100;
		sold = 0;
	}
	//sold plus fee
	double SoldFee(double m)
	{
		sold = m;
		balance = sold + Purchasefee;
		return balance;
	}
	double getfee()
	{
		return Purchasefee;
	}
	~Sell()
	{
		cout << "saving acccount destructor" << endl;
	}
};

class Purchase : public Account {
public:
	
public:
	Purchase()
	{
		feecharge = 100;
		buys = 0;

	}
	double buy(double c)
	{
		buys = c;
		balance = buys - feecharge;
		return balance;
	}
	double getfee()
	{
		return feecharge;
	}
	~Purchase()
	{
		cout << "Checking acccount destructor" << endl;
	}

};

