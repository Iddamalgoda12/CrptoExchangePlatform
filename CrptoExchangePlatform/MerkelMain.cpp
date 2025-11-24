#include "MerkelMain.h"
#include <iostream>
#include <map>
#include <vector>
#include "CsvReader.h"

MerkelMain::MerkelMain() {}

void MerkelMain::init()
{
    wallet.insertCurrency("BTC", 5);
    wallet.insertCurrency("ETH", 100);
    currentTime = orderBook.getEarliestTime();  //sets current time to the earliest time.
    int input;
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    };

}

void MerkelMain::printMenu()
{
	std::cout << "======================" << std::endl;
	std::cout << "1:Print help" << std::endl;
	std::cout << "2:Print exchange stats" << std::endl;
	std::cout << "3:Place an ask" << std::endl;
	std::cout << "4:Place a bid" << std::endl;
	std::cout << "5:Manage wallet" << std::endl;
	std::cout << "6:Continue/Process orders" << std::endl;
	std::cout << "======================" << std::endl;

    std::cout << "CurrentTime :" << currentTime<< std::endl;
}

int MerkelMain::getUserOption()
{
	int userOption=0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);                       //using cin causes some unexpected problems.thats why we use getline().
    try 
    {
        userOption = std::stoi(line);
    }
    catch (std::exception& e)
    {
        //
    }
	return userOption;
}

void MerkelMain::printHelp()
{
	std::cout << "Help - choose options from the menu" << std::endl;
	std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printMarketStatus()
{
   auto uniqueProducts= orderBook.getKnownProducts();    //calls the OB class function.
   for (auto const& p : uniqueProducts)
   {
       std::cout <<"Product: " << p << std::endl;                                                          //loops and prints BTC/ETH like unique product types.
       std::vector < OrderBookEntry > entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);  //gives how many 'ask' entries are there for that unique product type,at CURRENTTIME.
       std::cout << "No of entries:" << entries.size() << std::endl;                                      //we can change the current time by just pressing 6 now.so now we can see those orders at that time.
       std::cout<< "Highest ask price:" << OrderBook::getHighPrice(entries) << std::endl;
       std::cout << "Lowest ask price:" << OrderBook::getLowPrice(entries) << std::endl;
       std::cout << "Average ask price:" << OrderBook::getMeanPrice(OrderBook::getHighPrice(entries), OrderBook::getLowPrice(entries)) << std::endl;
   }
 
}


void MerkelMain::enterAsk()                         //takes an input "ETH/BTC ,200 , 0.5" and checks we have enough coins to do it.then stores in the orderbook.
{
    std::string input;
	std::cout << "make an Ask"<<std::endl<<"Enter : product ,price amount eg) ETH/BTC ,200 , 0.5" << std::endl;
    std::getline(std::cin, input);                                       //gets the user input string. eg)"ETH/BTC ,200 , 0.5".
	std::cout <<"You typed:" << input << std::endl;
    std::vector < std::string> tokens = CsvReader::tokenise(input,',');  //tokenized.
    if (tokens.size() != 3)                                               
    {
        std::cout << "MerkelMain::enterAsk Bad input!" << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CsvReader::stringsToObe(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::ask);     //converting types and making a OBE object.
            obe.userName = "simuser";
            if (wallet.canFulfillOrder(obe))                             //check if we have enough coins to do that order.
            {
                std::cout << "You have enough funds to do the order." << std::endl;
                orderBook.insertOrder(obe);                                //then stores it.
            }
            else
            {
                std::cout << "Wallet has insufficient funds." << std::endl;
            }
            
        }
        
        catch (const std::exception& e)
        {
            std::cout << "MerkelMain::enterAsk Bad input" << std::endl;
        }
        
    }
}

