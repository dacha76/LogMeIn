/************************************************************\
 * File: server_json.h
 * 
 * Description: 
 * 
 * This file contains  JSON relasted definitions, structures 
 * and function prototypes.
 * 
\************************************************************/
#ifndef __SERVER_JSON_H__
#define __SERVER_JSON_H__

#include <stdio.h>

//////////////////////// DEFINITIONS /////////////////////////////
#define cSERVER_JSON_AOR_STRING           "addressOfRecord"
#define cSERVER_JSON_AOR_VALUE_NUM_CHAR   30


//////////////////////// TYPEDEF /////////////////////////////
typedef struct {
    
    int key;          // Key used to speed up search for an entry
    int entryLength;  // pJson entry length
    const char * pJsonAoR;  // Pointer within pJson to the first address of record character
    const char * pJson;     // Complete JSON object 
        
} tJSON_ENTRY;

/////////////////////// FUNCTIONS ////////////////////////////

int ServerJsonEntryAdd(
    const char * f_pJson,
    tJSON_ENTRY * f_pJsonEntry 
    );
tJSON_ENTRY * ServerJsonEntryLookup(
    const char * f_pReqAor
    );
    
void ServerJsonEntryLog(
    FILE * f_pFileLog,
    tJSON_ENTRY * f_pJsonEntry 
    );
    
#endif /*__SERVER_JSON_H__*/