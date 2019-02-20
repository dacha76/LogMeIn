/************************************************************\
 * File: aor_server_rc.h
 * 
 * Description: 
 * 
 *    This file contains the return code used by the aorServer
 * application.
 * 
\************************************************************/
#ifndef __AOR_SERVER_RC_H__
#define __AOR_SERVER_RC_H__

// Expected return code if no error occurs.
#define cAOR_SERVER_RC_OK                           0x00000000

// Error codes
#define cAOR_SERVER_RC_FILE_NOT_FOUND               0x00000001
#define cAOR_SERVER_RC_FILE_WRITE_ERROR             0x00000002
#define cAOR_SERVER_RC_FILE_READ_ERROR              0x00000003
#define cAOR_SERVER_RC_JSON_ENTRY_NOT_FOUND         0x00000004
#define cAOR_SERVER_RC_JSON_ENTRY_AOR_NOT_FOUND     0x00000005
#define cAOR_SERVER_RC_JSON_ENTRY_PARSING_ERROR     0x00000006
#define cAOR_SERVER_RC_JSON_ENTRY_NUMBER_INVALID    0x00000007
#define cAOR_SERVER_RC_DUMP_FILE_MALLOC_ERROR       0x00000008
#define cAOR_SERVER_RC_DUMP_FILE_SIZE_ERROR         0x00000009
#define cAOR_SERVER_RC_CNCT_REMOVE_ERROR            0x0000000A

#endif /*__AOR_SERVER_RC_H__*/