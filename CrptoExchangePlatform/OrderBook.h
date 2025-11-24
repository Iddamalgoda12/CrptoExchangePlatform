//contains more advanced functions that merkalmain doesnt have.
//full order book is accesible here.

#pragma once
#include <iostream>
#include "OrderBookEntry.h"
#include <string>
#include <vector>
#include <algorithm>

//contains more advanced functions that merkalmain doesnt have.
class OrderBook
{
public:
	/**construct,reads csv file*/
	OrderBook(std::string fileName);

	/**return a vector of all known products eg)ETH/BTC , DOGE/BTC... in the data set*/
	std::vector<std::string> getKnownProducts();

	/**returns a vector of orders according to the sent filters*/
	std::vector<OrderBookEntry> getOrders(OrderBookType type,std::string product,std::string timestamp);

	/**returns the earliest time*/
	std::string getEarliestTime();

	/**returns the next time after the sent time in the orderbook.
	*if there is no next timestamp,it wraps to the first on again.*/
	std::string getNextTime(std::string timestamp);

	void insertOrder(OrderBookEntry& order);        //inserts user order in to the orderbook at the correct timeframe.there is another function inside this to sort the vector.

	std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);  //good one.
	                                                                                            //matchs and rreturns a vector of matched ones.

	
	static double getMeanPrice(double high, double low);
	static double getHighPrice(std::vector<OrderBookEntry>& orders);
	static double getLowPrice(std::vector<OrderBookEntry>& orders);
private:
	std::vector<OrderBookEntry> orders;

};

