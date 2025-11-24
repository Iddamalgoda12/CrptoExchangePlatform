#include "CsvReader.h"
#include <iostream>
#include <exception>
#include <fstream>


CsvReader::CsvReader()   //constructor
{

}

std::vector <OrderBookEntry> CsvReader::readCsv(std::string csvFileName)                //this takes the csvfile opens it,passes to other functions to tokenise and change types.
{
	std::vector <OrderBookEntry> entries;
    std::string oneLine;
    std::ifstream csvFile(csvFileName);
        if (csvFile.is_open())
        {
            while (std::getline(csvFile, oneLine))
            {
                try 
                {
                    OrderBookEntry obe = stringsToObe(tokenise(oneLine, ','));
                    entries.push_back(obe);
                }
                catch (const std::exception& e)
                {
                  //  std::cout << "bad line of code" << std::endl;
                }
            }
        }

	return entries;
}


std::vector<std::string> CsvReader::tokenise(std::string csvLine, char seperator)    //tokenize one full string to seperate strings and return it.
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;

    start = csvLine.find_first_not_of(seperator, 0);

    do {
        end = csvLine.find_first_of(seperator, start);

        if (start == csvLine.length() || start == end) break;
        if (end >= 0) 
        { 
            token = csvLine.substr(start, end - start);
        }
        else 
        { 
            token = csvLine.substr(start, csvLine.length() - start);
        }
        tokens.push_back(token);
        start = end + 1;

    } while (end > 0);

    return tokens;
}



OrderBookEntry CsvReader::stringsToObe(std::vector<std::string> tokens)         //first converter function.for csv file data.takes tokenized one full string,converts in to correct data types,returns an OBE object.
{
    double price;
    double amount;
    if (tokens.size() != 5)                        // bad tokens.
    {
       // std::cout << "Bad line" << std::endl;
        throw std::exception{};                   //throws exception directly to the calling of function,stops the belows codes from running.
    }

    try 
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (std::exception& e) 
    {
        /*std::cout << "CsvReader::stringsToObe Bad float!" << tokens[3] << std::endl;
        std::cout << "CsvReader::stringsToObe Bad float!" << tokens[4] << std::endl;*/
        throw;
    }
    OrderBookEntry obe
    {
        price,
        amount,
        tokens[0],
        tokens[1],
        OrderBookEntry::stringToOrderBookType(tokens[2])
    };
	return obe;
}

OrderBookEntry CsvReader::stringsToObe(std::string priceString, std::string amountString, std::string timestamp, std::string product, OrderBookType orderType)    //second converter function.for user input data.takes tokenized strings,converts in to correct data type.
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (std::exception& e)
    {
        /*std::cout << "CsvReader::stringsToObe Bad float!" << priceString << std::endl;
        std::cout << "CsvReader::stringsToObe Bad float!" << amountString << std::endl;*/
        throw;
    }
    OrderBookEntry obe
    {
        price,
        amount,
        timestamp,
        product,
        orderType
    };

    return obe;

}