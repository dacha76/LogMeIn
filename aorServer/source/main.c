#include <stdio.h>

#include "../include/aor_server.h"
#include "../include/aor_server_rc.h"

#include "source/server/include/server.h"

int main(int argc, char **argv)
{
    int returnCode = cAOR_SERVER_RC_OK;
    
    // Initialization
    returnCode = ServerInit();
    if ( returnCode == cAOR_SERVER_RC_OK )
    {
        FILE * pFile = fopen("Test.txt", "wt");
        AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
        
        // Dump the content of JSON entry into a file.
        if (pFile)
        {
            for (int i = 0; i < 1; i++ )
            {
                fprintf(pFile, "JsonEntry[%i]\n");
                fprintf(pFile, "key = 0x%08X\n", pServerCtx->pJsonEntry[i].key);
                fprintf(pFile, "entryLength = %i\n", pServerCtx->pJsonEntry[i].entryLength);
                fprintf(pFile, "%s:\"", cSERVER_JSON_AOR_STRING );
                fwrite(pServerCtx->pJsonEntry[i].pJsonAoR, sizeof(char), cSERVER_JSON_AOR_VALUE_NUM_CHAR, pFile);
                fprintf(pFile, "\"\n", cSERVER_JSON_AOR_STRING );
                fwrite(pServerCtx->pJsonEntry[i].pJson, sizeof(char), pServerCtx->pJsonEntry[i].entryLength, pFile);
                fprintf(pFile, "\n", cSERVER_JSON_AOR_STRING );
            }

            fclose(pFile);
        }
     
    }
    
    // terminate the server.
    ServerTerminate();

    // Quit
	return returnCode;
}
