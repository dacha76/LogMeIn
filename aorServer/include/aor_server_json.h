/************************************************************\
 * File: aor_server_json.h
 * 
 * Description: 
 * 
 *    This file contains the aorServer application's JSON 
 * relasted definitions, structures and function prototypes.
 * 
\************************************************************/

//////////////////////// TYPEDEF /////////////////////////////
typedef struct {
    
    int key;                // Key used to speed up search for an entry
    int entryLength;        // JSON entry length
    char addrOfRecord[32];  // Address of Record used to validate our match
    char * pJson;           // Complete JSON object 
    
    
} tJSON_ENTRY;

/////////////////////// FUNCTIONS ////////////////////////////

