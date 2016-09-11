#include "recvDeviceInfo.h"
#include "webServer.h"

int client_fd;
int server_fd;
struct sockaddr_in client_addr;
struct sockaddr_in server_addr;

void *thread_recvDeviceInfoFromClient(void *data)
{
    printf("> Create recvDeviceInfoFromClient thread\n");

    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("> Fail work to create socket fd!\n");
        exit(1);
    }

    printf("> Create server socket fd: %d\n", server_fd);

    memset((void *)&server_addr, 0x00, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(12121);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    while (true)
    {
        socklen_t client_size = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_size);

        if (client_fd == -1)
        {
            perror("> Accept error");
            continue;
        }

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, thread_recvData, (void *)&client_fd);
        pthread_detach(thread_id);
    }

    pthread_exit((void *)0);
}

void *thread_recvData(void *data)
{
    int client_fd = *((int *)data);
    int timeout = 0;

    bool initStatus = false;
    int distinction = 0;
    Sensor sensor;
    Actuator actuator;

    char query[1024];
    MYSQL connection;

    mysql_init(&connection);
    mysql_real_connect(&connection, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, NULL, 0);

    while (true)
    {
        if (!initStatus)
        {
            if (read(client_fd, &distinction, sizeof(distinction)) > 0)
            {
                initStatus = true;
            }
        }

        if (distinction == SENSOR)
        {
            if (read(client_fd, &sensor, sizeof(Sensor)) > 0)
            {
                sprintf(query, "INSERT INTO SensorLog VALUES(NOW(), 0x%X, %d, %d, %d, %d, %.2f, %d, %d)",
                        inet_addr(inet_ntoa(client_addr.sin_addr)), sensor.ultrasonic, sensor.ir, sensor.temperature, sensor.humidity, sensor.heatindex, sensor.light, sensor.gas);
                mysql_query(&connection, query);

                printf("> Client(%s) is connected\n", inet_ntoa(client_addr.sin_addr));
                printf("  Ultrasonic\t: %03d\t\t IR\t\t: %d\n", sensor.ultrasonic, sensor.ir);
                printf("  Humidity\t: %02d\t\t Temperature\t: %02d\n", sensor.humidity, sensor.temperature);
                printf("  Heatindex\t: %02.2f\t\t Light\t\t: %03d\n", sensor.heatindex, sensor.light);
                printf("  Gas\t\t: %04d\n", sensor.gas);

                printf("  Query: %s\n", query);
            }
            else
            {
                printf("  Client(%s) Timeout Count: %d\n", inet_ntoa(client_addr.sin_addr), timeout++);

                if (timeout > 60)
                {
                    printf("> Client(%s) is closed..\n", inet_ntoa(client_addr.sin_addr));
                    mysql_close(&connection);
                    close(client_fd);
                }

                delay(1);
            }
        }
        else if (distinction == ACTUATOR)
        {
            if (read(client_fd, &actuator, sizeof(Actuator)) > 0)
            {
                sprintf(query, "INSERT INTO ActuatorLog VALUES(NOW(), 0x%X, %d, %d, %d)",
                        inet_addr(inet_ntoa(client_addr.sin_addr)), actuator.fan, actuator.servo, actuator.buzzer);
                mysql_query(&connection, query);

                printf("> Client(%s) is connected\n", inet_ntoa(client_addr.sin_addr));
                printf("  Buzzer: %d\n", actuator.buzzer);
                printf("  Fan\t: %d\n", actuator.fan);
                printf("  Servo\t: %d\n", actuator.servo);

                printf("  Query: %s\n", query);
            }
            else
            {
                printf("  Client(%s) Timeout Count: %d\n", inet_ntoa(client_addr.sin_addr), timeout++);

                if (timeout > 60)
                {
                    printf("> Client(%s) is closed..\n", inet_ntoa(client_addr.sin_addr));
                    mysql_close(&connection);
                    close(client_fd);
                }

                delay(1);
            }
        }
    }
}
