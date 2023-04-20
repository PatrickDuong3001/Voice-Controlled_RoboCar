//
// uLCD_4DGL is a class to drive 4D Systems LCD screens
//
// Copyright (C) <2010> Stephane ROCHON <stephane.rochon at free.fr>
// Modifed for Goldelox processor <2013> Jim Hamblen
//
// uLCD_4DGL is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// uLCD_4DGL is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with uLCD_4DGL.  If not, see <http://www.gnu.org/licenses/>.

#include "mbed.h"
#include "uLCD_4DGL.h"

#define ARRAY_SIZE(X) sizeof(X)/sizeof(X[0])

//****************************************************************************************************
void uLCD_4DGL :: circle(int x, int y , int radius, int color)     // draw a circle in (x,y)
{
    char command[9]= "";

    command[0] = CIRCLE;

    command[1] = (x >> 8) & 0xFF;
    command[2] = x & 0xFF;

    command[3] = (y >> 8) & 0xFF;
    command[4] = y & 0xFF;

    command[5] = (radius >> 8) & 0xFF;
    command[6] = radius & 0xFF;

    int red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[7] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[8] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 9);
}
//****************************************************************************************************
void uLCD_4DGL :: filled_circle(int x, int y , int radius, int color)     // draw a circle in (x,y)
{
    char command[9]= "";

    command[0] = FCIRCLE;

    command[1] = (x >> 8) & 0xFF;
    command[2] = x & 0xFF;

    command[3] = (y >> 8) & 0xFF;
    command[4] = y & 0xFF;

    command[5] = (radius >> 8) & 0xFF;
    command[6] = radius & 0xFF;

    int red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[7] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[8] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 9);
}

//****************************************************************************************************
void uLCD_4DGL :: triangle(int x1, int y1 , int x2, int y2, int x3, int y3, int color)     // draw a traingle
{
    char command[15]= "";

    command[0] = TRIANGLE;

    command[1] = (x1 >> 8) & 0xFF;
    command[2] = x1 & 0xFF;

    command[3] = (y1 >> 8) & 0xFF;
    command[4] = y1 & 0xFF;

    command[5] = (x2 >> 8) & 0xFF;
    command[6] = x2 & 0xFF;

    command[7] = (y2 >> 8) & 0xFF;
    command[8] = y2 & 0xFF;

    command[9] = (x3 >> 8) & 0xFF;
    command[10] = x3 & 0xFF;

    command[11] = (y3 >> 8) & 0xFF;
    command[12] = y3 & 0xFF;

    int red5   = (color >> (16 + 3)) & 0x1F;               // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;               // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;               // get blue on 5 bits

    command[13] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[14] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 15);
}

//****************************************************************************************************
void uLCD_4DGL :: line(int x1, int y1 , int x2, int y2, int color)     // draw a line
{
    char command[11]= "";

    command[0] = LINE;

    command[1] = (x1 >> 8) & 0xFF;
    command[2] = x1 & 0xFF;

    command[3] = (y1 >> 8) & 0xFF;
    command[4] = y1 & 0xFF;

    command[5] = (x2 >> 8) & 0xFF;
    command[6] = x2 & 0xFF;

    command[7] = (y2 >> 8) & 0xFF;
    command[8] = y2 & 0xFF;

    int red5   = (color >> (16 + 3)) & 0x1F;               // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;               // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;               // get blue on 5 bits

    command[9] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;   // first part of 16 bits color
    command[10] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 11);
}

//****************************************************************************************************
void uLCD_4DGL :: rectangle(int x1, int y1 , int x2, int y2, int color)     // draw a rectangle
{
    char command[11]= "";

    command[0] = RECTANGLE;

    command[1] = (x1 >> 8) & 0xFF;
    command[2] = x1 & 0xFF;

    command[3] = (y1 >> 8) & 0xFF;
    command[4] = y1 & 0xFF;

    command[5] = (x2 >> 8) & 0xFF;
    command[6] = x2 & 0xFF;

    command[7] = (y2 >> 8) & 0xFF;
    command[8] = y2 & 0xFF;

    int red5   = (color >> (16 + 3)) & 0x1F;               // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;               // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;               // get blue on 5 bits

    command[9] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;   // first part of 16 bits color
    command[10] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 11);
}

