#include "screenlib.h"


void clear()
{
  system("@cls||clear");
}

void insertStr(Screen screen, char* str, char y, char x)
{
  u_char i, chr;
  for (i = 0; str[i] != '\0'; i++);
  chr = screen[y][x + i];
  strcpy(&screen[y][x], str);
  screen[y][x + i] = chr; // Replace the '\0' character by the previous character
}

void fillScr(Screen screen, char chr)
{
  for (char i = 0; i < SCREEN_HEIGHT; i++)
    for (char j = 0; j < SCREEN_WIDTH; j++)
      screen[i][j] = chr;
}

void renderScr(Screen screen)
{
  for (char i = 0; i < SCREEN_HEIGHT; i++)
  {
    for (char j = 0; j < SCREEN_WIDTH; j++)
      putchar(screen[i][j]);
    putchar('\n');
  }
}