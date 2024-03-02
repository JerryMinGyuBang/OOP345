/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-29
 * Previous Edit: 2024-March-02
 * -------------------------------------------------------------------------- */

#include "StockExchange.h"


//// Constructors and copy-control members
// default constructor
StockExchange::StockExchange() 
	: service_charge(SERVICE_CHARGE), prev_update_t(0)
{
	//cout << "StockExchange::StockExchange()" << endl;
	// call loadStockPrice() to load the stocks and prices into `stock_list` member
	this->loadStockPrice();
	// call loadStockHist() to load the history of price for each stock
	this->loadStockHist();
	// call loadTradeHist() to load the history of trade events
	this->loadTradeHist();
	// obtain the total number of trades as the size of `trade_hist` constainer
	this->trade_counts = (this->trade_hist).size();
}

// destructor
StockExchange::~StockExchange() {
	//cout << "StockExchange::~StockExchange()" << endl; // [TODO]: remove this line
}


//// Public interfaces
// get current price of of a particular stock - arg: <string> symbol
double StockExchange::getPrice(const string symbol) const {
	try 
	{
		if (stock_list.find(symbol) != stock_list.cend()) {
			return (stock_list.find(symbol))->second;
		}
		else {
			throw std::runtime_error("Symbol not found.");
		}
	}
	catch (const std::exception& e)
	{
		cerr << "Failed to get price for symbol <" << symbol << ">: "
			<< e.what()
			<< endl;
		return 0.0;
	}
}


// get the price history of a particular stock - arg: <string> symbol
map<string, double> StockExchange::getStockHist(const string symbol) const {
	// define an empty container for return
	map<string, double> ret; // returning a copy can avoid modifying system's record
	try {
		// iterator indicates symbol position in map
		auto it = stock_hist.find(symbol); 
		// check if the stock symbol exists
		if (it != stock_hist.end()) // stock history found
		{
			ret = it->second;
		}
		else 
		{
			throw std::runtime_error("No stock history relates to the symbol.");
		}
	}
	catch (const std::exception &e) {
		cerr << "Symbol <" << symbol << "> not found: "
			 << e.what()
			 << endl;
	}
	return ret;
}

// place StockTrade order
bool StockExchange::placeOrder(shared_ptr<StockTrade> &) {
	return true; // [TODO]
}

// convert system time to string in "YYYYMMDDhhmmss" format
/* Reference:
 * https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
**/
string StockExchange::convertTimeToString(std::time_t &t) {
	char timedisplay[100];
	struct tm buf;
	errno_t err = localtime_s(&buf, &t);
	if (std::strftime(timedisplay, sizeof(timedisplay), "%Y%m%d%H%M%S", &buf)) {
		// std::cout << timedisplay << '\n'; // [DEBUG]
	}
	return timedisplay;
}


//// Private utilities
// update all stocks' prices in the market
void StockExchange::updateMarket() {

	return ; // [TODO]
}

// process an individual oreder, update the status of the order
bool StockExchange::processOrder(shared_ptr<StockTrade> &) {
	
	return true; // [TODO]
}

