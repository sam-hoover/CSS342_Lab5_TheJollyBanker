// Banker.h				
// contains the Banker class definitions.
#ifndef BANKER_H
#define BANKER_H
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include "Account.h"
#include "TransactionFactory.h"
#include "Transaction.h"
#include "BSTree.h"
using namespace std;

const string TRANSACTION_LOG_FILE = "BankTrans.txt";

class Banker 
{
public:
	Banker();
	void CreateTransactionsLogFromFile();
	void ExecuteTransactionsLog();
	void DisplayAccounts() const;

	const std::queue<string> getTransactionsLog() const;
	const BSTree getAccounts() const;

private:
	void ExecuteTransaction(const Transaction* transaction);
	void ExecuteOpenAccount(const Transaction* transaction);
	void ExecuteDeposit(const Transaction* transaction);
	void ExecuteWithdrawal(const Transaction* transaction);
	void ExecuteTransfer(const Transaction* transaction);
	void ExecuteHistory(const Transaction* transaction);
	bool HasAccount(int accNumber, Account *&account) const;

	std::queue<string> transactionLog;
	BSTree accounts;
};

#endif