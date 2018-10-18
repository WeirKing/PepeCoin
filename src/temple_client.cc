#include		"temple_miner.h"
#include		"transaction.h"
#include 		"transaction_database.h"

using namespace std;

/*
 * Client commands:
 (G)enerate [username]
 (L)oad [username]
 (S)end [to_username] [amount]
 (C)urrent
 	prints currently loaded user
 (A)mount
 	prints the amount of templeCoin available to currently loaded user
 (F)iles
 	prints the known accounts and whether they are pub only or full keys
 */

/*
Need a consistent database of keypairs. This should stay stored even if disconnected from the network.
This can be done pretty easily by a map from a user-defined keypair name to the keypair struct.
this database should also acknowledge whether a keypair contains a private key or not. 
Pairs with a private key have the ability to make transactions, pairs without cannot.
*/

typedef struct {
	string username;
	string pv_key;
	string pb_key;
} key_pair;


TransactionDB db;
key_pair *current = new key_pair;

void handle_generate(string input);
bool handle_load(string input);
void handle_current();
bool handle_send();

void console(){

	string input;

	while (true){

		cout << ">>> ";
		cin >> input;
		char c;
		c = input[0] % 'a' % 'A' + 'A';

		switch(c){
			case 'G': {
				cin >> input;
				handle_generate(input);
				break;
			}
			case 'L': {
				cin >> input;
				handle_load(input);
				break;
			}
			case 'C': {
				handle_current();
				break;
			}
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}


string lower_string(string &input){
	int i = 0;
	string test;
	for (i = 0; i < input.length(); i++){
		test += tolower(input[i]);
	}
	input = test;
	return input;
}

/*
 * Invoked with: G, Generate
 * Handles the generation of a new user. Should take either a copy-pasted key or a file name of a key stored locally.
 * There needs to be a data structure for a logged keypair which will come from the stored keypairs.
 * Users need to be able to (L)oad a keypair based off a username and begin doing manipulations on that keypair. 
 * Users also need to be able to (L)oad one keypair and then (S)end money to another keypair denoted by username
 	or by copy-pasted key.
 */
void handle_generate(string input){
	cout << "username: " << input << endl;
	string pv_key, pb_key, file_name;
	file_name = "keys/" + lower_string(input) + ".key";
	crypto::generate_key_pair(pv_key, pb_key);
	crypto::save_key_pair(pv_key, pb_key, file_name);
}

/*
 * Invoked with: L, Load, 
 * Users should be able to (L)oad a keypair based off on supplied username. This keypair will be the active keypair.
 * Returns:
 	True if loaded file successfully
 	False if key could not be loaded
 */ 
bool handle_load(string input){

	string file_name = "keys/" + lower_string(input) + ".key";
	ifstream load(file_name);
	if (!load.good()){
		cout << "There is no file " << file_name << " in the current key directory." << endl;
		return false;
	}
	string pv_key, pb_key;
	if (!crypto::load_key_pair(pv_key, pb_key, file_name)){
		cout << file_name << " is not a valid key file" << endl;
		return false;
	}
	if (pv_key.compare("") == 0){
		cout << "Loaded public-only key" << endl;
	} else {
		cout << "Loaded keypair: " << lower_string(input) << endl;
	}

	current->username = lower_string(input);
	current->pv_key = pv_key;
	current->pb_key = pb_key;
	return true;
}

bool handle_load_suppressed(string username, string &pb_key){

	string file_name = "keys/" + lower_string(username) + ".key";
	ifstream load(file_name);
	if (!load.good()){
		return false;
	}
	string pv_key;
	if (!crypto::load_key_pair(pv_key, pb_key, file_name)){
		return false;
	}
	return true;
}

/*
 * Invoked with: C, Current
 * Outputs the information regarding the currently loaded keypair to the screen
 */
void handle_current(){
	if (current->username.empty()){
		cout << "No user is currently loaded\n";
		return;
	}
	cout << "Username: " << current->username << endl;
	if (current->pv_key.empty()){
		cout << "Public key only\n";
	}
}


/*
 * Invoked with: S, Send
 * Finds an unspent transaction for the currently loaded user. Makes a new transaction based off of that 
 	transaction and the to pub_key.
 * Communicates with the network controls to send the trnasaction to the network. 

 * TODO
 	Figure out how you're going to implement the transaction db.
 	Maybe make another high-level utility file so the client handle_ functions can be simplified.
 */
bool handle_send(){
	string to, to_pb = "";
	int amount;
	cin >> to;
	cin >> amount;
	handle_load_suppressed(to, to_pb);
	Transaction *new_t = new Transaction;
	new_t->public_key = to_pb;
	db.get()



	return true;
}

int main(){
	console();
}