// display trade history - called by admin
void StockExchange::displayTradeHistory() const {
	// traverse the `trade_hist` member to print all the records
	for (map<string, shared_ptr<StockTrade> >::const_iterator cit = trade_hist.cbegin();
		cit != trade_hist.cend(); ++cit) {
		cout << cit->second->trade_id << ": "
			<< cit->second->stock_symbol << " "
			<< getTradeTypeAsString(cit->second->trade_type) << " "
			<< cit->second->quantity << " "
			<< "$" << cit->second->price << " "
			<< getOrderStatusAsString(cit->second->status)
			<< endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	return ;
}

// load stock and the corresponding current price
void StockExchange::loadStockPrice() {
	// define variables to store information from files
	istringstream iss;	// input string stream
	ifstream ifs;		// input file stream
	string symbol;		// stock symbol
	double price;		// stock price

	// load data from file
	ifs.open(STOCK_FILE, fstream::in);
	if (ifs.is_open()) {
		iss.clear();	// clear the string stream before assignment
		// traverse the file to load the data
		for (string line; std::getline(ifs, line); iss.clear()) {
			iss.str(line);	// load the current line into string stream
			iss >> symbol;	// obtain stock symbol from current line
			iss >> price;	// obtain current price of the stock
			(this->stock_list).insert(std::pair<string, double>(symbol, price));
		}
		ifs.close();
	}
	else {
		cerr << "Failed to open file: " << STOCK_FILE << endl;
		return ;
	}
	return ;
}

// load stock history
void StockExchange::loadStockHist() {
	// define variables to store information from files
	istringstream iss;	// input string stream
	ifstream ifs;		// input file stream
	string time;		// time of price
	double price;		// stock price

	string file_prefix = "stock_"; // prefix of stock files

	// open and read file based on stock symbols
	for (map<string, double>::const_iterator cit = stock_list.cbegin();
		cit != stock_list.cend();
		++cit) // loop through the `stock_list` using iterator
	{
		try {
			// open file "stock_<symbol>.txt"
			ifs.open(file_prefix + (cit->first) + ".txt", fstream::in);
			if (ifs.is_open()) {
				iss.clear(); // clear the string stream before assignment
				// traverse the file to load the data
				for (string line; std::getline(ifs, line); iss.clear()) {
					iss.str(line);	// load the current line into string stream
					iss >> time;
					iss >> price;
					((this->stock_hist)[cit->first]).insert(std::pair<string, double>(time, price));
				}
				ifs.close();
			}
			else {
				ifs.close();
				throw std::runtime_error("File not found.");
			}
		}
		catch (const std::exception& e)
		{
			cerr << "Failed to open file <" << file_prefix + (cit->first) + ".txt" << ">: "
				<< e.what()
				<< endl;

			// if a stock file was not successfully opened, 
			// create a new file for later operations, output and truncate modes
			ofstream ofs(file_prefix + (cit->first) + ".txt", ofstream::out | ofstream::trunc);
			// hard conversion to the nearest update time
			std::time_t cur_t = (size_t(getCurrentTime() / UPDATE_DURATION) - 1) * UPDATE_DURATION;
			// write to file
			ofs << convertTimeToString(cur_t) << " " << cit->second << endl;
			// close file
			ofs.close();
			// notify file creation
			cout << "Created file <" << (file_prefix + (cit->first) + ".txt") << "> "
				 << "and wrote current price to file"
				 << endl;
		}
	}
	return ;
}

// load trade history
void StockExchange::loadTradeHist() {
	// define variables to store information from files
	istringstream iss;	// input string stream
	ifstream ifs;		// input file stream
	
	string t_id, sym;				// trade_id, stock symbol
	double price;					// stock price
	size_t trade_type, order_status, quantity;
	
	// load data from file
	ifs.open(EXCHANGE_FILE, fstream::in);
	if (ifs.is_open()) {
		string line;			// create a variable to store current line of input
		iss.clear();			// clear the string stream before assignment
		std::getline(ifs,line); // get the first line
		iss.str(line);
		iss >> prev_update_t;	// first line is the `prev_update_t` member
		
		// traverse the remaining file to load the data
		for (iss.clear(); std::getline(ifs, line); iss.clear()) {
			iss.str(line);	// load the current line into string stream
			// obtain data in the order of: id, sym, trade_type, quantity, price, status
			iss >> t_id >> sym >> trade_type >> quantity >> price >> order_status;			
			// construct shared_ptr and stores into container
			trade_hist[t_id] = std::make_shared<StockTrade>(t_id,
															sym,
															quantity,
															price,
															getTradeTypeFromInt(trade_type),
															getOrderStatusFromInt(order_status)
															);
		}
		ifs.close();
	}
	else {
		cerr << "Failed to open file: " << EXCHANGE_FILE << endl;
		return;
	}
	return;

}


