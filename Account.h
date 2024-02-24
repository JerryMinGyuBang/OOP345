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
	double stockquantity = 0;
	double stockquantityfinal = 100;
	double stockprice = 50;
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
	virtual void setprice(double p)
	{
		stockprice = p;
	}
	virtual double getBalance()
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
		stockquantity =  sold / stockprice ;
		if (stockquantityfinal > stockquantity) {
			balance -= sold - Purchasefee;
			stockquantityfinal -= stockquantity;
		}		
		return stockquantity;
	}
	void setQuantity(double q)
	{
		stockquantityfinal = q;
	}
	void setprice(double p)
	{
		stockprice = p;
	}
	double getQuantity()
	{
		return stockquantityfinal;
	}
	double getfee()
	{
		return Purchasefee;
	}
	double getBalance()
	{
		return balance;
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
	void setQuantity(double q)
	{
		stockquantityfinal = q;
	}
	double getQuantity()
	{
		return stockquantityfinal;
	}
	void setprice(double p)
	{
		stockprice = p;
	}
	double buy(double c)
	{
		double buy = c;
		stockquantity = buy / stockprice;
		balance = balance - buy - Purchasefee;
		stockquantityfinal += stockquantity;
		return stockquantity;
	}
	double getfee()
	{
		return feecharge;
	}
	double getBalance()
	{
		return balance;
	}
	~Purchase()
	{
		cout << "Checking acccount destructor" << endl;
	}

};

