#include <stdio.h>
#include "../include/server_test.h"
#include "../include/server_test_rc.h"

int main(int argc, char **argv)
{
    int returnCode;
    
    printf("Test 0: 1 Query, No timeout: ");
	returnCode = Test0();
    if (returnCode != cAOR_SERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
    
    printf("Test 1: 1 Query, sleep=10sec, visually verify that connection timed out: ");
	returnCode = Test1();
    if (returnCode != cAOR_SERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
    
    printf("Test 2, opening 8 connection, sending 2048 req: ");
	returnCode = Test2();
    if (returnCode != cAOR_SERVER_TEST_RC_OK)
    {
        printf("ERROR 0x%08X\n\n", returnCode);
        return returnCode; 
    }
    else
        printf("OK\n\n");
        
	return 0;
}
