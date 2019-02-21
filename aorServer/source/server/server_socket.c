/************************************************************\
 * File: serverSocket.c
 * 
 * Description: 
 * 
 * This file contains methods used manage client connections. 
 * 
\************************************************************/
#include <sys/socket.h>
#include <sys/time.h>
#include <stdlib.h>


#include "../../include/server.h"
#include "../../include/server_rc.h"
#include "../../include/server_log.h"
#include "../../include/server_socket.h"

///////////////////// DEFINITIONS //////////////////////////

/////////////////// STATIC PROTOTYPES //////////////////////
static long _GetTimeUs();

/////////////////////// FUNCTIONS //////////////////////////

/************************************************************\
  Function: ServerSocketInit
\************************************************************/
int ServerSocketInit( )
{
    int returnCode = cAOR_SERVER_RC_OK;
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    
    // Create a socket.
    pServerCtx->socketTcp = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP );
    if (pServerCtx->socketTcp)
    {
        int opt = 1;
        
        // Good habit to allow reuse of address.
        if(setsockopt(pServerCtx->socketTcp, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) >= 0)   
        {
            // Bind the socket.
            pServerCtx->socketAddr.sin_family = AF_INET; 
            pServerCtx->socketAddr.sin_addr.s_addr = INADDR_ANY; 
            pServerCtx->socketAddr.sin_port = htons( cSERVER_SOCKET_UDP_PORT ); 
            
            if (!bind(pServerCtx->socketTcp, (struct sockaddr *)&pServerCtx->socketAddr, sizeof(pServerCtx->socketAddr)))
            {
                // Socket has been bound to our IP, 
                if (listen(pServerCtx->socketTcp, cSERVER_SOCKET_MAX_PENDING_CNCT) >= 0)
                {
                    char bufferLog[256];
                    sprintf(bufferLog, "Server listening on all IPs, port=%d", cSERVER_SOCKET_UDP_PORT );
                    ServerLog(bufferLog);
                }
                else
                    returnCode = cAOR_SERVER_RC_SOCKET_ERROR_LISTEN;
            }
            else
                returnCode = cAOR_SERVER_RC_SOCKET_ERROR_BIND;
        }
        else    
            returnCode = cAOR_SERVER_RC_SOCKET_ERROR_SOCKOPT;
    }
    else
        returnCode = cAOR_SERVER_RC_SOCKET_ERROR;
       
    return returnCode;
}


/************************************************************\
  Function: ServerSocketTerminate
\************************************************************/
void ServerSocketTerminate()
{
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    
    // Close the server socket used to receive connections
    if (pServerCtx->socketTcp)
        close(pServerCtx->socketTcp);
}



