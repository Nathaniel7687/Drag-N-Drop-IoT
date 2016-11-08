#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	FILE *pFile = NULL;
                pFile = fopen( "./Pi with Pi/ipInfo.txt", "r" );
                if( pFile != NULL )
                {
                    char strTemp[255];
                    char *pStr;

                    while( !feof( pFile ) )
                    {
                        pStr = fgets( strTemp, sizeof(strTemp), pFile );
                        printf( "%s", pStr );
                    }
                    fclose( pFile );
                }
                else
                {
                    //에러 처리
                }

	
	return 0;
}
