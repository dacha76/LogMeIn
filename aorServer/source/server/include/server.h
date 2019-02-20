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
#ifndef __SERVER_H__
#define __SERVER_H__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#include <stdio.h>

#include "server_json.h"
#include "server_cnct.h"
  
#define cSERVER_CONFIG_FILE_NAME    "server.cfg"  
#define cSERVER_DUMP_FILE_NAME    "../sip_dump.txt"

typedef struct
{
    unsigned numLookupKeyCollision;
    unsigned numLookupEntryNotFound;
    unsigned numLookupRequest;
    
} AOR_SERVER_STATS;

typedef struct
{
    // Socket information
    int socketTcp;
    struct sockaddr_in socketAddr; 
    
    // JSON entries
    int numJsonEntry;
    tJSON_ENTRY * pJsonEntry;
    
    // Client connections
    unsigned numClientCnct;
    tCLIENT_CNCT * pClientCnct;
    
    // Dump File information.
    FILE * pFileDump;
    char * pfileContent;

    AOR_SERVER_STATS Stats;
    
} AOR_SERVER_CTX;

extern AOR_SERVER_CTX g_ServerCtx;


static inline AOR_SERVER_CTX * ServerGetCtx()
{
    return &g_ServerCtx;
}

#endif /*__SERVER_H__*/