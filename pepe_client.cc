#include		"pepe_miner.h"

using namespace std;

/*
 * Client commands:
 (G)enerate [username]
 (L)oad [username]
 (S)end [to_username] [amount]
 (C)urrent
 	prints currently loaded user
 (A)mount
 	prints the amount of PepeCoin available to currently loaded user
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

key_pair *current = new key_pair;

void handle_generate(string input);
bool handle_load(string input);

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
	file_name = lower_string(input) + ".key";
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

	string file_name = lower_string(input) + ".key";
	ifstream load(file_name);
	if (!load.good()){
		cout << "There is no file " << file_name << " in the current key directory." << endl;
		return false;
	}
	string pv_key, pb_key;
	if (!crypto::load_key_pair(pv_key, pb_key, file_name)){
		cout << file_name << " is not a valid key file" << endl;
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

int main(){
	console();
}
