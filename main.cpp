#include "mbed.h"
#include "PwmOut.h"
#include "uLCD_4DGL.h"
#include "rtos.h"
#include "Motor.h"
#include "PinDetect.h"
#include "ultrasonic.h"
#include "Speaker.h"

Serial pc(USBTX, USBRX);
Motor motorA(p21, p17, p15);
Motor motorB(p22, p19, p20);
Serial device(p13, p14);
Ticker ledTick;

DigitalOut frontLeftLED(p5);
DigitalOut frontRightLED(p8);
DigitalOut backLeftLED(p18);
DigitalOut backRightLED(p16);

volatile int commandReceived = 0;
volatile bool turning = false;
uLCD_4DGL uLCD(p9,p10,p30);

void dist(int distance){}

//Define necessary components for the robot
ultrasonic mu(p6, p7, .1, 1, &dist);


/*
 * Method to control the LEDs of the robot based on the global variable 'ledType'.
 * When the robot moves forward, two front LEDs light up.
 * When the robot moves backward, two rear LEDs light up.
 * When the robot turns left, two LEDs on left side light up.
 * When the robot turns right, two LEDs on right side light up.
 */
void ledController() {
    if (commandReceived == 3) {    //two front LEDs up when moving forward
        frontLeftLED = 1;
        frontRightLED = 1;
        backLeftLED = 0;
        backRightLED = 0;
    } else if (commandReceived == 4) { //two back LEDs up when moving backward
        frontLeftLED = 0;
        frontRightLED = 0;
        backLeftLED = 1;
        backRightLED = 1;
    } else if (commandReceived == 1) {  //turn left LEDs up
        frontLeftLED = 1;
        frontRightLED = 0;
        backLeftLED = 1;
        backRightLED = 0;
    } else if (commandReceived == 2) {  //turn right LEDs up
        frontLeftLED = 0;
        frontRightLED = 1;
        backLeftLED = 0;
        backRightLED = 1;
    } else {        //when idling
        frontLeftLED = 0;
        frontRightLED = 0;
        backLeftLED = 0;
        backRightLED = 0;
    }
    Thread::wait(1000);
}

/*
 * The method to play sound effects concurrently with the movement of the robot.
 * When the robot moves forward, play "Barbie Girl" song.
 * Whenever an obstacles is detected while moving forward, immediately silence the song and switch to another suitable sound effect.
 * When the robot moves backward or turns, a suitable beeping sound will play accordingly.
 */
