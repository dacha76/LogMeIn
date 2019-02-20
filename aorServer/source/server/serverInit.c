/************************************************************\
 * File: serverInit.c
 * 
 * Description: 
 * 
 *    This file contains the server initialisation method.
 * It performs the following tasks:
 *    - Allocates the server context
 *    - Loads the server config
 *    - Initializes the server context
 *    - Processes the dump file
 *    - Open the TCP socket
 * 
\************************************************************/
#include <stdio.h>
#include <string.h>

#include "../../include/aor_server_rc.h"

#include "include/server.h"

/////////////////// FUNCTION PROTOTYPES ////////////////////
static int _DumpLoad(
    );
static int _DumpParse(
    char * f_pfileContent,
    int f_fileContentSize
    );
static int _DumpGetNumJsonEntry(
    char * f_pfileContent,
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
 
    returnCode = _DumpLoad();

    return returnCode;
}


static int _DumpLoad()
{
    int returnCode = cAOR_SERVER_RC_OK;
    FILE * pFileDump = NULL;
    char * pfileContent = NULL;
    
    // Open the dump file
    pFileDump = fopen(cSERVER_DUMP_FILE_NAME, "rt");
    if ( !pFileDump )
    {
        printf("ERROR: could not open file (%s)\n", cSERVER_DUMP_FILE_NAME );
        return cAOR_SERVER_RC_FILE_NOT_FOUND;
    }
    
    // Find out how much memory is required to load the content of the file.
    {
        int fileSize;
        
        fseek(pFileDump, 0, SEEK_END);
        fileSize = ftell(pFileDump);
        
        if ( fileSize )
        {
            // Return the file pointer at the start of the file.
            fseek(pFileDump, 0, SEEK_SET);
            
            // Allocate memory to store the file content.
            pfileContent = malloc(fileSize);
            if ( pfileContent )
            {
                int numByteRead;
                
                // Read the file content.
                numByteRead = fread(pfileContent, sizeof(char), fileSize, pFileDump );
                
                if ( numByteRead != fileSize )
                    returnCode = cAOR_SERVER_RC_FILE_READ_ERROR;
                    
                if ( returnCode == cAOR_SERVER_RC_OK )
                {
                    // If we have been able to retrieve the file content, parse it
                    returnCode = _DumpParse( pfileContent, fileSize );
                }  

                free(pfileContent);
            }
            
            
            
        }
    }

    fclose(pFileDump);
    
   return returnCode;
}



static int _DumpGetNumJsonEntry(
    char * f_pfileContent,
    int f_fileContentSize
    )
{
    int numEntries = 0;
    char * pCurPos = f_pfileContent;
    
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
   char * f_pfileContent,
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
           // Now load each JSON object from the dump into the table of JSON entry.
           
       }
   }
   else
   {
       returnCode = cAOR_SERVER_RC_JSON_ENTRY_NOT_FOUND;
       printf("ERROR: Could not find any JSON entries\n");
   }    
    
   return returnCode;
}