// Banker.cpp				
// contains the Banker class declarations.
#ifndef BANKER_CPP
#define BANKER_CPP
#include "Banker.h"

Banker::Banker() {}

const std::queue<string> Banker::getTransactionsLog() const 
{
	return(transactionLog);
}

const BSTree Banker::getAccounts() const 
{
	return(accounts);
}

void Banker::CreateTransactionsLogFromFile() {
	ifstream inFile;
	string line;
	inFile.open(TRANSACTION_LOG_FILE);
	while(inFile.good()) 
	{
		getline(inFile, line);
		if(line != "") {
			transactionLog.push(line);
		}
	}
	inFile.close();
}

void Banker::ExecuteTransactionsLog() 
{
	TransactionFactory* fact = new TransactionFactory();
	while(!transactionLog.empty()) {
		stringstream stream(transactionLog.front());
		transactionLog.pop();
		Transaction* trans = fact->createTransaction(stream);
		if(trans != nullptr) 
		{
			ExecuteTransaction(trans);
		} 
		delete trans;
	}
	delete fact;
}

void Banker::ExecuteTransaction(const Transaction *transaction) 
{
	switch(transaction->getType()) 
	{
	case OPEN_ACCOUNT:
		ExecuteOpenAccount(transaction);
		break;
	case DEPOSIT:
		ExecuteDeposit(transaction);
		break;
	case WITHDRAWAL:
		ExecuteWithdrawal(transaction);
		break;
	case TRANSFER:
		ExecuteTransfer(transaction);
		break;
	case HISTORY:
		ExecuteHistory(transaction);
		break;
	default:
		cerr << "ERROR: Invalid Command" << endl;
		break;
	}
}

void Banker::ExecuteOpenAccount(const Transaction *transaction) 
{
	Account* newAccount;
	if(HasAccount(transaction->getAccount(), newAccount)) 
	{
		cerr << "ERROR: Account " << transaction->getAccount() 
			<< " Already Exists. Transaction declined." << endl;
		return;
	}
	newAccount = new Account(transaction->getFirstname(),transaction->getLastname(), transaction->getAccount());
	accounts.Insert(newAccount);
	return;
}

void Banker::ExecuteDeposit(const Transaction *transaction) 
{
	Account *accPtr;
	if(HasAccount(transaction->getAccount(), accPtr)) 
	{
		if(accPtr->Deposit(transaction)) 
		{
			return;
		} 
	} 
	else 
	{
		cerr << "ERROR: Account " << transaction->getAccount() 
			<< " Does Not Exist. Transaction declined." << endl;
	}
	return;
}

void Banker::ExecuteWithdrawal(const Transaction *transaction) 
{
	Account* accPtr;
	if(HasAccount(transaction->getAccount(), accPtr)) 
	{
		if(accPtr->Withdrawal(transaction)) 
		{
			return;
		} 
	} 
	else 
	{
		cerr << "ERROR: Account " << transaction->getAccount() 
			<< " Does Not Exist. Transaction declined." << endl;
	}
	return;
}

void Banker::ExecuteTransfer(const Transaction *transaction) 
{
	Account* transFromPtr;
	Account* transToPtr;

	if(transaction->getAccount() == transaction->getSecondaryAccount()) 
	{
		if(HasAccount(transaction->getAccount(), transFromPtr)) 
		{
			if(transaction->getFund() != transaction->getSecondaryFund()) 
			{
				if(transFromPtr->LocalTransfer(transaction)) 
				{
					return;
				}
			} else {
				cerr << "ERROR: Funds must be different to perform a Transfer. Transaction declined" << endl;
			}
		} 
		else 
		{
			cerr << "ERROR: Account " << transaction->getAccount() 
				<< " Does Not Exist. Transaction declined." << endl;
		}
	}
	else 
	{
		if(HasAccount(transaction->getAccount(), transFromPtr)) 
		{
			if(HasAccount(transaction->getSecondaryAccount(), transToPtr)) 
			{
				if(transFromPtr->OutsideTransfer(transaction, transToPtr)) 
				{
					return;
				}
			} 
			else 
			{
				cerr << "ERROR: Account " << transaction->getSecondaryAccount() 
					<< " Does Not Exist. Transaction declined." << endl;
			}
		} 
		else 
		{
			cerr << "ERROR: Account " << transaction->getAccount() 
				<< " Does Not Exist. Transaction declined." << endl;
		}
	}
	return;
}

void Banker::ExecuteHistory(const Transaction *transaction) 
{
	Account* accPtr;
	if(HasAccount(transaction->getAccount(), accPtr)) 
	{
		accPtr->History(transaction);
		return;
	} 
	else 
	{
		cerr << "ERROR: Account " << transaction->getAccount() 
			<< " Does Not Exist. Transaction declined." << endl;
	}
	return;
}

bool Banker::HasAccount(int accNumber, Account *&account) const 
{
	if(accNumber != ERROR_VALUE) 
	{
		if(accounts.Retreive(accNumber, account))
		{
			return(true);
		} 
	}
	return(false);
}

void Banker::DisplayAccounts() const 
{
	cout << "BANK ACCOUNTS:" << endl;
	if(!accounts.isEmpty()) 
	{
		accounts.Display();
	} 
	else
	{
		cout << "There are no accounts to display." << endl;
	}
}

#endif