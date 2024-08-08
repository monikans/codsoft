#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits> 

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    int randomNumber = std::rand() % 100 + 1;
    int userGuess = 0;

    std::cout << "Welcome to the Number Guessing Game!" << std::endl;
    std::cout << "I have generated a random number between 1 and 100." << std::endl;
    while (userGuess != randomNumber) {
        std::cout << "Please enter your guess: ";
        if (!(std::cin >> userGuess)) {
            std::cout << "Invalid input. Please enter a number between 1 and 100." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (userGuess < 1 || userGuess > 100) {
            std::cout << "Please enter a valid number between 1 and 100." << std::endl;
            continue; 
        }

        if (userGuess < randomNumber) {
            std::cout << "Your guess is too low. Try again!" << std::endl;
        } else if (userGuess > randomNumber) {
            std::cout << "Your guess is too high. Try again!" << std::endl;
        } else {
            std::cout << "Congratulations! You've guessed the correct number: " << randomNumber << std::endl;
        }
    }

    return 0;
}