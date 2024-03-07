/* ----------------------------------------------------------------------------
 *
 * Author: M. Tang
 * Maintainer: M. Tang
 * Creation Date: 2024-March-02
 * Previous Edit: 2024-March-06
 * -------------------------------------------------------------------------- */

#include "Portfolio.h"


 //// Constructors and copy-control members
 // default constructor
Portfolio::Portfolio() {

}

// parameterized constructor 
Portfolio::Portfolio(const string user_name, std::shared_ptr<StockExchange> &ex)
	: u_name(user_name), available_fund(0.0), total_withdrawal(0.0), total_invest(0.0), earning(0.0), exchange_ptr(ex)
{
	// load data members from file based on user_name
	this->loadPortfolio(user_name);
	
	//cout << "Portfolio::Portfolio()" << endl; // [TODO]: remove this line
}

// copy constructor
Portfolio::Portfolio(const Portfolio &rhs) {
	*this = rhs;
	/* equivalently
	this->available_fund	= rhs.available_fund;
	this->total_withdrawal = rhs.total_withdrawal;
	this->total_invest		= rhs.total_invest;
	this->trade_record		= rhs.trade_record;
	this->owned_stocks		= rhs.owned_stocks;
	this->earning			= rhs.earning;
	this->exchange_ptr		= rhs.exchange_ptr;
	*/
}

// copy-assignment operator
Portfolio &Portfolio::operator=(const Portfolio &rhs) {
	// check for self-assignment
	if (!(this == &rhs))
	{
		this->available_fund = rhs.available_fund;
		this->total_withdrawal = rhs.total_withdrawal;
		this->total_invest = rhs.total_invest;
		this->trade_record = rhs.trade_record;
		this->owned_stocks = rhs.owned_stocks;
		this->earning = rhs.earning;
		this->exchange_ptr = rhs.exchange_ptr;
	}
	return *this;
}

// destructor
Portfolio::~Portfolio() {
	//cout << "~Portfolio::Portfolio()" << endl; // [TODO]: remove this line
}

