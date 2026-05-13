//handles basic functions like printmenu(), getuseroption() ....

#pragma once       
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
	void init();

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
	OrderBook orderBook{"data.csv"};  // kelinma constructor call ekenma csv file eka read wee vector ekakata addwee,OB class eka balanna.
	
	Wallet wallet1;   

};
