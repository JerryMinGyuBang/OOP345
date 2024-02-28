#pragma once
#ifndef COMMON_H
#define COMMON_H

//// Define file MACROS
// admin file
#define ADMIN_FILE		"admin.txt"
// member file
#define MEMBER_FILE		"member.txt"
// stock file
#define STOCK_FILE		"stock.txt"


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
	PENDING = 1,
	FINISHED = 2,
	CANCELLED = 3,
};


#endif /* COMMON_H */