//// Public interfaces
// create an `StockTrade` object and call `StockExchange::placeOrder` interface
bool Portfolio::createOrder(const string symbol, const size_t quan, const TRADETYPE tt) {
	// define variables to construct the `StockTrade` object
	string t_id_ = "T-";	// trade Id
	double p_;				// price
	time_t t_cur_;			// current time
	bool ret = true;		// return value, default: true

	try {
		t_cur_ = getCurrentTime();					// obtain current time
		p_ = this->exchange_ptr->getPrice(symbol);	// obtain current stock price
		if (p_ < MINIMUM_PRICE) {
			cout << "Invalid stock symbol to trade." << endl;
			throw std::runtime_error("Invalid stock symbol to trade.");
		}
		t_id_ = t_id_ + this->exchange_ptr->convertTimeToString(t_cur_) + "-" + symbol;

		// create a smart pointer to a `StockTrade` object
		std::shared_ptr<StockTrade> st_ptr = std::make_shared<StockTrade>(symbol, quan, tt);
		if ( !(st_ptr->setPrice(p_)) ) // set price for the trade
		{
			cout << "Failed to set a valid trade price." << endl;
			throw std::runtime_error("Failed to set a valid trade price.");
		}
		if (!(st_ptr->setTradeId(t_id_))) // set trade Id for the trade
		{
			cout << "Failed to set a valid trade ID." << endl;
			throw std::runtime_error("Failed to set a valid trade ID.");
		}

		// perform action based on TRADETYPE
		if (tt == TRADETYPE::BUY) {
			// check if there is sufficient fund to continue the trading
			if (this->available_fund < quan * p_ + SERVICE_CHARGE) {
				// no sufficient fund - set status to CANCELLED
				cout << "Error: no sufficient fund to complete the trade order." << endl;
				st_ptr->setStatus(ORDERSTATUS::CANCELLED);
				ret = false;
			}
			else { // valid action
				// set status to PENDING
				st_ptr->setStatus(ORDERSTATUS::PENDING);
				/// update the portfolio's data
				// update `available_fund`
				this->available_fund = this->available_fund - quan * p_ - SERVICE_CHARGE;
				// update `trade_record`
				(this->trade_record).insert(t_id_);
				// update `owned_stocks`
				if (owned_stocks.find(symbol) == owned_stocks.end()) {
					// current portfolio does not have the purchased stock
					owned_stocks[symbol] = quan;
				}
				else {
					(owned_stocks.find(symbol))->second += quan;
				}
			}
		}
		else if (tt == TRADETYPE::SELL) {
			// define variable for data handling
			auto s_it = owned_stocks.find(symbol);

			// first check if the stock is owned
			if (s_it == owned_stocks.end()) {
				// does not own the stock to sell
				cout << "Error: attempting to sell a not owned stock." << endl;
				st_ptr->setStatus(ORDERSTATUS::CANCELLED);
				ret = false;
			}
			// then check whether there is sufficient shares to sell
			if (s_it->second < quan) {
				// no sufficient quantity to sell
				cout << "Error: attempting to sell more than the owned shares." << endl;
				st_ptr->setStatus(ORDERSTATUS::CANCELLED);
				ret = false;
			}
			// finally check whether there is sufficient fund to process the order
			if (this->available_fund + quan * p_ < SERVICE_CHARGE) {
				// no sufficient fund to process the order
				cout << "Error: no sufficient fund to complete the trade order." << endl;
				st_ptr->setStatus(ORDERSTATUS::CANCELLED);
				ret = false;
			}
			
			// set status to PENDING
			if (st_ptr->getStatus() == ORDERSTATUS::INCOMPLETE)
			{
				st_ptr->setStatus(ORDERSTATUS::PENDING);
				/// update the portfolio's data
				// update `available_fund`
				this->available_fund = this->available_fund + quan * p_ - SERVICE_CHARGE;
				// update `trade_record`
				(this->trade_record).insert(t_id_);
				// update `owned_stocks`
				s_it->second -= quan;
				if (s_it->second == 0) // remove element when owned quantity goes to zero
				{
					(this->owned_stocks).erase(symbol);
				}
			}
		}
		else {
			throw std::runtime_error("Invalid TRADETYPE.");
		}

		// call `StockExchange::placeOrder` interface
		ret = exchange_ptr->placeOrder(st_ptr);

		// check if trade order processed successfully
		if (ret) {
			// write updated portfolio data to file
			this->writePortfolioToFile();
		}
	}
	catch (...) {
		cerr << "Error(s) encountered when creating and/or placing a StockTrade order."
			<< " Order declined."
			<< endl;
		ret = false;
	}

	return ret; 
}

// show portfolio positions
void Portfolio::showPositions() {
	// call `getUpdatedPositions` to interface with `StockExchange` for updated prices
	map<string, double> price_map = this->getUpdatedPositions();
	// obtain current account earning - note: `this->earning` also updated
	double earn = this->getEarning(price_map);
	// calculate the net worth of the stocks (not consider `available_fund`)
	double s_w = 0.0;
	for (const auto &ele : price_map) {
		s_w += ele.second * (this->owned_stocks[ele.first]);
	}
	// print portfolio informaiton
	cout << "User: <" << this->u_name << ">";
	cout << "\nCurrent portfolio holds the following stocks: " << endl << endl;
	this->displayStockInfo(price_map); // call `Portfolio::displayStockInfo` to display stocks
	cout << "\nStock net worth: $" << s_w << endl;
	this->displayFundInfo(); // call `Portfolio::displayFundInfo` to display fund data
	cout << "Net profit/loss of portfolio over the account history: $" << earn << endl;
	
	return ;
}

// show trade records for a single stock based on stock symbol
void Portfolio::showTradeRecord(const string symbol) const {
	// traverse `trade_record` to find `trade_id` that relate to the symbol
	for (const string &st : trade_record) {
		// recall that each trade Id ends with the stock symbol
		size_t pos = st.find_last_of('-');
		if (st.substr(pos+1) == symbol) // display StockTrade data if symbol matched
		{
			// using the `displayData` interface of `StockTrade` class to display info
			this->exchange_ptr->getSingleStockTrade(st)->displayData();
		}
	}
}

// show all trading record for the current portfolio
void Portfolio::showAllTradeRecords() const {
	// traverse the `trade_record` member and display the information
	for (const auto &ele : trade_record) {
		// using the `displayData` interface of `StockTrade` class to display info
		this->exchange_ptr->getSingleStockTrade(ele)->displayData();
	}
}

