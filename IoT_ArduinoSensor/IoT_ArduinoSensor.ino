#include "DHT.h"

#define START_BIT 0x7700
#define END_BIT 0xF00F
#define SENSOR_BIT_USD 0xD2
#define SENSOR_BIT_IRD 0xD3
#define SENSOR_BIT_DHT 0xD4
#define SENSOR_BIT_PTR 0xA0
#define SENSOR_BIT_GAS 0xA8

#define DHTPIN 48
#define DHTTYPE DHT11   // DHT 11

#define LIGHTPIN 0
#define IRDISPIN 38
#define IRLEDPIN 36

#define ECHOPIN 26
#define TRIGPIN 28

#define GASPIN 8

DHT dht(DHTPIN, DHTTYPE);

int preDistance;

#define EXIST_ULTRASONIC    0b00001;
#define EXIST_IR            0b00010;
#define EXIST_DHT           0b00100;
#define EXIST_LIGHT         0b01000;
#define EXIST_GAS           0b10000;

void setup()
{
    Serial.begin(115200);

    dht.begin();
    pinMode(IRDISPIN, INPUT);
    pinMode(IRLEDPIN, OUTPUT);
    pinMode(ECHOPIN, INPUT);
    pinMode(TRIGPIN, OUTPUT);   // Use LED indicator (if required)
    pinMode(LIGHTPIN, INPUT);
    pinMode(GASPIN, INPUT);

    while (!Serial);
    delay(1000);

    //Serial.println();
    //Serial.print("Test: ");
    //Serial.println(connectionList, BIN);
}

void loop()
{
    Serial.print(START_BIT, HEX);

    int connectionList = 0b00000;
    char buf[3];

    if (getUltrasonic()) {
        connectionList |= EXIST_ULTRASONIC;
    }

    if (getIR()) {
        connectionList |= EXIST_IR;
    }

    if (getHumidityTemperature()) {
        connectionList |= EXIST_DHT;
    }

    if (getLight()) {
        connectionList |= EXIST_LIGHT;
    }

    if (getGas()) {
        connectionList |= EXIST_GAS;
    }

    sprintf(buf, "%02X", connectionList);
    Serial.print(buf);
    Serial.print(END_BIT, HEX);

    delay(100);
}

int getUltrasonic()
{
    int maximumRange = 400; // Maximum range needed
    int minimumRange = 0; // Minimum range needed
    long duration, distance; // Duration used to calculate distance

    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIGPIN, LOW);
    duration = pulseIn(ECHOPIN, HIGH);

    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration / 58.2;

    if (distance >= maximumRange || distance <= minimumRange) {
        /* Send a negative number to computer and Turn LED ON
        to indicate "out of range" */
        //Serial.println("-1");
        distance = preDistance;
        //digitalWrite(pin, HIGH); // LED Control
    }
    else {
        /* Send the distance to the computer using Serial protocol, and
        turn LED OFF to indicate successful reading. */
        preDistance = distance;
        //digitalWrite(pin, LOW); // LED Control
    }

    char buf[5];

    sprintf(buf, "%04X", distance);
    Serial.print(SENSOR_BIT_USD, HEX);
    Serial.print(buf);

    return distance;
}

/******************************************************************************
* This function can be used with a panasonic pna4602m ir sensor
* it returns a zero if something is detected by the sensor, and a 1 otherwise
* The function bit bangs a 38.5khZ waveform to an IR led connected to the
* IRLEDPIN for 1 millisecond, and then reads the IR sensor pin to see if
* the reflected IR has been detected
******************************************************************************/
int getIR()
{
    int halfPeriod = 13; //one period at 38.5khZ is aproximately 26 microseconds
    int cycles = 38; //26 microseconds * 38 is more or less 1 millisecond
    int i;

    for (i = 0; i <= cycles; i++)
    {
        digitalWrite(IRLEDPIN, HIGH);
        delayMicroseconds(halfPeriod);
        digitalWrite(IRLEDPIN, LOW);
        delayMicroseconds(halfPeriod - 1);     // - 1 to make up for digitaWrite overhead    
    }

    char buf[3];
    int obstacle = digitalRead(IRDISPIN);

    sprintf(buf, "%02X", obstacle);
    Serial.print(SENSOR_BIT_IRD, HEX);
    Serial.print(buf);//display the results

    return obstacle;
}

int getHumidityTemperature()
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();

    int hic;

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
        h = 0;
        t = 0;
        hic = 0;
    }
    else {
        // Compute heat index in Celsius (isFahreheit = false)
        hic = dht.computeHeatIndex(t, h, false) * 100;
    }

    char buf[5];

    Serial.print(SENSOR_BIT_DHT, HEX);

    sprintf(buf, "%02X%02X", (int)h, (int)t);
    Serial.print(buf);

    sprintf(buf, "%04X", hic);
    Serial.print(buf);

    return h + t + hic;
}

int getLight()
{
    int light = analogRead(LIGHTPIN);
    char buf[5];

    sprintf(buf, "%04X", light);
    Serial.print(SENSOR_BIT_PTR, HEX);
    Serial.print(buf);

    return light;
}

int getGas()
{
    int gas = analogRead(GASPIN);
    char buf[5];

    sprintf(buf, "%04X", gas);
    Serial.print(SENSOR_BIT_GAS, HEX);
    Serial.print(buf);

    return gas;
}
