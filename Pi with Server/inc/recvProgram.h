#include <arpa/inet.h>
#include <stdbool.h> // bool, true, false
#include <netinet/in.h>
#include <string.h> // memset()
#include <sys/socket.h>
#include <sys/stat.h>

#define MAX_FILE_BUFF_SIZE 4096

void* thread_recvProgramFromServer(void* data);
