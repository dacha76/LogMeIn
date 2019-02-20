/************************************************************\
 * File: aor_server_rc.h
 * 
 * Description: 
 * 
 *    This file contains the return code used by the aorServer
 * application.
 * 
\************************************************************/

// Expected return code if no error occurs.
#define cAOR_SERVER_RC_OK                   0x00000000

// Error codes
#define cAOR_SERVER_RC_FILE_NOT_FOUND       0x00000001
#define cAOR_SERVER_RC_FILE_WRITE_ERROR     0x00000002
#define cAOR_SERVER_RC_FILE_READ_ERROR      0x00000003
#define cAOR_SERVER_RC_JSON_ENTRY_NOT_FOUND 0x00000004
