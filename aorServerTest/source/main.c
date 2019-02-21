#include <stdio.h>
#include "../include/server_test.h"
#include "../include/server_test_rc.h"

int main(int argc, char **argv)
{
    int returnCode;
    
    printf("Test 0.1: 1 Valid Query: ");
	returnCode = Test0( 0 );
    if (returnCode != cSERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");

    printf("Test 0.2: 1 Invalid Query: ");
	returnCode = Test0( 1 );
    if (returnCode != cSERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
    
    printf("Test 1: 1 Query, sleep=15sec, connection timeout test: ");
	returnCode = Test1();
    if (returnCode != cSERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
    
    printf("Test 2, opening 8 connection, sending 2048 req: ");
	returnCode = Test2();
    if (returnCode != cSERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
        

    printf("Test 3: 1 Query comprised of multiple AORs: ");
	returnCode = Test3();
    if (returnCode != cSERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
            
	return 0;
}
