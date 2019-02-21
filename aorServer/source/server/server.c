/************************************************************\
 * File: server.c
 * 
 * Description: 
 * 
 *    This file contains the server initialisation and cleanup methods.
 *  
 *    serverInit() performs the following tasks:
 *    - Allocates the server context
 *    - Loads the server config
 *    - Initializes the server context
 *    - Processes the dump file
 *    - Open the TCP socket
 *  
 *    serverTerminate() releases all allocated resources
 * 
 *    This file also contains the declaration of the server 
 *    context: g_ServerCtx.  
 * 
\************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/server.h"
#include "../../include/server_rc.h"
#include "../../include/server_log.h"
#include "../../include/server_socket.h"

/////////////////// STATIC PROTOTYPES ////////////////////
static int _DumpLoad(
    );
static int _DumpParse(
    const char * f_pfileContent,
    int f_fileContentSize
    );
static int _DumpGetNumJsonEntry(
    const char * f_pfileContent,
    int f_fileContentSize
    );
    
/////////////////////// GLOBALS ////////////////////////////
AOR_SERVER_CTX g_ServerCtx;


/************************************************************\
  Function: serverInit
\************************************************************/
int ServerInit()
{
    int returnCode = cAOR_SERVER_RC_OK;
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    
    // Init the context.
    memset(pServerCtx, 0, sizeof(AOR_SERVER_CTX));
    
    // Set the server start time used by the logs.
    time(&pServerCtx->timeStart);
  
    // Load the dump.
    returnCode = ServerLogInit();
    if (returnCode == cAOR_SERVER_RC_OK)
    {
        returnCode = _DumpLoad();
        if (returnCode == cAOR_SERVER_RC_OK)
        {
            // Init the socket.
            returnCode = ServerSocketInit();
            if (returnCode != cAOR_SERVER_RC_OK)
                ServerLogError("ServerSocketInit", returnCode);
        }
        else
            ServerLogError("_DumpLoad", returnCode);
    }
    else
        ServerLogError("ServerLogInit", returnCode);
    
    return returnCode;
}

/************************************************************\
  Function: ServerTerminate
\************************************************************/
void ServerTerminate()
{
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();

    // Remove all client connections.
    while( pServerCtx->numClientCnct != 0)
    {
        tCLIENT_CNCT * pCnct = pServerCtx->pClientCnct;
        pServerCtx->pClientCnct = pCnct->pNext;
        
        close(pCnct->socketTcpCnct);
        
        free(pCnct);
        pServerCtx->numClientCnct--;
    }
    
    // Terminate the server socket.
    ServerSocketTerminate();
   
    // Release the JSON resources.
    if (pServerCtx->pJsonEntry)
        free(pServerCtx->pJsonEntry);
       
    // Release the file content.
    if (pServerCtx->pfileContent)
        free(pServerCtx->pfileContent);
        
    // Close any opened file.
    if (pServerCtx->pFileDump)
        fclose(pServerCtx->pFileDump);
        
    // Terminate the logs
    ServerLogTerminate();
        
}




static int _DumpLoad()
{
    int returnCode = cAOR_SERVER_RC_OK;
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
   
    // Open the dump file
    pServerCtx->pFileDump = fopen(cSERVER_DUMP_FILE_NAME, "rt");
    if ( !pServerCtx->pFileDump )
    {
        printf("ERROR: could not open file (%s)\n", cSERVER_DUMP_FILE_NAME );
        return cAOR_SERVER_RC_FILE_NOT_FOUND;
    }
    
    // Find out how much memory is required to load the content of the file.
    {
        int fileSize;
        
        fseek(pServerCtx->pFileDump, 0, SEEK_END);
        fileSize = ftell(pServerCtx->pFileDump);
        
        if ( fileSize )
        {
            // Return the file pointer at the start of the file.
            fseek(pServerCtx->pFileDump, 0, SEEK_SET);
            
            // Allocate memory to store the file content.
            pServerCtx->pfileContent = malloc(fileSize);
            if ( pServerCtx->pfileContent )
            {
                int numByteRead;
                
                // Read the file content.
                numByteRead = fread(pServerCtx->pfileContent, sizeof(char), fileSize, pServerCtx->pFileDump );
                
                if ( numByteRead != fileSize )
                    returnCode = cAOR_SERVER_RC_FILE_READ_ERROR;
                    
                if ( returnCode == cAOR_SERVER_RC_OK )
                {
                    // If we have been able to retrieve the file content, parse it
                    returnCode = _DumpParse( pServerCtx->pfileContent, fileSize );
                }  
            }
            else
                returnCode = cAOR_SERVER_RC_DUMP_FILE_MALLOC_ERROR;
        }
        else
            returnCode = cAOR_SERVER_RC_DUMP_FILE_SIZE_ERROR;
    }

    fclose(pServerCtx->pFileDump);
    pServerCtx->pFileDump = NULL;
    
   return returnCode;
}



static int _DumpGetNumJsonEntry(
    const char * f_pfileContent,
    int f_fileContentSize
    )
{
    int numEntries = 0;
    char * pCurPos = (char *)f_pfileContent;
    
    // Find out how many entries are present in the dump.
    // The technique used here is to look for closing brackets '}' used
    // to terminate JSON objects.
    
    while ( pCurPos )
    {
        pCurPos = strchr(pCurPos, '}');
        if (pCurPos)
        {   
            pCurPos++;
            numEntries++;
        }
    }
    
    return numEntries;
}


static int _DumpParse(
   const char * f_pfileContent,
   int f_fileContentSize
   )
{
   int returnCode = cAOR_SERVER_RC_OK;
   AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
   
   // Get the number of entries form the file.
   pServerCtx->numJsonEntry = _DumpGetNumJsonEntry(f_pfileContent, f_fileContentSize);
   if (pServerCtx->numJsonEntry)
   {
       // Allocate an array of JSON entries
       pServerCtx->pJsonEntry = malloc(pServerCtx->numJsonEntry * sizeof(tJSON_ENTRY));
       if (pServerCtx->pJsonEntry)
       {
           char * pNextJsonEntryString = (char *)f_pfileContent;
           tJSON_ENTRY * pJsonEntry;
               
           // Now load each JSON object from the dump into the table of JSON entry.
           for ( int i = 0; i < pServerCtx->numJsonEntry; i++ )
           {
               // Load the next entry;
               pJsonEntry = &pServerCtx->pJsonEntry[i];

               returnCode = ServerJsonEntryAdd(pNextJsonEntryString, pJsonEntry);
               if (returnCode == cAOR_SERVER_RC_OK)
               {
                   // Look for the next entry. Make sure to move the pointer after the 
                   // last processed '{' character.
                   pNextJsonEntryString = strchr(++pNextJsonEntryString, '{');
                   if (!pNextJsonEntryString)
                   {
                       // No '{' found, we are done here. Check if we got all our entries.
                       if (i != (pServerCtx->numJsonEntry - 1))
                          returnCode = cAOR_SERVER_RC_JSON_ENTRY_NUMBER_INVALID;
                      
                       break;
                   }
               }
               else
                   break;
           }
           
       }
   }
   else
   {
       returnCode = cAOR_SERVER_RC_JSON_ENTRY_NOT_FOUND;
       printf("ERROR: Could not find any JSON entries\n");
   }    
    
   return returnCode;
}