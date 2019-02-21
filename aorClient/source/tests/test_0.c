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

/////////////////// STATIC PROTOTYPES //**//////////////////

/////////////////////// FUNCTIONS //////////////////////////

/************************************************************\
  Function: ServerCnctAdd
\************************************************************/
int Test0()
{
    int returnCode = cAOR_SERVER_TEST_RC_OK;
    tTEST_CLIENT client;
    char addressOfRecord[] = "0158b11f4ffa05636b000100620002";
    
    // Create our first client and send a string to the server.
    memset(&client, 0, sizeof(client));
    
    returnCode = ClientInit(&client);
    if (returnCode == cAOR_SERVER_TEST_RC_OK)
    {
        int transferSize;
        
        // Send a request to the server.
        transferSize = write(client.socketTcp, addressOfRecord, sizeof(addressOfRecord));
        if (transferSize == sizeof(addressOfRecord))
        {
            char buffer[1024];
            
            memset(buffer, 0, sizeof(buffer));
            
            // Wait for an answer.
            transferSize = read(client.socketTcp, buffer, sizeof(buffer) );
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
        }
        else
            returnCode = cAOR_SERVER_TEST_RC_SOCKET_ERROR_WRITE;
    }
    
    return returnCode;
}