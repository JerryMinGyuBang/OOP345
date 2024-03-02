/* ----------------------------------------------------------------------------
 * 
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-March-01
 * -------------------------------------------------------------------------- */

#pragma once
#ifndef STOCKEXCHANGE_H
#define STOCKEXCHANGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <ctime>
#include <map>
//#include <ctime>
using namespace std;

#include "Common.h"
#include "StockTrade.h"

struct StockTrade; // forward declaration of the `StockTrade` struct

// class `STOCKEXCHANGE_H`
class StockExchange {
//friend Admin;

public:
	//// Constructors and copy-control members
	// default constructor
	StockExchange();
	// destructor
	~StockExchange();


	//// Public interfaces
	// get current price of of a particular stock - arg: <string> symbol
	double getPrice(const string) const;
	// get the price history of a particular stock - arg: <string> symbol
	map<string, double> getStockHist(const string) const;
	// place StockTrade order
	bool placeOrder(shared_ptr<StockTrade> &);
	// convert system time to string in "YYYYMMDDhhmmss" format
	string convertTimeToString(std::time_t &);


//private: // [TODO]: uncomment the private keyword after testing
	//// Private utilities
	// update all stocks' prices in the market
	void updateMarket();
	// process an individual oreder, update the status of the order
	bool processOrder(shared_ptr<StockTrade> &);
	// display trade history - called by admin
	void displayTradeHistory() const;
	// load stock and the corresponding current price
	void loadStockPrice();
	// load stock history
	void loadStockHist();
	// load trade history
	void loadTradeHist();


	//// Data members
	// stocks and prices stock_list: {key: val} = {symbol: curr_price}
	map<string, double> stock_list;
	//
	/* price history of each individual stock
	 * stocks and their historical prices: {symbol: {string, trade_price}}
	 */
	map<string, map<string, double>> stock_hist;
	// count of total number of trade events
	size_t trade_counts;
	// history of all trade records: {trade_id, shared_ptr<StockTrade>}
	map<string, shared_ptr<StockTrade> > trade_hist;
	// time of previous price update
	time_t prev_update_t;
	// service charge
	double service_charge;

}; //  end of class `StockExchange`



#endif /* STOCKEXCHANGE_H */
