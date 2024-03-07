/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-27
 * Previous Edit: 2024-March-06
 * -------------------------------------------------------------------------- */

#pragma once
#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <ctime>

//// Define file MACROS
// admin file
#define ADMIN_FILE		"admin.txt"
// member file
#define MEMBER_FILE		"member.txt"
// stock file
#define STOCK_FILE		"stock.txt"
// stock exchange system file
#define EXCHANGE_FILE	"exchange.txt"


//// Define common parameters
// minimum stock price
#define MINIMUM_PRICE	0.01
// exchange service charge
#define SERVICE_CHARGE	2
// duration in seconds for every stock price update
#define UPDATE_DURATION 1
// update mechanism - 0: no change; 1 - standard normal
#define UPDATE_RULE		1


//// Define enumerations
// TradeType - unscoped enumeration type
enum TRADETYPE
{
	BUY = 1,
	SELL = 2,
};

// OrderStatus - unscoped enumeration type
enum ORDERSTATUS
{
	INCOMPLETE = 0,
	PENDING = 1,
	FINISHED = 2,
	CANCELLED = 3,
};


//// Utilities supplement to the enumeration types
// return string object based on `TRADETYPE` object
std::string getTradeTypeAsString(const TRADETYPE &tt);
// return `TRADETYPE` object based on Integer
TRADETYPE getTradeTypeFromInt(const size_t ci);
// return string object based on `ORDERSTATUS` object
std::string getOrderStatusAsString(const ORDERSTATUS &os);
// return `ORDERSTATUS` object based on Integer
ORDERSTATUS getOrderStatusFromInt(const size_t ci);


//// Other utilities
// obtain current time and returns a `std::time_t` object
time_t getCurrentTime();
// get a random number from the standard normal distribution
double getStandardNormalRN();
// a helper function to reset the screen - WINDOWS only
void resetScreen();


#endif /* COMMON_H */
