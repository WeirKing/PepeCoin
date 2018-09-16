#include "transaction_database.h"

void TransactionDB::add(Transaction *new_t, string hash){
	map[hash] = *new_t;
}

void TransactionDB::remove(string hash){
	map.erase(hash);
}
Transaction* TransactionDB::get(string hash){
	if (map[hash] != map.end()){
		return &map[hash];
	}
	return NULL;
}