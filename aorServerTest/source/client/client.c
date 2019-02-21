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
    int f_testCaseIdx
    )
{
    int returnCode = cSERVER_TEST_RC_OK;

    f_pClient->testCaseIdx = f_testCaseIdx;

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
