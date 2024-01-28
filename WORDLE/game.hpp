#pragma once
#include "assets.hpp"
#include "attempt.hpp"
#include "drawing.hpp"
class Game {
public :
	Game();
private :
	int guessIndex = 0;
	int letterIndex = 0;

	
	
	const int ASCII_UNIQUE = sf::Keyboard::KeyCount;
	const int alphabetSize = 25;
	bool * wasKeyReleased; // to avoid spamming letters by holding

	const int wordLength = Attempt::wordLength;
	const int possibleAttempts = Attempt::possibleAttempts;

	Attempt* attempts;
	sf::RectangleShape** boxes;

	std::string wordToGuess;
	
	int gameStatus = PLAYING;
	enum gameStatus {
		PLAYING,
		WON,
		LOST
	};

	enum letterPositions {
		CORRECTLETTER_WRONGSPOT,
		CORRECTLETTER_CORRECTSPOT,
		WRONGLETTER
	};

public :
	int getWordLength();
	int getPossibleAttempts();
	sf::RectangleShape** getBoxes();
	Attempt* getAttempts();
	Attempt& getCurrentAttempt();
	int getCurrentLetterIndex();
	void moveToNextLetter();
	void moveToPreviousLetter();

	bool getWasKeyReleased(int keyID);
	void setWasKeyReleased(int keyID, bool value);

	const int getASCII_UNIQUE();

	bool isLetterValid(int keyCodeID);
	int getNumberOfKeysPressed();
	void putLetterInCurrentBox(int keyCodeID);

	void confirmAttempt();
	void colorBoxes();

	void setWordToGuess();
	int getLetterPositionTag(std::string guessedLetter, int boxID);

	bool guessIsAValidWord();

	int getGameStatus();
	void updateGameStatus();

	void drawEndGameScreen();

	void resetGame();


};
inline Game game;