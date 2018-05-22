/**
 * A List of all the unspent transactions.
 */
#ifndef __transaction_db__
#define __transaction_db__

#include 		<map>
#include		<string>
#include 		"transaction.h"



class TransactionDB{
public:

std::map<string, Transaction> map;

/*
 * Adds the transaction to the database. Assumes the hash is valid already. 
 */
void add(Transaction *new_t, string hash);
/*
 * Remove the transaction with the specified hash
 */
void remove(string hash);
/*
 * Returns a pointer to the transaction with the specified hash
 */
Transaction* get(string hash);
};

#endif