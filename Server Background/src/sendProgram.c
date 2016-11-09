#include "sendProgram.h"

bool initStatus;
int server_fd;
struct sockaddr_in server_addr;

int main()
{
    pthread_t p_thread;
    int tid;
    int status;

    tid = pthread_create(&p_thread, NULL, thread_sendProgramToClient, NULL);
    if (tid < 0) {
        perror("thread_sendProgramToClient() create error");
        exit(1);
    }

    pthread_join(p_thread, (void**)&status);

    return 0;
}

void delay(float time)
{
    struct timespec req = { 0 };
    double s;
    double ms;
    ms = modf(time, &s) * 1000000000;

    req.tv_sec = s;
    req.tv_nsec = ms;
    while (nanosleep(&req, NULL) && errno == EINTR)
        ;
}

void printfln()
{
    printf("\n");
}

void* thread_sendProgramToClient(void* data)
{
    printf("> Create manageProgramFromServer thread\n");

    while (true) {
        // TODO: Have to define path of Pi with Pi base code's directory.
        if (access("/home/supercom2/Projects/Drag-N-Drop-IoT/Server Background/PiBuild/build.sh", F_OK) == 0) {
            // This section is build program.
            {
                printf("> Start build the program.\n");
                int pid = fork();
                if (pid == 0) {
                    // TODO: Have to change build.sh path.
                    execl("/home/supercom2/Projects/Drag-N-Drop-IoT/Server Background/PiBuild/build.sh", "build.sh", NULL);
                    return 0;
                }

                remove("./PiBuild/build.sh");
            }

            // TODO: Need to modify that send program both sensor and actuator.
            // This section is send program.
            {
                if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                    printf("> Fail work to create socket fd!\n");
                    exit(1);
                }
                printf("> Create server socket fd: %d\n", server_fd);

                memset((void*)&server_addr, 0x00, sizeof(server_addr));
                server_addr.sin_family = AF_INET;

                FILE* pFile = fopen("./PiBuild/ipInfo.txt", "r");
                if (pFile != NULL) {
                    char strTemp[255];
                    char* pStr = NULL;
                    bool init = false;
                    printf("> Open ipInfo.txt file.\n");

                    while (!feof(pFile)) {
                        pStr = fgets(strTemp, sizeof(strTemp), pFile);
			printf("> Sensor IP: %s\n", pStr);

                        if (!init) {
                            init = true;
                            server_addr.sin_addr.s_addr = inet_addr(pStr);
                            server_addr.sin_port = htons(12122);

                            while (connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                                perror("> Connect to server error");
                                delay(1);
                            }

                            size_t fileSize = 0;
                            size_t readTotalSize = 0;
                            size_t readSize = 0;
                            FILE* file = fopen("./PiBuild/sensor", "rb");
                            char buff[MAX_FILE_BUFF_SIZE] = { '\0' };

                            fseek(file, 0, SEEK_END);
                            fileSize = ftell(file);
                            fseek(file, 0, SEEK_SET);
                            printf("> File size: %zuKB\n", fileSize);

                            send(server_fd, &fileSize, sizeof(fileSize), 0);
                            while (readTotalSize != fileSize) {
                                readSize = fread(buff, 1, MAX_FILE_BUFF_SIZE, file);
                                readTotalSize += readSize;
                                send(server_fd, buff, readSize, 0);
                            }

                            printf("> File sent\n");
                            close(server_fd);
                            fclose(file);
                            remove("./PiBuild/sensor");

                            pthread_exit((void*)0);
                        } else {
                            server_addr.sin_addr.s_addr = inet_addr(pStr);
                            server_addr.sin_port = htons(12122);

                            while (connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                                perror("> Connect to server error");
                                delay(1);
                            }

                            size_t fileSize = 0;
                            size_t readTotalSize = 0;
                            size_t readSize = 0;
                            FILE* file = fopen("./PiBuild/actuator", "rb");
                            char buff[MAX_FILE_BUFF_SIZE] = { '\0' };

                            fseek(file, 0, SEEK_END);
                            fileSize = ftell(file);
                            fseek(file, 0, SEEK_SET);
                            printf("> File size: %zuKB\n", fileSize);

                            send(server_fd, &fileSize, sizeof(fileSize), 0);
                            while (readTotalSize != fileSize) {
                                readSize = fread(buff, 1, MAX_FILE_BUFF_SIZE, file);
                                readTotalSize += readSize;
                                send(server_fd, buff, readSize, 0);
                            }

                            printf("> File sent\n");
                            close(server_fd);
                            fclose(file);
                            remove("./PiBuild/actuator");

                            pthread_exit((void*)0);
                        }
                    }
                    fclose(pFile);
                } else {
                    //에러 처리
                }

                remove("./PiBuild/ipInfo.txt");
            }
        } else {
            //perror("> Can't find build.sh");
        }
        delay(1);
    }
}
