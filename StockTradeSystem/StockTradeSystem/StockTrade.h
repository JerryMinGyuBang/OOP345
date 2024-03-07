/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-Feb-29
 * -------------------------------------------------------------------------- */

#pragma once
#ifndef STOCKTRADE_H
#define STOCKTRADE_H

#include <iostream>
#include <string>
using namespace std;

#include "Common.h"
#include "StockExchange.h"
#include "Portfolio.h"

class Portfolio;
class StockExchange;

struct StockTrade {

	friend StockExchange;
	friend Portfolio;

public:
	//// Constructors and copy-control members
	// default constructor
	StockTrade();
	// parameterized constructor
	StockTrade(const string symbol, const size_t num, const TRADETYPE t_type);
	// parameterized constructor with full input
	StockTrade(const string t_id, const string sym, const size_t num, const double p, const TRADETYPE tt, const ORDERSTATUS os);
	// destructor
	~StockTrade();
	
	//// Data members
	// unique trade ID for each `StockTrade` object
	string trade_id;
	// stock symbol of the traded stock
	string stock_symbol;
	// quantity of the trade volume
	size_t quantity;
	// price of the current trade event
	double price;
	// trade type: BUY or SELL
	TRADETYPE trade_type;
	// trade transaction status: pending, finished, cancelled
	ORDERSTATUS status;

	//// Public interfaces
	// set current stock price to trade - called by `StockExchange`
	bool setPrice(const double);
	// set unique trade Id of the current trade - called by `StockExchange`
	bool setTradeId(const string);
	// get unique trade Id of the current trade - called by `Portfolio`
	string getTradeId() const;
	// set trade status
	bool setStatus(const ORDERSTATUS);
	// get trade status
	ORDERSTATUS getStatus() const;
	// display information of the current `StockTrade` object
	void displayData() const;

}; //  end of struct `StockTrade`


#endif /* STOCKTRADE_H */