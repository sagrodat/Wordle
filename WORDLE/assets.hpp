#pragma once
#include "SFML/Graphics.hpp"
#include "resourcesPath.hpp"
#include "sfmlObjects.hpp"
#include <fstream>


class Assets
{
public:
	Assets();
private:
	//////////////// TEXT //////////////////////
	struct {
		sf::Font font;
		std::string path = resourcesPath.concatenate("fonts\\titlefont.otf");
	}titleFont;

	struct {
		sf::Font font;
		std::string path = resourcesPath.concatenate("fonts\\gamefont.otf");
	}gameFont;

	struct {
		sf::Text text;
		sf::Color color = sf::Color(sf::Color::White);
		std::string content = "WORDLE";
		int characterSize = 50;
		sf::Vector2f position = sf::Vector2f(0, 25);
	}titleText;

	////////////// FILES ////////////////////////

	std::vector<std::string> * validWords;
	std::string validWordsPath = resourcesPath.concatenate("validWords.txt");

	/////////////// END GAME SCREEN /////////////////////
	struct {
		sf::Text text;
		int characterSize = 50;
	}endGameText;

	struct {
		sf::Text text;
		sf::Color color = sf::Color(sf::Color::White);
		sf::String content = "Press any key to restart...";
		int characterSize = 25;
	}restartText;

	struct {
		sf::Text text;
		sf::Color color = sf::Color(sf::Color::White);
		int characterSize = 50;
	}correctWord;

	////////// BACKGROUND PLANE /////////////////
	struct {
		sf::RectangleShape rect;
		sf::Vector2f position = sf::Vector2f(0, 0);
		sf::Color color = sf::Color(40, 40, 40); // dark gray
		sf::Vector2f size = sf::Vector2f(sfmlObjects.getWindowWidth(), sfmlObjects.getWindowHeight());
	}background;
	

public :
	/////////// BOXES //////////////

	struct {
		sf::Color defaultBox = sf::Color(80,80,80); // kinda gray
		sf::Color defaultLetter = sf::Color::White;
		sf::Color correctLetterWrongSpot = sf::Color(200, 200, 0); //dark yellow
		sf::Color correctLetterCorrectSpot = sf::Color(0, 200, 0);// dark green
		sf::Color wrongLetter = sf::Color(200, 0, 0); // dark red
	}colors;

	

public :
	sf::Font & getGameFont(); // passed by reference because copy isn't done correctly by SFML
	sf::Text getTitleText();
	void loadAssets();
	void centerTextXByWindow(sf::Text& text);
	void centerTextXYByShape(sf::Text& text, sf::RectangleShape shape);
	void centerTextXByShape(sf::Text& text, sf::RectangleShape shape);
	std::vector<std::string> *getValidWords();
	sf::Text& getEndGameText();
	sf::Text getRestartText();
	sf::Text&getCorrectWordText();
	sf::RectangleShape getBackgroundRect();
};
inline Assets assets;