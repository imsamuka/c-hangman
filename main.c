#include "screenlib.h"

const char BLANK_CHR = ' ';
#define WORD_SIZE 32

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

void playHangman(char screen[SCREEN_HEIGHT][SCREEN_WIDTH], char* word)
{
  // Setup Variables
  u_char countdown = 6;
  char letter = '\0';
  char tried[91 - 65 + 1] = ""; // Alphabet size + '\0'
  char solvedWord[WORD_SIZE] = "";
  for (u_char i = 0; word[i] != '\0'; i++) solvedWord[i] = '_';


  // Setup Screen
  fillScr(screen, BLANK_CHR);
  insertStr(screen, "Tried: ", 2, 14);
  insertStr(screen, "Tries: ", 3, 14);
  {
    // Draw Loose
    for (char i = 2; i <= 8; i++) screen[i][2] = '|'; // Pole
    insertStr(screen, "_______", 1, 2); // Line above
    screen[2][8] = '|'; // Above the head
  }


  // Start Game Loop
  do {
    // Draw Game State
    insertStr(screen, tried, 2, 14 + 7);
    screen[3][14 + 7] = countdown + OPT_OFFSET;
    for (u_char i = 0; solvedWord[i] != '\0'; i++) screen[8][14 + i*2] = solvedWord[i];
    drawMan(screen, countdown);


    // Render Screen
    clear();
    renderScr(screen);


    // Win and Lose Condition
    {
      if (countdown <= 0)
      {
        printf("You Lose!\n");
        break;
      }

      if (strEqual(word, solvedWord))
      {
        printf("You WIN!!!!!\n");
        break;
      }
    }


    // Ask Letter
    {
      // Get Letter
      printf("Type the letter: ");
      scanf("%c", &letter);

      // Validate letter
      letter = upperChar(letter);
      if (letter < 65 || letter > 90) continue;
      if (chrInStr(letter, tried)) continue;

      // Update tried
      u_char i;
      for (i = 0; tried[i] != '\0'; i++);
      tried[i] = letter;

      if (chrInStr(letter, word))
      {
        // Update solvedWord
        for (i = 0; word[i] != '\0'; i++)
          if (word[i] == letter) solvedWord[i] = letter;
      }
      else countdown--;
    }

  } while (1);

}

int main() {

  char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
  enum Options opt = askDifficulty(screen, HARD);
  char word[WORD_SIZE] = "PANACEIA";

  while (opt != CLOSE)
  {
    // Select a word based on difficulty
    // Play the game
    playHangman(screen, word);
    // Start Again
    opt = askDifficulty(screen, opt);
  }

  printf("Goodbye! Let's play again :>\n");

  return 0;
}