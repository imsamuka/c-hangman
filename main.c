#include "screenlib.h"
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#define BUF_SIZE 256
#define WORD_SIZE 32

enum Options { CLOSE, EASY, MEDIUM, HARD };
const u_char OPT_OFFSET = 48;

char upperChar(char chr)
{
  if (chr >= 97 && chr <= 122)
    return chr - 32; // ASCII offset
  return chr;
}

void appendChr(char chr, char* str)
{
  u_char i;
  for (i = 0; str[i] != '\0'; i++);
  str[i] = chr;
  str[i+1] = '\0';
}

bool chrInStr(char chr, char* str)
{
  for (u_char i = 0; str[i] != '\0'; i++)
    if (chr == str[i]) return 1;
  return false;
}

bool strEqual(char* str1, char* str2)
{
  u_char i;
  for (i = 0; str1[i] != '\0'; i++)
    if (str1[i] != str2[i]) return 0;
  return str1[i] == str2[i];
}

void drawMan(Screen screen, char countdown)
{
  const u_char x = 7;
  const u_char y = 3;

  // Clear
  for (char i = y; i <= y+3; i++)
      for (char j = x; j <= x+2; j++)
        screen[i][j] = BLANK_CHR;

  switch (countdown)
  {
  case 0:
    screen[y+3][x+2] = '\\';
  case 1:
    screen[y+3][x+0] = '/';
  case 2:
    screen[y+1][x+2] = '\\';
  case 3:
    screen[y+1][x+0] = '/';
  case 4:
    screen[y+1][x+1] = '|';
    screen[y+2][x+1] = '|';
  case 5:
    screen[y+0][x+1] = 'O';
  default:
    break;
  }
}

enum Options askDifficulty(Screen screen)
{
  enum Options opt;

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


  // Render Screen
  clear();
  renderScr(screen);


  // Ask Difficulty Number
  {
    char selection;

    printf("Type the number: ");
    scanf(" %c", &selection);

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
  if (opt != CLOSE) sleep(1);

  return opt;
}

void playHangman(Screen screen, char* word)
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
      scanf(" %c", &letter);

      // Validate letter
      letter = upperChar(letter);
      if (letter < 65 || letter > 90) continue;
      if (chrInStr(letter, tried)) continue;

      // Update tried
      appendChr(letter, tried);

      if (chrInStr(letter, word))
      {
        // Update solvedWord
        for (u_char i = 0; word[i] != '\0'; i++)
          if (word[i] == letter) solvedWord[i] = letter;
      }
      else countdown--;
    }

  } while (1);


  // Delay
  sleep(1);
}

bool isValidWord(char* word, enum Options opt)
{
  char letters[WORD_SIZE] = "";
  u_char uniqueLetters = 0;

  for (u_char i = 0; word[i] != '\0'; i++)
  {
    if (!chrInStr(word[i], letters))
    {
      appendChr(word[i], letters);
      uniqueLetters++;
    }
  }

  switch (opt)
  {
  case HARD:
    return uniqueLetters >= 5;
  case MEDIUM:
    return uniqueLetters == 4;
  case EASY:
  default:
    return uniqueLetters == 3;
  }
}

void getWord(char* filePath, enum Options opt, char* word)
{
  FILE* fptr = (void*) 0;

  int wordIndex = rand() % 400; // Used to select a random word
  int wordsFound = 0;

  bool valid = false;

  char chr;
  char buf[BUF_SIZE] = "";

  char wordCandidate[WORD_SIZE] = "";

  printf("wordIndex: %i\n", wordIndex);

  while (wordIndex > 0)
  {

    // Open file
    fptr = fopen(filePath, "r");
    if (!fptr)
    {
      printf("Failed to open file to choose word...\n");
      exit(1);
    }

    // Iterate through file
    while (wordIndex > 0 && fgets(buf, BUF_SIZE, fptr))
    {
      // Iterate through buffer
      for (u_char i = 0; i < BUF_SIZE && buf[i] != '\0'; i++)
      {
        chr = upperChar(buf[i]);

        // Start a word
        if (!valid && chr == ' ')
        {
          valid = true;
          wordCandidate[0] = '\0';
        }

        // Construct the word
        else if (valid && chr >= 65 && chr <= 90) appendChr(chr, wordCandidate);

        // Finalize the word
        else if (valid && chr == ' ')
        {
          if (isValidWord(wordCandidate, opt))
          {
            wordsFound++;
            //printf("%i (%i) word: %s\n", wordsFound, wordIndex-1, wordCandidate);
            if (--wordIndex <= 0) break;
          }

          // Since chr is a ' ' and we didn't break, start a new word
          wordCandidate[0] = '\0';
        }

        // Invalidate the word
        else valid = false;
      }

    }

    // Close file
    fclose(fptr);

    // Avoid infinite loop - close if no word was found
    if (!wordsFound)
    {
      printf("No valid words found...\n");
      exit(1);
    }

  }

  // Copy the word
  if (isValidWord(wordCandidate, opt))
  {
    strcpy(word, wordCandidate);
  }
  else
  {
    printf("Couldn't select a valid word...\n");
    exit(1);
  }
}

int main() {

  Screen screen;
  enum Options opt = askDifficulty(screen);
  char word[WORD_SIZE] = "";
  srand(time(NULL));

  while (opt != CLOSE)
  {
    // Select a word based on difficulty
    getWord("words.txt", opt, word);
    // Play the game
    playHangman(screen, word);
    // Start Again
    opt = askDifficulty(screen);
  }

  printf("Goodbye! Let's play again :>\n");

  return 0;
}