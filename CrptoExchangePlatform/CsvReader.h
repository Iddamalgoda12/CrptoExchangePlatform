//Basically takes the csvfile,reads line by line,tokenize it and store in a vector and returns.
//but this is called through OrderBook class.

#pragma once
#include <vector>
#include<string>
#include "OrderBookEntry.h"

class CsvReader
{
public:
	CsvReader(); //constructor
	static std::vector <OrderBookEntry> readCsv(std::string csvFile) ; //this takes the csvfile,reads line by line,tokenize it and store in a vector and returns.
	static std::vector<std::string> tokenise(std::string csvLine, char seperator); //tokenize full string to seperate strings.
	static OrderBookEntry stringsToObe(std::string priceString, std::string amountString, std::string timestamp , std::string product ,OrderBookType orderType); //takes tokenized strings,converts in to correct data type.
	/** Append rows in the same shape as readCsv: timestamp,product,side,price,amount */
	static void appendOrdersToCsv(std::string csvFileName, const std::vector<OrderBookEntry>& entries);
	/** Empty or create the file (truncate). Call once per program run if you want a fresh log. */
	static void truncateCsv(std::string csvFileName);

private:
	static OrderBookEntry stringsToObe(std::vector<std::string> strings); //takes tokenized strings,converts in to correct data type.



};
