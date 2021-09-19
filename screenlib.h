#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_HEIGHT 10
#define SCREEN_WIDTH 80

void clear();
void insertStr(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], char* str, char y, char x);
void fillScr(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], char chr);
void renderScr(char screen[SCREEN_HEIGHT][SCREEN_WIDTH]);
