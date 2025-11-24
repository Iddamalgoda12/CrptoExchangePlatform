
#include <iostream>
#include <map>
using namespace std;

void printMenu()
{
	cout << "======================" << endl;
	cout << "1:Print help" << endl;
	cout << "2:Print exchange stats" << endl;
	cout << "3:Place an ask" << endl;
	cout << "4:Place a bid" << endl;
	cout << "5:Print wallet" << endl;
	cout << "6:Continue" << endl;
	cout << "======================" << endl;

	cout << "Type in 1-6" << endl;
}

int getUserOption()
{
	int userOption;
	cin >> userOption;
	cout << "You chose:" << userOption << endl;
	return userOption;

}

void printHelp()
{
	cout << "Help - choose options from the menu" << endl;
	cout << "and follow the on screen instructions." << endl;
}

void printMArketStatus()
{
	cout << "Printing exchange rates" << endl;
	cout << "follow the on screen instructions." << endl;
}
void enterOffer()
{
	cout << "placing an ask" << endl;
	cout << "follow the on screen instructions." << endl;
}

void enterBid()
{
	cout << "placing a bid" << endl;
	cout << "and follow the on screen instructions." << endl;
}

void printWallet()
{
	cout << "printing wallet" << endl;
	cout << "follow the on screen instructions." << endl;
}

void goToNextTimeFrame()
{
	cout << "continue" << endl;
}

void processUserOption(int userOption)
{
	map<int, void(*)()> menu;

    menu[1] = printHelp;
	menu[2] = printMArketStatus;
	menu[3] = enterOffer;
	menu[4] = enterBid;
	menu[5] = printWallet;
	menu[6] = goToNextTimeFrame;

	if (menu.find(userOption) != menu.end())
	{
		menu[userOption]();
	}
	else
	{
		cout << "please choose between 1-6" << endl;
	}

}

int main()
{

	while (true)
	{
		printMenu();
		int userOption=getUserOption();
		processUserOption(userOption);

	}
	return 0;
}

