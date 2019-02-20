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

/////////////////// FUNCTION PROTOTYPES ////////////////////
/////////////////////// GLOBALS ////////////////////////////


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
                f_pJsonEntry->key = ServerJsonEntryCreateKey(f_pJsonEntry->pJsonAoR);
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
  Function: ServerJsonEntryCreateKey
\************************************************************/
int ServerJsonEntryCreateKey(
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



/************************************************************\
  Function: ServerJsonEntryLog
\************************************************************/
int ServerJsonEntryAdd(
    FILE * f_pFileLog,
    tJSON_ENTRY * f_pJsonEntry 
    )
{
    // Fill the print buffer.
    fprintf(f_pFileLog, "JsonEntry[%i]\n");
    fprintf(f_pFileLog, "key = 0x%08X\n", pServerCtx->pJsonEntry[i].key);
    fprintf(f_pFileLog, "entryLength = %i\n", pServerCtx->pJsonEntry[i].entryLength);
    fprintf(f_pFileLog, "%s:\"", cSERVER_JSON_AOR_STRING );
    fwrite(pServerCtx->pJsonEntry[i].pJsonAoR, sizeof(char), cSERVER_JSON_AOR_VALUE_NUM_CHAR, f_pFileLog);
    fprintf(f_pFileLog, "\"\n", cSERVER_JSON_AOR_STRING );
    fwrite(pServerCtx->pJsonEntry[i].pJson, sizeof(char), pServerCtx->pJsonEntry[i].entryLength, f_pFileLog);
    fprintf(f_pFileLog, "\n", cSERVER_JSON_AOR_STRING );
  
   
    
}