/**
 * Title: pepe_miner.cc
 * Author: Kixo
 * Purpose: miner for pepe coin
 * Date: 4/1/2018
 */


#include		<sys/socket.h>		  /* for socket() and bind() */
#include		<stdio.h>			   /* printf() and fprintf() */
#include		<stdlib.h>			  /* for atoi() and exit() */
#include		<arpa/inet.h>		   /* for sockaddr_in and inet_ntoa() */
#include		<sys/types.h>
#include		"pepe_miner.util"	   /* utility funcions for pepe miner */
#include		<unistd.h>
#include		<assert.h>
#include		"transaction.h"
#include		"transaction_database.h"

TransactionDB transaction_db;

/*
 * Performs all the functions of the pepe coin including the console interface. Run in a continual loop

 * TODO: Everything
 */
int main_operation_loop(){
	int max_fd = 0, i, fd_result;
	fd_set fds;
	for (i = 0; i < connected_clients.size(); i++){
		FD_SET(connected_clients[i], &fds);						 //Set the specified client file descriptor to be waited on
		if (connected_clients[i] > max_fd){
			max_fd = connected_clients[i] + 1;					  //The max file descriptor must be one greated than the largest file descriptor
		}
	}
	fd_result = select(max_fd, &fds, NULL, NULL, NULL);			 //Wait indefinitely for a return on one of the clients.
	if (fd_result == -1){
		printf("Error on selecting a client file descriptor\n");
		exit(1);
	}

	for (i = 0; i < connected_clients.size(); i++){				 //Check each individual client to see which has an awaiting message (can have multiple messages per select).
		if (FD_ISSET(connected_clients[i], &fds)){
			handle_incoming_message(connected_clients[i]);		  //Handle incoming message based on client socket fd.
		}
	}
	return 0;
}


/*
 * Handles a new transaction received from the network
 * It should either add the transaction to the currently mined block or add it to the queue of transactions to be added to new block.
 * Should only handle valid transactions, if the transaction is invalid just do nothing
 *
 * TODO most everything
 */
void handle_transaction_message(MESSAGE *m){
    string prev_hash;
    Transaction *t_p, t, *prev_t;
	assert(m->header == 'T');
	t_p = (Transaction *)m;		//TODO make sure this nonsense actually works lmao
    t = *t_p;

	prev_t = transaction_db.get(prev_hash);
	if (prev_t == NULL){
		console_message("Received invalid transaction");
    }
	bool valid = t.verify_transaction(prev_t);
	if (!valid){
		console_message("Received invalid transaction");
	}

	//TODO add the new transaction to the queue of new transactions
}

/*
 * First thing run when starting the function. Should implement the main_operation_loop to perform its stuff.
 */
int main() {
	//initialize_connection();
	int new_client_socket;
	new_client_socket = connect_to_client((char *)"127.0.0.1", 60000);
	MESSAGE *message = new MESSAGE;
	message->header = 'M';
	strcpy(message->info, (char *)"This is a message to the server\n\0");

	send_message(message, new_client_socket);
	cout << "Message successfully sent to server\n";
	close(new_client_socket);
}
