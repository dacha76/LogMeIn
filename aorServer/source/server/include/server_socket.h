/************************************************************\
 * File: server_socket.h
 * 
 * Description: 
 * 
 * This file contains TCP socket relasted definitions, structures 
 * and function prototypes.
 * 
\************************************************************/
#ifndef __SERVER_SOCKET_H__
#define __SERVER_SOCKET_H__

#include <stdio.h>

//////////////////////// DEFINITIONS /////////////////////////////
#define cSERVER_SOCKET_UDP_PORT           0x5200
#define cSERVER_SOCKET_MAX_PENDING_CNCT   5

/////////////////// FUNCTIONS PROTOTYPES /////////////////////////

int ServerSocketInit();
int ServerSocketPoll();

void ServerSocketTerminate();


#endif /*__SERVER_SOCKET_H__*/