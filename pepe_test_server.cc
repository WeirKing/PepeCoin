/**
 * Title: pepe_miner.cc
 * Author: Kixo
 * Purpose: miner for pepe coin
 * Date: 4/1/2018
 */


#include        <sys/socket.h>          /* for socket() and bind() */
#include        <stdio.h>               /* printf() and fprintf() */
#include        <stdlib.h>              /* for atoi() and exit() */
#include        <arpa/inet.h>           /* for sockaddr_in and inet_ntoa() */
#include        <sys/types.h>
#include        "pepe_miner.util"       /* utility funcions for pepe miner */
#include        <unistd.h>

/*
 * Performs all the functions of the pepe coin including the console interface. Run in a continual loop

 * TODO: Everything
 */
int main_operation_loop(){

}

/*
 * First thing run when starting the function. Should implement the main_operation_loop to perform its stuff.
 */
int main() {
    initialize_connection();
    struct sockaddr_in new_client_address;
    unsigned int client_address_length;
    int new_client_socket;
    new_client_socket = accept(welcome_socket, (struct sockaddr *) &new_client_address, &client_address_length);
    cout << "Accepted new client\n";
    close(welcome_socket);
    close(new_client_socket);
}
