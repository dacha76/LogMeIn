/************************************************************\
 * File: server_log.h
 * 
 * Description: 
 * 
 * This file contains log relasted definitions, structures 
 * and function prototypes.
 * 
\************************************************************/
#ifndef __SERVER_LOG_H__
#define __SERVER_LOG_H__

#include <stdio.h>

//////////////////////// DEFINITIONS /////////////////////////////
#define cSERVER_LOG_FILE_NAME           "server_log.txt"

/////////////////// FUNCTIONS PROTOTYPES /////////////////////////
int ServerLogInit();
void ServerLog(
    char * f_pLogString 
    );
void ServerLogError(
    char * f_pErrorSource,
    int f_error
    );
#endif /*__SERVER_LOG_H__*/