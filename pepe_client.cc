#include		"pepe_miner.h"
//#include		"crypto_util.cpp"
#include 		<map>
using namespace std;

enum commands {error, com_load, com_store, com_generate};
static map<string, commands> inputToCommand;
void initialize();
int main(){
	initialize();
	string input;
	while (true){

//Get user input
		cout << ">>> ";
		getline(cin, input);

//Parse the chosen command
		string s_command = input.substr(0, input.find(" "));
		transform(s_command.begin(), s_command.end(), s_command.begin(), ::toupper);
		int command;
		command = inputToCommand[s_command];

//Switch based off of the command
		switch(command){

		//Generate a new public and private key.
		case(com_generate):{
			
			break;
		}
		
		case(error):{
			cout << "now this works" << endl;
		}
		}
	}
	return 0;
}



void initialize(){
	inputToCommand["G"] = com_generate;
	inputToCommand["GENERATE"] = com_generate;
}