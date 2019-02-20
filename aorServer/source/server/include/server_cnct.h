/************************************************************\
 * File: server_cnct.h
 * 
 * Description: 
 * 
 * This file contains client connection structures, definitions
 * and function prototypes.
 * 
\************************************************************/
#ifndef __SERVER_CLIENT_CNCT_H__
#define __SERVER_CLIENT_CNCT_H__

#include <stdio.h>
#include <time.h>

//////////////////////// DEFINITIONS /////////////////////////////
#define cSERVER_CLIENT_CNCT_TIMEOUT_MS           10000     // 10 seconds timeout.


//////////////////////// TYPEDEF /////////////////////////////
typedef struct {
    
    void * pNext;       // Next pointer used to linked entries.
    
    // Client information.
    unsigned short clientPort;          // TCP port of this connection's client
    // ADDRESSE clientAddr; // IPv4 address of this connection's client
    
    time_t  timeStart;  // Time, in seconds when this session was created.
    time_t  timeLastRequest;  // Time, in seconds when the last request was received.
            
} tCLIENT_CNCT;

/////////////////////// FUNCTIONS ////////////////////////////

tCLIENT_CNCT * ServerCnctAdd(
    const unsigned short f_ClientPort
    );

#endif /*__SERVER_CLIENT_CNCT_H__*/