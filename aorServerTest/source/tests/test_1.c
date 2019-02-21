/************************************************************\
 * File: test_0.c
 * 
 * Description: 
 * 
 * This file contains Test #0.
 * 
 * This test creates a single client connection and sends a
 * address of record and wait for an answer from the server.
 * 
\************************************************************/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/server_test.h"
#include "../../include/server_test_rc.h"
#include "../../include/server_test_client.h"

///////////////////// DEFINITIONS //////////////////////////

#define cTEST_0_AOR_TEST_CASE_IDX       7

/////////////////// STATIC PROTOTYPES //**//////////////////

/////////////////////// GLOBALS //////////////////////////
extern tTEST_CLIENT_CASE_AOR g_aorTestCases[];

/************************************************************\
  Function: Test1
\************************************************************/
int Test1()
{
    int returnCode = cAOR_SERVER_TEST_RC_OK;
    int testCaseIdx = cTEST_0_AOR_TEST_CASE_IDX;
    tTEST_CLIENT client;
    
    // Create our first client and send a string to the server.
    memset(&client, 0, sizeof(client));
    
    returnCode = ClientInit(&client, testCaseIdx );
    if (returnCode == cAOR_SERVER_TEST_RC_OK)
    {
        int transferSize;
        
        // Send a request to the server.
        transferSize = write(client.socketTcp, g_aorTestCases[client.testCaseIdx].addressOfRecord, cSERVER_TEST_AOR_VALUE_NUM_CHAR);
        if (transferSize == cSERVER_TEST_AOR_VALUE_NUM_CHAR)
        {
            char buffer[1024];
            
            memset(buffer, 0, sizeof(buffer));
            
            // Wait for an answer.
            transferSize = read(client.socketTcp, buffer, sizeof(buffer) );
            if (transferSize > 0)
            {
                // Verify that we received the expected response.
                if ( memcmp(g_aorTestCases[client.testCaseIdx].expectedAnswer, buffer, transferSize))
                {
                    returnCode = cAOR_SERVER_TEST_RC_TEST_ERROR;
                    printf("ERROR: Did not get the expected answer\n");
                }
            }
        }
        else
            returnCode = cAOR_SERVER_TEST_RC_SOCKET_ERROR_WRITE;
    }

    // Sleep before terminating the client.
    sleep(10);
    
    // Close our client.
    if (returnCode == cAOR_SERVER_TEST_RC_OK)
    {
        ClientTerminate(&client);
    }
    
    return returnCode;
}