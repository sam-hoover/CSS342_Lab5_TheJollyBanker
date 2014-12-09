// Transaction.cpp				
// contains the class declarations for the Transaction class and 
// its children classes: OpenAccountTransaction, DepositTransaction,
// WithdrawalTransaction, TransferTransaction, and HistoryTransaction.
#ifndef TRANSACTION_CPP
#define TRANSACTION_CPP
#include "Transaction.h"

void Transaction::ParseAccountInformation(istream &sin, int &account, int &fundType) 
{
	string numbers;
	sin >> numbers;
	
	if(numbers.size() < ACCOUNT_NUMBER_MAX) 
	{
		cerr << "ERROR: Invalid Account Number" << endl;
		valid = false;
	} 
	else if(numbers.size() == ACCOUNT_NUMBER_MAX && getType() == HISTORY) 
	{
		valid = true;
		account = stoi(numbers);
	} 
	else if(numbers.size() == ACCOUNT_NUMBER_MAX + FUND_NUMBER_MAX) 
	{
		account = stoi(numbers.substr(0, ACCOUNT_NUMBER_MAX));
		fundType = stoi(numbers.substr(ACCOUNT_NUMBER_MAX, numbers.size()));
		valid = true;
	} 
	else 
	{
		cerr << "ERROR: Invalid Account Information" << endl;
		valid = false;
	}
}

void OpenAccountTransaction::Parse(istream &sin) 
{
	string name;
	sin >> lastname;
	sin >> firstname;
	sin >> account;
	if(account < 1000 || account > 9999) {
		cerr << "ERROR: Invalid Account Number" << endl;
		account = ERROR_VALUE;
		valid = false;
	} else {
		valid = true;
	}
}

void DepositTransaction::Parse(istream &sin) 
{
	ParseAccountInformation(sin, account, fund);
	if(valid) 
	{
		sin >> amount;
		if(amount <= 0) 
		{
			valid = false;
			cerr << "ERROR: Invalid Amount" << endl;
		}
	}

}

void WithdrawalTransaction::Parse(istream &sin) 
{
	ParseAccountInformation(sin, account, fund);
	if(valid) 
	{
		sin >> amount;
		if(amount <= 0) 
		{
			valid = false;
			cerr << "ERROR: Invalid Amount" << endl;
		}
	}
}

void TransferTransaction::Parse(istream &sin) 
{
	ParseAccountInformation(sin, account, primaryFund);
	if(valid) 
	{
		sin >> amount;
		if(amount <= 0) 
		{
			valid = false;
			cerr << "ERROR: Invalid Amount" << endl;
		} 
		else 
		{
			ParseAccountInformation(sin, secondaryAccount, secondaryFund);
		}
	}
}

void HistoryTransaction::Parse(istream &sin) 
{
	ParseAccountInformation(sin, account, fund);
}

#endif