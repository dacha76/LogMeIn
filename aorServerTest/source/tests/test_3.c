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

#define cTEST_3_NUM_AOR_PER_REQUEST  6

/////////////////// STATIC PROTOTYPES //**//////////////////

/////////////////////// GLOBALS //////////////////////////
extern tTEST_CLIENT_CASE_AOR g_aorTestCases[];

/************************************************************\
 * Function: Test3
 * 
 * This test performs the following tasks:
 *  - Connects to the server at:
 *       ~ IP: 127.0.0.1 (localhost)
 *       ~ PORT: cSERVER_TEST_SOCKET_UDP_PORT (0x5200)
 *  - Sends an "addressOfRecord" from file "sip.dump"
 *  - Validates that the server returns the expected JSON object.
 * 
\************************************************************/
int Test3()
{
    int i;
    int returnCode = cSERVER_TEST_RC_OK;
    int testCaseIdx[8] = {0, 1, 2, 3, 4, 5, 6 ,7};
    tTEST_CLIENT client;
    
    srand(1234);

    // Create our first client and send a string to the server.
    memset(&client, 0, sizeof(client));
    
    returnCode = ClientInit(&client, 0 ); // Ignore test case since we are going to use more than one case.
    if (returnCode == cSERVER_TEST_RC_OK)
    {
        int requestSize = 0;
        int transferSize = 0;
        char clientReq[1024] = {0};
        
        
        // Create a multiple case request. Each entry is seperated by a '\n' character.
        memcpy(clientReq, g_aorTestCases[testCaseIdx[0]].addressOfRecord, cSERVER_TEST_AOR_VALUE_NUM_CHAR);
        requestSize += cSERVER_TEST_AOR_VALUE_NUM_CHAR;
        
        for (i=1; i<cTEST_3_NUM_AOR_PER_REQUEST; i++)
        {
            // Insert the '\n' character.
            clientReq[requestSize++] = (char)'\n';
            
            // Insert the next AOR
            memcpy(&clientReq[requestSize], g_aorTestCases[testCaseIdx[i]].addressOfRecord, cSERVER_TEST_AOR_VALUE_NUM_CHAR);
            requestSize += cSERVER_TEST_AOR_VALUE_NUM_CHAR;
        }
        
        // Send a request to the server.
        transferSize = write(client.socketTcp, clientReq, requestSize);
        if (transferSize == requestSize)
        {
            char buffer[4096] = {0};
            
            // Wait for an answer.
            transferSize = read(client.socketTcp, buffer, sizeof(buffer) );
            if (transferSize > 0)
            {
                char * pToken;
                const char delim[2] = "\n";
                
                // Tokenize our answer and verify its content.
                pToken = strtok(buffer, delim);
                i = 0;  // First JSON object should come from first AOR
                
                while(pToken)
                {
                    // Verify that we received the expected response.
                    if ( memcmp(g_aorTestCases[i].expectedAnswer, pToken, strlen(g_aorTestCases[i].expectedAnswer)))
                    {
                        returnCode = cSERVER_TEST_RC_TEST_ERROR;
                        printf("ERROR: Did not get the expected answer\n");
                    }
                    
                     pToken = strtok(NULL, delim);
                     i++;
                }
            }
        }
        else
            returnCode = cSERVER_TEST_RC_SOCKET_ERROR_WRITE;
    }

   
    // Close our client.
    ClientTerminate(&client);
   
    return returnCode;
}