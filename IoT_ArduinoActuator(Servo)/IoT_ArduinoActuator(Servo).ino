/* Sweep
by BARRAGAN <http://barraganstudio.com>
This example code is in the public domain.

modified 8 Nov 2013
by Scott Fitzgerald
http://arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h> 

#define PIN_SERVO 10

#define START_BIT 0x6600
#define END_BIT 0xF00F
#define ACTUATOR_SERVO 0xD0

Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position 

void setup()
{
    Serial.begin(115200);
    myservo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object

    while (!Serial);
    delay(1000);
}

int level = 0;
void loop()
{
    boolean isValidInput;

    do
    {
        // execute the menu option based on the character recieved
        switch (Serial.read())
        {
        case '0':
            level = 0;
            myservo.write(0);

            isValidInput = true;
            break;

        case '1':
            level = 1;
            myservo.write(45);
            
            isValidInput = true;
            break;

        case '2':
            level = 2;
            myservo.write(90);

            isValidInput = true;
            break;

        case '3':
            level = 3;
            myservo.write(135);

            isValidInput = true;
            break;

        case '4':
            level = 4;
            myservo.write(180);

            isValidInput = true;
            break;

        default:
            // wrong character! display the menu again!
            isValidInput = false;
            break;
        }
    } while (isValidInput == true);


    Serial.print(START_BIT, HEX);
    char buf[3];
    sprintf(buf, "%02X", level);
    Serial.print(ACTUATOR_SERVO, HEX);
    Serial.print(buf);
    Serial.print(END_BIT, HEX);

    delay(100);
}
