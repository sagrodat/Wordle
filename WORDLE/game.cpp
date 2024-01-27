#include "Game.hpp"

Game::Game()
{
	entries = new sf::RectangleShape*[possibleAttempts];

	int entryHeight = (sfmlObjects.getWindowHeight() - sfmlObjects.getTitleSpaceHeight()) / possibleAttempts;
	int entryWidth = (sfmlObjects.getWindowWidth()) / wordLength;

	for (int attempt = 0; attempt < possibleAttempts; attempt++)
	{
		entries[attempt] = new sf::RectangleShape[wordLength];
		for (int letter = 0; letter < wordLength; letter++)
		{
			

			entries[attempt][letter].setPosition(sf::Vector2f
			(letter * entryWidth ,
				sfmlObjects.getTitleSpaceHeight() + attempt * entryHeight ));

			entries[attempt][letter].setSize(sf::Vector2f(
				entryWidth,
				entryHeight));

			entries[attempt][letter].setOutlineThickness(-5.0f);
			entries[attempt][letter].setOutlineColor(sf::Color::White);
			entries[attempt][letter].setFillColor(sf::Color::Black);
		}
	}

}

int Game::getWordLength() { return wordLength; }
int Game::getPossibleAttempts() { return possibleAttempts; }
sf::RectangleShape** Game::getEntries() { return entries; }