/************************************************************\
  Function: ServerSocketPoll
\************************************************************/
int ServerSocketPoll()
{
    int returnCode = cAOR_SERVER_RC_OK;
    AOR_SERVER_CTX * pServerCtx = ServerGetCtx();
    tCLIENT_CNCT * pCnct = NULL;
//    tCLIENT_CNCT ClientCnct[2];
    struct timeval timeout;
    int selectResult;
    
    // Set of socket descriptors use for non-blocking operation.
    fd_set serverFds;  
    int maxSocketDescriptor;

    //clear the socket set  
    FD_ZERO(&serverFds);   
  
    //add master socket to set  
    FD_SET(pServerCtx->socketTcp, &serverFds);   
    maxSocketDescriptor = pServerCtx->socketTcp;   
    
    // add any connection we have active.
    pCnct = pServerCtx->pClientCnct;
    while (pCnct != NULL)
    {
        FD_SET(pCnct->socketTcpCnct, &serverFds);
        
        if(pCnct->socketTcpCnct > maxSocketDescriptor)
            maxSocketDescriptor = pCnct->socketTcpCnct;
            
        pCnct = pCnct->pNext;
    }
    
    // Now, wait for activity on one of the sockets , timeout is NULL so we are blocking.  
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    
    selectResult = select( maxSocketDescriptor + 1 , &serverFds , NULL , NULL , &timeout);
    if (selectResult > 0)
    {
        // We got activity.
        
        // Did we get a new connection request from a client.
        if (FD_ISSET(pServerCtx->socketTcp, &serverFds))   
        {
            int socketCnct;
            socklen_t addrlen;
            struct sockaddr_in address;          
            
            socketCnct = accept(pServerCtx->socketTcp, (struct sockaddr *)&address, &addrlen);
            if (socketCnct >= 0)
            {
                // Add a new connection for that socket.
                pCnct = ServerCnctAlloc();
                if (pCnct)
                {
                    char buffer[256];
                    
                    sprintf(buffer, "New Connection id=%d from ip=%s, port=%d", 
                        socketCnct,
                        inet_ntoa(address.sin_addr),
                        ntohs (address.sin_port)
                        );
                    // Log the new connection.
                    ServerLog(buffer);
                    
                    // Configure the connection.
                    pCnct->clientAddress = address;
                    pCnct->socketTcpCnct = socketCnct;
                }
                else
                    returnCode = cAOR_SERVER_RC_CNCT_ADD_ERROR;
            }
            else
                returnCode = cAOR_SERVER_RC_CNCT_ADD_ERROR;
        }
        
        // If all went well, continue with the connection.
        if ( returnCode == cAOR_SERVER_RC_OK)
        {
            pCnct = pServerCtx->pClientCnct;
            while ( pCnct != NULL )   
            {   
                if (FD_ISSET( pCnct->socketTcpCnct , &serverFds))   
                {   
                    char buffer[1024] = { 0 };
                    int numBytesRead = 0;
                    
                    numBytesRead = recv(pCnct->socketTcpCnct, buffer, sizeof(buffer), 0);
                    if ( numBytesRead < cSERVER_JSON_AOR_VALUE_NUM_CHAR )
                    {
                        // Tests have shown that receiving 0 bytes correspond to the 
                        // client closing its connection.
                        if (numBytesRead == 0)
                        {
                            char buffer[256];
                    
                            // Connection in timeout... remove from list.
                            sprintf(buffer, "Connection id=%d disconnected from server", 
                                pCnct->socketTcpCnct
                                );
                            // Log the new connection.
                            ServerLog(buffer);                        
                    
                            // Flag the entry as an entry to remove.
                            pCnct->removeFlag = 1;
                        }
                        else
                        {
                            // This is bad, we did not get enough data for a valid AOR.
                            returnCode = cAOR_SERVER_RC_SOCKET_ERROR_READ;
                        }
                    }                
                    else
                    {
                        tJSON_ENTRY * pJsonEntry;
                        char logBuffer[256];
                        long timeUs;
                        long timeUsStop;
                        
                        // Log the reception of new request.
                        time(&pCnct->timeLastRequest);  
                        pServerCtx->Stats.numLookupRequest++;

                        sprintf(logBuffer, "Request Rcvd from id=%d", 
                            pCnct->socketTcpCnct
                            );
                        ServerLog(logBuffer);                        
                        
                        // Time the processing time required for stats purposes.
                        timeUs = _GetTimeUs();
                        
                        // Process the request.
                        pJsonEntry = ServerJsonEntryLookup(buffer);
                        if (pJsonEntry)
                        {
                            // We found a match.
                            // Send back the JSON object associated to the received address of record.
                            send(pCnct->socketTcpCnct, pJsonEntry->pJson, pJsonEntry->entryLength, 0 );   
                        }
                        else
                        {
                            // Lookup failed.
                            pServerCtx->Stats.numLookupEntryNotFound++;
                            
                            sprintf(logBuffer, "ERROR: Lookup failed for connection id=%d", 
                                pCnct->socketTcpCnct
                                );
                            // Log the new connection.
                            ServerLog(logBuffer);                        
                        }
                        
                        // Udpate stats.
                        timeUsStop = _GetTimeUs();
                        timeUs = timeUsStop - timeUs;
                        
                        pServerCtx->Stats.lookupRequestTotalTimeUs += timeUs;
                        
                        if (timeUs < pServerCtx->Stats.lookupRequestMinTimeUs)
                            pServerCtx->Stats.lookupRequestMinTimeUs = timeUs;
                         
                        if (timeUs > pServerCtx->Stats.lookupRequestMaxTimeUs)
                            pServerCtx->Stats.lookupRequestMaxTimeUs = timeUs;
                    } 
                    
                    if (returnCode != cAOR_SERVER_RC_OK)
                        break;
                }
                
                // Move to the next entry.
                pCnct = pCnct->pNext;
            }                
        }

    }
    else if (selectResult < 0)
    {
        returnCode = cAOR_SERVER_RC_SOCKET_ERROR_SELECT;
    }
    
    return returnCode;
}
    
 
 
 /************************************************************\
  * Static Function: _GetTimeUs
  * 
  * Returns time in microseconds.
  * 
\************************************************************/
static long _GetTimeUs()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}