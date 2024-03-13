#pragma once
#include<iostream>
#include "StockTrade.h"
#include <string>

class Account {
public:
	double balance = 0;
	double Purchasefee = 0;
	double sold = 0;
	double feecharge = 0;
	double buys = 0;
	double stockquantity = 0;
	double stockquantityfinal = 100;
	double stockprice = 50;
	double totalProfit = 0;
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
			std::cout << "Error Message, Balance less than 0" << std::endl;
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
		
	}
};


class Sell : public Account {
public:
	Sell()
	{
		Purchasefee = 100;
		sold = 0;
	}
	double SoldFee(double m)
	{
		sold = m;
		stockquantity = sold / stockprice;
		if (stockquantityfinal > stockquantity) {
			balance = -balance - sold - Purchasefee;
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
	std::string getType()
	{
		return "sell";
	}
	void setBalance(double b)
	{
		balance = b;
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
	double sell(double c)
	{
		double buy = c;
		stockquantity = buy / stockprice;
		balance = buy - Purchasefee;
		stockquantityfinal += stockquantity;
		totalProfit += balance;  
		return totalProfit;
	}
	~Sell()
	{
		
	}
};

class Purchase : public Account {
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
	void setBalance(double b)
	{
		balance = b;
	}
	double getQuantity()
	{
		return stockquantityfinal;
	}
	std::string getType()
	{
		return "buy";
	}
	void setprice(double p)
	{
		stockprice = p;
	}
	double buy(double c)
	{
		double buy = c;
		stockquantity = buy / stockprice;
		balance = buy - Purchasefee;
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
	double buy1(double c)
	{
		double buy = c;
		stockquantity = buy / stockprice;
		balance = buy - Purchasefee;
		stockquantityfinal += stockquantity;
		totalProfit -= balance;  
		return totalProfit;
	}
	~Purchase()
	{
		
	}
};
