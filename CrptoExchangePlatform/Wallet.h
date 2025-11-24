//my wallet

#pragma once
#include <iostream>
#include <string>
#include <map>
#include "OrderBookEntry.h"
#include "CsvReader.h"

class Wallet
{
public:
	Wallet();   //constructor
	 
	/**insert currency to the wallet*/
	void insertCurrency(std::string type, double amount);

	/**remove currency to the wallet*/
	bool removeCurrency(std::string type, double amount);

	/**check if the wallet contains this much currency or more */
	bool containsCurrency(std::string type, double amount);

	//takes an order and checks if we have enough money to do it.
	bool canFulfillOrder(OrderBookEntry order);

	/**generate a string representation of the wallet */
	std::string toString();

	/**update the contents of the wallet */
	void processSale(OrderBookEntry& sale);

	void printWallet(Wallet wallet);

private:
	//this is what we use to store data in the wallet eg)currencies and amounts.thats why used a map.
	std::map<std::string, double> currencies;


};
