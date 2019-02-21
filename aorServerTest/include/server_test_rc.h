/************************************************************\
 * File: aor_server_test_rc.h
 * 
 * Description: 
 * 
 *    This file contains the return code used by the aorServerTest
 * application.
 * 
\************************************************************/
#ifndef __AOR_SERVER_TEST_RC_H__
#define __AOR_SERVER_TEST_RC_H__

// Expected return code if no error occurs.
#define cAOR_SERVER_TEST_RC_OK                          0x00000000

// Error codes
#define cAOR_SERVER_TEST_RC_SOCKET_ERROR                0x00000001
#define cAOR_SERVER_TEST_RC_SOCKET_ERROR_CONNECT        0x00000002
#define cAOR_SERVER_TEST_RC_SOCKET_ERROR_WRITE          0x00000003
#define cAOR_SERVER_TEST_RC_TEST_ERROR                  0x00000004

#endif /*__AOR_SERVER_TEST_RC_H__*/