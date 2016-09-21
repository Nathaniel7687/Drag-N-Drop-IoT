#include <Servo.h> 

#define PIN_SERVO 10

#define START_BIT1      0x77
#define START_BIT2      0x00
#define END_BIT1        0xF0
#define END_BIT2        0x0F
#define ACTUATOR_SERVO  0xD0

int level = 1;
int TX_data[6] = { START_BIT1,      START_BIT2,
                   ACTUATOR_SERVO,  0,
                   END_BIT1,        END_BIT2 };

Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position 

void setup()
{
    Serial.begin(115200);
    myservo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object

    while (!Serial);
    delay(1000);

    myservo.write(0);
}

void loop()
{
    boolean isValidInput;

    do
    {
        // execute the menu option based on the character recieved
        switch (Serial.read())
        {
        case '0':
            level = 1;
            myservo.write(0);

            isValidInput = true;
            break;

        case '1':
            level = 2;
            myservo.write(45);
            
            isValidInput = true;
            break;

        case '2':
            level = 3;
            myservo.write(90);

            isValidInput = true;
            break;

        case '3':
            level = 4;
            myservo.write(135);

            isValidInput = true;
            break;

        case '4':
            level = 5;
            myservo.write(180);

            isValidInput = true;
            break;

        default:
            // wrong character! display the menu again!
            isValidInput = false;
            break;
        }
    } while (isValidInput == true);

    TX_data[3] = level;
    for (int i = 0; i < 6; i++) {
        Serial.write(TX_data[i]);
    }

    //delay(100);
}
