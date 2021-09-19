#include "screenlib.h"

const char BLANK_CHR = ' ';

enum Options { CLOSE, EASY, MEDIUM, HARD };
const u_char OPT_OFFSET = 48;

char upperChar(char chr)
{
  if (chr >= 97 && chr <= 122)
    return chr - 32; // ASCII offset
  return chr;
}

u_char chrInStr(char chr, char* str)
{
  for (u_char i = 0; str[i] != '\0'; i++)
    if (chr == str[i]) return 1;
  return 0;
}

u_char strEqual(char* str1, char* str2)
{
  u_char i;
  for (i = 0; str1[i] != '\0'; i++)
    if (str1[i] != str2[i]) return 0;
  return str1[i] == str2[i];
}

void drawMan(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], char countdown)
{
  // Clear
  for (char i = 3; i <= 6; i++)
      for (char j = 7; j <= 9; j++)
        screen[i][j] = BLANK_CHR;

  switch (countdown)
  {
  case 0:
    screen[6][9] = '\\';
  case 1:
    screen[6][7] = '/';
  case 2:
    screen[4][9] = '\\';
  case 3:
    screen[4][7] = '/';
  case 4:
    screen[4][8] = '|';
    screen[5][8] = '|';
  case 5:
    screen[3][8] = 'O';
  default:
    break;
  }
}

void drawLoose(char screen[SCREEN_HEIGHT][SCREEN_WIDTH])
{
  // Pole
  for (char i = 2; i <= 8; i++)
    screen[i][2] = '|';

  // Line above
  insertStr(screen, "_______", 1, 2);

  // Above the head
  screen[2][8] = '|';
}

enum Options askDifficulty(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], enum Options opt)
{
  // Clear Screen
  fillScr(screen, BLANK_CHR);


  // Draw Static Text
  insertStr(screen, "C Hangman!", 1, 6);
  insertStr(screen, "Select a Difficulty:", 3, 3);

  insertStr(screen, "Hard", 5, 6);
  insertStr(screen, "Medium", 6, 6);
  insertStr(screen, "Easy", 7, 6);
  insertStr(screen, "Close", 8, 6);


  // Draw the respective numbers
  screen[5][4] = HARD + OPT_OFFSET;
  screen[6][4] = MEDIUM + OPT_OFFSET;
  screen[7][4] = EASY + OPT_OFFSET;
  screen[8][4] = CLOSE + OPT_OFFSET;

  // Draw the selected option
  insertStr(screen, "(default)", 8 - opt, 14);


  // Render Screen
  clear();
  renderScr(screen);


  // Ask Difficulty Number
  {
    u_char selection;

    printf("Type the number: ");
    scanf("%c", &selection);
    if (selection - OPT_OFFSET >= CLOSE && selection - OPT_OFFSET <= HARD)
    {
      opt = selection - OPT_OFFSET;
    }
  }


  // Show Selected Difficulty
  printf("Selected ");

  switch (opt)
  {
  case HARD:
    printf("Hard!!!!"); break;
  case MEDIUM:
    printf("Medium!"); break;
  case EASY:
    printf("Easy..."); break;
  case CLOSE:
    printf("Close :("); break;
  default:
    printf("Error????"); break;
  }

  putchar('\n');

  return opt;
}

int main() {

  char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
  enum Options opt = askDifficulty(screen, HARD);

  while (opt != CLOSE)
  {
    // Select a word
    // Start the game
    // Start Again
    opt = askDifficulty(screen, opt);
  }

  printf("Goodbye! Let's play again :>\n");

  return 0;
}