void soundPlayer() {
    Speaker mySpeaker(p23);
    while (1) {
        if (commandReceived == 3) {   //forward song
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(415,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(330,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(415,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(554,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(440,0.5,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(0,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(370,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(311,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(370,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(494,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(415,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(370,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(330,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(0,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(330,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(277,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(330,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(370,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(277,0.5,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(0,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(370,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(330,0.3,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(415,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(370,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(415,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
            mySpeaker.PlayNote(0,0.4,1);
            if (commandReceived == 2) {
                continue;
            }
        } else if (commandReceived == 4) { //backward sound
            mySpeaker.PlayNote(1500,0.3,1);
            mySpeaker.PlayNote(1000,0.3,1);
        }
    }
}

/*
 * The method to control the EasyVR device.
 * The EasyVR device communicates using char. Specific characters match with specific default Command Wordset.
 * This method helps decipher EasyVR's messages and reflect those messages on the 'commandReceived' variable.
 */
void listener() {
    char rchar=0;
    //wake up device - needs more work and a timeout
    device.putc('b');
    while (device.getc()!='o') {
        device.putc('b');
        Thread::wait(200);
    }
    while (1) {
        device.putc('i'); //Start Recognition
        device.putc('C'); //Use Wordset 2 - basic movements
        while (device.readable()!=0) {}
        if (device.getc()=='s') {
            device.putc(' ');
            rchar=device.getc();
            if (rchar == 'A') {        //turn left
                commandReceived = 1;
                rchar = 0;
            } else if (rchar == 'B') { //turn right
                commandReceived = 2;
                rchar = 0;
            } else if (rchar == 'E') { //go forward
                commandReceived = 3;
                rchar = 0;
            } else if (rchar == 'F') { //go backward
                commandReceived = 4;
                rchar = 0;
            }
        }
        Thread::wait(200);
    }
}

/*
 * The method to control the DC motors based on the voice commands or when the robot meets an obstacle.
 * Control the robot to move forward, backward, or turn left, turn right.
 */
void motorControl() {
    while(1) {
        if (commandReceived == 1) { //turn left command 1
            motorA.speed(0.4);
            motorB.speed(-0.4);
            Thread::wait(1000);
            commandReceived = 0;
        }  else if (commandReceived == 2) { //turn right command 2
            motorA.speed(-0.4);
            motorB.speed(0.4);
            Thread::wait(1000);
            if (turning == false) {
                commandReceived = 0;
            } else {
                commandReceived = 2;
            }
        } else if (commandReceived == 3) { //forward command 3
            bool move = true;
            while (move == true) {
                int distance = mu.getCurrentDistance();
                if (distance > 10 && distance < 200) {  //turn right when meet obstacles
                    commandReceived = 2;
                    move = false;
                } else { // moves forward forever unless turning right when obstacles are met
                    motorA.speed(0.5);
                    motorB.speed(0.5);
                }
                Thread::wait(100);
            }
            commandReceived = 0;
        } else if (commandReceived == 4){  //backward command 4
            int j = 0;
            while (j < 2) { //2 seconds total
                motorA.speed(-0.4);
                motorB.speed(-0.4);
                j+=1;
                Thread::wait(1000);
            }
            commandReceived = 0;
        } else  {   //command 0
            motorA.speed(0);
            motorB.speed(0);
        }
    }
}

/*
 * The method to read the distance between the ultrasonic sensor and an object in the sensing range.
 * If the object is within [10,300] mm range from the sensor, then send a turning signal to the Mbed.
 * Otherwise, no turning signal will be fired to the Mbed.
 */
void sonarCheck() {
    while(1) {
        int distance = mu.getCurrentDistance();
        if (distance > 10 && distance < 300) {  //turn right when meet obstacles
            commandReceived = 2;
            turning = true;
        } else if (distance < 10 || distance > 300){
            turning = false;
        }
        Thread::wait(100);
    }
}

/*
 * Main function where the Mbed initiates the threads that control the EasyVR, motors, LEDs, and ultrasonic sensor
 */
int main() {
    uLCD.cls();
    uLCD.background_color(BLACK);
    uLCD.baudrate(3000000); //jack up baud rate to max for fast display

    mu.startUpdates();//start measuring the distance
    Thread listenerThread(listener);
    Thread soundThread(soundPlayer);
    Thread motorThread(motorControl);
    Thread sonarThread(sonarCheck);
    ledTick.attach(&ledController,0.2);

    int distance = 0;
    int lastCommand1 = commandReceived;
    int lastCommand2 = commandReceived;
    bool replaceFace = true;
    while(1) {
        lastCommand1 = lastCommand2;
        lastCommand2 = commandReceived;

        if (lastCommand1 != lastCommand2) {
            uLCD.cls();
            replaceFace = true;
        }

        if (commandReceived == 1 && replaceFace) { //turn left command 1
            uLCD.filled_circle(85, 25, 18, BLUE);
            uLCD.filled_circle(85, 65, 15, BLUE);
            replaceFace = false;
        }  else if (commandReceived == 2 && replaceFace) { //turn right command 2
            uLCD.filled_circle(85, 55, 15, RED);
            uLCD.filled_circle(85, 100, 18, RED);
            replaceFace = false;
        } else if (commandReceived == 3 && replaceFace) { //forward command 3
            uLCD.filled_circle(85, 40, 15, YELLOW);
            uLCD.filled_circle(85, 85, 15, YELLOW);
            uLCD.filled_circle(80, 40, 15, BLACK);
            uLCD.filled_circle(80, 85, 15, BLACK);
            uLCD.filled_circle(50, 64, 20, YELLOW);
            uLCD.filled_circle(55, 64, 20, BLACK);
            replaceFace = false;
        } else if (commandReceived == 4 && replaceFace){  //backward command 4
            uLCD.filled_circle(85, 40, 15, GREEN);
            uLCD.filled_circle(85, 85, 15, GREEN);
            uLCD.filled_circle(100, 50, 15, BLACK);
            uLCD.filled_circle(100, 75, 15, BLACK);
            uLCD.filled_circle(20, 64, 25, GREEN);
            uLCD.filled_circle(15, 64, 25, BLACK);
            replaceFace = false;
        } else if (commandReceived == 0 && replaceFace){   //command 0
            uLCD.filled_circle(85, 40, 15, YELLOW);
            uLCD.filled_circle(85, 85, 15, YELLOW);
            uLCD.filled_circle(50, 64, 20, YELLOW);
            uLCD.filled_circle(55, 64, 20, BLACK);
            replaceFace = false;
        }
        Thread::wait(10);
    }
}