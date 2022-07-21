#include <Servo.h>

/* constants */
const int SWITCH_PIN = 12; /* set the pin numbers */
const int LID_SERVO_PIN = 11;
const int SWITCH_SERVO_PIN = 10;
const int SPEAKER_PIN = 9;
const int OPEN = 35; /* the angle for the lid to be open */
const int CLOSED = 80; /* the angle for the lid to be closed */
const int PUSHED = 180; /* the angle for the arm to push the switch */
const int INSIDE = 60; /* the angle for the arm to be insdide the box */

/* variables */
Servo lidServo; /* for control of the lid */
Servo switchServo; /* for control of switch flipper */
int lidPos; /* lid servo position */
int switchPos; /* switch servo position */
int delayTime; /* how long for servos to delay between writes */

void phrase1()
{
    int k = random(1000,2000);

    for (int i = 0; i <= random(100,2000); i++)
    {
        tone(SPEAKER_PIN, k+(-i*2));
        delay(random(.9,2));
    }

    for (int i = 0; i <= random(100,1000); i++)
    {
        tone(SPEAKER_PIN, k + (i * 10));
        delay(random(.9,2));
    }
}

void phrase2()
{
    int k = random(1000,2000);

    for (int i = 0; i <= random(100,2000); i++)
    {
        tone(SPEAKER_PIN, k+(i*2));
        delay(random(.9,2));
    }

    for (int i = 0; i <= random(100,1000); i++)
    {
        tone(SPEAKER_PIN, k + (-i * 10));
        delay(random(.9,2));
    }
}

/*
* Note: I DID NOT write this function or functions phrase1 and
* phrase2, I found them on this website:
*
* https://www.instructables.com/R2D2-Sound-Generator/
*/
void playR2D2Sound()
{
    int K = 2000;

    switch (random(1,7))
    {
        case 1:phrase1(); break;
        case 2:phrase2(); break;
        case 3:phrase1(); phrase2(); break;
        case 4:phrase1(); phrase2(); phrase1();break;
        case 5:phrase1(); phrase2(); phrase1(); phrase2(); phrase1();break;
        case 6:phrase2(); phrase1(); phrase2(); break;
    }

    for (int i = 0; i <= random(3, 9); i++)
    {
        tone(SPEAKER_PIN, K + random(-1700, 2000));
        delay(random(70, 170));
        noTone(SPEAKER_PIN);
        delay(random(0, 30));
    }
    
    noTone(SPEAKER_PIN);
    delay(random(0, 750));
}

/*
* opening the lid requires going from 0 degrees to 45 degrees
*/
void openLid()
{
    /* pick a random speed at which to open the lid */
    switch (random(0, 3))
    {
        case 0:
          delayTime = 0;
          break;

        case 1:
          delayTime = 15;
          break;

        case 2:
          delayTime = 25;
          break;
    }

    for (lidPos = CLOSED; lidPos >= OPEN; lidPos--)
    {
        lidServo.write(lidPos);
        delay(delayTime);
    }
}

/*
* closing the lid requires going from 45 degrees back to 0
*/
void closeLid()
{
    /* pick a random speed at which to close the lid */
    switch (random(0, 3))
    {
        case 0:
            delayTime = 5;
            break;

        case 1:
            delayTime = 15;
            break;

        case 2:
            delayTime = 25;
            break;
    }

    for (lidPos = OPEN; lidPos <= CLOSED; lidPos++)
    {
        lidServo.write(lidPos);
        delay(delayTime);
    }
}

/*
* flipping the switch requires the servo to move from 0 to 45 degrees, and then
* back from 45 degrees to 0
*/
void flipSwitch()
{
    /* generate random delay */
    switch (random(0, 3))
    {
        case 0:
            delayTime = 0;
            break;

        case 1:
            delayTime = 10;
            break;
    }

    /* flip the switch */
    for (switchPos = INSIDE; switchPos <= PUSHED; switchPos++)
    {
        switchServo.write(switchPos);
        delay(delayTime);
    }

    /* generate random delay */
    switch (random(0, 3))
    {
        case 0:
            delayTime = 0;
            break;

        case 1:
            delayTime = 10;
            break;

        case 2:
            delayTime = 20;
            break;
    }

    delay(random(0, 1000));

    /* bring the arm back in */
    for (switchPos = PUSHED; switchPos >= INSIDE; switchPos--)
    {
        switchServo.write(switchPos);
        delay(delayTime);
    }
}

void setup()
{
    /* setup pins used for I/O */
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    pinMode(SPEAKER_PIN, OUTPUT);
    
    /* for the "random" noises */
    randomSeed(analogRead(0));
    
    /* setup the servos */
    switchServo.attach(SWITCH_SERVO_PIN);
    switchServo.write(INSIDE);
    lidServo.attach(LID_SERVO_PIN);
    lidServo.write(CLOSED);
}

void loop()
{
    if (!digitalRead(SWITCH_PIN)) /* if the switch is switched, turn it off! */
    {
        delay(random(100, 1000));
        playR2D2Sound();
        openLid();
        flipSwitch();
        playR2D2Sound();
        delay(random(50, 750));
        closeLid();
    }
}
