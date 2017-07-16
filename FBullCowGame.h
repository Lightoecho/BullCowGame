/* The game logic (No view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/


#pragma once

#include <string>

// to make syntax UE4 friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {

	int32 Bulls = 0;
	int32 Cows = 0;
	
};

enum class EGuessStatus {

	Invalid_Status,
	ok,
	Not_Isogram,
	Wrong_length,
	Not_Lowercase

};

enum class EResetStatus {

	No_Hidden_Word

};

class FBullCowGame {
public:
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const ;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();

	FBullCowCount SubmitValidGuess(FString);


private:

	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};