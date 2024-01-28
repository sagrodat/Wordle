#include "attempt.hpp"

Attempt::Attempt() 
{
	letters = new sf::Text[wordLength];
	for (int i = 0; i < wordLength; i++)
	{
		letters[i].setFont(assets.getGameFont());
		letters[i].setFillColor(assets.colors.defaultLetter);
		letters[i].setCharacterSize(defaultCharacterSize);
		//position set in game.cpp constructor
		
		//text set by user later 
	}
}

sf::Text* Attempt::getLetters() {	return letters; }
