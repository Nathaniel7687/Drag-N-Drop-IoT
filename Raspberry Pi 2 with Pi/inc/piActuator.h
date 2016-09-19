#define USB_SERIAL "/dev/ttyACM1"
#define BAUD_RATE 115200
#define DATA_BIT 8
#define STOP_BIT 1
#define PARITY_BIT 0

typedef struct Sensor
{
    int ultrasonic;
    int ir;
    int humidity;
    int temperature;
    float heatindex;
    int light;
    int gas;
} Sensor;

void openDevice(int *);

void delay(float);
void printfln();
