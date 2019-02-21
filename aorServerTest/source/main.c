#include <stdio.h>
#include "../include/server_test.h"
#include "../include/server_test_rc.h"

int main(int argc, char **argv)
{
    int returnCode;
    
    printf("Test 1, opening 8 connection, sending 1024 req: ");
	returnCode = Test1();
    if (returnCode != cAOR_SERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
    
    printf("Test 0, sub-test 1: 1 Query, No timeout: ");
	returnCode = Test0( 0 );
    if (returnCode != cAOR_SERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
    
    printf("Test 0, sub-test 2: 1 Query, sleep=10sec: ");
	returnCode = Test0( 10 );
    if (returnCode != cAOR_SERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
        
	return 0;
}
