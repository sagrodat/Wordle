#pragma once
#include "SFML/Graphics.hpp"
class SFMLObjects {
public:
	SFMLObjects();
private:
	const int WINDOW_WIDTH = 700;
	const int WINDOW_HEIGHT = 700;
	const int TITLE_SPACE_HEIGHT = 100;
	sf::RenderWindow* window;
	sf::Mouse* mouse;

public:
	sf::RenderWindow* getWindow();
	const int getWindowHeight();
	const int getWindowWidth();
	const int getTitleSpaceHeight();
	sf::Mouse* getMouse();
};
inline SFMLObjects sfmlObjects;