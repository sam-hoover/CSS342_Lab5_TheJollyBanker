// TransactionFactory.cpp			
// contains the TransactionFactory class declarations.
#ifndef TRANSACTIONFACTORY_CPP
#define TRANSACTIONFACTORY_CPP
#include "TransactionFactory.h"

Transaction* TransactionFactory::createTransaction(istream &sin) 
{
	Transaction* trans = nullptr;
	char ch = sin.get();
	switch(ch) {
	case OPEN_ACCOUNT:
		trans = new OpenAccountTransaction(sin);
		break;
	case DEPOSIT:
		trans = new DepositTransaction(sin);
		break;
	case WITHDRAWAL:
		trans = new WithdrawalTransaction(sin);
		break;
	case TRANSFER:
		trans = new TransferTransaction(sin);
		break;
	case HISTORY:
		trans = new HistoryTransaction(sin);
		break;
	default:
		cerr << "ERROR: Invalid Command" << endl;
		break;
	}

	if(trans != nullptr && !trans->isValid()) 
	{
		trans = nullptr;
	}
	return(trans);
}


#endif