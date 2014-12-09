// Transaction.h				
// contains the class definitions for the Transaction class and 
// its children classes: OpenAccountTransaction, DepositTransaction,
// WithdrawalTransaction, TransferTransaction, and HistoryTransaction.
#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>
using namespace std;

const int ACCOUNT_NUMBER_MAX = 4;
const int FUND_NUMBER_MAX = 1;
const int ERROR_VALUE = -1;
const char OPEN_ACCOUNT = 'O';
const char DEPOSIT = 'D';
const char WITHDRAWAL = 'W';
const char TRANSFER = 'T';
const char HISTORY = 'H';

class Transaction 
{
public:
	Transaction() : account(ERROR_VALUE), valid(false) {}
	virtual ~Transaction() {}
	virtual void Parse(istream &sin) = 0;
	virtual int getFund() const {return(ERROR_VALUE);}
	virtual int getAmount() const {return(ERROR_VALUE);}
	virtual int getSecondaryAccount() const {return(ERROR_VALUE);}
	virtual int getSecondaryFund() const {return(ERROR_VALUE);}
	virtual string getFirstname() const {return("");}
	virtual string getLastname() const {return("");}
	virtual char getType() const {return(NULL);}
	int getAccount() const {return(account);}
	bool isValid() const {return(valid);}

protected:
	void ParseAccountInformation(istream &sin, int &accountNumber, int &accountType);
	int account;
	bool valid;
};

class OpenAccountTransaction : public Transaction 
{
public:
	OpenAccountTransaction(istream &sin) : Transaction(), firstname(""), lastname("") {Parse(sin);}
	virtual ~OpenAccountTransaction() {}
	string getFirstname() const {return(firstname);}
	string getLastname() const {return(lastname);}
	char getType() const {return(OPEN_ACCOUNT);}
	void Parse(istream &sin);
private:
	string firstname;
	string lastname;
};

class DepositTransaction : public Transaction 
{
public:
	DepositTransaction(istream &sin) : Transaction(), fund(ERROR_VALUE), amount(ERROR_VALUE) {Parse(sin);}
	virtual ~DepositTransaction() {}
	int getFund() const {return(fund);}
	int getAmount() const {return(amount);}
	char getType() const {return(DEPOSIT);}
	void Parse(istream &sin);
private:
	int fund;
	int amount;
};

class WithdrawalTransaction : public Transaction 
{
public:
	WithdrawalTransaction(istream &sin) : Transaction(), fund(ERROR_VALUE), amount(ERROR_VALUE) {Parse(sin);}
	virtual ~WithdrawalTransaction() {}
	int getFund() const {return(fund);}
	int getAmount() const {return(amount);}
	char getType() const {return(WITHDRAWAL);}
	void Parse(istream &sin);
private:
	int fund;
	int amount;
};

class TransferTransaction : public Transaction 
{
public:
	TransferTransaction(istream &sin) : Transaction(), primaryFund(ERROR_VALUE), amount(ERROR_VALUE), secondaryAccount(ERROR_VALUE), secondaryFund(ERROR_VALUE) {Parse(sin);}
	virtual ~TransferTransaction() {}
	int getFund() const {return(primaryFund);}
	int getAmount() const {return(amount);}
	int getSecondaryAccount() const {return(secondaryAccount);}
	int getSecondaryFund() const {return(secondaryFund);}
	char getType() const {return(TRANSFER);}
	void Parse(istream &sin);
private:
	int primaryFund;
	int amount;
	int secondaryAccount;
	int secondaryFund;
};

class HistoryTransaction : public Transaction 
{
public:
	HistoryTransaction(istream &sin) : Transaction(), fund(ERROR_VALUE) {Parse(sin);}
	virtual ~HistoryTransaction() {}
	int getFund() const {return(fund);}
	char getType() const {return(HISTORY);}
	void Parse(istream &sin);
private:
	int fund;
};

#endif