// Account.cpp				
// contains the Account class declarations.
#ifndef ACCOUNT_CPP
#define ACCOUNT_CPP
#include "Account.h"

Account::Fund::Fund() : balance(NULL) {}

Account::Account() : clientFirstname(NULL), clientLastname(NULL), accountID(NULL) 
{
	for(int i = 0; i < NUM_OF_FUNDS; i++) 
	{
		fund[i] = new Fund();
	}
}

Account::Account(string firstname, string lastname, int idNumber) : clientFirstname(firstname), 
	clientLastname(lastname), accountID(idNumber) 
{
	for(int i = 0; i < NUM_OF_FUNDS; i++) 
	{
		fund[i] = new Fund();
	}
}

Account::~Account() 
{
	for(int i = 0; i < NUM_OF_FUNDS; i++) 
	{
		delete fund[i];
	}
}

string Account::getClientFirstname() const 
{
	return(clientFirstname);
}

string Account::getClientLastname() const 
{
	return(clientLastname);
}

int Account::getAccountID() const 
{
	return(accountID);
}

int Account::getFundBalance(int accType) const 
{
	if(accType >= 0 && accType <= 9) 
	{
		return(fund[accType]->balance);
	} 
	else 
	{
		return(ERROR_VALUE);
	}
}

bool Account::Deposit(const Transaction* transaction) 
{
	int fundType = ERROR_VALUE;
	if(getAccountID() == transaction->getAccount()) 
	{
		fundType = transaction->getFund();
	} 
	else 
	{
		fundType = transaction->getSecondaryFund();
	}

	fund[fundType]->balance += transaction->getAmount();
	fund[fundType]->history.push_back("D $" + to_string(transaction->getAmount()));
	return(true);
}

bool Account::Withdrawal(const Transaction* transaction) 
{
	bool retVal = false;
	int fundType = ERROR_VALUE;

	if(getAccountID() == transaction->getAccount()) 
	{
		fundType = transaction->getFund();
	} 
	else 
	{
		fundType = transaction->getSecondaryFund();
	}

	switch(fundType) 
	{
	case FundType::MoneyMarket:
		if(WithdrawalWithCoverage(fund[MoneyMarket], fund[PrimeMoneyMarket], transaction->getAmount())) 
		{
			retVal = true;
		}
		break;

	case FundType::PrimeMoneyMarket:
		if(WithdrawalWithCoverage(fund[PrimeMoneyMarket], fund[MoneyMarket], transaction->getAmount())) 
		{
			retVal = true;
		}
		break;

	case FundType::LongTermBond:
		if(WithdrawalWithCoverage(fund[LongTermBond], fund[ShortTermBond], transaction->getAmount())) 
		{
			retVal = true;
		}
		break;

	case FundType::ShortTermBond:
		if(WithdrawalWithCoverage(fund[ShortTermBond], fund[LongTermBond], transaction->getAmount())) 
		{
			retVal = true;
		}
		break;

	case FundType::IndexFund500:
	case FundType::CapitalValueFund:
	case FundType::GrowthEquityFund:
	case FundType::GrowthIndexFund:
	case FundType::ValueFund:
	case FundType::ValueStockIndex:
		if(fund[fundType]->balance >= transaction->getAmount()) 
		{
			fund[fundType]->balance -= transaction->getAmount();
			fund[fundType]->history.push_back("W $" + to_string(transaction->getAmount()));
			retVal = true;
		} 
		else 
		{
			fund[fundType]->history.push_back("W $" + to_string(transaction->getAmount()) + " (declined)");
			retVal = false;
		}
		break;
	default:
		break;
		retVal = false;
	}

	if(!retVal) 
	{
		cerr << "ERROR: [" << getAccountID() << " | " << FUND_TYPE[fundType] <<
			"]: Insufficient funds to withdrawal $" << transaction->getAmount() << ". " << endl;
	}

	return(retVal);
}

bool Account::WithdrawalWithCoverage(Fund* primaryFund, Fund* coverageFund, int amount) 
{
	if(primaryFund->balance >= amount) 
	{
		primaryFund->balance -= amount;
		primaryFund->history.push_back("W $" + to_string(amount));
		return(true);
	} 
	else 
	{
		int sumToCover = amount - primaryFund->balance;
		if(coverageFund->balance >= sumToCover)
		{
			if(amount - sumToCover > 0) {
				primaryFund->balance -= (amount - sumToCover);
				primaryFund->history.push_back("W $" + to_string(amount - sumToCover));
			}
			
			coverageFund->balance -= sumToCover;
			coverageFund->history.push_back("W $" + to_string(sumToCover));
			return(true);
		}
		primaryFund->history.push_back("W $" + to_string(amount) + " (declined)");
	}
	return(false);
}


