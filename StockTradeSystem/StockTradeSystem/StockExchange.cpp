/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-Feb-29
 * Previous Edit: 2024-March-06
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
double StockExchange::getPrice(const string symbol) {
	// first update the market before attempting to check a specific stock price
	this->updateMarket();
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

// get multiple stock prices at once
map<string, double> StockExchange::getMultiPrices(set<string> query_symbols) {
	// first update the market before querying information
	this->updateMarket();
	// define return variable
	map<string, double> ret;
	// traverse the `stock_list` to search for each stock information
	for (const string &ele : query_symbols) {
		try {
			auto it = stock_list.find(ele);
			if (it != stock_list.end()) {
				ret.insert(*it);
			}
			else {
				throw std::runtime_error("Symbol not found.");
			}
		}
		catch (const std::exception &e) {
			cerr << "Failed to get price for symbol <" << ele << ">: "
				<< e.what()
				<< endl;
		}
	}
	return ret;
}

// display stock market price information
void StockExchange::displayMarket() {
	// first update market to refresh market information
	this->updateMarket();
	// display market stock prices information
	std::cout << "\nStock-Price at (YYYYMMDDhhmmss): "
		<< this->convertTimeToString(this->prev_update_t) 
		<< endl << endl;
	// using a lambda function to display the market information
	std::for_each(stock_list.cbegin(), stock_list.cend(),
		[](const std::pair<std::string, double>& p_) {
			std::cout << p_.first << ": $" << p_.second << std::endl; });
}

// get stock trade record based on a specific `trade_id`
shared_ptr<StockTrade> &StockExchange::getSingleStockTrade(const string t_id) {
	return (this->trade_hist).find(t_id)->second;
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
bool StockExchange::placeOrder(shared_ptr<StockTrade> &st_ptr)
{
	if (this->processOrder(st_ptr)) // if order is successfully processed 
	{
		// if success, write changes to file
		this->writeExchangeToFile();
		std::cout << "Trade order processed successfully." << endl;
		return true;
	}
	else // trade order was not processed
	{
		std::cout << "Order process declined." << endl;
		return false;
	}
}

// convert system time to string in "YYYYMMDDhhmmss" format
/* Reference:
 * https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
**/
string StockExchange::convertTimeToString(const std::time_t &t) {
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
/*
 * [NOTE]: the logic flow of this function is subject to changes to
 * incoporate different update mechanisms.
 **/
void StockExchange::updateMarket() {
	time_t cur_t = getCurrentTime();	// obtain current time
	std::string cur_t_str = this->convertTimeToString(cur_t); // time_t to string
	// market data is updated only if the previous update is before UPDATE_DURATION
	if (cur_t - this->prev_update_t > UPDATE_DURATION) {
		this->prev_update_t = cur_t; // set prev_update_t to current time
		// update each stock independently
		for (auto it = stock_list.begin(); it != stock_list.end(); ++it) {
			// update the stock price
			if (UPDATE_RULE == 1) // 1 - standard normal
			{
				it->second += getStandardNormalRN(); // uses a  random standard normal val
			}
			// else if (...) {} // add other update rule
			else 
			{ 
				it->second += 0.0; // default: 0 - no change
			}
			// append the newest price into the `stock_hist` container
			(this->stock_hist)[it->first][cur_t_str] = it->second;
		}
		// write the updated prices to file - individual price changed
		this->writePriceToFile();
		// write the stock history to file - stock's history changed
		this->writeStockToFile();
		// write exchange data to file - `prev_update_t` changed
		this->writeExchangeToFile();
	}

	return ;
}

// process an individual oreder, update the status of the order
bool StockExchange::processOrder(shared_ptr<StockTrade> &st_ptr)
{
	// action based on status of the `StockTrade` object
	if (st_ptr->status == ORDERSTATUS::PENDING) 
	{
		// set order status to FINISHED
		st_ptr->setStatus(ORDERSTATUS::FINISHED);
		// insert current `StockTrade` pointer to `trade_hist`
		(this->trade_hist).insert(std::pair<string, shared_ptr<StockTrade> >(st_ptr->trade_id, st_ptr));
		// update `trade_counts`
		this->trade_counts = (this->trade_hist).size();
	}
	else if (st_ptr->status == ORDERSTATUS::CANCELLED)
	{
		std::cout << "Discarding CANCELLED trade order..." << endl;
		return false;
	}
	else 
	{
		std::cout << "Invalid trade order status for processing." << std::endl;
		return false;
	}
	return true;
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
			trade_hist[t_id] = std::make_shared<StockTrade>(
				t_id,
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

// write stock price information to file - truncate mode
void StockExchange::writePriceToFile() const {
	// define variables for file handling
	ofstream ofs;	// output file stream

	try {
		// open the stock file in output and truncation modes
		ofs.open(STOCK_FILE, ofstream::out | ofstream::trunc);
		// each row stores the stock symbol and price, space separated
		for (const auto &ele : stock_list) {
			ofs << std::fixed << std::setprecision(2)		// keep two decimal places
				<< ele.first << " " << ele.second << endl; // newline at the row's end
		}
		// close file when finishes writting
		ofs.close();
	}
	catch (const std::exception &e) {
		cerr << "An error occurs when writting to <"
			<< STOCK_FILE << ">: "
			<< e.what()
			<< endl;
	}
	return ;
}

// write current stock price into stock history file - truncate mode
void StockExchange::writeStockToFile() const {
	// define variables for file handling
	ofstream ofs;	// output file stream
	string file_prefix = "stock_";	// prefix of individual stock file
	string stock_sym;				// symbol of current stock

	for (auto cit = stock_hist.cbegin(); cit != stock_hist.cend(); ++cit) 
	{
		stock_sym = cit->first;	// the first element is the stock symbol
		try {
			// open the file "stock_<symbol>.txt" in output and truncation mode
			ofs.open(file_prefix + stock_sym + ".txt", ofstream::out | ofstream::trunc);
			// each row stores the time and price of an update for current stock
			for (auto c_sit = (cit->second).cbegin(); c_sit != (cit->second).cend(); ++c_sit) {
				ofs << c_sit->first << " " 
					<< std::fixed << std::setprecision(2)	// keep two decimal places
					<< c_sit->second << endl;				// newline at the end
			}
			ofs.close(); // close file when finishes writing
		}
		catch (const std::exception &e) {
			cerr << "An error occurs when writting to <"
				<< file_prefix + stock_sym + ".txt" << ">: "
				<< e.what()
				<< endl;
		}
	}
	return ;
}

// write exchange data to file
void StockExchange::writeExchangeToFile() const {
	// define variables for file handling
	ofstream ofs;	// output file stream

	try {
		// open the exchange file in output and truncation modes
		ofs.open(EXCHANGE_FILE, ofstream::out | ofstream::trunc); 
		// first line stores the `prev_update_t` member
		ofs << this->prev_update_t << std::endl; // newline at the end
		// second row and onwards are StockTrade records
		for (auto cit = trade_hist.cbegin(); cit != trade_hist.cend(); ++cit)
		{
			// traverse the `trade_hist` member to retrieve the data
			ofs << cit->first << " "; // first element is the `trade_id`
			ofs << cit->second->stock_symbol << " ";	// `stock_symbol`
			ofs << cit->second->trade_type << " ";		// `trade_type`
			ofs << cit->second->quantity << " ";		// `quantity`
			ofs << cit->second->price << " ";			// `price`
			ofs << cit->second->status					// last element of a row: `status`
				<< endl;								// newline at the end
		}
		ofs.close(); // close file when finishes writing

	}
	catch (const std::exception &e) {
		cerr << "An error occurs when writting to <"
			<< EXCHANGE_FILE << ">: "
			<< e.what()
			<< endl;
	}
	return ;
}
