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


//Media Commands

//******************************************************************************************************
int uLCD_4DGL :: media_init()
{
    int resp = 0;
    char command[1] = "";
    command[0] = MINIT;
    writeCOMMAND(command, 1);
    while (!_cmd.readable()) wait_ms(TEMPO);              // wait for screen answer
    if (_cmd.readable()) {
        resp = _cmd.getc();           // read response
        resp = resp << 8 + _cmd.getc();
    }
    return resp;
}

//******************************************************************************************************
void uLCD_4DGL :: set_byte_address(int hi, int lo)
{
    char command[5]= "";
    command[0] = SBADDRESS;

    command[1] = (hi >> 8) & 0xFF;
    command[2] = hi & 0xFF;

    command[3] = (lo >> 8) & 0xFF;
    command[4] = lo & 0xFF;
    writeCOMMAND(command, 5);
}

//******************************************************************************************************
void uLCD_4DGL :: set_sector_address(int hi, int lo)
{

    char command[5]= "";
    command[0] = SSADDRESS;

    command[1] = (hi >> 8) & 0xFF;
    command[2] = hi & 0xFF;

    command[3] = (lo >> 8) & 0xFF;
    command[4] = lo & 0xFF;
    writeCOMMAND(command, 5);
}

//******************************************************************************************************
char uLCD_4DGL :: read_byte()
{
    char resp = 0;
    char command[1] = "";
    command[0] = READBYTE;
    writeCOMMAND(command, 1);
    while (!_cmd.readable()) wait_ms(TEMPO);              // wait for screen answer
    if (_cmd.readable()) {
        resp = _cmd.getc();           // read response
        resp = _cmd.getc();
    }
    return resp;
}

//******************************************************************************************************
int  uLCD_4DGL :: read_word()
{
    int resp=0;
    char command[1] = "";
    command[0] = READWORD;
    writeCOMMAND(command, 1);
    while (!_cmd.readable()) wait_ms(TEMPO);              // wait for screen answer
    if (_cmd.readable()) {
        resp = _cmd.getc();           // read response
        resp = resp << 8 + _cmd.getc();
    }
    return resp;
}

//******************************************************************************************************
void uLCD_4DGL :: write_byte(int value)
{
    char command[3]= "";

    command[0] = WRITEBYTE;

    command[1] = (value >> 8) & 0xFF;
    command[2] = value & 0xFF;
    writeCOMMAND(command,3);
}

//******************************************************************************************************
void uLCD_4DGL :: write_word(int value)
{
    char command[3]= "";

    command[0] = WRITEWORD;

    command[1] = (value >> 8) & 0xFF;
    command[2] = value & 0xFF;
    writeCOMMAND(command,3);
}

//******************************************************************************************************
void uLCD_4DGL :: flush_media()
{
    char command[1] = "";
    command[0] = FLUSHMEDIA;
    writeCOMMAND(command, 1);
}

//******************************************************************************************************
void uLCD_4DGL :: display_image(int x, int y)
{
    char command[6]= "";
    command[0] = DISPLAYIMAGE;

    command[1] = (x >> 8) & 0xFF;
    command[2] = x & 0xFF;

    command[3] = (y >> 8) & 0xFF;
    command[4] = y & 0xFF;
    writeCOMMAND(command, 5);
}

//******************************************************************************************************
void uLCD_4DGL :: display_video(int x, int y)
{
    char command[5]= "";
    command[0] = DISPLAYVIDEO;

    command[1] = (x >> 8) & 0xFF;
    command[2] = x & 0xFF;

    command[3] = (y >> 8) & 0xFF;
    command[4] = y & 0xFF;
    writeCOMMAND(command, 5);
}

//******************************************************************************************************
void uLCD_4DGL :: display_frame(int x, int y, int w)
{
    char command[7]= "";

    command[0] = DISPLAYFRAME;

    command[1] = (x >> 8) & 0xFF;
    command[2] = x & 0xFF;

    command[3] = (y >> 8) & 0xFF;
    command[4] = y & 0xFF;

    command[5] = (w >> 8) & 0xFF;
    command[6] = w & 0xFF;
    writeCOMMAND(command,7);
}

