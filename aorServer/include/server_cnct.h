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
#define cSERVER_CLIENT_CNCT_TIMEOUT_SEC           7     // 7 seconds timeout.


//////////////////////// TYPEDEF /////////////////////////////
typedef struct {
    
    void * pNext;       // Next pointer used to linked entries.
 
    int removeFlag;     // Flag used to indicate that this entry must be removed.
 
    // Client's connection socket.
    int socketTcpCnct;
 
    // Client information.
    struct sockaddr_in clientAddress;  
    
    time_t  timeStart;        // Time, in seconds when this session was created.
    time_t  timeLastRequest;  // Time, in seconds when the last request was received.
            
} tCLIENT_CNCT;

/////////////////////// FUNCTIONS ////////////////////////////

tCLIENT_CNCT * ServerCnctAlloc();

int ServerCnctFree(
    tCLIENT_CNCT * f_pCnct
    );
    
int ServerCnctUpdate();

#endif /*__SERVER_CLIENT_CNCT_H__*/