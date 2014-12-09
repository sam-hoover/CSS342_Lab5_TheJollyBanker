// TransactionFactory.h				
// contains the TransactionFactory class definitions.
#ifndef TRANSACTIONFACTORY_H
#define TRANSACTIONFACTORY_H
#include "Transaction.h"

class TransactionFactory 
{
public:
	Transaction* createTransaction(istream &sin);
};

#endif