#pragma once
#include "assets.hpp"
class Game {
public :
	Game();
private :
	int guessIndex = 0;
	int letterIndex = 0;

	const int wordLength = 5;
	const int possibleAttempts = 6;

	sf::RectangleShape** entries;

public :
	int getWordLength();
	int getPossibleAttempts();
	sf::RectangleShape** getEntries();
};
inline Game game;