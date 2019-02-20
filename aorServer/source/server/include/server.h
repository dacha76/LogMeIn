/************************************************************\
 * File: server.h
 * 
 * Description: 
 * 
 *    This file contains private definitions, structures and 
 * function prototypes that should not be used by resources
 * other than the server.
 * 
\************************************************************/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */

#include "../../../include/aor_server_json.h"
  
#define cSERVER_CONFIG_FILE_NAME    "server.cfg"  
#define cSERVER_DUMP_FILE_NAME    "../sip_dump.txt"


typedef struct
{
    int numJsonEntry;
    tJSON_ENTRY * pJsonEntry;
        
} AOR_SERVER_CTX;

extern AOR_SERVER_CTX g_ServerCtx;


static inline AOR_SERVER_CTX * ServerGetCtx()
{
    return &g_ServerCtx;
}
