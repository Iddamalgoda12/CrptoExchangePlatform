#include "OrderBook.h"
#include "CsvReader.h"
#include <map>


/**construct,reads csv file*/
OrderBook::OrderBook(std::string fileName)
{
	orders = CsvReader::readCsv(fileName);            //full order list is accessible in this file.
}

/**return a vector of all known products in the data set*/
std::vector<std::string> OrderBook::getKnownProducts()
{
	std::vector<std::string> products;
	std::map<std::string, bool> prodMap;
	for (const OrderBookEntry& e : orders)       //loops over orders and find unique producs like BTC/ETH and stores them in map.
	{
		prodMap[e.product] = true;     
	}

	for (auto const& e : prodMap)               //loops over the map and stores those unique products in a vector.
	{
		products.push_back(e.first);
	}

	return products;

}

/**returns a vector of orders according to the sent filters*/
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
	if (next_timestamp == "") orders[0].timestamp;

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





std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product,std::string timestamp)  //ETH/BTC , 5 A.M.
{

	std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);  //all asks of that time and product type..
	std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);  //all sales of that time.

	std::vector<OrderBookEntry> sales;

	if (asks.size() == 0 || bids.size() == 0)
	{
		std::cout << " OrderBook::matchAsksToBids no bids or asks" << std::endl;
		return sales;
	}

	  //completed ask-bid means sales stored here.

	std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);   //sort asks by ascending order.
	std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDec);    //sort bids by decending order.

	std::cout << "Asks: " << asks.size() << " Bids: " << bids.size() << std::endl;

	for (OrderBookEntry& ask : asks)       //sorted from lowest
	{
		
		for (OrderBookEntry& bid : bids)       //sorted from highest
		{
			
			if (bid.price >= ask.price)// Normally this is true lots of times.-----------------//high priority for the lowest asker,and for the highest bidder.
			{	                                                                                 //those two solved first.Normally this is true lots of times.

				OrderBookEntry sale{ ask.price ,0/*default amount*/ ,timestamp ,product ,OrderBookType::asksale };  //created new object to store solved ask-bids means sales.
				if (bid.userName == "simuser")
				{
					sale.userName = "simuser";                       // if the user is the one making the bid,it's then a bidsale.
					sale.orderType = OrderBookType::bidsale;
				}
				if (ask.userName == "simuser")
				{
					sale.userName = "simuser";                       // if the user is the one making the ask,it's then a asksale.
					sale.orderType = OrderBookType::asksale;
				}
				   	                                                                              
				/*always solves for ask price even though bidder like to pay more.*/
				if (bid.amount == ask.amount)   //now check the amounts.
				{
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = 0;
					break;                        //ask is completed.so break and go to next ask.

				}
				if (bid.amount > ask.amount)
				{
					sale.amount = ask.amount;
					sales.push_back(sale);
					bid.amount = bid.amount - ask.amount;
					break;

				}
				if (bid.amount < ask.amount && bid.amount > 0)
				{
					sale.amount = bid.amount;
					sales.push_back(sale);
					ask.amount = ask.amount - bid.amount;
					bid.amount = 0;

					continue;                                         //continue in this cause ask amount is not filled.
				}


			}
		}

	}
	return sales;


}