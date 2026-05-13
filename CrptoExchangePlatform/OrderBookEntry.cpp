#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double _price, double _amount, std::string _timestamp, std::string _product, OrderBookType _orderType, std::string _userName)
	:price(_price), amount(_amount), timestamp(_timestamp), product(_product), orderType(_orderType) ,userName(_userName)
{
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
	if (s == "ask") return OrderBookType::ask;
	if (s == "bid") return OrderBookType::bid;
	if (s == "asksale") return OrderBookType::asksale;
	if (s == "bidsale") return OrderBookType::bidsale;
	if (s == "sale") return OrderBookType::sale;
	return OrderBookType::unknown;

}

std::string OrderBookEntry::orderBookTypeToString(OrderBookType t)
{
	switch (t)
	{
	case OrderBookType::bid: return "bid";
	case OrderBookType::ask: return "ask";
	case OrderBookType::sale: return "sale";
	case OrderBookType::asksale: return "asksale";
	case OrderBookType::bidsale: return "bidsale";
	default: return "unknown";
	}
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
{
	return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
{
	return e1.price < e2.price;
}
bool OrderBookEntry::compareByPriceDec(OrderBookEntry& e1, OrderBookEntry& e2)
{
	return e1.price > e2.price;
}