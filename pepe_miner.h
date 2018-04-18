/**
 * Title: pepe_miner.util
 * Author: Kixo
 * Purpose: header file for the pepe miner
 * Date: 4/1/2018
 */

#include        <sys/socket.h>          /* for socket() and bind() */
#include        <stdio.h>               /* printf() and fprintf() */
#include        <stdlib.h>              /* for atoi() and exit() */
#include        <arpa/inet.h>           /* for sockaddr_in and inet_ntoa() */
#include        <sys/types.h>
#include        <iostream>

using namespace std;

#define MESSAGE_LENGTH 1024
#define WELCOME_PORT 60000

int welcome_socket;



/*
 * A generic message that performs the communication between miners
 * When differently formatted info needs to be transmitted the generic array is converted into the correct info
 * The message type is defined by a constant header character.

 * TODO: none
 */
typedef struct _MESSAGE {
    char header;                            //Defines the type of message to follow

    char info[MESSAGE_LENGTH-1];                //Generic array to be treated as different data for communications
} MESSAGE;


int main_operation_loop();
int send_message(MESSAGE *message, int sockfd);
int broadcast_message(MESSAGE *message);
int initialize_connection();
void quit_error(string error_message);
int connect_to_client(char *ip, int port);


/*
 * Quit the program with the given error message
 */
void quit_error(string error_message){
    cout << error_message << endl;
    exit(1);
}
