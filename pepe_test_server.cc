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

bool end_program = false;

/*
 * Performs all the functions of the pepe coin including the console interface. Run in a continual loop

 * TODO: Compartmentalize handling of different message types.
 */
int main_communication_loop(){
    int max_fd = 1, i, fd_result;
    fd_set fds;
    FD_ZERO(&fds);
    for (i = 0; i < connected_clients.size(); i++){
        FD_SET(connected_clients[i], &fds);                          //Set the specified client file descriptor to be waited on
        if (connected_clients[i] > max_fd){max_fd = connected_clients[i] + 1;}//The max file descriptor must be one greated than the largest file descriptor
    }
    FD_SET(welcome_socket, &fds);                                   //Setting the welcome socket to be handled
    if (welcome_socket > max_fd){max_fd = welcome_socket + 1;}

    FD_SET(0, &fds);                                            //Setting the stdin socket
    if (0 > max_fd){max_fd = 0 + 1;};                       

    fd_result = select(max_fd, &fds, NULL, NULL, NULL);             //Wait indefinitely for a return on one of the clients.
    if (fd_result == -1){
        printf("Error on selecting a client file descriptor\n");
        exit(1);
    }

    for (i = 0; i < connected_clients.size(); i++){                 //Check each individual client to see which has an awaiting message (can have multiple messages per select).
        if (FD_ISSET(connected_clients[i], &fds)){
            handle_incoming_message(i);                   //Handle incoming message based on client socket index.
        }
    }
    if (FD_ISSET(welcome_socket, &fds)){                            //Check if the welcome socket to see an awaiting client
        struct sockaddr_in new_client_address;
        unsigned int client_address_length;
        int new_client_socket;
        new_client_socket = accept(welcome_socket, (struct sockaddr *) &new_client_address, &client_address_length);
        connected_clients.push_back(new_client_socket);
        cout << "Accepted new client\n";
    }

    if (FD_ISSET(0, &fds)){                                         //Check if there is standard input.
        char c;
        cin >> c;
        if (c == 'Q' or c == 'q'){
            end_program = true;
        }
    }

/*      //Test code to see which file descriptor is set
    for (i = 0; i < max_fd; i++){
        if (FD_ISSET(i, &fds)){
            cout << "fd set: " << i << endl;
        }
    }
*/
}  

/*
 * First thing run when starting the function. Should implement the main_operation_loop to perform its stuff.
 */
int main() {
    initialize_connection();
    int k = 0;

    while (end_program != true){
        main_communication_loop();
        k++;
    }

    close(welcome_socket);
    int i;
    for (i = 0; i < connected_clients.size(); i++){
        close(connected_clients[i]);
    }
}
