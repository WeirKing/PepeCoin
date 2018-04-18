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
    //initialize_connection();
    int new_client_socket;
    new_client_socket = connect_to_client((char *)"127.0.0.1", 60000);
    close(new_client_socket);
}
