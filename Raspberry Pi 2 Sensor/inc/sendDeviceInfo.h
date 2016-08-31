#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h> // memset()
#include <sys/socket.h>
#include <termios.h>

#define USB_SERIAL      "/dev/ttyACM0"
#define BAUD_RATE       115200
#define DATA_BIT        8
#define STOP_BIT        1
#define PARITY_BIT      0

#define SEIRAL_MAX_BUFF 20

#define START_BIT1      0x77
#define START_BIT2      0x00
#define END_BIT1        0xF0
#define END_BIT2        0x0F

#define SENSOR_BIT_USD  0xD2
#define SENSOR_BIT_IR   0xD3
#define SENSOR_BIT_DHT  0xD4
#define SENSOR_BIT_PTR  0xA0
#define SENSOR_BIT_GAS  0xA8

enum {
    START_COL1 = 0,
    START_COL2 = 1,
    ULTRASONIC_COL = 2,
    IR_COL = 5,
    HT_COL = 7,
    LIGHT_COL = 12,
    GAS_COL = 15,
    END_COL1 = 18,
    END_COL2 = 19
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

int fd;
unsigned char data[SEIRAL_MAX_BUFF];
Sensor* sensor;

int server_fd;
struct sockaddr_in server_addr;

void* thread_sendDeviceInfoToServer(void* data);

void openDevice();
void readPacket();
void setDataFromPacket();
void sendSensorInfoToServer();

void delay(float);
void strncat_s(unsigned char*, unsigned char*, int, int);

void TEST_setSensorStruct();