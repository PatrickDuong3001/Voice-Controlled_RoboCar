//
// uLCD_4DGL is a class to drive 4D Systems TFT touch screens
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

//****************************************************************************************************
void uLCD_4DGL :: set_font_size(char width, char height)     // set font size
{
    if (current_orientation == IS_PORTRAIT) {
        current_fx = width;
        current_fy = height;
    } else {
        current_fy = height;
        current_fx = width;
    }
    max_col = current_w / (current_fx*current_wf);
    max_row = current_h / (current_fy*current_hf);
}

//****************************************************************************************************
void uLCD_4DGL :: set_font(char mode)     // set font - system or SD media
{
    char command[3]= "";

    command[0] = SETFONT;
    command[1] = 0;
    command[2] = mode;

    current_font = mode;

    if (current_orientation == IS_PORTRAIT) {
        current_w = SIZE_X;
        current_h = SIZE_Y;
    } else {
        current_w = SIZE_Y;
        current_h = SIZE_X;
    }

    switch (mode) {
        case FONT_5X7 :

            current_fx = 6;
            current_fy = 8;
            break;
        case FONT_7X8 :
            current_fx = 7;
            current_fy = 8;
            break;
        case FONT_8X8 :
            current_fx = 8;
            current_fy = 8;
            break;
        case FONT_8X12 :
            current_fx = 8;
            current_fy = 12;
            break;
        case FONT_12X16 :
            current_fx = 12;
            current_fy = 16;
            break;
        default:
            current_fx = 8;
            current_fy = 8;
    }

    max_col = current_w / (current_fx*current_wf);
    max_row = current_h / (current_fy*current_hf);

    writeCOMMAND(command, 3);
}



//****************************************************************************************************
void uLCD_4DGL :: text_mode(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTMODE;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void uLCD_4DGL :: text_bold(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTBOLD;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void uLCD_4DGL :: text_italic(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTITALIC;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void uLCD_4DGL :: text_inverse(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTINVERSE;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void uLCD_4DGL :: text_underline(char mode)     // set text mode
{
    char command[3]= "";

    command[0] = TEXTUNDERLINE;
    command[1] = 0;
    command[2] = mode;

    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void uLCD_4DGL :: text_width(char width)     // set text width
{
    char command[3]= "";

    command[0] = TEXTWIDTH;
    command[1] = 0;
    command[2] = width;
    current_wf = width;
    max_col = current_w / (current_fx*current_wf);
    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void uLCD_4DGL :: text_height(char height)     // set text height
{
    char command[3]= "";

    command[0] = TEXTHEIGHT;
    command[1] = 0;
    command[2] = height;
    current_hf = height;
    max_row = current_h / (current_fy*current_hf);
    writeCOMMAND(command, 3);
}


//****************************************************************************************************
void uLCD_4DGL :: text_char(char c, char col, char row, int color)     // draw a text char
{
    char command[6]= "";
    command[0] = 0xE4; //move cursor
    command[1] = 0;
    command[2] = row;
    command[3] = 0;
    command[4] = col;
    writeCOMMAND(command, 5);

    command[0] = 0x7F;  //set color

    int red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[1] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[2] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color
    writeCOMMAND(command, 3);

    command[0] = TEXTCHAR;  //print char
    command[1] = 0;
    command[2] = c;
    writeCOMMAND(command, 3);

}


//****************************************************************************************************
void uLCD_4DGL :: text_string(char *s, char col, char row, char font, int color)     // draw a text string
{

    char command[1000]= "";
    int size = strlen(s);
    int i = 0;

    set_font(font);

    command[0] = 0xE4; //move cursor
    command[1] = 0;
    command[2] = row;
    command[3] = 0;
    command[4] = col;
    writeCOMMAND(command, 5);

    command[0] = 0x7F;  //set color
    int red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[1] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[2] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color
    writeCOMMAND(command, 3);

    command[0] = TEXTSTRING;
    for (i=0; i<size; i++) command[1+i] = s[i];
    command[1+size] = 0;
    writeCOMMANDnull(command, 2 + size);
}



//****************************************************************************************************
void uLCD_4DGL :: locate(char col, char row)     // place text curssor at col, row
{
    char command[5] = "";
    current_col = col;
    current_row = row;
    command[0] = MOVECURSOR; //move cursor
    command[1] = 0;
    command[2] = current_row;
    command[3] = 0;
    command[4] = current_col;
    writeCOMMAND(command, 5);
}

//****************************************************************************************************
void uLCD_4DGL :: color(int color)     // set text color
{
    char command[5] = "";
    current_color = color;
    command[0] = 0x7F;  //set color

    int red5   = (color >> (16 + 3)) & 0x1F;              // get red on 5 bits
    int green6 = (color >> (8 + 2))  & 0x3F;              // get green on 6 bits
    int blue5  = (color >> (0 + 3))  & 0x1F;              // get blue on 5 bits

    command[1] = ((red5 << 3)   + (green6 >> 3)) & 0xFF;  // first part of 16 bits color
    command[2] = ((green6 << 5) + (blue5 >>  0)) & 0xFF;  // second part of 16 bits color
    writeCOMMAND(command, 3);
}

//****************************************************************************************************
void uLCD_4DGL :: putc(char c)      // place char at current cursor position
//used by virtual printf function _putc
{
    char command[6] ="";
    if(c<0x20) {
        if(c=='\n') {
            current_col = 0;
            current_row++;
            command[0] = MOVECURSOR; //move cursor to start of next line
            command[1] = 0;
            command[2] = current_row;
            command[3] = 0;
            command[4] = current_col;
            writeCOMMAND(command, 5);
        }
        if(c=='\r') {
            current_col = 0;
            command[0] = MOVECURSOR; //move cursor to start of line
            command[1] = 0;
            command[2] = current_row;
            command[3] = 0;
            command[4] = current_col;
            writeCOMMAND(command, 5);
        }
        if(c=='\f') {
            uLCD_4DGL::cls(); //clear screen on form feed
        }
    } else {
        command[0] = PUTCHAR;
        command[1] = 0x00;
        command[2] = c;
        writeCOMMAND(command,3);
        current_col++;
    }
    if (current_col == max_col) {
        current_col = 0;
        current_row++;
        command[0] = MOVECURSOR; //move cursor to next line
        command[1] = 0;
        command[2] = current_row;
        command[3] = 0;
        command[4] = current_col;
        writeCOMMAND(command, 5);
    }
    if (current_row == max_row) {
        current_row = 0;
        command[0] = MOVECURSOR; //move cursor back to start
        command[1] = 0;
        command[2] = current_row;
        command[3] = 0;
        command[4] = current_col;
        writeCOMMAND(command, 5);
    }
}


//****************************************************************************************************
void uLCD_4DGL :: puts(char *s)     // place string at current cursor position
{

    text_string(s, current_col, current_row, current_font, current_color);

    current_col += strlen(s);

    if (current_col >= max_col) {
        current_row += current_col / max_col;
        current_col %= max_col;
    }
    if (current_row >= max_row) {
        current_row %= max_row;
    }
}
