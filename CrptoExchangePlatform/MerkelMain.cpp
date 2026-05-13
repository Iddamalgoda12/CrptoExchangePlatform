#include "MerkelMain.h"
#include <iostream>
#include <map>
#include <vector>
#include "CsvReader.h"
#include <iomanip>
#include <windows.h>

using namespace std;

MerkelMain::MerkelMain() {}

void MerkelMain::init()
{
    wallet1.insertCurrency("BTC", 5);
    wallet1.insertCurrency("ETH", 100);
    currentTime = orderBook.getEarliestTime();
    CsvReader::truncateCsv("sales.csv");

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
    cout << "========================================================================" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "                              MERKEL TRADE                              " << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "========================================================================" << endl;

    cout << "  1:Print help" << endl;
    cout << "  2:Print exchange stats" << endl;
    cout << "  3:Place an Ask(sell)" << endl;
    cout << "  4:Place a Bid(buy)" << endl;
    cout << "  5:Manage wallet" << endl;
    cout << "  6:Continue/Process orders" << endl;

    cout << "========================================================================" << endl;

    cout << "CurrentTime :" << currentTime << endl;
}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    string line;

    cout << "Type in 1-6" << endl << endl;

    getline(cin, line);

    try
    {
        userOption = stoi(line);
    }
    catch (exception& e)
    {

    }

    return userOption;
}

void MerkelMain::printHelp()
{
    cout << "========================================================================" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "                              MERKEL TRADE                              " << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "                               HELP GUIDE                               " << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "========================================================================" << endl;

    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "WHAT IS THIS PROGRAM?" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "This is a simulated cryptocurrency exchange." << endl;
    cout << "You can view market prices, place buy/sell orders," << endl;
    cout << "and manage your wallet using real historical data." << endl;
    cout << "Your starting wallet: 5 BTC and 100 ETH." << endl;

    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "MENU OPTIONS EXPLAINED:" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "------------------------------------------------------------------------" << endl;

    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "[1] Print Help" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "    Shows this help guide." << endl;

    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "[2] Print Exchange Stats" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "    Shows market data for the current time frame." << endl;
    cout << "    Displays all available trading pairs (e.g. ETH/BTC, DOGE/BTC)." << endl;
    cout << "    For each pair you will see:" << endl;
    cout << "      - Number of active ask orders" << endl;
    cout << "      - Highest ask price" << endl;
    cout << "      - Lowest ask price" << endl;
    cout << "      - Average ask price" << endl;

    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "[3] Place an Ask (SELL)" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "    Use this to SELL a cryptocurrency." << endl;
    cout << "    You will be asked to enter: product, price, amount" << endl;
    cout << "      - Example input:  ETH/BTC ,0.02165,1" << endl;
    cout << "      - This means: Sell 1 ETH at a price of 0.02165 BTC each." << endl;
    cout << "    NOTE: You must have enough of the first currency (ETH)" << endl;
    cout << "    in your wallet to place this order." << endl;
    cout << "    The order will NOT execute until you press 6 (Process Orders)." << endl;

    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "[4] Place a Bid (BUY)" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "    Use this to BUY a cryptocurrency." << endl;
    cout << "    You will be asked to enter: product, price, amount" << endl;
    cout << "      - Example input:  ETH/BTC,0.02125,3" << endl;
    cout << "      - This means: Buy 3 ETH by paying 0.02125 BTC each (total 100 BTC)." << endl;
    cout << "    NOTE: You must have enough of the second currency (BTC)" << endl;
    cout << "    in your wallet to cover the total cost (price x amount)." << endl;
    cout << "    The order will NOT execute until you press 6 (Process Orders)." << endl;

    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "[5] Manage Wallet" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "    Opens the wallet menu where you can:" << endl;
    cout << "      1 - Add currency" << endl;
    cout << "      2 - Withdraw currency" << endl;
    cout << "      3 - Return to the main menu" << endl;
    cout << "    When adding or removing, enter in this format:" << endl;
    cout << "      currency, amount  (e.g.  ETH, 10)" << endl;

    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
    cout << "[6] Continue / Process Orders" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "    Matches all pending ask and bid orders for the current time frame." << endl;
    cout << "    If your order is matched, your wallet is updated automatically." << endl;
    cout << "    After processing, the clock moves to the next time frame." << endl;
    cout << "    Keep pressing 6 to simulate time passing in the market." << endl;

    cout << endl;
    cout << "========================================================================" << endl;
}

void MerkelMain::printMarketStatus()
{
    auto uniqueProducts = orderBook.getKnownProducts();

    for (auto const& p : uniqueProducts)
    {
        cout << "Product: ";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << p << endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        vector<OrderBookEntry> askentries =
            orderBook.getOrders(OrderBookType::ask, p, currentTime);

        cout << " No of ASK entries:\t" << askentries.size() << endl;

        cout << fixed << setprecision(6);

        cout << " Highest ask price:\t"
            << OrderBook::getHighPrice(askentries) << endl;

        cout << " Lowest ask price:\t"
            << OrderBook::getLowPrice(askentries) << endl;

        cout << " Average ask price:\t"
            << OrderBook::getMeanPrice(
                OrderBook::getHighPrice(askentries),
                OrderBook::getLowPrice(askentries))
            << endl << endl;

        cout << defaultfloat;

        vector<OrderBookEntry> bidentries =
            orderBook.getOrders(OrderBookType::bid, p, currentTime);

        cout << " No of BID entries:\t" << bidentries.size() << endl;

        cout << fixed << setprecision(6);

        cout << " Highest bid price:\t"
            << OrderBook::getHighPrice(bidentries) << endl;

        cout << " Lowest bid price:\t"
            << OrderBook::getLowPrice(bidentries) << endl;

        cout << " Average bid price:\t"
            << OrderBook::getMeanPrice(
                OrderBook::getHighPrice(bidentries),
                OrderBook::getLowPrice(bidentries))
            << endl << endl;

        cout << defaultfloat;
    }
}

