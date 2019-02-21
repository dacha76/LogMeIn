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
    int testCaseIdx;
        
} tTEST_CLIENT;

typedef struct {
    
    char addressOfRecord[128];
    
    char expectedAnswer[2048];
        
} tTEST_CLIENT_CASE_AOR;

/////////////////////// FUNCTIONS ////////////////////////////

int ClientInit(
    tTEST_CLIENT * f_pClient,
    int f_testCaseIdx
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
