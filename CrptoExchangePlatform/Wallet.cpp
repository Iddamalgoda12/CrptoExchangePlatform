#include "Wallet.h"
#include <exception>


Wallet::Wallet()
{

}

void Wallet::insertCurrency(std::string type, double amount)
{
    double balance = 0;
    if (amount < 0) throw std::exception{};          
    if (currencies.count(type) == 0)  balance = 0;   //checks btc currency type is there .
    else balance = currencies[type];

    balance = balance + amount;            //adds the amount we want to the balance.
    currencies[type] = balance;            //stores the correct currency.

}

bool Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0) return 0;          
    if (currencies.count(type) == 0)  return 0;   //checks btc currency type is there. if not we cant remove it.
    else
     {
        if (containsCurrency(type, amount))    //calls contains currency.checks if asked amount to remove is there.
        {
            currencies[type] = currencies[type] - amount;
            return 1;
        }
        else return 0;
            
     }                                           
}


//this is boolean.doesnt return the ammount.just check if the passed amount is there or not.
bool Wallet::containsCurrency(std::string type, double amount)
{
    if (currencies.count(type) == 0)  return 0;   //checks btc currency type is not there .
    else return currencies[type] >= amount;       //then checks if amount=10 is there,if there return 1.          
}

std::string Wallet::toString()              //gives a full string list of all the currencies and amounts in the wallet.
{
    std:: string s;
    for (std::pair<std::string, double> pair : currencies)
    {
        s = s + pair.first + ":" + std::to_string(pair.second) + "\n";
    }
    return s;

}

//ckecks if we can do the passed order.
bool Wallet::canFulfillOrder(OrderBookEntry order)   //ask- BTC/ETH sells for ETH.
{
    std::vector<std::string> currs = CsvReader::tokenise(order.product, '/');  //tokenize "BTC/ETH" in to "BTC" , "ETH".
    //ask
    if (order.orderType == OrderBookType::ask)
    {
        double amount = order.amount;                 // amount BTC we need to sell.
        std::string currency = currs[0];              //we are asking to sell BTC,so we need btc.
        return containsCurrency(currency, amount);    //amount we asked to sell.
    }
    //bid

    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount*order.price;          // amount ETH we needed to buy BTC.
        std::string currency = currs[1];                  //to buy BTC, we need ETH.
        return containsCurrency(currency, amount);       //checks the amount asked in the order is in our wallet.
    }
    return false;
}

void Wallet::processSale(OrderBookEntry& sale)
{
    std::vector<std::string> currs = CsvReader::tokenise(sale.product, '/');  //tokenize "BTC/ETH" in to "BTC" , "ETH".
    //asksales
    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;                 // amount BTC user need to sell.
        std::string outgoingCurrency = currs[0];              //user is asks to sell BTC,so it outgoes.
        
        double incomingAmount = sale.amount * sale.price;          // amount ETH user received.
        std::string incomingCurrency = currs[1];

        currencies[outgoingCurrency] = currencies[outgoingCurrency] - outgoingAmount;
        currencies[incomingCurrency] = currencies[incomingCurrency] + incomingAmount;

    }

    //bidsales
    if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];

        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[outgoingCurrency] = currencies[outgoingCurrency] - outgoingAmount;
        currencies[incomingCurrency] = currencies[incomingCurrency] + incomingAmount;
    }

}

void Wallet::printWallet(Wallet wallet)
{
    std::cout << "Your wallet" << std::endl;                                   //printswallet.
    std::cout << "--------------------" << std::endl;
    std::string myWallet = wallet.toString();
    if (myWallet == "") std::cout << "Your wallet is empty" << std::endl;
    else std::cout << myWallet << std::endl;
    std::cout << "--------------------" << std::endl;
}
