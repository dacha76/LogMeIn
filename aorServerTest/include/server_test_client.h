/************************************************************\
 * File: server_test_client.h
 * 
 * Description: 
 * 
 *    This file contains the test client's definitions,
 * structures and function prototypes.
 * 
\************************************************************/
#ifndef __SERVER_TEST_CLIENT_H__
#define __SERVER_TEST_CLIENT_H__

/////////////////////// FUNCTIONS ////////////////////////////
#define cSERVER_TEST_SOCKET_UDP_PORT           0x5200

//////////////////////// TYPEDEF /////////////////////////////
typedef struct {
    
    // Client's socket.
    int socketTcp;
    
    char addressOfRecord[128];
        
} tTEST_CLIENT;

/////////////////////// FUNCTIONS ////////////////////////////

int ClientInit(
    tTEST_CLIENT * f_pClient,
    char * f_pAddressOfRecord
    );
int ClientSocketInit(
    tTEST_CLIENT * f_pClient
    );
    
void ClientTerminate(
    tTEST_CLIENT * f_pClient
    );    
void ClientSocketTerminate(
    tTEST_CLIENT * f_pClient
    );
#endif /*__SERVER_TEST_CLIENT_H__*/
