#include "StockTrade.h"

//// Constructors and copy-control members
// default constructor
StockTrade::StockTrade() {

}

// parameterized constructor
StockTrade::StockTrade(string symbol, size_t num, TRADETYPE t_type) {

}

// destructor
StockTrade::~StockTrade() {

}


//// Public interfaces
// set current stock price to trade - called by `StockExchange`
bool StockTrade::setPrice(double) {

	return true; // [TODO]
}

// set unique trade Id of the current trade - called by `StockExchange`
bool StockTrade::setTradeId(string) {

	return true; // [TODO]
}

// set trade status
bool StockTrade::setStatus(ORDERSTATUS) {

	return true; // [TODO]
}