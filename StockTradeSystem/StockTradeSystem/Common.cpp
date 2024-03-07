/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-March-02
 * Previous Edit: 2024-March-05
 * -------------------------------------------------------------------------- */

#include "Common.h"


 //// Utilities supplement to the enumeration types
 // return string object based on `TRADETYPE` object
std::string getTradeTypeAsString(const TRADETYPE &tt)
{
	switch (tt) {
	case TRADETYPE::BUY:
		return "BUY";
	case TRADETYPE::SELL:
		return "SELL";
	}
	return "";
}

// return `TRADETYPE` object based on Integer
TRADETYPE getTradeTypeFromInt(const size_t ci)
{
	switch (ci) {
	case 1:
		return BUY;
	default: // i.e., case 2
		return SELL;
	}
}

// return string object based on `ORDERSTATUS` object
std::string getOrderStatusAsString(const ORDERSTATUS &os)
{
	switch (os) {
	case ORDERSTATUS::INCOMPLETE:
		return "INCOMPLETE";
	case ORDERSTATUS::PENDING:
		return "PENDING";
	case ORDERSTATUS::FINISHED:
		return "FINISHED";
	case ORDERSTATUS::CANCELLED:
		return "CANCELLED";
	}
	return "";
}

// return `ORDERSTATUS` object based on Integer
ORDERSTATUS getOrderStatusFromInt(const size_t ci)
{
	switch (ci) {
	case 1:
		return PENDING;
	case 2:
		return FINISHED;
	case 3:
		return CANCELLED;
	default: // i.e., case 0
		return INCOMPLETE;
	}
}


//// Other utilities
// obtain current time and returns a `std::time_t` object
time_t getCurrentTime() {
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::time_t curr_time = std::chrono::system_clock::to_time_t(now);
	return curr_time;
}

// get a random number from the standard normal distribution
double getStandardNormalRN() {
	double ret;
	// define the random number generator and the distribution
	std::default_random_engine generator;
	generator.seed((unsigned long long)(getCurrentTime()));
	std::normal_distribution<double> distribution(0.0, 1.0);
	// get a random value that is standard-normally distributed
	ret = distribution(generator);
	ret = (double)((int)(ret * 100)) / 100;	// keep only two decimal places
	return ret;
}

// a helper function to reset the screen - WINDOWS only
void resetScreen() {
	std::cout << std::endl;		// adjust spacing
	system("pause");	// wait for user to press any key
	system("cls");		// clear screen before back to menu
}