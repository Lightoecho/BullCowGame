#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax UE4 friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7,21} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {

	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;

}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const { 
	
	if (!IsIsogram(Guess)) { // If the guess isn't an isogram 
	
		return EGuessStatus::Not_Isogram;  

	} else if (!IsLowercase(Guess)) { // If guess isn't all lowercase

		return EGuessStatus::Not_Lowercase;

	} else if ( Guess.length() != GetHiddenWordLength()) { // If the guess length

		return EGuessStatus::Wrong_length;

	} else {

		return EGuessStatus::ok;

	}
	
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {

	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match
			if(Guess[GChar] == MyHiddenWord[MHWChar]) {
				// incriment bulls if they're in the same place
				if (MHWChar == GChar) {
					BullCowCount.Bulls++; //incrimetns bulls
				} else {
					BullCowCount.Cows++; // must be a cow
				}
				
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {

	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) {            // for all letters of the word

		Letter = tolower(Letter);   // handle mixed case
		if (LetterSeen[Letter]) {         // if letter is in the map
			return false;   // we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true; // for example in cases where /0 us entered
}

bool FBullCowGame::IsLowercase(FString Word) const {

	for (auto Letter : Word) {

		if (!islower(Letter)) { // if not a lowercase letter
			return false;
		}
	}
	return true;
}