// get earning (i.e., profit/loss) of the portfolio
double Portfolio::getEarning() {
	//get updated earning for current portfolio
	auto price_map = this->getUpdatedPositions();
	// call the overloaded version to get the earning
	return this->getEarning(price_map);
}

// overloaded - get earning of the portfolio - also updates `earning`
double Portfolio::getEarning(const map<string, double> &price_map) {
	// calculate the earning based on current market prices of stocks
	double temp = 0.0;
	for (auto cit = price_map.cbegin(); cit != price_map.cend(); ++cit)
	{
		// stock worthing = unit price * quantity
		temp += (cit->second) * (owned_stocks[cit->first]);
	}
	temp += this->available_fund;	// all the liquidity
	temp += this->total_withdrawal;	// all positive worth over history
	temp -= this->total_invest;		// subtract total cost
	this->earning = temp;			// assign the calculated value to `earning`
	// return the updated earning
	return this->earning;
}

// get available fund for stock trading
double Portfolio::getAvailableFund() const {
	return this->available_fund;
}

// display fund information: available fund and total invested amount
void Portfolio::displayFundInfo() const {
	std::cout << std::fixed << std::setprecision(2)		// keep two decimal places
		<< "Available cash in portfolio: $" << this->available_fund << std::endl
		<< "Total withdrawan amount since account creation: $" << this->total_withdrawal << std::endl
		<< "Total invested amount since account creation: $" << this->total_invest
		<< std::endl;

	return ;
}

// display stock infromation: stock symbol, quantity, price, subtotal
void Portfolio::displayStockInfo() {
	// call `this->getUpdatedPosistions()` to obtain the current price map
	auto price_map = this->getUpdatedPositions();
	// call the parameterized `Portfolio::displayStockInfo(price_map)` to display info
	this->displayStockInfo(price_map);
	
	return ;
}

// write current portfolio information to file
void Portfolio::writePortfolioToFile() const {
	// define variables for file handling
	ofstream ofs;	// output file stream
	string file_prefix = "member_"; // prefix of member portfolio file

	try {
		// open the file "member_<user_name>.txt" in output and truncation mode
		ofs.open(file_prefix + this->u_name + ".txt", ofstream::out | ofstream::trunc);
		// first line of the file stores available_fund and total_invest
		ofs << std::fixed << std::setprecision(2)		// keep two decimal places
			<< available_fund << " "					// first: available_fund
			<< total_withdrawal <<  " "					// second: total_withdrawal
			<< total_invest								// third: total_invest
			<< std::endl;								// newline at the end
		// second line stores the `trade_id` strings stored in `trade_record`
		for (auto cit = trade_record.cbegin(); cit != trade_record.cend(); ofs << " ")
		{
			ofs << *(cit++);
		}
		ofs << std::endl; // newline at the end
		// third line and onwards store the owned stocks' symbols and quantities
		for (auto cit = owned_stocks.cbegin(); cit != owned_stocks.cend(); ++cit) {
			ofs << cit->first << " " << cit->second << endl;
		}
		// close file when finishes writting
		ofs.close();
	}
	catch (const std::exception &e) {
		cerr << "An error occurs when writting to <" 
			<< file_prefix + this->u_name + ".txt" << ">: "
			<< e.what()
			<< endl;
	}
	return ;
}


