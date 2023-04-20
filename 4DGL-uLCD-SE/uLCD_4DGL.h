//
// uLCD_4DGL is a class to drive 4D Systems TFT touch screens
//
// Fork of 4DGL library for 4D Systems LCD displays
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

// @author Stephane Rochon

#include "mbed.h"
#ifndef _uLCD
#define _uLCD 0
// Debug Verbose off - SGE commands echoed to USB serial for debugmode=1
#ifndef DEBUGMODE
#define DEBUGMODE 0
#endif

// Common WAIT value in milliseconds between commands
#define TEMPO 0

// 4DGL SGE Function values for Goldelox Processor
#define CLS          '\xD7'
#define BAUDRATE     '\x0B' //null prefix
#define VERSION      '\x08' //null prefix
#define BCKGDCOLOR   '\x6E'
#define TXTBCKGDCOLOR '\x7E'
#define DISPCONTROL  '\x68'
#define SETVOLUME    '\x76'
#define CIRCLE       '\xCD'
#define FCIRCLE      '\xCC'
#define TRIANGLE     '\xC9'
#define LINE         '\xD2'
#define FRECTANGLE   '\xCE'
#define RECTANGLE    '\xCF'
#define ELLIPSE      '\x65' //na
#define PIXEL        '\xCB'
#define READPIXEL    '\xCA'
#define SCREENCOPY   '\x63'  //na?
#define PENSIZE      '\xD8'
#define SETFONT      '\x7D'
#define TEXTMODE     '\x77'
#define TEXTBOLD     '\x76'
#define TEXTITALIC   '\x75'
#define TEXTINVERSE  '\x74'
#define TEXTUNDERLINE '\x73'
#define TEXTWIDTH    '\x7C'
#define TEXTHEIGHT   '\x7B'
#define TEXTCHAR     '\xFE'
#define TEXTSTRING   '\x06'  //null prefix
#define MOVECURSOR   '\xE4'
#define BLITCOM      '\x0A'
#define PUTCHAR      '\xFE'
#define DISPPOWER    '\x66'
//media commands for uSD card
#define MINIT        '\xB1'
#define SBADDRESS    '\xB9'
#define SSADDRESS    '\xB8'
#define READBYTE     '\xB7'
#define READWORD     '\xB6'
#define WRITEBYTE    '\xB5'
#define WRITEWORD    '\xB4'
#define FLUSHMEDIA   '\xB2'
#define DISPLAYIMAGE '\xB3'
#define DISPLAYVIDEO '\xBB'
#define DISPLAYFRAME '\xBA'



// Screen answers
#define ACK          '\x06'
#define NAK          '\x15'



// Screen states
#define OFF          '\x00'
#define ON           '\x01'

// Graphics modes
#define SOLID        '\x00'
#define WIREFRAME    '\x01'

// Text modes
#define TRANSPARENT  '\x00'
#define OPAQUE       '\x01'

// Fonts Sizes
#define FONT_7X8     '\x00' //only builtin font 
#define FONT_5X7     '\x04'
#define FONT_8X8     '\x01'
#define FONT_8X12    '\x02'
#define FONT_12X16   '\x03'
#define MEDIAFONT    '\x07'


// Data speed
#define BAUD_110     27271
#define BAUD_300     9999
#define BAUD_600     4999
#define BAUD_1200    2499
#define BAUD_2400    1249
#define BAUD_4800    624
#define BAUD_9600    312
#define BAUD_14400   207
#define BAUD_19200   155
#define BAUD_31250   95
#define BAUD_38400   77
#define BAUD_56000   53
#define BAUD_57600   51
#define BAUD_115200  25
#define BAUD_128000  22
#define BAUD_256000  11
#define BAUD_300000  10
#define BAUD_375000  8
#define BAUD_500000  6
#define BAUD_600000  4
#define BAUD_750000  3
#define BAUD_1000000 2
#define BAUD_1500000 1
#define BAUD_3000000 0

// Defined Colors
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define YELLOW 0xFFFF00
#define LGREY 0xBFBFBF
#define DGREY 0x5F5F5F

// Mode data
#define BACKLIGHT    '\x00'
#define DISPLAY      '\x01'
#define CONTRAST     '\x02'
#define POWER        '\x03'
#define ORIENTATION  '\x04'
#define TOUCH_CTRL   '\x05'
#define IMAGE_FORMAT '\x06'
#define PROTECT_FAT  '\x08'

// change this to your specific screen (newer versions) if needed
// Startup orientation is PORTRAIT so SIZE_X must be lesser than SIZE_Y
//uLCD144-G2 is a 128 by 128 pixel display
#define SIZE_X       128
#define SIZE_Y       128

