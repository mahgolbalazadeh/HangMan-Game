#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Function to clear the console screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to display the current state of the hangman
void displayHangman(int incorrectGuesses) {
    vector<string> hangman = {
        " +---+",
        " |   |",
        "     |",
        "     |",
        "     |",
        "     |",
        "======"
    };

    if (incorrectGuesses > 0) hangman[2] = " O   |";   // Head
    if (incorrectGuesses > 1) hangman[3] = " |   |";   // Body
    if (incorrectGuesses > 2) hangman[3] = "/|   |";   // One arm
    if (incorrectGuesses > 3) hangman[3] = "/|\\  |";  // Both arms
    if (incorrectGuesses > 4) hangman[4] = "/    |";   // One leg
    if (incorrectGuesses > 5) hangman[4] = "/ \\  |";  // Both legs

    for (const auto& line : hangman) {
        cout << line << endl;
    }
}

// Function to display remaining guesses as a countdown
void displayCountdown(int remainingGuesses) {
    cout << "Remaining guesses: " << remainingGuesses << endl;
}

// Function to display a dancing hangman animation when the player wins
void displayDance() {
    vector<string> danceFrames = {
        " \\O/  \n  |   \n / \\  ",
        "  O   \n /|\\  \n / \\  ",
        " \\O   \n  |\\  \n / \\  ",
        "  O/  \n /|   \n / \\  "
    };

    // Loop through the dance frames to animate
    for (int i = 0; i < 12; ++i) {
        clearScreen(); // Clear the screen for each frame
        cout << danceFrames[i % danceFrames.size()] << endl;
        this_thread::sleep_for(chrono::milliseconds(400)); // Delay between frames
    }
}

// Function to display a "Game Over" animation in a fixed rectangle
void displayGameOverAnimation() {
    vector<string> gameOverFrames = {
        "***************\n*  GAME OVER  *\n***************",
        "***************\n*   GAME OVER *\n***************",
        "***************\n*    GAME OVER*\n***************",
        "***************\n*   GAME OVER *\n***************"
    };

    // Loop through the frames to animate "Game Over"
    for (int i = 0; i < 8; ++i) {
        clearScreen(); // Clear the screen for each frame
        cout << gameOverFrames[i % gameOverFrames.size()] << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // Delay between frames
    }
}

// Function to randomly select a word from a chosen difficulty level
string getRandomWord(const vector<string>& words) {
    return words[rand() % words.size()];
}

// Function to display the difficulty selection toggle
string chooseDifficulty() {
    vector<string> difficulties = {"Easy", "Medium", "Hard"};
    int currentChoice = 0;
    char input;

    while (true) {
        clearScreen();
        cout << "Select Difficulty: [" << difficulties[currentChoice] << "]" << endl;
        cout << "Type '>' to toggle to the next difficulty, '.' to confirm: ";
        cin >> input;

        if (input == '>') {
            currentChoice = (currentChoice + 1) % difficulties.size();  // Cycle through options
        } else if (input == '.') {
            break; // Confirm selection
        }
    }

    return difficulties[currentChoice];
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    // Word lists based on difficulty
    vector<string> easyWords = {"hat", "cat", "pen", "sun", "dog", "red", "cup"};
    vector<string> mediumWords = {"village", "knife", "orange", "rabbit", "school", "market", "theater", "flower"};
    vector<string> hardWords = {"computer", "mountain", "restaurant", "hospital", "backpack", "stadium", "pajamas"};

    string difficulty = chooseDifficulty();
    vector<string> chosenWords;

    if (difficulty == "Easy") {
        chosenWords = easyWords;
    } else if (difficulty == "Medium") {
        chosenWords = mediumWords;
    } else if (difficulty == "Hard") {
        chosenWords = hardWords;
    }

    string wordToGuess = getRandomWord(chosenWords);
    string guessedWord(wordToGuess.length(), '_');
    int incorrectGuesses = 0;
    const int maxIncorrectGuesses = 6;
    vector<char> incorrectLetters;

    while (incorrectGuesses < maxIncorrectGuesses && guessedWord != wordToGuess) {
        cout << "Current word: " << guessedWord << endl;
        cout << "Incorrect guesses: ";
        for (char letter : incorrectLetters) {
            cout << letter << " ";
        }
        cout << endl;

        displayHangman(incorrectGuesses);
        displayCountdown(maxIncorrectGuesses - incorrectGuesses);

        char guess;
        cout << "Enter your guess: ";
        cin >> guess;
        guess = tolower(guess);

        if (wordToGuess.find(guess) != string::npos) {
            for (size_t i = 0; i < wordToGuess.length(); i++) {
                if (wordToGuess[i] == guess) {
                    guessedWord[i] = guess;
                }
            }
        } else {
            incorrectLetters.push_back(guess);
            incorrectGuesses++;
        }
    }

    // If the player wins, show dance animation
    if (guessedWord == wordToGuess) {
        cout << "Congratulations! You've guessed the word: " << wordToGuess << endl;
        displayDance();  // Show the dancing hangman
    } else {
        cout << "Game Over! The word was: " << wordToGuess << endl;
        displayHangman(maxIncorrectGuesses);  // Display the full hangman
        displayGameOverAnimation();  // Display the game over animation
    }

    return 0;
}
