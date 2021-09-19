#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_HEIGHT 10
#define SCREEN_WIDTH 80

typedef char Screen[SCREEN_HEIGHT][SCREEN_WIDTH];

void clear();
void insertStr(Screen screen, char* str, char y, char x);
void fillScr(Screen screen, char chr);
void renderScr(Screen screen);
