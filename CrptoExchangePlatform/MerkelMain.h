//handles basic functions like printmenu(), getuseroption() ....

#pragma once                  //put top of every header.fixes duplicate implementations .h and .cpp have the same.
#include "OrderBookEntry.h"
#include <vector>
#include "OrderBook.h"
#include "wallet.h"
#include "CsvReader.h"
 
class MerkelMain
{
public:
	MerkelMain();
	//call this to start the app.
	void init();      //adding constructor and and a initialization fucntions is good.first cunstructor is called,then initialization.

private:
	std::vector <OrderBookEntry> orders;

	void printMenu();
	int getUserOption();
	void printHelp();
	void printMarketStatus();
	void enterAsk();
	void enterBid();
	void manageWallet();
	void goToNextTimeFrame();
	void processUserOption(int userOption);

	std::string currentTime;
	OrderBook orderBook{"data.csv"};  // kelinma constructor call ekenma csv file ek aread wee vector ekakata addwee,OB class eka balanna.
	
	Wallet wallet;   

};
