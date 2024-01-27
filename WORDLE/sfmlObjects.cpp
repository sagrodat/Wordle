#include "SFMLObjects.hpp"
SFMLObjects::SFMLObjects()
{
	window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake game", sf::Style::Titlebar | sf::Style::Close);
	mouse = new sf::Mouse;
}

sf::RenderWindow* SFMLObjects::getWindow() { return window; }
sf::Mouse* SFMLObjects::getMouse() { return mouse; }
const int SFMLObjects::getWindowHeight() { return WINDOW_HEIGHT; }
const int SFMLObjects::getWindowWidth() { return WINDOW_WIDTH; }
const int SFMLObjects::getTitleSpaceHeight() { return TITLE_SPACE_HEIGHT; }