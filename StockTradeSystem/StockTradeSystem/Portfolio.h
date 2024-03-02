/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-March-02
 * Previous Edit: 2024-March-02
 * -------------------------------------------------------------------------- */

#pragma once
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
using namespace std;

#include "Common.h"

// class `Portfolio`
class Portfolio {
public:
	//// Constructors and copy-control members
	// default constructor
	//Portfolio();
	// destructor
	//~Portfolio();

	//// Public interfaces


private:
	//// Data members
	// owned stocks by current portfolio
	map<string, size_t> owned_stocks;
	// trade records - a set of `trade_id` string
	set<string> trade_record;
	// portfolio profit or loss
	double earning;

}; // end of class `Portfolio`


#endif /* PORTFOLIO_H */
