#include <stdio.h>

#include "../include/aor_server.h"
#include "../include/aor_server_rc.h"

#include "server/include/server.h"
#include "server/include/server_socket.h"

int main(int argc, char **argv)
{
    int returnCode = cAOR_SERVER_RC_OK;
    
    // Initialization
    returnCode = ServerInit();
    if ( returnCode == cAOR_SERVER_RC_OK )
    {
        // Poll our socket until something goes bad.
        do
        {
            returnCode = ServerSocketPoll();
            
        } while (returnCode == cAOR_SERVER_RC_OK);
    }
    
    // terminate the server.
    ServerTerminate();

    // Quit
	return returnCode;
}
