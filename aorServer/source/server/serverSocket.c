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

#include "../../include/aor_server_rc.h"
#include "include/server.h"
#include "include/server_socket.h"
#include "include/server_cnct.h"

///////////////////// DEFINITIONS //////////////////////////

/////////////////// STATIC PROTOTYPES //////////////////////

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
                if (listen(pServerCtx->socketTcp, cSERVER_SOCKET_MAX_PENDING_CNCT)<0)
                {
                    returnCode = cAOR_SERVER_RC_SOCKET_ERROR_LISTEN;
                }
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
    tCLIENT_CNCT * pCnct = pServerCtx->pClientCnct;
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
    for(int i=0; i<pServerCtx->numClientCnct; i++)
    {
        FD_SET(pCnct->socketTcpCnct, &serverFds);
        
        if(pCnct->socketTcpCnct > maxSocketDescriptor)
            maxSocketDescriptor = pCnct->socketTcpCnct;
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
            if (socketCnct)
            {
                // Add a new connection for that socket.
                pCnct = ServerCnctAdd();
                if (pCnct)
                {
                    // Configure the connection.
                    pCnct->clientAddress = address;
                    pCnct->socketTcpCnct = socketCnct;
                }
                else
                    returnCode = cAOR_SERVER_RC_CNCT_ADD_ERROR;
            }
            
            // Check if we have activity on the client connection.
            pCnct = pServerCtx->pClientCnct;
            
            for (int i = 0; i < pServerCtx->numClientCnct; i++)   
            {   
                if (FD_ISSET( pCnct->socketTcpCnct , &serverFds))   
                {   
                    char buffer[1024] = { 0 };
                    int numBytesRead = 0;
                    
                    numBytesRead = read(pCnct->socketTcpCnct, buffer, sizeof(buffer));
                    if ( numBytesRead < cSERVER_JSON_AOR_VALUE_NUM_CHAR )
                    {
                        // This is bad, we did not get enough data for a valid AOR.
                        returnCode = cAOR_SERVER_RC_SOCKET_ERROR_READ;
                    }
                    else
                    {
                        tJSON_ENTRY * pJsonEntry;
                        
                        printf("Retrieved pClientReq of length %i:\n", numBytesRead);
                        printf("%s", buffer);
                        
                        // Process the request.
                        pJsonEntry = ServerJsonEntryLookup(buffer);
                        if (pJsonEntry)
                        {
                            // We found a match.
                            // Send back the JSON object associated to the received address of record.
                            send(pCnct->socketTcpCnct, pJsonEntry->pJson, pJsonEntry->entryLength, 0 );   
                        }
                    } 
                }   
            }
        }
    }
    else if (selectResult < 0)
    {
        returnCode = cAOR_SERVER_RC_SOCKET_ERROR_SELECT;
    }

    // Check if we have some connections in timeout.
    if (returnCode == cAOR_SERVER_RC_OK)
    {
        time_t  timeCurrent;
        int numClientCnctOriginal; // Number of client may change in the context.
        tCLIENT_CNCT * pNext;
        
        // Look for connection timeout 
        time(&timeCurrent);
        
        // Loop through all active connections.
        pCnct = pServerCtx->pClientCnct;
        numClientCnctOriginal = pServerCtx->numClientCnct;
        
        for ( int i=0; i<numClientCnctOriginal; i++)
        {
            // Save right away the next entry in case we release the current entry.
            pNext = pCnct->pNext;
            
            // Check for timeout.
            if ((timeCurrent - pCnct->timeLastRequest) > cSERVER_CLIENT_CNCT_TIMEOUT_MS)
            {
                // Connection in timeout... remove from list.
                returnCode = ServerCnctRemove(pCnct);
                if (returnCode != cAOR_SERVER_RC_OK)
                    break;
            }
            
            // Move to the next connection.
            pCnct = pNext;
        }
    }
    
    return returnCode;
}
    
 