#include "screenlib.h"


void clear()
{
  system("@cls||clear");
}

void insertStr(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], char* str, char y, char x)
{
  u_char i, chr;
  for (i = 0; str[i] != '\0'; i++);
  chr = screen[y][x + i];
  strcpy(&screen[y][x], str);
  screen[y][x + i] = chr; // Replace the '\0' character by the previous character
}

void fillScr(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], char chr)
{
  for (char i = 0; i < SCREEN_HEIGHT; i++)
    for (char j = 0; j < SCREEN_WIDTH; j++)
      screen[i][j] = chr;
}

void renderScr(char screen[SCREEN_HEIGHT][SCREEN_WIDTH])
{
  for (char i = 0; i < SCREEN_HEIGHT; i++)
  {
    for (char j = 0; j < SCREEN_WIDTH; j++)
      putchar(screen[i][j]);
    putchar('\n');
  }
}