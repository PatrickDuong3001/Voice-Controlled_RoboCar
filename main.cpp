//#include "cmsis_os.h"
#include "mbed.h"
#include "PwmOut.h"
//#include "uLCD_4DGL.h"
#include "mbed2/293/drivers/DigitalOut.h"
#include "rtos.h"
#include "Motor.h"
#include "PinDetect.h"
#include "ultrasonic.h"
#include "Speaker.h"

Serial pc(USBTX, USBRX);
Motor motorA(p21, p17, p18);
Motor motorB(p22, p19, p20);
Speaker mySpeaker(p23);
Serial device(p13, p14);
Ticker ledTick;

DigitalOut frontLeftLED(p5);
DigitalOut frontRightLED(p6);
DigitalOut backLeftLED(p15);
DigitalOut backRightLED(p16);

int commandReceived = 0;
int soundType = 0;
int ledType = 0;
//uLCD_4DGL uLCD(p9,p10,p30);

void dist(int distance){}

//Define necessary components for the robot
ultrasonic mu(p6, p7, .1, 1, &dist);

void ledController() {
    if (ledType == 1) {    //two front LEDs up when moving forward
        frontLeftLED = 1;
        frontRightLED = 1;
        backLeftLED = 0;
        backRightLED = 0;
    } else if (ledType == 2) { //two back LEDs up when moving backward
        frontLeftLED = 0;
        frontRightLED = 0;
        backLeftLED = 1;
        backRightLED = 1;
    } else if (ledType == 3) {  //turn left LEDs up
        frontLeftLED = 1;
        frontRightLED = 0;
        backLeftLED = 1;
        backRightLED = 0;
    } else if (ledType == 4) {  //turn right LEDs up
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
}

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
            pc.printf("char: %c", rchar);
            if (rchar == 'A') {         //turn left
                commandReceived = 1;
                rchar = 0;
            } else if (rchar == 'B') { //turn right
                commandReceived = 2;
                rchar = 0;
            } else if (rchar == 'E') { //go forward infinitely
                commandReceived = 3;
                rchar = 0;
            } else if (rchar == 'F') { //go backward -- maybe unnecessary
                commandReceived = 4;
                rchar = 0;
            }
        }
        Thread::wait(200);
    }
}

void soundPlayer() {
    while (1) {
        if (soundType == 1) {   //forward sond
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
        } else if (soundType == 2) { //backward sound
            mySpeaker.PlayNote(1500,0.3,1);
            mySpeaker.PlayNote(1000,0.3,1);
        } else if (soundType == 3) { //turn left/right sound
            mySpeaker.PlayNote(1200,0.3,1);
            mySpeaker.PlayNote(0,0.3,0);
        } else if (soundType == 0){
            mySpeaker.PlayNote(0, 0.3, 0);
            mySpeaker.PlayNote(0,0.3,0);
        }
    }
}

int main() {
    //set up uLCD for display
    //uLCD.cls();
    //uLCD.background_color(BLACK);
    //uLCD.baudrate(3000000); //jack up baud rate to max for fast display
    mu.startUpdates();//start measuring the distance
    Thread listenerThread(listener);
    Thread soundThread(soundPlayer);
    ledTick.attach(&ledController,0.2);

    int distance = 0;
    while(1) {
        distance = mu.getCurrentDistance();
        pc.printf("command: %d\n", commandReceived);
        if (commandReceived == 1) { //turn left command 1
            ledType = 3;
            soundType = 3;
            Thread::wait(1000);
            motorA.speed(-1);
            motorB.speed(0);
            Thread::wait(1000);
            commandReceived = 0;
            soundType = 0;
            ledType = 0;
        }  else if (commandReceived == 2) { //turn right command 2
            ledType = 4;
            soundType = 3;
            Thread::wait(1000);
            motorA.speed(1);
            motorB.speed(0);
            Thread::wait(1000);
            commandReceived = 0;
            soundType = 0;
            ledType = 0;
        } else if (commandReceived == 3) { //forward command 3
            ledType = 1;
            motorA.speed(-1);
            motorB.speed(1);
            soundType = 1;
        } else if (commandReceived == 4){  //backward command 4
            ledType = 2;
            soundType = 2;
            int j = 0;
            while (j < 11) {    //move backward for only 3 seconds
                motorA.speed(1);
                motorB.speed(-1);
                j++;
            }
            commandReceived = 0;
            soundType = 0;
            ledType = 0;
            Thread::wait(200);
        } else  {   //command 0
            ledType = 0;
            motorA.speed(0);
            motorB.speed(0);
        }
        pc.printf("distance: %d\n", distance);
        if (distance > 10 && distance < 100) {  //turn right when meet obstacles
            ledType = 0;
            motorA.speed(0);
            motorB.speed(0);
            commandReceived = 2;
        }
    }
}