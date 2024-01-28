#include "assets.hpp"

Assets::Assets()
{
	loadAssets();
}

void Assets::loadAssets()
{
	//fonts
	titleFont.font.loadFromFile(titleFont.path);
	gameFont.font.loadFromFile(gameFont.path);

	//title text
	titleText.text.setFont(titleFont.font);
	titleText.text.setFillColor(titleText.color);
	titleText.text.setPosition(titleText.position);
	titleText.text.setCharacterSize(titleText.characterSize);
	titleText.text.setString(titleText.content);
	centerTextXByWindow(titleText.text);

	//list of valid words in game
	validWords = new std::vector<std::string>;
	std::ifstream wordsFile(validWordsPath);
	std::string word;
	while (std::getline(wordsFile, word))
	{
		validWords->push_back(word);
	}

	//end game text
	endGameText.text.setCharacterSize(endGameText.characterSize);
	endGameText.text.setFont(gameFont.font);

	//restart text
	restartText.text.setCharacterSize(restartText.characterSize);
	restartText.text.setFillColor(restartText.color);
	restartText.text.setString(restartText.content);
	restartText.text.setFont(gameFont.font);

	//background rect
	background.rect.setSize(background.size);
	background.rect.setPosition(background.position);
	background.rect.setFillColor(background.color);


}

void Assets::centerTextXByWindow(sf::Text& text)
{
	float centerX = sfmlObjects.getWindowWidth() / 2;
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setPosition(sf::Vector2f(centerX - textBounds.width / 2, text.getPosition().y));
}


void Assets::centerTextXYByShape(sf::Text& text, sf::RectangleShape shape)
{

	float centerX = shape.getPosition().x + (shape.getSize().x / 2);
	
	sf::FloatRect textBounds = text.getLocalBounds();

	float centerY = shape.getPosition().y + (shape.getSize().y / 2);

	text.setPosition(sf::Vector2f(centerX - textBounds.width / 2, centerY - textBounds.height));
}

void Assets::centerTextXByShape(sf::Text& text, sf::RectangleShape shape)
{
	float centerX = shape.getPosition().x + (shape.getSize().x / 2);

	sf::FloatRect textBounds = text.getLocalBounds();

	text.setPosition(sf::Vector2f(centerX - textBounds.width / 2, text.getPosition().y));

}

sf::Text Assets::getTitleText() { return titleText.text; }
sf::Font & Assets::getGameFont() { return gameFont.font; }

std::vector<std::string> * Assets::getValidWords() { return validWords; }

sf::Text& Assets::getEndGameText() { return endGameText.text; }
sf::Text Assets::getRestartText() { return restartText.text; }

sf::RectangleShape Assets::getBackgroundRect() { return background.rect; }
