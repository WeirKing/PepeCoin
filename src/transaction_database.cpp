#include "transaction_database.h"

TransactionDB::TransactionDB(){
	
}
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

bool TransactionDB::close(string file){
	Transaction temp;
	ofstream out(file);
	out << map.size();
	for (auto const& x: map){
		temp = x.second;
		out << x.first << endl;
		out << temp.signed_hash << endl 
		<< temp.public_key << endl 
		<< temp.prev_hash << endl;
	}
	out.close();
}
bool TransactionDB::load(string file){
	Transaction temp;
	
}