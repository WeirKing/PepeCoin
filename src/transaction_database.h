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

TransactionDB();
/*
 * Makes a new database based off of the file
 */
TransactionDB(string file);
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


/*
 * Closes the database and stores the current information to a file
 */
bool close(string file);

/*
 * Loads the database with info from file
 */
bool load(string file);
};
#endif