bool Account::LocalTransfer(const Transaction* transaction)
{
	if(Withdrawal(transaction)) 
	{
		fund[transaction->getSecondaryFund()]->balance += transaction->getAmount();

		string input = "T $" + 
			to_string(transaction->getAmount()) + " to [" + 
			to_string(transaction->getSecondaryAccount()) + " | " + 
			FUND_TYPE[transaction->getSecondaryFund()] + "]";
		if(fund[transaction->getFund()]->history.empty()) {
			fund[transaction->getFund()]->history.push_back(input);
		} else {
			fund[transaction->getFund()]->history.back() = input;
		}

		fund[transaction->getSecondaryFund()]->history.push_back("T $" + to_string(transaction->getAmount()) 
			+ " from [" + to_string(transaction->getAccount()) + " | " + 
			FUND_TYPE[transaction->getFund()] + "]");
		return(true);
	}
	fund[transaction->getFund()]->history.back() = "T $" + to_string(transaction->getAmount()) + 
		" to [" + to_string(transaction->getSecondaryAccount()) + " | " + 
		FUND_TYPE[transaction->getSecondaryFund()] + "] (declined)";
	return(false);
}

bool Account::OutsideTransfer(const Transaction* transaction, Account *&transAcc) 
{
	if(Withdrawal(transaction)) 
	{
		transAcc->fund[transaction->getSecondaryFund()]->balance += transaction->getAmount();
		string input = "T $" + to_string(transaction->getAmount()) + 
			" to [" + to_string(transaction->getSecondaryAccount()) + " | " + 
			FUND_TYPE[transaction->getSecondaryFund()] + "]";

		if(fund[transaction->getFund()]->history.empty()) {
			fund[transaction->getFund()]->history.push_back(input);
		} else {
			fund[transaction->getFund()]->history.back() = input;
		}

		transAcc->fund[transaction->getSecondaryFund()]->history.push_back("T $" + to_string(transaction->getAmount()) 
			+ " from [" + to_string(transaction->getAccount()) + " | " 
			+ FUND_TYPE[transaction->getFund()]  + "]");
		return(true);
	}
	fund[transaction->getFund()]->history.back() = "T $" + 
		to_string(transaction->getAmount()) + " to [" +
		to_string(transaction->getSecondaryAccount()) + " | " 
		+ FUND_TYPE[transaction->getSecondaryFund()] + "] (declined)";
	return(false);
}

void Account::History(const Transaction* transaction) const 
{
	cout << "Account History [" << to_string(getAccountID()) << " | " +
		getClientFirstname() << " " + getClientLastname();
	if(transaction->getFund() == ERROR_VALUE) 
	{
		cout << "]: All Active Funds\n";
		for(int i = 0; i < NUM_OF_FUNDS; i++) 
		{
			if(!fund[i]->history.empty()) 
			{
				cout << "   " << FUND_TYPE[i] << ": $" << fund[i]->balance << endl;
				for(unsigned j = 0; j < fund[i]->history.size(); j++) 
				{
					cout << '\t' << fund[i]->history[j] << endl;
				}
			}
		}
		cout << endl;
	} 
	else 
	{
		cout << " | " << FUND_TYPE[transaction->getFund()] << "]: $" 
			<< fund[transaction->getFund()]->balance << endl;
		for(unsigned i = 0; i < fund[transaction->getFund()]->history.size(); i++) 
		{
			cout << '\t' << fund[transaction->getFund()]->history[i] << endl;
		}
		cout << endl;
	}
}

bool Account::operator==(const Account &account) const {
	if(getAccountID() == account.getAccountID()) {
		return(true);
	}
	return(false);
}

bool Account::operator!=(const Account &account) const {
	if(!(*this == account)) {
		return(true);
	}
	return(false);
}

bool Account::operator>(const Account &account) const {
	if(getAccountID() > account.getAccountID()) {
		return(true);
	}
	return(false);
}

bool Account::operator>=(const Account &account) const {
	if(*this > account || *this == account) {
		return(true);
	}
	return(false);
}

bool Account::operator<(const Account &account) const {
	if(!(*this >= account)) {
		return(true);
	}
	return(false);
}

bool Account::operator<=(const Account &account) const {
	if(*this < account || *this == account) {
		return(true);
	}
	return(false);
}

ostream& operator<<(ostream& sout, const Account& account) {
	sout << "[" << account.getAccountID() << " | " << account.getClientFirstname() 
		<< " " << account.getClientLastname() << "]" << endl;
	for(int i = 0; i < NUM_OF_FUNDS; i++) {
		sout << '\t' << FUND_TYPE[i] << ": $" << account.getFundBalance(i) << endl;
	}
	return(sout);
}

#endif