void MerkelMain::enterAsk()
{
    string input;

    cout << "MAKE AN ASK:" << endl
        << "Enter : product ,price amount eg) ETH/BTC ,0.02165,1" << endl;

    getline(cin, input);

    cout << "You typed:" << input << endl;

    vector<string> tokens = CsvReader::tokenise(input, ',');

    if (tokens.size() != 3)
    {
        cout << "MerkelMain::enterAsk Bad input!" << input << endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe =
                CsvReader::stringsToObe(
                    tokens[1],
                    tokens[2],
                    currentTime,
                    tokens[0],
                    OrderBookType::ask);

            obe.userName = "user1";

            if (wallet1.canFulfillOrder(obe))
            {
                cout << "You have enough funds to do the order." << endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                cout << "Wallet has insufficient funds." << endl;
            }
        }
        catch (const exception& e)
        {
            cout << "MerkelMain::enterAsk Bad input" << endl;
        }
    }
}

void MerkelMain::enterBid()
{
    string input;

    cout << "MAKE A BID" << endl
        << "Enter : product ,price amount eg) ETH/BTC ,0.02125,3" << endl;

    getline(cin, input);

    cout << "You typed:" << input << endl;

    vector<string> tokens = CsvReader::tokenise(input, ',');

    if (tokens.size() != 3)
    {
        cout << "MerkelMain::enterBid Bad input!" << input << endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe =
                CsvReader::stringsToObe(
                    tokens[1],
                    tokens[2],
                    currentTime,
                    tokens[0],
                    OrderBookType::bid);

            obe.userName = "user1";

            if (wallet1.canFulfillOrder(obe))
            {
                cout << "You have enough funds to do the order." << endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                cout << "Wallet has insufficient funds." << endl;
            }
        }
        catch (const exception& e)
        {
            cout << "MerkelMain::enterBid Bad input" << endl;
        }
    }
}

void MerkelMain::manageWallet()
{
    wallet1.printWallet(wallet1);

    while (true)
    {
        int userOption = 0;
        string line;

        cout << "Enter 1 to add currency to your wallet" << endl;
        cout << "Enter 2 to withdraw currency from your wallet" << endl;
        cout << "Enter 3 to Return to main menu" << endl;

        getline(cin, line);

        try
        {
            userOption = stoi(line);
        }
        catch (exception& e)
        {

        }

        if (userOption == 1)
        {
            vector<string> tokens;
            string userLine;

            cout << "Enter currency type and amount to add. eg) ETH, 10" << endl;

            getline(cin, userLine);

            tokens = CsvReader::tokenise(userLine, ',');

            wallet1.insertCurrency(tokens[0], stod(tokens[1]));

            cout << "Successfully added money to your account!" << endl;

            wallet1.printWallet(wallet1);

            cout << endl;
        }

        if (userOption == 2)
        {
            vector<string> tokens;
            string userLine;

            cout << "Enter currency type and amount to remove. eg) ETH, 10" << endl;

            getline(cin, userLine);

            tokens = CsvReader::tokenise(userLine, ',');

            wallet1.removeCurrency(tokens[0], stod(tokens[1]));

            cout << "Successfully removed money from your account!" << endl;

            wallet1.printWallet(wallet1);

            cout << endl;
        }

        if (userOption == 3)
            break;
    }
}

void MerkelMain::goToNextTimeFrame()
{
    cout << endl;
    cout << "Processing Orders:" << endl;

    vector<OrderBookEntry> sales;
    vector<OrderBookEntry> allSalesThisFrame;

    for (string p : orderBook.getKnownProducts())
    {
        cout << " matching: ";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        cout << p << endl;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        sales = orderBook.matchAsksToBids(p, currentTime);

        cout << " Sales : " << sales.size() << endl;

        for (OrderBookEntry& sale : sales)
        {
            cout << fixed << setprecision(6);
            cout << " Sale price: " << sale.price;

            cout << defaultfloat;
            cout << " \tamount " << sale.amount << endl;

            if (sale.userName == "user1")
            {
                wallet1.processSale(sale);
            }
        }

        allSalesThisFrame.insert(
            allSalesThisFrame.end(),
            sales.begin(),
            sales.end());

        cout << endl;
    }

    CsvReader::appendOrdersToCsv("sales.csv", allSalesThisFrame);

    cout << "Going to the next time frame" << endl << endl;

    currentTime = orderBook.getNextTime(currentTime);
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
        cout << "Please choose between 1-6" << endl;
    }
}