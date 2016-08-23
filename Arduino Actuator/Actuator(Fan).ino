/*
HG7881_Motor_Driver_Example - Arduino sketch

This example shows how to drive a motor with using HG7881 (L9110) Dual
Channel Motor Driver Module.  For simplicity, this example shows how to
drive a single motor.  Both channels work the same way.

This example is meant to illustrate how to operate the motor driver
and is not intended to be elegant, efficient or useful.

Connections:

Arduino digital output D10 to motor driver input B-IA.
Arduino digital output D11 to motor driver input B-IB.
Motor driver VCC to operating voltage 5V.
Motor driver GND to common ground.
Motor driver MOTOR B screw terminals to a small motor.

Related Banana Robotics items:

BR010038 HG7881 (L9110) Dual Channel Motor Driver Module
https://www.BananaRobotics.com/shop/HG7881-(L9110)-Dual-Channel-Motor-Driver-Module

https://www.BananaRobotics.com
*/

// functional connections
#define MOTOR_B_PWM 9 // Motor B PWM Speed --> Motor B Input A --> MOTOR B +
#define MOTOR_B_DIR 8 // Motor B Direction --> Motor B Input B --> MOTOR B -

// the actual values for "fast" and "slow" depend on the motor
#define PWM_LEVEL1 55  // arbitrary slow speed PWM duty cycle
#define PWM_LEVEL2 155 // arbitrary fast speed PWM duty cycle
#define PWM_LEVEL3 205  // arbitrary slow speed PWM duty cycle
#define PWM_LEVEL4 255  // arbitrary slow speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes

#define START_BIT1      0x66
#define START_BIT2      0x00
#define END_BIT1        0xF0
#define END_BIT2        0x0F
#define ACTUATOR_FAN    0xD8

int level = 0;
int TX_data[6] = { START_BIT1,      START_BIT2,
                   ACTUATOR_FAN,    0,
                   END_BIT1,        END_BIT2 };

void setup()
{
    Serial.begin(115200);

    pinMode(MOTOR_B_DIR, OUTPUT);
    pinMode(MOTOR_B_PWM, OUTPUT);
    digitalWrite(MOTOR_B_DIR, LOW);
    digitalWrite(MOTOR_B_PWM, LOW);

    while (!Serial);
    delay(1000);
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
            level = 0;

            digitalWrite(MOTOR_B_DIR, LOW);
            digitalWrite(MOTOR_B_PWM, LOW);
            isValidInput = true;
            break;

        case '1':
            level = 1;

            // always stop motors briefly before abrupt changes
            digitalWrite(MOTOR_B_DIR, LOW);
            digitalWrite(MOTOR_B_PWM, LOW);
            //delay(DIR_DELAY);
            // set the motor speed and direction
            digitalWrite(MOTOR_B_DIR, LOW); // direction = reverse
            analogWrite(MOTOR_B_PWM, PWM_LEVEL1); // PWM speed = slow
            isValidInput = true;
            break;

        case '2':
            level = 2;

            // always stop motors briefly before abrupt changes
            digitalWrite(MOTOR_B_DIR, LOW);
            digitalWrite(MOTOR_B_PWM, LOW);
            //delay(DIR_DELAY);
            // set the motor speed and direction
            //digitalWrite(MOTOR_B_DIR, LOW); // direction = reverse      
            analogWrite(MOTOR_B_PWM, PWM_LEVEL2); // PWM speed = fast
            isValidInput = true;
            break;

        case '3':
            level = 3;

            // always stop motors briefly before abrupt changes
            digitalWrite(MOTOR_B_DIR, LOW);
            digitalWrite(MOTOR_B_PWM, LOW);
            //delay(DIR_DELAY);
            // set the motor speed and direction
            //digitalWrite(MOTOR_B_DIR, LOW); // direction = reverse      
            analogWrite(MOTOR_B_PWM, PWM_LEVEL3); // PWM speed = fast
            isValidInput = true;
            break;

        case '4':
            level = 4;

            // always stop motors briefly before abrupt changes
            digitalWrite(MOTOR_B_DIR, LOW);
            digitalWrite(MOTOR_B_PWM, LOW);
            //delay(DIR_DELAY);
            // set the motor speed and direction
            //digitalWrite(MOTOR_B_DIR, LOW); // direction = reverse      
            analogWrite(MOTOR_B_PWM, PWM_LEVEL4); // PWM speed = fast
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

    delay(100);
}
