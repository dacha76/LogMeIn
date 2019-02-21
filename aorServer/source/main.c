/************************************************************\
 * File: main.c
 * 
 * Description: 
 * 
 * Program entry point (main).
 * performs the following steps:
 *  - Initialize the server
 *  - Peform the poll action
 *     * Poll for new connection
 *     * Poll for connection requests
 *     * Check for connection timeout.
 *  - Cleanup if an error occur. 
 * 
\************************************************************/
#include <stdio.h>

#include "../include/server.h"
#include "../include/server_rc.h"
#include "../include/server_log.h"

/************************************************************\
  Function: main
\************************************************************/
int main(int argc, char **argv)
{
    int returnCode = cAOR_SERVER_RC_OK;
    
    // Initialization
    returnCode = ServerInit();
    if ( returnCode == cAOR_SERVER_RC_OK )
    {
        // Server started
        
        // Log that we started the server.
        
        
        // Poll our socket until something goes bad.
        do
        {
            returnCode = ServerSocketPoll();
            if (returnCode == cAOR_SERVER_RC_OK)
            {
                returnCode = ServerCnctUpdate();
                if (returnCode != cAOR_SERVER_RC_OK)
                    ServerLogError("ServerCnctUpdate", returnCode);
            }
            else
                ServerLogError("ServerSocketPoll", returnCode);
                
        } while (returnCode == cAOR_SERVER_RC_OK);
    }
    else
        ServerLogError("ServerInit", returnCode);
         
    // terminate the server.
    ServerTerminate();

    // We are done.
	return returnCode;
}
