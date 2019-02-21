/************************************************************\
 * File: server_cnct.c
 * 
 * Description: 
 * 
 * This file contains methods used manage client connections. 
 * 
\************************************************************/
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../include/server.h"
#include "../../include/server_rc.h"
#include "../../include/server_log.h"

///////////////////// DEFINITIONS //////////////////////////

/////////////////// STATIC PROTOTYPES //**//////////////////

/////////////////////// FUNCTIONS //////////////////////////

/************************************************************\
  Function: ServerCnctAlloc
\************************************************************/
tCLIENT_CNCT * ServerCnctAlloc()
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
        pServerCtx->Stats.numTcpCnctActive++;
    }
        
    return pCnct;
}

/************************************************************\
  Function: ServerCnctFree
\************************************************************/
int ServerCnctFree(
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
        for (i=0; i<pServerCtx->Stats.numTcpCnctActive; i++)
        {
            if (pCnctList->pNext == f_pCnct)
            {
                pCnctList->pNext = f_pCnct->pNext;
                break;
            }
            pCnctList = pCnctList->pNext;
        }
        
        if (i == pServerCtx->Stats.numTcpCnctActive)
        {
            // We did not find any connection pointing to our entry.
            returnCode = cAOR_SERVER_RC_CNCT_REMOVE_ERROR;
        }
    }
    
    if (returnCode == cAOR_SERVER_RC_OK)
    {
        // All went well, update the stats and free our entry.
        if (f_pCnct->socketTcpCnct)
            close(f_pCnct->socketTcpCnct);
            
        pServerCtx->Stats.numTcpCnctActive--;
        pServerCtx->Stats.numTcpCnctClosed++;

        free(f_pCnct);
    }
    
    return returnCode;
}



/************************************************************\
  Function: ServerCnctUpdate
\************************************************************/
int ServerCnctUpdate()
{
    int returnCode = cAOR_SERVER_RC_OK;
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    tCLIENT_CNCT * pNext;
    tCLIENT_CNCT * pCnct;
    time_t  timeCurrent;
  
    // Look for connection timeout 
    time(&timeCurrent);
    
    // Loop through all active connections.
    pCnct = pServerCtx->pClientCnct;
    while (pCnct != NULL)
    {
        // Save right away the next entry in case we release the current entry.
        pNext = pCnct->pNext;
        
        // Check for timeout.
        if ((timeCurrent - pCnct->timeLastRequest) > cSERVER_CLIENT_CNCT_TIMEOUT_SEC) 
        {
            char buffer[256];
            
            // Connection in timeout...
            sprintf(buffer, "Connection timeout for id=%d", 
                pCnct->socketTcpCnct
                );
            ServerLog(buffer);
            
            // Flag the entry as to be removed.
            pCnct->removeFlag = 1;
        }
        
        // Remove the entry (may be caused by disconnect or timeout.
        if (pCnct->removeFlag)
        {
            returnCode = ServerCnctFree(pCnct);
            if (returnCode != cAOR_SERVER_RC_OK)
            {
                ServerLogError("ServerCnctFree", returnCode);
                break;
            }
        }
        
        // Move to the next connection.
        pCnct = pNext;
    }
    
    return returnCode;
}
