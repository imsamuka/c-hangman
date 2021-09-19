#include "screenlib.h"


void clear()
{
  system("@cls||clear");
}

void insertStr(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], char* str, char y, char x)
{
  strcpy(&screen[y][x], str);
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
      printf("%c", screen[i][j]);
    printf("\n");
  }
}