#include "recvDeviceInfo.h"

//int client_fd;
//int server_fd;
//struct sockaddr_in client_addr;
//struct sockaddr_in server_addr;

int main()
{
    pthread_t p_thread;
    int tid;
    int status;

    tid = pthread_create(&p_thread, NULL, thread_recvDeviceInfoFromClient, NULL);
    if (tid < 0) {
        perror("thread_recvDeviceInfoFromClient() create error");
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

void *thread_recvDeviceInfoFromClient(void *data)
{
    printf("> Create recvDeviceInfoFromClient thread\n");

    SocketInfo sockInfo;
    if ((sockInfo.server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("> Fail work to create socket fd!\n");
        exit(1);
    }

    printf("> Create server socket fd: %d\n", sockInfo.server_fd);

    memset((void *)&sockInfo.server_addr, 0x00, sizeof(struct sockaddr_in));
    sockInfo.server_addr.sin_family = AF_INET;
    sockInfo.server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockInfo.server_addr.sin_port = htons(12121);

    bind(sockInfo.server_fd, (struct sockaddr *)&sockInfo.server_addr, sizeof(struct sockaddr_in));
    listen(sockInfo.server_fd, 5);

    while (true)
    {
        socklen_t client_size = sizeof(struct sockaddr_in);
        sockInfo.client_fd = accept(sockInfo.server_fd, (struct sockaddr *)&sockInfo.client_addr, &client_size);

        if (sockInfo.client_fd == -1)
        {
            perror("> Accept error");
            continue;
        }

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, thread_recvData, (void *)&sockInfo);
        pthread_detach(thread_id);
    }

    pthread_exit((void *)0);
}

void *thread_recvData(void *data)
{
    SocketInfo sockInfo = *((SocketInfo *)data);
    int timeout = 0;

    bool initStatus = false;
    int distinction = 0;
    Sensor sensor;
    Actuator actuator;

    char query[1024];
    MYSQL connection;

    if (mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0) == NULL)
    {
        printf("> Fail to connect mysql server.\n");
        exit(1);
    }

    while (true)
    {
        if (!initStatus)
        {
            if (read(sockInfo.client_fd, &distinction, sizeof(distinction)) > 0)
            {
                initStatus = true;
            }
        }

        if (distinction == SENSOR)
        {
            if (read(sockInfo.client_fd, &sensor, sizeof(Sensor)) > 0)
            {
                timeout = 0;
                
                // INSERT QUERY IN SensorLog
                sprintf(query, "INSERT INTO SensorLog VALUES(");
                // Current Time
                sprintf(query, "%sNOW(2), ", query);
                // Client IP Address
                sprintf(query, "%s0x%X, ", query, htonl(sockInfo.client_addr.sin_addr.s_addr));

                if (sensor.ultrasonic == 0)
                {
                    sprintf(query, "%s%s, ", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d, ", query, sensor.ultrasonic);
                }

                if (sensor.ir == 0)
                {
                    sprintf(query, "%s%s, ", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d, ", query, sensor.ir - 1);
                }

                if (sensor.temperature == 0)
                {
                    sprintf(query, "%s%s, ", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d, ", query, sensor.temperature);
                }

                if (sensor.humidity == 0)
                {
                    sprintf(query, "%s%s, ", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d, ", query, sensor.humidity);
                }

                if (sensor.heatindex == 0)
                {
                    sprintf(query, "%s%s, ", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%.2f, ", query, sensor.heatindex);
                }

                if (sensor.light == 0)
                {
                    sprintf(query, "%s%s, ", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d, ", query, sensor.light);
                }

                if (sensor.gas == 0)
                {
                    sprintf(query, "%s%s", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d", query, sensor.gas);
                }

                // CLOSE QUERY
                sprintf(query, "%s)", query);
                mysql_query(&connection, query);

                printf("> Client(%s) is connected\n", inet_ntoa(sockInfo.client_addr.sin_addr));
                printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor.ultrasonic, sensor.ir);
                printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor.humidity, sensor.temperature);
                printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor.heatindex, sensor.light);
                printf("  Gas\t\t: %04d\n", sensor.gas);

                printf("  Query : %s\n", query);
                // printf("  Error: %s\n", mysql_error(&connection));
            }
            else
            {
                printf("  Client(%s) Timeout Count: %d\n", inet_ntoa(sockInfo.client_addr.sin_addr), timeout++);

                if (timeout > 60)
                {
                    printf("> Client(%s) is closed..\n", inet_ntoa(sockInfo.client_addr.sin_addr));
                    mysql_close(&connection);
                    close(sockInfo.client_fd);

                    return 0;
                }

                delay(1);
            }
        }
        else if (distinction == ACTUATOR)
        {
            if (read(sockInfo.client_fd, &actuator, sizeof(Actuator)) > 0)
            {
                timeout = 0;

                // INSERT QUERY IN ActuatorLog
                sprintf(query, "INSERT INTO ActuatorLog VALUES(");
                // Current Time
                sprintf(query, "%sNOW(2), ", query);
                // Client IP Address
                sprintf(query, "%s0x%X, ", query, htonl(sockInfo.client_addr.sin_addr.s_addr));

                if (actuator.fan == 0)
                {
                    sprintf(query, "%s%s, ", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d, ", query, actuator.fan);
                }

                if (actuator.servo == 0)
                {
                    sprintf(query, "%s%s, ", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d, ", query, actuator.servo);
                }

                if (actuator.buzzer == 0)
                {
                    sprintf(query, "%s%s", query, "NULL");
                }
                else
                {
                    sprintf(query, "%s%d", query, actuator.buzzer);
                }

                // CLOSE QUERY
                sprintf(query, "%s)", query);
                mysql_query(&connection, query);

                printf("> Client(%s) is connected\n", inet_ntoa(sockInfo.client_addr.sin_addr));
                printf("  Buzzer: %d\n", actuator.buzzer);
                printf("  Fan\t: %d\n", actuator.fan);
                printf("  Servo\t: %d\n", actuator.servo);

                printf("  Query : %s\n", query);
                // printf("  Error: %s\n", mysql_error(&connection));
            }
            else
            {
                printf("  Client(%s) Timeout Count: %d\n", inet_ntoa(sockInfo.client_addr.sin_addr), timeout++);

                if (timeout > 60)
                {
                    printf("> Client(%s) is closed..\n", inet_ntoa(sockInfo.client_addr.sin_addr));
                    mysql_close(&connection);
                    close(sockInfo.client_fd);

                    return 0;
                }

                delay(1);
            }
        }
    }
}
