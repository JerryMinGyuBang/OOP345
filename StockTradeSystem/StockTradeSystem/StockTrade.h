#pragma once
#ifndef STOCKTRADE_H
#define STOCKTRADE_H

#include <iostream>
#include <string>
using namespace std;

#include "Common.h"
#include "StockExchange.h"

struct StockTrade {
	//friend StockExchange;

public:
	//// Constructors and copy-control members
	// default constructor
	StockTrade();
	// parameterized constructor
	StockTrade(string symbol, size_t num, TRADETYPE t_type);
	// destructor
	~StockTrade();
	
	//// Data members
	// unique trade ID for each `StockTrade` object
	string trade_id;
	string stock_symbol;
	size_t quantity;
	double price;
	TRADETYPE trade_type;
	ORDERSTATUS status;

	//// Public interfaces
	// set current stock price to trade - called by `StockExchange`
	bool setPrice(double);
	// set unique trade Id of the current trade - called by `StockExchange`
	bool setTradeId(string);
	// set trade status
	bool setStatus(ORDERSTATUS);

}; //  end of struct `StockTrade`


#endif /* STOCKTRADE_H */