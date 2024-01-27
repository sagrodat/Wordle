#include "assets.hpp"

Assets::Assets()
{
	loadAssets();
}

void Assets::loadAssets()
{
	titleFont.font.loadFromFile(titleFont.path);
	gameFont.font.loadFromFile(gameFont.path);

	titleText.text.setFont(titleFont.font);
	titleText.text.setFillColor(titleText.color);
	titleText.text.setPosition(titleText.position);
	titleText.text.setCharacterSize(titleText.characterSize);
	titleText.text.setString(titleText.content);
	centerText(titleText.text);
}

void Assets::centerText(sf::Text& text)
{
	float centerX = sfmlObjects.getWindowWidth() / 2;
	sf::FloatRect textBounds = text.getLocalBounds();
	text.setPosition(sf::Vector2f(centerX - textBounds.width / 2, text.getPosition().y));
}

sf::Text Assets::getTitleText() { return titleText.text; }