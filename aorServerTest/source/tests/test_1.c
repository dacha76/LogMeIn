/************************************************************\
 * File: test_0.c
 * 
 * Description: 
 * 
 * This file contains Test #0.
 * 
 * This test creates 8 client connections and test that the 
 * server seems to answer them.
 * 
\************************************************************/
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/server_test.h"
#include "../../include/server_test_rc.h"
#include "../../include/server_test_client.h"

///////////////////// DEFINITIONS //////////////////////////

#define cTEST1_NUM_CLIENTS              8
#define cTEST1_NUM_REQUESTS             1024

/////////////////// STATIC PROTOTYPES //**//////////////////

/////////////////////// FUNCTIONS //////////////////////////

/************************************************************\
  Function: Test1
\************************************************************/
int Test1()
{
    int returnCode = cAOR_SERVER_TEST_RC_OK;
    int i;
    int clientIdx;
    tTEST_CLIENT clients[cTEST1_NUM_CLIENTS];
    char * addressOfRecord[8] = 
                              { "0158b11f4ffa05636b000100620002",
                                "01546f59a9033db700000100610001",
                                "0157a7d9674085c9d7000100620002",
                                "0142e2fa3543cb32bf000100620002",
                                "015807d1ff2f9b9e3e000100620002",
                                "7MR33EomywYZqwE6qIyfpHY2HTDbqn",
                                "93wW5ULzPn0nYR0MACfxiMUnWJTUC2",
                                "0152adf0a6c49c2884000100620007" };
    srand(0x111);
   
    // Create our first client and send a string to the server.
    memset(&clients, 0, sizeof(clients));
    
    // Init the clients
    for (i=0; i< cTEST1_NUM_CLIENTS; i++)
    {
        returnCode = ClientInit(&clients[i], addressOfRecord[i]);
        if (returnCode != cAOR_SERVER_TEST_RC_OK)
        {
            printf("ERROR: could not init client %d\n", i);
            return returnCode;
        }
    }
    
    for (i=0; i<cTEST1_NUM_REQUESTS; i++)
    {
        int transferSize;
        tTEST_CLIENT * pClient;
        
        // Select a client
        clientIdx = rand() % cTEST1_NUM_CLIENTS;
        pClient = &clients[clientIdx];
        printf("Client id=%d sending request\n", pClient->socketTcp);
        // Send a request to the server.
        transferSize = send(pClient->socketTcp, pClient->addressOfRecord, cSERVER_TEST_AOR_VALUE_NUM_CHAR, 0);
        if (transferSize == cSERVER_TEST_AOR_VALUE_NUM_CHAR)
        {
            char buffer[1024];
            
            memset(buffer, 0, sizeof(buffer));
            
            // Wait for an answer.
            transferSize = recv(pClient->socketTcp, buffer, sizeof(buffer), 0 );
            if (transferSize > 0)
            {
                FILE * pLogFile;
                
                printf("%s\n", buffer );
                
                pLogFile = fopen("server_test_log.txt", "wt");
                if (pLogFile)
                {
                    fwrite(buffer, sizeof(char), transferSize, pLogFile);
                    fclose(pLogFile);
                }
            }
            
            usleep(100000);
        }
        else
        {
            returnCode = cAOR_SERVER_TEST_RC_SOCKET_ERROR_WRITE;
            break;
        }
    }

  
    // Close our client.
    if (returnCode == cAOR_SERVER_TEST_RC_OK)
    {
        for (i=0; i<cTEST1_NUM_CLIENTS; i++)
            ClientTerminate(&clients[i]);
    }
    
    return returnCode;
}