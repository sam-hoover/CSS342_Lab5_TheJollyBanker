// BankDriver.cpp		
// contains main for the Banker and supporting classes.
#include <iostream>
#include <string>
#include "Banker.h"
using namespace std;

int main() 
{
	Banker jolly;
	jolly.CreateTransactionsLogFromFile();
	jolly.ExecuteTransactionsLog();
	jolly.DisplayAccounts();
	cout << "any key to exit." << endl;
	cin.get();
	return(0);
}
