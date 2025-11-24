//OBE class,used to make OBE type variables.(correct data type varibles).
//also has function to sort two OBe objects by their timestamp.
#pragma once
#include <string>

enum class OrderBookType { bid, ask,unknown,asksale ,bidsale}; //this is like defining our own data type with only bid and ask.


class OrderBookEntry
{

public:
	double price;
	double amount;
	std::string timestamp;
	std::string product;
	OrderBookType orderType;
	std::string userName;

	//constructor
	OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType, std::string _userName="dataset");  //default username set to "dataset".
	//a small function to convert string to {ask.bid} type.
	static OrderBookType stringToOrderBookType(std::string s);

	static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2);  //this is for insertORder() func in OB class.

	static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2);   //these are needed for matchAsksToBids() in OrderBook class.
	static bool compareByPriceDec(OrderBookEntry& e1, OrderBookEntry& e2);

};