#define IS_LANDSCAPE 0
#define IS_PORTRAIT  1

// Screen orientation
#define LANDSCAPE    '\x00'
#define LANDSCAPE_R  '\x01'
#define PORTRAIT     '\x02'
#define PORTRAIT_R   '\x03'

// Parameters
#define ENABLE       '\x00'
#define DISABLE      '\x01'
#define RESET        '\x02'

#define NEW          '\x00'
#define OLD          '\x01'

#define DOWN         '\x00'
#define UP           '\x01'

#define PROTECT      '\x00'
#define UNPROTECT    '\x02'

//**************************************************************************
// \class uLCD_4DGL uLCD_4DGL.h
// \brief This is the main class. It shoud be used like this : uLCD_4GDL myLCD(p9,p10,p11);
/**
Example:
* @code
* // Display a white circle on the screen
* #include "mbed.h"
* #include " uLCD_4DGL.h"
*
* uLCD_4GDL myLCD(p9,p10,p11);
*
* int main() {
*     myLCD.circle(120, 160, 80, WHITE);
* }
* @endcode
*/

class uLCD_4DGL : public Stream
{

public :

    uLCD_4DGL(PinName tx, PinName rx, PinName rst);

// General Commands *******************************************************************************

    /** Clear the entire screen using the current background colour */
    void cls();

    /** Reset screen */
    void reset();


    /** Set serial Baud rate (both sides : screen and mbed)
    * @param Speed Correct BAUD value (see uLCD_4DGL.h)
    */
    void baudrate(int speed);

    /** Set background colour to the specified value
    * @param color in HEX RGB like 0xFF00FF
    */
    void background_color(int color);

    /** Set screen display mode to specific values
    * @param mode See 4DGL documentation
    * @param value See 4DGL documentation
    */
    void textbackground_color(int color);

    /** Set screen display mode to specific values
    * @param mode See 4DGL documentation
    * @param value See 4DGL documentation
    */
    void display_control(char mode);
    void display_power(char mode);
    /** Set internal speaker to specified value
    * @param value Correct range is 8 - 127
    */
    void set_volume(char value);

// Graphics Commands *******************************************************************************

    /** Draw a circle centered at x,y with a radius and a colour. It uses Pen Size stored value to draw a solid or wireframe circle
    * @param x Horizontal position of the circle centre
    * @param y Vertical position of the circle centre
    * @param radius Radius of the circle
    * @param color Circle color in HEX RGB like 0xFF00FF
    */
    void circle(int x , int y , int radius, int color);
    void filled_circle(int x , int y , int radius, int color);
    void triangle(int, int, int, int, int, int, int);
    void line(int, int, int, int, int);
    void rectangle(int, int, int, int, int);
    void filled_rectangle(int, int, int, int, int);
    void pixel(int, int, int);
    int  read_pixel(int, int);
    void pen_size(char);
    void BLIT(int x, int y, int w, int h, int *colors);

// Text Commands
    void set_font(char);
    void set_font_size(char width, char height);  
    void text_mode(char);
    void text_bold(char);
    void text_italic(char);
    void text_inverse(char);
    void text_underline(char);
    void text_width(char);
    void text_height(char);
    void text_char(char, char, char, int);
    void text_string(char *, char, char, char, int);
    void locate(char, char);
    void color(int);
    void putc(char);
    void puts(char *);

//Media Commands
    int media_init();
    void set_byte_address(int, int);
    void set_sector_address(int, int);
    char read_byte();
    int  read_word();
    void write_byte(int);
    void write_word(int);
    void flush_media();
    void display_image(int, int);
    void display_video(int, int);
    void display_frame(int, int, int);

// Screen Data
    int type;
    int revision;
    int firmware;
    int reserved1;
    int reserved2;

// Text data
    char current_col;
    char current_row;
    int  current_color;
    char current_font;
    char current_orientation;
    char max_col;
    char max_row;
    int current_w, current_h;
    int current_fx, current_fy;
    int current_wf, current_hf;


protected :

    Serial     _cmd;
    DigitalOut _rst;
    //used by printf
    virtual int _putc(int c) {
        putc(c);
        return 0;
    };
    virtual int _getc() {
        return -1;
    }

    void freeBUFFER  (void);
    void writeBYTE   (char);
    void writeBYTEfast   (char);
    int  writeCOMMAND(char *, int);
    int  writeCOMMANDnull(char *, int);
    int  readVERSION (char *, int);
    int  getSTATUS   (char *, int);
    int  version     (void);
#if DEBUGMODE
    Serial pc;
#endif // DEBUGMODE
};

typedef unsigned char BYTE;
#endif







