/* This is the console executable, that make use of the BullCow class
 * This acts as the view in a MVC pattern, and is responsible for all
 * user interaction. For gamelogic see the FBullCowGame class
 */

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax UE4 friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool ASKToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game, which we re-use across plays

// The entry point for our Aplication
int main() {
	
	std::cout << BCGame.GetCurrentTry();

	bool bPlayAgin = false;

	do {

		PrintIntro();
		PlayGame();
		bPlayAgin = ASKToPlayAgain();

	} while (bPlayAgin);

	return 0; // Leave the Game

}

void PrintIntro() {

	std::cout << "         }---{         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;

}

// plays a single game to completion
void PlayGame() {

	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop asking for guesses while the game
	// is NOT won and there are still turns remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { 

		FText Guess = GetValidGuess();

		// Submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually untill the user gives a valid guess
FText GetValidGuess() {

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter isogram.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is guess is valid
			break;
		}
	} while (Status != EGuessStatus::ok); // Keep looping until we get no errors
	return Guess;
}

bool ASKToPlayAgain() {

	std::cout << "Do you want to play again with the same hidden word? (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');

	std::cout << std::endl;

	return false;

}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU HAVE GUESS THE HIDDEN WORD\n";
	} else {
		std::cout << "YOU HAVE FAILED TO GUESS THE HIDDEN WORD\n";
	}
}
