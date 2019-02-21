/************************************************************\
 * File: server_log.c
 * 
 * Description: 
 * 
 * This file contains log methods.
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
  Function: ServerLogInit
\************************************************************/
int ServerLogInit()
{
    int returnCode = cAOR_SERVER_RC_OK;
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    
    pServerCtx->pFileLog = fopen(cSERVER_LOG_FILE_NAME, "wt");
    if (pServerCtx->pFileLog)
    {
        char buffer[256];
        sprintf(buffer, "aorServer version %s", cSERVER_VERSION);
        ServerLog(buffer);
    }
    else
        returnCode = cAOR_SERVER_RC_CANNOT_OPEN_LOG_FILE;
    
    return returnCode;
}


/************************************************************\
  Function: ServerLogTerminate
\************************************************************/
void ServerLogTerminate()
{
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    
    if (pServerCtx->pFileLog)
        fclose(pServerCtx->pFileLog);
}

/************************************************************\
  Function: ServerLog
\************************************************************/
void ServerLog(
    char * f_pLogString 
    )
{
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    time_t timeLog; 
    char buffer[80]; 
    struct tm *timeLogFormated;
   
    /* Get the current time */
    timeLog = time(NULL);

    /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
    timeLogFormated = localtime(&timeLog);
    strftime(buffer, sizeof(buffer), "[%a %Y-%m-%d %H:%M:%S %Z]", timeLogFormated);
    
    printf("%s:%s\n", buffer, f_pLogString);
    
    if (pServerCtx->pFileLog)
        fprintf(pServerCtx->pFileLog, "%s:%s\n", buffer, f_pLogString );
}



/************************************************************\
  Function: ServerLogError
\************************************************************/
void ServerLogError(
    char * f_pErrorSource,
    int f_error
    )
{
    char buffer[256]; 
    
    sprintf(buffer, "ERROR 0x%08X from %s", f_error, f_pErrorSource);
    ServerLog(buffer);
}



/************************************************************\
  Function: ServerLogStats
\************************************************************/
void ServerLogStats()
{
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    AOR_SERVER_STATS * pStats = &pServerCtx->Stats;
    
    char bufferLog[2048] = { 0 }; 
    int avgTimeUs = 0;

    if (pStats->numLookupRequest)
        avgTimeUs = (int)(pStats->lookupRequestTotalTimeUs/pStats->numLookupRequest);
    
    sprintf(bufferLog, "Stats Report:\n\n\
         -numTcpCnctActive=%d\n\
         -numTcpCnctClosed=%d\n\n\
         -lookupRequestMinTimeUs=%d\n\
         -lookupRequestAvgTimeUs=%d\n\
         -lookupRequestMaxTimeUs=%d\n\n\
         -numLookupRequest=%d\n\
         -numLookupEntryNotFound=%d\n\
         -numLookupKeyCollision=%d\n\n",
         pStats->numTcpCnctActive,
         pStats->numTcpCnctClosed,
         pStats->lookupRequestMinTimeUs,
         avgTimeUs,
         pStats->lookupRequestMaxTimeUs,
         pStats->numLookupRequest,
         pStats->numLookupEntryNotFound,
         pStats->numLookupKeyCollision
         );
         
    ServerLog(bufferLog);
}
