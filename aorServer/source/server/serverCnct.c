/************************************************************\
 * File: serverCnct.c
 * 
 * Description: 
 * 
 * This file contains methods used manage client connections. 
 * 
\************************************************************/
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/aor_server_rc.h"

#include "include/server.h"

///////////////////// DEFINITIONS //////////////////////////

/////////////////// STATIC PROTOTYPES //**//////////////////

/////////////////////// FUNCTIONS //////////////////////////

/************************************************************\
  Function: ServerCnctAdd
\************************************************************/
tCLIENT_CNCT * ServerCnctAdd()
{
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    tCLIENT_CNCT * pCnct = NULL;
    
    // Allocate memory for this new entry.
    pCnct = malloc(sizeof(tCLIENT_CNCT));
    if ( pCnct)
    {
        // Clear the entry.
        memset(pCnct, 0, sizeof(tCLIENT_CNCT));
        
        // get the time of creation.
        time(&pCnct->timeStart);
        pCnct->timeLastRequest = pCnct->timeStart;
        
        // Now insert the entry in the list.
        pCnct->pNext = pServerCtx->pClientCnct;
        pServerCtx->pClientCnct = pCnct;
        
        // Indicate that we have a new entry.
        pServerCtx->numClientCnct++;
    }
        
    return pCnct;
}

/************************************************************\
  Function: ServerCnctRemove
\************************************************************/
int ServerCnctRemove(
    tCLIENT_CNCT * f_pCnct
    )
{
    int returnCode = cAOR_SERVER_RC_OK;
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    tCLIENT_CNCT * pCnctList = NULL;
    
    // Parse the connection list to find this connecion's previous entry
    // Then update it's next pointer to make sure we do not lose any entries.
    
    pCnctList = pServerCtx->pClientCnct;
    
    // Check for the exception where our entry is the first in the list.
    if (pCnctList == f_pCnct)
    {
        pServerCtx->pClientCnct = f_pCnct->pNext;
    }
    else
    {
        int i;
        // We need to go through the list.
        for (i=0; i<pServerCtx->numClientCnct; i++)
        {
            if (pCnctList->pNext == f_pCnct)
            {
                pCnctList->pNext = f_pCnct->pNext;
                break;
            }
        }
        
        if (i == pServerCtx->numClientCnct)
        {
            // We did not find any connection pointing to our entry.
            returnCode = cAOR_SERVER_RC_CNCT_REMOVE_ERROR;
        }
    }
    
    if (returnCode == cAOR_SERVER_RC_OK)
    {
        // All went well, update the stats and free our entry.
        pServerCtx->numClientCnct--;
        free(f_pCnct);
    }
    
    return returnCode;
}

