/************************************************************\
 * File: serverTerminate.c
 * 
 * Description: 
 * 
 *    Releases all resources allocated by the server.
 * 
\************************************************************/
#include <stdio.h>
#include <string.h>

#include "../../include/aor_server_rc.h"

#include "include/server.h"

/////////////////// FUNCTION PROTOTYPES ////////////////////
/////////////////////// GLOBALS ////////////////////////////

/************************************************************\
  Function: ServerTerminate
\************************************************************/
int ServerTerminate()
{
   AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
   
   // Release the JSON resources.
   if (pServerCtx->pJsonEntry)
       free(pServerCtx->pJsonEntry);
    
   return;
}
