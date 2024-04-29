#include "monitor.h"
#include "common.h"
#include "libc/stdint.h"

volatile uint16_t cursor_x = 0;
volatile uint16_t cursor_y = 0;
uint16_t *video_memory = (uint16_t*)0xB8000;


void monitor_put(char c)
{   
    uint8_t backColour = 0;
   uint8_t foreColour = 15;

   // The attribute byte is made up of two nibbles - the lower being the
   // foreground colour, and the upper the background colour.
   uint8_t  attributeByte = (backColour << 4) | (foreColour & 0x0F);
   // The attribute byte is the top 8 bits of the word we have to send to the
   // VGA board.
   uint16_t attribute = attributeByte << 8;
   uint16_t *location;

   // Handle a backspace, by moving the cursor back one space
   if (c == 0x08 && cursor_x)
   {
       cursor_x--;
   }

   // Handle a tab by increasing the cursor's X, but only to a point
   // where it is divisible by 8.
   else if (c == 0x09)
   {
       cursor_x = (cursor_x+8) & ~(8-1);
   }

   // Handle carriage return
   else if (c == '\r')
   {
       cursor_x = 0;
   }

   // Handle newline by moving cursor back to left and increasing the row
   else if (c == '\n')
   {
       cursor_x = 0;
       cursor_y++;
   }
   // Handle any other printable character.
   else if(c >= ' ')
   {
       location = video_memory + (cursor_y*80 + cursor_x);
       *location = c | attribute;
       cursor_x++;
   }

   // Check if we need to insert a new line because we have reached the end
   // of the screen.
   if (cursor_x >= 80)
   {
       cursor_x = 0;
       cursor_y ++;
   }

   // Scroll the screen if needed.
   scroll();
   // Move the hardware cursor.
   move_cursor();
}

void monitor_clear()
{
   // Make an attribute byte for the default colours
   uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

   int i;
   for (i = 0; i < 80*25; i++)
   {
       video_memory[i] = blank;
   }

   // Move the hardware cursor back to the start.
   cursor_x = 0;
   cursor_y = 0;
   move_cursor();
}

void monitor_write(char *c)
{
   int i = 0;
   while (c[i])
   {
        monitor_put(c[i++]);
   }
}

void monitor_write_hex(uint32_t n)
{
    
}

void monitor_write_dec(uint32_t n)
{
    uint32_t temp = n;
    char str[64];
    int i=0;

    do    
    {
        uint32_t temp2 = temp%10;   //12304 % 10 = 4. (1230*10 + 4)
        str[i] = temp2 + '0';
        temp = temp/10;
        i=i+1;
    }while (temp);

    uint32_t strlen = findstrlength(str);

    char strret[strlen];

    for(int j = strlen-1; j>=0 ; j--){
        for(uint32_t p = 0; p<strlen; p++){
            strret[p]=str[j];
        }
    }

    monitor_write(strret);
}

int32_t findstrlength(char *str){
    uint32_t strlen = 0;

    while(str[strlen]){
        strlen++;
    }
    return strlen;
}

void move_cursor()
{
   // The screen is 80 characters wide...
   uint16_t cursorLocation = cursor_y * 80 + cursor_x;
   outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
   outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
   outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
   outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

void scroll()
{

   // Get a space character with the default colour attributes.
   uint8_t attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   uint16_t blank = 0x20 /* space */ | (attributeByte << 8);

   // Row 25 is the end, this means we need to scroll up
   if(cursor_y >= 25)
   {
       // Move the current text chunk that makes up the screen
       // back in the buffer by a line
       int i;
       for (i = 0*80; i < 24*80; i++)
       {
           video_memory[i] = video_memory[i+80];
       }

       // The last line should now be blank. Do this by writing
       // 80 spaces to it.
       for (i = 24*80; i < 25*80; i++)
       {
           video_memory[i] = blank;
       }
       // The cursor should now be on the last line.
       cursor_y = 24;
   }
}