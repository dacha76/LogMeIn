/************************************************************\
 * File: server_test_rc.h
 * 
 * Description: 
 * 
 *    This file contains the return code used by the aorServerTest
 * application.
 * 
\************************************************************/
#ifndef __SERVER_TEST_RC_H__
#define __SERVER_TEST_RC_H__

// Expected return code if no error occurs.
#define cSERVER_TEST_RC_OK                          0x00000000

// Error codes
#define cSERVER_TEST_RC_SOCKET_ERROR                0x00000001
#define cSERVER_TEST_RC_SOCKET_ERROR_CONNECT        0x00000002
#define cSERVER_TEST_RC_SOCKET_ERROR_WRITE          0x00000003
#define cSERVER_TEST_RC_TEST_ERROR                  0x00000004
#define cSERVER_TEST_RC_SOCKET_ERROR_READ           0x00000005

#endif /*__SERVER_TEST_RC_H__*/