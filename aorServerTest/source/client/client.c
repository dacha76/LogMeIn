/************************************************************\
 * File: client.c
 * 
 * Description: 
 * 
 *    This file contains client methods.
 * 
\************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/server_test.h"
#include "../../include/server_test_rc.h"
#include "../../include/server_test_client.h"


/////////////////// STATIC PROTOTYPES ////////////////////

/************************************************************\
  Function: ClientInit
\************************************************************/
int ClientInit(
    tTEST_CLIENT * f_pClient,
    char * f_pAddressOfRecord
    )
{
    int returnCode = cAOR_SERVER_TEST_RC_OK;

    // copy the AOR in the client.
    memcpy(f_pClient->addressOfRecord, f_pAddressOfRecord, cSERVER_TEST_AOR_VALUE_NUM_CHAR);

    // Not much to do here except init the socket using the 
    // address configured in f_pClient.
    returnCode = ClientSocketInit(f_pClient);
    
    return returnCode;
}

/************************************************************\
  Function: ClientTerminate
\************************************************************/
void ClientTerminate(
    tTEST_CLIENT * f_pClient
    )
{
    ClientSocketTerminate(f_pClient);
}
