// Account.h				
// contains the Account class definitions.
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Transaction.h"
using namespace std;

const string FUND_TYPE[10] = {
	"Money Market",
	"Prime Money Market",
	"Long-Term Bond",
	"Short-Term Bond",
	"Index Fund 500",
	"Capital Value Fund",
	"Growth Equity Fund",
	"Growth Index Fund",
	"Value Fund",
	"Value Stock Index"
};
const int NUM_OF_FUNDS = 10;

class Account 
{
	friend ostream& operator<<(ostream& sout, const Account& account);

public:
	enum FundType 
	{
		MoneyMarket, 
		PrimeMoneyMarket,
		LongTermBond, 
		ShortTermBond,
		IndexFund500, 
		CapitalValueFund, 
		GrowthEquityFund,
		GrowthIndexFund, 
		ValueFund, 
		ValueStockIndex
	};
	
	Account();
	Account(string firstname, string lastname, int idNumber);
	~Account();

	string getClientFirstname() const;
	string getClientLastname() const;
	int getAccountID() const;
	int getFundBalance(int accountType) const;

	bool Deposit(const Transaction* transaction);
	bool Withdrawal(const Transaction* transaction);
	bool LocalTransfer(const Transaction* transaction);
	bool OutsideTransfer(const Transaction* transaction, Account *&transAcc);
	void History(const Transaction* transaction) const;

	bool operator==(const Account &account) const;
	bool operator!=(const Account &account) const;
	bool operator<(const Account &account) const;
	bool operator<=(const Account &account) const;
	bool operator>(const Account &account) const;
	bool operator>=(const Account &account) const;

private:
	struct Fund 
	{
		Fund();
		int balance;
		vector<string> history;
	};

	bool WithdrawalWithCoverage(Fund* primaryFund, Fund* coverageFund, int amount);
	string clientFirstname;
	string clientLastname;
	int accountID;
	Fund* fund[NUM_OF_FUNDS];
};

#endif