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
            char Aor[] = "0142e2fa3543cb32bf000100620002";
            tJSON_ENTRY * pJsonEntry;
            
            // Lookup the entry
            pJsonEntry = ServerJsonEntryLookup(Aor);
            if ( pJsonEntry )
                ServerJsonEntryLog(pFile, pJsonEntry);
            else
                pServerCtx->Stats.numLookupEntryNotFound++;

            fclose(pFile);
        }
     
    }
    
    // terminate the server.
    ServerTerminate();

    // Quit
	return returnCode;
}
