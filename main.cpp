//#include "cmsis_os.h"
#include "mbed.h"
#include "PwmOut.h"
//#include "uLCD_4DGL.h"
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
int commandReceived = 0;
int soundType = 0;
//uLCD_4DGL uLCD(p9,p10,p30);

void dist(int distance){}

//Define necessary components for the robot
ultrasonic mu(p6, p7, .1, 1, &dist);

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
    int distance = 0;
    while(1) {
        distance = mu.getCurrentDistance();
        pc.printf("command: %d\n", commandReceived);
        if (commandReceived == 1) { //turn left command 1
            soundType = 3;
            Thread::wait(1000);
            motorA.speed(-1);
            motorB.speed(0);
            Thread::wait(1000);
            commandReceived = 0;
            soundType = 0;
        }  else if (commandReceived == 2) { //turn right command 2
            soundType = 3;
            Thread::wait(1000);
            motorA.speed(1);
            motorB.speed(0);
            Thread::wait(1000);
            commandReceived = 0;
            soundType = 0;
        } else if (commandReceived == 3) { //forward command 3   
            motorA.speed(-1);
            motorB.speed(1);
            soundType = 1;
        } else if (commandReceived == 4){  //backward command 4
            soundType = 2;
            int j = 0;
            while (j < 11) {
                motorA.speed(1);
                motorB.speed(-1);
                j++;
            }
            commandReceived = 0;
            soundType = 0;
            Thread::wait(200);
        } else  {   //command 0
            motorA.speed(0);
            motorB.speed(0);
        }
        pc.printf("distance: %d\n", distance);
        if (distance > 10 && distance < 100) {  //turn right when meet obstacles
            motorA.speed(0);
            motorB.speed(0);
            commandReceived = 2;
        } 
    }
}