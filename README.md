# c-hangman
Practice by creating the HangMan game in pure C

## Specifications

- Pick words in a text file
- Limited number of tries
- Words must not have special characters
- Visual feedback for:
  - Opening, Choosing Difficulty
  - Closing the program
  - Winning
  - Losing
  - Number of tries left (Counter + Hangman)
- Difficulty Setting:
  - Easy: 3 Unique letters
  - Medium: 4 Unique Letters
  - Hard: more than 5 Unique Letters

## Game Flow

1. First Screen.
2. Ask the difficulty or close, then select a random word with the specified setting.
3. Open the main game UI: plot letter quantity, the loose, and the tries countdown.
4. Ask for a letter.
    - If letter was selected previously, return to 3.
    - If letter exists in the word, update the variables. If the word is complete, show win and return to 2, else return to 3.
    - If letter don't exist in the word, decrease countdown. If countdown is 0, show Lose and return to 2, else return to 3.


