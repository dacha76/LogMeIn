#include "../include/aor_server.h"
#include "../include/aor_server_rc.h"

int main(int argc, char **argv)
{
    int returnCode = cAOR_SERVER_RC_OK;
    
    // Initialization
    returnCode = ServerInit();
    if ( returnCode == cAOR_SERVER_RC_OK )
    {
        // Do something here.
        
     
    }
    
    // terminate the server.
    ServerTerminate();

    // Quit
	return returnCode;
}
