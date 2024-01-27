#pragma once
#include "SFML/Graphics.hpp"
#include "resourcesPath.hpp"
#include "sfmlObjects.hpp"


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

public :
	sf::Text getTitleText();
	void loadAssets();
	void centerText(sf::Text& text);
};
inline Assets assets;