void MerkelMain::enterBid()
{
    std::string input;
    std::cout << "make an Bid" << std::endl << "Enter : product ,price amount eg) ETH/BTC ,200 , 0.5" << std::endl;
    std::getline(std::cin, input);                                       //gets the user input string. eg)"ETH/BTC ,200 , 0.5".
    std::cout << "You typed:" << input << std::endl;
    std::vector < std::string> tokens = CsvReader::tokenise(input, ',');  //tokenized.
    if (tokens.size() != 3)                                               //converting types and making a OBE object.
    {
        std::cout << "MerkelMain::enterBid Bad input!" << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CsvReader::stringsToObe(tokens[1], tokens[2], currentTime, tokens[0], OrderBookType::bid);  //converting types.
            obe.userName = "simuser";
            if (wallet.canFulfillOrder(obe))                             //check if we have enough coins to do that order.
            {
                std::cout << "You have enough funds to do the order." << std::endl;
                orderBook.insertOrder(obe);                                //then stores it.
            }
            else
            {
                std::cout << "Wallet has insufficient funds." << std::endl;
            }

        }

        catch (const std::exception& e)
        {
            std::cout << "MerkelMain::enterBid Bad input" << std::endl;
        }

    }
}

void MerkelMain::manageWallet()
{
    wallet.printWallet(wallet);
    
    while (true)
    {
        int userOption = 0;
        std::string line;
        std::cout << "Enter 1 to add currency to your wallet" << std::endl;
        std::cout << "Enter 2 to withdraw currency from your wallet" << std::endl;
        std::cout << "Enter 3 to Return to main menu" << std::endl;

        std::getline(std::cin, line);                       //using cin causes some unexpected problems.thats why we use getline().
        try
        {
            userOption = std::stoi(line);
        }
        catch (std::exception& e)
        {
            //
        }

        if (userOption == 1)
        {
            std::vector<std::string> tokens;
            std::string userLine;
            std::cout << "Enter currency type and amount to add. eg) ETH, 10" << std::endl;
            std::getline(std::cin, userLine);
            tokens = CsvReader::tokenise(userLine, ',');
            wallet.insertCurrency(tokens[0], stod(tokens[1]));
            std::cout << "Successfully added money to your account!" << std::endl;
            wallet.printWallet(wallet);
            std::cout << std::endl;
        }

        if (userOption == 2)
        {
            std::vector<std::string> tokens;
            std::string userLine;
            std::cout << "Enter currency type and amount to remove. eg) ETH, 10" << std::endl;
            std::getline(std::cin, userLine);
            tokens = CsvReader::tokenise(userLine, ',');
            wallet.removeCurrency(tokens[0], stod(tokens[1]));
            std::cout << "Successfully removed money from your account!" << std::endl;
            wallet.printWallet(wallet);
            std::cout << std::endl;
        }
        if (userOption == 3) break;
    }

}

void MerkelMain::goToNextTimeFrame()                //this is where matching should happen.cause in the current time orders must be completed before the next timeframe.
{
    std::cout << "Processing Orders" << std::endl;
    std::vector<OrderBookEntry> sales;
    for (std::string p : orderBook.getKnownProducts())        // ETH/BTC ,DOGE/BTC .... we have to match all products.
    {
        std::cout << "matching " << p << std::endl;
        sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales : " << sales.size() << std::endl;

        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.userName == "simuser")                             //if simuser then we have to update the wallet.
            {
                wallet.processSale(sale);
            }
        }
    }
    std::cout << "Going to the next time frame" << std::endl;
    currentTime = orderBook.getNextTime(currentTime);               //now we can just go to the next time just by clicking 6 number.
    
}


void MerkelMain::processUserOption(int userOption)
{
   
    if (userOption == 1)
    {
        printHelp();
    }
    else if (userOption == 2)
    {
        printMarketStatus();
    }
    else if (userOption == 3)
    {
        enterAsk();
    }
    else if (userOption == 4)
    {
        enterBid();
    }
    else if (userOption == 5)
    {
        manageWallet();
    }
    else if (userOption == 6)
    {
        goToNextTimeFrame();
    }
    else
    {
        std::cout << "Please choose between 1-6" << std::endl;
    }
}
