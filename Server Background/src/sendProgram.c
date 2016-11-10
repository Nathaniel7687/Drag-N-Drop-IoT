#include "sendProgram.h"

bool initStatus;
int sensor_fd;
int actuator_fd;
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

    memset((void*)&server_addr, 0x00, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12122);

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
            }

            printf("> Waiting the build..\n\n");
            while (access("/home/supercom2/Projects/Drag-N-Drop-IoT/Server Background/PiBuild/build.sh",     F_OK) == 0) {
                delay(1);
            }

            // TODO: Need to modify that send program both sensor and actuator.
            // This section is send program.
            {
                FILE* pFile = fopen("./PiBuild/ipInfo.txt", "r");
                if (pFile != NULL) {
                    char ipStr[45];
                    char tipStr[20] = "165.132.121.125";
                    bool init = false;
                    printf("\n> Open ipInfo.txt file.\n");

                    while (!feof(pFile)) {
                        fgets(ipStr, sizeof(ipStr), pFile);

                        if (!init) {
                            if ((sensor_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                                printf("> Fail work to create socket fd!\n");
                                exit(1);
                            }

                            printf("> Create server socket fd: %d\n", sensor_fd);

                            printf("> Sensor IP: %s", ipStr);
                            init = true;
                            server_addr.sin_addr.s_addr = inet_addr(tipStr);

                            if (connect(sensor_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                                perror("> Connect to Sensor Device error");
                                continue;
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

                            send(sensor_fd, &fileSize, sizeof(fileSize), 0);
                            while((readSize = fread(buff, 1, MAX_FILE_BUFF_SIZE, file)) > 0) {
                                readTotalSize += readSize;
                                send(sensor_fd, buff, readSize, 0);
                            }

                            printf("> Success file transfer.\n\n");
                            fclose(file);
                            remove("./PiBuild/sensor");
                            close(sensor_fd);
                        } else {
                            if ((actuator_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
                                printf("> Fail work to create socket fd!\n");
                                exit(1);
                            }
                            printf("> Create server socket fd: %d\n", actuator_fd);

                            printf("> Actuator IP: %s\n", ipStr);
                            server_addr.sin_addr.s_addr = inet_addr(tipStr);

                            if (connect(actuator_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                                perror("> Connect to Actuator Device error");
                                continue;
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

                            send(actuator_fd, &fileSize, sizeof(fileSize), 0);
                            while ((readSize = fread(buff, 1, MAX_FILE_BUFF_SIZE, file)) > 0) {
                                readTotalSize += readSize;
                                send(actuator_fd, buff, readSize, 0);
                            }

                            printf("> Success file transfer.\n\n");
                            fclose(file);
                            remove("./PiBuild/actuator");
                            close(actuator_fd);
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
    pthread_exit((void*)0);
}
