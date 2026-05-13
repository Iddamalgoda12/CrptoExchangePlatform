#include "OrderBook.h"
#include "CsvReader.h"
#include <map>
#include <deque>
#include <unordered_set>


/**construct,reads csv file*/
OrderBook::OrderBook(std::string fileName)
{
	orders = CsvReader::readCsv(fileName);            //full order list is accessible in this file.
}

/**return a vector of all known products in the data set*/
std::vector<std::string> OrderBook::getKnownProducts()
{
	std::unordered_set<std::string> productsSet;

	// Insert unique product names into unordered_set
	for (const OrderBookEntry& e : orders)
	{
		productsSet.insert(e.product);
	}

	// Convert unordered_set to vector
	std::vector<std::string> products;

	for (const std::string& product : productsSet)
	{
		products.push_back(product);
	}

	return products;
}

/**searches in the orderbook according to the sent filters and return them*/
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> order_sub;
	for (const OrderBookEntry& e : orders)
	{
		if (e.orderType == type && e.product == product && e.timestamp == timestamp)
		{
			order_sub.push_back(e);
		}

	}
	return order_sub;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
	double max = orders[0].price;
	for (const OrderBookEntry& e : orders)
	{
		if (e.price > max) max = e.price;
	}
	return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
	double low = orders[0].price;
	for (const OrderBookEntry& e : orders)
	{
		if (e.price < low) low = e.price;
	}
	return low;
}

std::string OrderBook::getEarliestTime()
{
	return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
	std::string next_timestamp = "";
	for (const OrderBookEntry& e : orders)
	{
		if (e.timestamp > timestamp)
		{
			next_timestamp = e.timestamp;  //if e.timestamp is bigger than the passed timestamp parameter,it becomes the next_timestamp and breaks.
			break;
		}
	}
	if (next_timestamp == "") next_timestamp = orders[0].timestamp;

	return next_timestamp;

}

//takes highest and lowest prices and returns average price.
double OrderBook::getMeanPrice(double high,double low)
{ 
	double average = (high + low) / 2;
	return average;

}

void OrderBook::insertOrder(OrderBookEntry& order)
{
	orders.push_back(order);                                                              //pushes the order at the end
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);          //inside <algorithm> header.need another function as the third parameter,its the one tells the function how to compare.

}



std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
	std::vector<OrderBookEntry> askVec = getOrders(OrderBookType::ask, product, timestamp);
	std::vector<OrderBookEntry> bidVec = getOrders(OrderBookType::bid, product, timestamp);
	std::vector<OrderBookEntry> sales;

	if (askVec.empty() || bidVec.empty()) return sales;

	std::sort(askVec.begin(), askVec.end(),OrderBookEntry::compareByPriceAsc);   //sorting ASC
	std::sort(bidVec.begin(), bidVec.end(),OrderBookEntry::compareByPriceDec);   //sorting DEC

	std::deque<OrderBookEntry> asks(askVec.begin(), askVec.end());                //deques.
	std::deque<OrderBookEntry> bids(bidVec.begin(), bidVec.end());

	while (!asks.empty() && !bids.empty())
	{
		OrderBookEntry& ask = asks.front();   //not pop,just access front.
		OrderBookEntry& bid = bids.front();

		if (bid.price < ask.price)
			break;

		double tradedAmount =std::min(ask.amount, bid.amount);  //minimum of both ask,bid as the sale.

		OrderBookEntry sale{
			ask.price,
			tradedAmount,
			timestamp,
			product,
			OrderBookType::sale
		};

		if (bid.userName == "user1")
		{
			sale.orderType = OrderBookType::bidsale;
		}

		else if (ask.userName == "user1")
		{
			sale.orderType = OrderBookType::asksale;
		}

		sales.push_back(sale);

		ask.amount = ask.amount - tradedAmount;
		bid.amount = bid.amount - tradedAmount;

		if (ask.amount == 0) asks.pop_front();
		if (bid.amount == 0) bids.pop_front();
	}

	return sales;
}