//****************************************************************************************************
void uLCD_4DGL :: filled_rectangle(int x1, int y1 , int x2, int y2, int color)     // draw a rectangle
{
    char command[11]= "";

    command[0] = FRECTANGLE;

    command[1] = (x1 >> 8) & 0xFF;
    command[2] = x1 & 0xFF;

    command[3] = (y1 >> 8) & 0xFF;
    command[4] = y1 & 0xFF;

    command[5] = (x2 >> 8) & 0xFF;
    command[6] = x2 & 0xFF;

    command[7] = (y2 >> 8) & 0xFF;
    command[8] = y2 & 0xFF;

    int red5   = (color >> (16 + 3)) & 0x1F;               // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;               // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;               // get blue on 5 bits

    command[9] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;   // first part of 16 bits color
    command[10] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 11);
}



//****************************************************************************************************
void uLCD_4DGL :: pixel(int x, int y, int color)     // draw a pixel
{
    char command[7]= "";

    command[0] = PIXEL;

    command[1] = (x >> 8) & 0xFF;
    command[2] = x & 0xFF;

    command[3] = (y >> 8) & 0xFF;
    command[4] = y & 0xFF;

    int red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[5] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[6] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color

    writeCOMMAND(command, 7);
}
//****************************************************************************************************
void uLCD_4DGL :: BLIT(int x, int y, int w, int h, int *colors)     // draw a block of pixels
{
    int red5, green6, blue5;
    writeBYTEfast('\x00');
    writeBYTEfast(BLITCOM);
    writeBYTEfast((x >> 8) & 0xFF);
    writeBYTEfast(x & 0xFF);
    writeBYTEfast((y >> 8) & 0xFF);
    writeBYTEfast(y & 0xFF);
    writeBYTEfast((w >> 8) & 0xFF);
    writeBYTE(w & 0xFF);
    writeBYTE((h >> 8) & 0xFF);
    writeBYTE(h & 0xFF);
    wait_ms(1);
    for (int i=0; i<w*h; i++) {
        red5   = (colors[i] >> (16 + 3)) & 0x1F;              // get red on 5 bits
        green6 = (colors[i] >> (8 + 2))  & 0x3F;              // get green on 6 bits
        blue5  = (colors[i] >> (0 + 3))  & 0x1F;              // get blue on 5 bits
        writeBYTEfast(((red5 << 3)   + (green6 >> 3)) & 0xFF);  // first part of 16 bits color
        writeBYTEfast(((green6 << 5) + (blue5 >> 0)) & 0xFF);  // second part of 16 bits color
    }
    int resp=0;
    while (!_cmd.readable()) wait_ms(TEMPO);              // wait for screen answer
    if (_cmd.readable()) resp = _cmd.getc();           // read response if any
    switch (resp) {
        case ACK :                                     // if OK return   1
            resp =  1;
            break;
        case NAK :                                     // if NOK return -1
            resp = -1;
            break;
        default :
            resp =  0;                                 // else return   0
            break;
    }
#if DEBUGMODE
    pc.printf("   Answer received : %d\n",resp);
#endif

}
//******************************************************************************************************
int uLCD_4DGL :: read_pixel(int x, int y)   // read screen info and populate data
{

    char command[6]= "";
    command[0] = 0xFF;
    command[1] = READPIXEL;

    command[2] = (x >> 8) & 0xFF;
    command[3] = x & 0xFF;

    command[4] = (y >> 8) & 0xFF;
    command[5] = y & 0xFF;

    int i, temp = 0, color = 0, resp = 0;
    char response[3] = "";

    freeBUFFER();

    for (i = 0; i < 6; i++) {                   // send all chars to serial port
        writeBYTE(command[i]);
    }

    while (!_cmd.readable()) wait_ms(TEMPO);    // wait a bit for screen answer

    while ( resp < ARRAY_SIZE(response)) {   //read ack and 16-bit color response
        temp = _cmd.getc();
        response[resp++] = (char)temp;
    }

    color = ((response[1] << 8) + response[2]);

    return color; 
}


//****************************************************************************************************
void uLCD_4DGL :: pen_size(char mode)     // set pen to SOLID or WIREFRAME
{
    char command[2]= "";

    command[0] = PENSIZE;
    command[1] = mode;
    writeCOMMAND(command, 2);
}



