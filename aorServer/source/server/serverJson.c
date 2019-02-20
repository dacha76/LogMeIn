/************************************************************\
 * File: serverJson.c
 * 
 * Description: 
 * 
 *    This file contains methods used by the server to manage 
 * JSON entries.
 * 
\************************************************************/
#include <stdio.h>
#include <string.h>

#include "../../include/aor_server_rc.h"

#include "include/server.h"

///////////////////// DEFINITIONS //////////////////////////

/////////////////// STATIC PROTOTYPES ////////////////////
static int _JsonEntryCreateKey(
    const char * f_pAddressOfRecord 
    );

/************************************************************\
  Function: ServerJsonEntryAdd
\************************************************************/
int ServerJsonEntryAdd(
    const char * f_pJson,
    tJSON_ENTRY * f_pJsonEntry 
    )
{
    int returnCode = cAOR_SERVER_RC_OK;
    
    // Set the JSON first character pointer.
    f_pJsonEntry->pJson = f_pJson;
    
    // Now, find where the first character of the "addressOfRecord" is located
    f_pJsonEntry->pJsonAoR = strstr(f_pJson, cSERVER_JSON_AOR_STRING);
    if (f_pJsonEntry->pJsonAoR)
    {
        // We found cSERVER_JSON_AOR_STRING, now skip to its value.
        f_pJsonEntry->pJsonAoR = strchr(f_pJsonEntry->pJsonAoR, ':');
        if (f_pJsonEntry->pJsonAoR)
        {
            // Now skip the ':' and '"' characters to get the first address character.
            f_pJsonEntry->pJsonAoR += 2;
        }
        else
            returnCode = cAOR_SERVER_RC_JSON_ENTRY_AOR_NOT_FOUND;
            
        // Finally, extract the length of this JSON entry.
        if (returnCode ==cAOR_SERVER_RC_OK)
        {
            char * pTemp;
            
            // Extract the number of character in this JSON using the following
            // equation:
            //    entryLength = (&f_pJsonEntry->pJson['}'] - &f_pJsonEntry->pJson['{']) + 1;
            //
            // Note: at this point, f_pJsonEntry->pJson should be equal to 
            // &f_pJsonEntry->pJson['{'].
            
            pTemp = strchr(f_pJsonEntry->pJson, '}');
            if (pTemp)
            {
                // We found the closing brackets, now let's extract the math.
                f_pJsonEntry->entryLength = (pTemp - f_pJsonEntry->pJson) + 1;
                
                // Generate the key.
                f_pJsonEntry->key = _JsonEntryCreateKey(f_pJsonEntry->pJsonAoR);
            }
            else
                returnCode = cAOR_SERVER_RC_JSON_ENTRY_PARSING_ERROR;
        }
    }
    else
        returnCode = cAOR_SERVER_RC_JSON_ENTRY_AOR_NOT_FOUND;
    

    return returnCode;
}


/************************************************************\
 * Function: ServerJsonEntryLookup
 * 
 * This function searches through the table of JSON entry for a 
 * matching key and return a pointer to the matching entry if
 * one is found.
 * 
 * Returns NULL if entry is not found.
 * 
\************************************************************/
tJSON_ENTRY * ServerJsonEntryLookup(
    const char * f_pReqAor
    )
{
    int reqKey;
    tJSON_ENTRY * pJsonEntry = NULL;
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    
    // Create a key for the requested Address of Record (f_pReqAor)
    reqKey = _JsonEntryCreateKey(f_pReqAor);
    
    for (int i=0; i < pServerCtx->numJsonEntry; i++)
    {
        if (pServerCtx->pJsonEntry[i].key == reqKey)
        {
            // We have a key match, now let's make sure the string
            // also matches. Use memcmp to make sure we do not have to deal
            // with termination character issues.
            if (!memcmp(pServerCtx->pJsonEntry[i].pJsonAoR, f_pReqAor, cSERVER_JSON_AOR_VALUE_NUM_CHAR))
            {
                // We have a match.
                pJsonEntry = &pServerCtx->pJsonEntry[i];
                break;
            }
            else
            {
                // We have a key value used by more than one entry, increase the appropriate
                // stat and continue our research.
                pServerCtx->Stats.numLookupKeyCollision++;
            }
        }
    }
    
    return pJsonEntry;
}


/************************************************************\
  Function: ServerJsonEntryLog
\************************************************************/
void ServerJsonEntryLog(
    FILE * f_pFileLog,
    tJSON_ENTRY * f_pJsonEntry 
    )
{
    // Fill the print buffer.
    fprintf(f_pFileLog, "key = 0x%08X\n", f_pJsonEntry->key);
    fprintf(f_pFileLog, "entryLength = %i\n", f_pJsonEntry->entryLength);
    fprintf(f_pFileLog, "%s:\"", cSERVER_JSON_AOR_STRING );
    fwrite(f_pJsonEntry->pJsonAoR, sizeof(char), cSERVER_JSON_AOR_VALUE_NUM_CHAR, f_pFileLog);
    fprintf(f_pFileLog, "\"\n");
    fwrite(f_pJsonEntry->pJson, sizeof(char), f_pJsonEntry->entryLength, f_pFileLog);
    fprintf(f_pFileLog, "\n");
}




/************************************************************\
  Function: _JsonEntryCreateKey
\************************************************************/
static int _JsonEntryCreateKey(
    const char * f_pAddressOfRecord 
    )
{
    int key = 0;
    
    // Create a simple key by adding up all the character (checksum) 
    // from the string. 
    // Could be improved through the use of a CRC.
    
    for (int i=0; i < cSERVER_JSON_AOR_VALUE_NUM_CHAR; i++ )
        key += f_pAddressOfRecord[i];
    
    return key;
}
