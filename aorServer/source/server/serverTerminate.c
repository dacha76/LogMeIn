/************************************************************\
 * File: serverTerminate.c
 * 
 * Description: 
 * 
 *    Releases all resources allocated by the server.
 * 
\************************************************************/
#include <stdlib.h>

#include "../../include/aor_server_rc.h"

#include "include/server.h"

/////////////////// FUNCTION PROTOTYPES ////////////////////
/////////////////////// GLOBALS ////////////////////////////

/************************************************************\
  Function: ServerTerminate
\************************************************************/
void ServerTerminate()
{
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();

    // Remove all client connection.
    while( pServerCtx->numClientCnct != 0)
    {
        tCLIENT_CNCT * pCnct = pServerCtx->pClientCnct;
        pServerCtx->pClientCnct = pCnct->pNext;
        
        free(pCnct);
        pServerCtx->numClientCnct--;
    }
   
    // Release the JSON resources.
    if (pServerCtx->pJsonEntry)
        free(pServerCtx->pJsonEntry);
       
    // Release the file content.
    if (pServerCtx->pfileContent)
        free(pServerCtx->pfileContent);
        
    // Close any opened file.
    if (pServerCtx->pFileDump)
        fclose(pServerCtx->pFileDump);
    
    return;
}
