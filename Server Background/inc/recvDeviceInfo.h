#include <arpa/inet.h>
#include <stdbool.h>    // bool, true, false
#include <netinet/in.h>
#include <string.h>     // memset()
#include <sys/socket.h>
#include <termios.h>

enum {
    SENSOR = 1,
    ACTUATOR = 2  
};

typedef struct Sensor {
    int     ultrasonic;
    int     ir;
    int     humidity;
    int     temperature;
    float   heatindex;
    int     light;
    int     gas;
} Sensor;

typedef struct Actuator {
    int     buzzer;
    int     fan;
    int     servo;
} Actuator;

int client_fd;
int server_fd;
struct sockaddr_in client_addr;
struct sockaddr_in server_addr;

void* thread_recvDeviceInfoFromClient(void*);
void* thread_recvData(void*);

void openDevice();
void readPacket();
void setDataFromDevice();
void recvDeviceInfoToServer();
