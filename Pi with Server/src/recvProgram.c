#include "recvProgram.h"

int client_fd;
int server_fd;
struct sockaddr_in client_addr;
struct sockaddr_in server_addr;

int main () {
    pthread_t p_thread;
    int tid;
    int status;

    tid = pthread_create(&p_thread, NULL, thread_recvProgramFromServer, NULL);
    if (tid < 0)
    {
        perror("thread_recvProgramFromServer() create error");
        exit(1);
    }

    pthread_join(p_thread, (void **)&status);

    return 0;
}

void delay(float time)
{
    struct timespec req = {0};
    double s;
    double ms;
    ms = modf(time, &s) * 1000000000;

    req.tv_sec = s;
    req.tv_nsec = ms;
    while (nanosleep(&req, NULL) && errno == EINTR);
}

void printfln()
{
    printf("\n");
}

void *thread_recvProgramFromServer(void *data)
{
    printf("> Create manageProgramFromServer thread\n");

    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("> Fail work to create socket fd!\n");
        exit(1);
    }

    printf("> Create server socket fd: %d\n", server_fd);

    memset((void *)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(12122);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    while (true)
    {
        // This section is recieve program.
        {
            socklen_t client_size = sizeof(client_addr);
            client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_size);

            if (client_fd == -1)
            {
                perror("> Accept error");
		delay(1);
                continue;
            }

            printf("> Remove exsisting program.\n");
            size_t buffSize = MAX_FILE_BUFF_SIZE;
            size_t fileSize = 0;
            size_t readSize = 0;
            FILE *file = fopen("recvedProgram", "wb");
            char buff[MAX_FILE_BUFF_SIZE] = {'\0'};

            read(client_fd, &fileSize, sizeof(size_t));
            printf("> File size: %zuKB\n", fileSize);
            while (fileSize != 0)
            {
                if (fileSize < 512) {
                    buffSize = fileSize;
                }

                readSize = read(client_fd, buff, buffSize);
                fileSize -= readSize;
                fwrite(buff, sizeof(char), readSize, file);
            }
            close(client_fd);
            fclose(file);
            chmod("recvedProgram", 0777);
            printf("> Sucess file receive.\n");
        }

        // This section is run the program.
        {
            int pid = fork();
            if (pid == 0)
            {
                // TODO: Have to change the program path.
                execl("/home/nathaniel/Drag-N-Drop-IoT/Pi with Server/recvedProgram", "recvedProgram", NULL);
                return 0;
            }
            printf("> Run received program.\n");
        }
    }

    pthread_exit((void *)0);
}