//// Private utilities
// load portfolio information from file
void Portfolio::loadPortfolio(const string &user_name) {
	// define variables to store information from files
	istringstream iss;	// input string stream
	ifstream ifs;		// input file stream
	string symbol;		// stock symbol
	size_t num;			// shares of stock owned
	string trade_id;	// trade Id for trade events
	
	string file_prefix = "member_"; // prefix of member portfolio file

	// loading data from file
	try 
	{
		// open file "member_<user_name>.txt"
		ifs.open(file_prefix + user_name + ".txt", fstream::in);
		if (ifs.is_open()) // file read successfully
		{
			string line;	// variable to store the current line data in file
			
			// first line stores the available fund, total withdrawal and invested amt
			iss.clear();	// clear the string stream before assignment
			std::getline(ifs, line); // get entire line
			iss.str(line); // load current line to string stream
			iss >> (this->available_fund) >> (this->total_withdrawal) >> (this->total_invest);
			
			// second line stores the all trade ID history related to the portfolio
			iss.clear();	// clear the string stream before assignment
			std::getline(ifs, line); // get entire line
			iss.str(line); // load current line to string stream
			while (iss >> trade_id) {
				(this->trade_record).insert(trade_id);
			}

			// third line onwards are key-value pairs: {stock_symbol: owned_quantity}
			for (iss.clear(); std::getline(ifs, line); iss.clear()) {
				iss.str(line);			// load current line to string stream
				iss >> symbol >> num;	// assign value to variables
				(this->owned_stocks).insert(std::pair<string, size_t>(symbol, num));
			}
			ifs.close();
		}
		else {
			ifs.close();
			throw std::runtime_error("File not found.");
		}
	}
	catch (const std::exception &e) {
		cerr << "Failed to open file <" << file_prefix + user_name + ".txt" << ">: "
			 << e.what()
			 << endl;
	}

	return ;
}

// get updated porfolio positions - interacts with `StockExchange` object
map<string, double> Portfolio::getUpdatedPositions() {
	// interface with `StockExchange` and return the symbol-price `map`
	set<string> query;	// define a `set` to store the owned stocks' symbols
	std::for_each(owned_stocks.cbegin(), owned_stocks.cend(),
		[&query](const std::pair<std::string, size_t>& p_) { query.insert(p_.first); });

	// call `StockExchange::getMultiPrices` interface to obtain prices of owned stocks
	map<string, double> price_map = this->exchange_ptr->getMultiPrices(query);
	return price_map;
}

// display stock infromation: stock symbol, quantity, price, subtotal
void Portfolio::displayStockInfo(const map<string, double> &price_map) {
	// define a lambda function to format the output
	auto print_content = [](std::string content, std::string prefix = "")
	{
		std::cout << std::left << std::setw(13)
			<< std::setfill(' ')
			<< (prefix + content);
	};

	// compute the average stock purchase price
	this->computeAvgPrices();

	// print stock informaiton
	print_content("\tStock"); print_content(" Quantity");
	print_content(" Price"); print_content(" Subtotal");
	print_content(" AvgBuyPrice"); print_content(" NetEarning");
	std::cout << "\n\t" << std::string(12 * 6 + 5 * 1, '-') << "\n";
	for (const auto &ele : price_map) {
		cout << "\t";
		print_content(ele.first);
		print_content(std::to_string(this->owned_stocks[ele.first]));
		std::string s = std::to_string(ele.second);
		print_content(s.substr(0, s.find(".") + 3), "$");
		print_content(std::to_string(ele.second*owned_stocks[ele.first]).substr(0, s.find(".") + 3), "$");
		print_content(std::to_string(avg_prices[ele.first]).substr(0, s.find(".") + 3), "$");
		s = std::to_string((ele.second - avg_prices[ele.first]) * owned_stocks[ele.first]);
		print_content(s.substr(0, s.find(".") + 3), "$");
		std::cout << std::endl;
	}
}

// compute average prices
void Portfolio::computeAvgPrices() {
	// traverse through the `owned_stock` member to compute each individual stock
	for (const auto &ele : this->owned_stocks) {
		// define variables for average purchase price calculation
		size_t cnt_total  = 0;			// number of total purchased shared
		double cost_total = 0.0;		// total cost of all the purchases

		// traverse `trade_record` to find `trade_id` that relate to the symbol
		for (const string &st : trade_record) {
			// recall that each trade Id ends with the stock symbol
			size_t pos = st.find_last_of('-');
			if (st.substr(pos + 1) == ele.first) // uses StockTrade data if symbol matched
			{
				// get the smart pointer to the corresponding `StockTrade` object
				auto st_ptr = this->exchange_ptr->getSingleStockTrade(st);
				// accumulate values if the TRADETYPE is BUY
				if (st_ptr->trade_type == TRADETYPE::BUY) {
					cnt_total  += st_ptr->quantity;
					cost_total += (st_ptr->quantity * st_ptr->price);
				}
			}
		}
		double p_avg = cost_total / (double)(cnt_total);
		// insert the calculated value into `this->avg_prices`
		(this->avg_prices).insert(std::pair<string, double>(ele.first, p_avg));
	}
}