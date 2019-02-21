/************************************************************\
 * File: test_0.c
 * 
 * Description: 
 * 
 * This file contains Test #0.
 * 
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
 * Function: Test0
 * 
 * This test performs the following tasks:
 *  - Connects to the server at:
 *       ~ IP: 127.0.0.1 (localhost)
 *       ~ PORT: cSERVER_TEST_SOCKET_UDP_PORT (0x5200)
 *  - Sends an "addressOfRecord" from file "sip.dump"
 *  - Validates that the server returns the expected JSON object.
 * 
\************************************************************/
int Test0()
{
    int returnCode = cSERVER_TEST_RC_OK;
    int testCaseIdx = cTEST_0_AOR_TEST_CASE_IDX;
    tTEST_CLIENT client;
    
    // Create our first client and send a string to the server.
    memset(&client, 0, sizeof(client));
    
    returnCode = ClientInit(&client, testCaseIdx );
    if (returnCode == cSERVER_TEST_RC_OK)
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
                    returnCode = cSERVER_TEST_RC_TEST_ERROR;
                    printf("ERROR: Did not get the expected answer\n");
                }
            }
        }
        else
            returnCode = cSERVER_TEST_RC_SOCKET_ERROR_WRITE;
    }

   
    // Close our client.
    if (returnCode == cSERVER_TEST_RC_OK)
    {
        ClientTerminate(&client);
    }
    
    return returnCode;
}