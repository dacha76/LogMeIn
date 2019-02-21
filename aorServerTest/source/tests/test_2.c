/************************************************************\
 * File: test_2.c
 * 
 * Description: 
 * 
 * This file contains Test #2
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
#define cTEST1_NUM_REQUESTS             2048

/////////////////// STATIC PROTOTYPES //**//////////////////

/////////////////////// GLOBALS //////////////////////////
extern tTEST_CLIENT_CASE_AOR g_aorTestCases[];

/************************************************************\
 * Function: Test2
 * 
 * This test performs the following tasks:
 *  - Sets up 8 client connections.
 *       ~ Select one of 8 test cases for each clients
 *  - Connects each client to the server at:
 *       ~ IP: 127.0.0.1 (localhost)
 *       ~ PORT: cSERVER_TEST_SOCKET_UDP_PORT (0x5200)
 *  - Performs cTEST1_NUM_REQUESTS random requests
 *       ~ Selects one of the client (randomly)
 *       ~ Sends its associated request
 *       ~ Validates that the server answer with the expected JSON object.
 * 
\************************************************************/
int Test2()
{
    int returnCode = cAOR_SERVER_TEST_RC_OK;
    int i;
    int clientIdx;
    tTEST_CLIENT clients[cTEST1_NUM_CLIENTS];

    srand(0x111);
   
    // Create our first client and send a string to the server.
    memset(&clients, 0, sizeof(clients));
    
    // Init the clients
    for (i=0; i< cTEST1_NUM_CLIENTS; i++)
    {
        returnCode = ClientInit(&clients[i], i );
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
        
        // Send a request to the server.
        printf("Client id=%d sending request\n", pClient->socketTcp);
        transferSize = send(pClient->socketTcp, g_aorTestCases[pClient->testCaseIdx].addressOfRecord, cSERVER_TEST_AOR_VALUE_NUM_CHAR, 0);
        
        if (transferSize == cSERVER_TEST_AOR_VALUE_NUM_CHAR)
        {
            char buffer[1024];
            
            memset(buffer, 0, sizeof(buffer));
            
            // Wait for an answer.
            transferSize = recv(pClient->socketTcp, buffer, sizeof(buffer), 0 );
            if (transferSize > 0)
            {
                // Verify that we received the expected response.
                if ( memcmp(g_aorTestCases[pClient->testCaseIdx].expectedAnswer, buffer, transferSize))
                {
                    returnCode = cAOR_SERVER_TEST_RC_TEST_ERROR;
                    printf("ERROR: Did not get the expected answer\n");
                }
            }
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