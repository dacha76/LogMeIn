/************************************************************\
 * File: client_socket.c
 * 
 * Description: 
 * 
 *    This file contains client socket methods.
 * 
\************************************************************/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../include/server_test.h"
#include "../../include/server_test_rc.h"
#include "../../include/server_test_client.h"


/////////////////// STATIC PROTOTYPES ////////////////////

/************************************************************\
  Function: ClientSocketInit
\************************************************************/
int ClientSocketInit(
    tTEST_CLIENT * f_pClient
    )
{
    int returnCode = cSERVER_TEST_RC_OK;

    // Create a socket.
    f_pClient->socketTcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if (f_pClient->socketTcp)
    {
        struct sockaddr_in socketAddr; 
      
        printf("Mew Client id=%d\n", f_pClient->socketTcp);
 
        // Bind the socket.
        socketAddr.sin_family = AF_INET; 
        socketAddr.sin_port = htons( cSERVER_TEST_SOCKET_UDP_PORT ); 
        
        // Test using localhost.
        socketAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        if (connect(f_pClient->socketTcp, (struct sockaddr *)&socketAddr, sizeof(socketAddr)) < 0)
            returnCode = cSERVER_TEST_RC_SOCKET_ERROR_CONNECT;
    }
    else
        returnCode = cSERVER_TEST_RC_SOCKET_ERROR;
          
    return returnCode;
}


/************************************************************\
  Function: ClientSocketTerminate
\************************************************************/
void ClientSocketTerminate(
    tTEST_CLIENT * f_pClient
    )
{
    printf("Removing Client id=%d\n", f_pClient->socketTcp);
   
    if (f_pClient->socketTcp)
        close(f_pClient->socketTcp);
}