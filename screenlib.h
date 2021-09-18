#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 80

typedef struct
{
  char height;
  //char canvas[][WIDTH];
} Screen;

void clearScr();
void insertStr(Screen screen, char* str, char y, char x);
void renderScr(Screen screen);
