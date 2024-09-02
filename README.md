# Hangman Game

This is a simple console-based Hangman game implemented in C++. The game includes a "dancing" hangman animation when the player wins, a "game over" animation in case of losing, and different difficulty levels for players to choose from.

## Features

- **Three Difficulty Levels**: Easy, Medium, Hard (chosen using toggle controls).
- **Dynamic Animations**: 
  - "Dancing Hangman" animation when the player wins.
  - "Game Over" animation displayed in a fixed rectangle when the player loses.
- **Remaining Guesses Display**: A countdown of remaining guesses.
- **Case Insensitivity**: The game is not case-sensitive.
  
## How to Play

1. **Run the Program**: Compile and run the `hangman.cpp` file using any standard C++ compiler.
2. **Choose Difficulty**: Type `>` to toggle through the difficulty levels and `.` to confirm your choice.
3. **Guess Letters**: Enter letters to guess the hidden word. If the guess is correct, the word will be revealed incrementally. If not, the hangman figure will start to form.
4. **Win or Lose**: 
   - If you guess all the letters correctly before the hangman is fully drawn, you win, and the hangman will dance!
   - If you fail to guess the word within the allowed number of incorrect guesses, the "Game Over" animation is shown.

## Requirements

- A C++ compiler that supports C++11 or later.
- The ability to clear the console screen (platform-dependent).

## How to Compile

Use any standard C++ compiler
