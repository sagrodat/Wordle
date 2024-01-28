#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "assets.hpp"


class Attempt
{
public :
	Attempt();

	static const int wordLength = 5;
	static const int possibleAttempts = 6;

private :


	const int defaultCharacterSize = 50;
	
	

	sf::Text * letters;
	


public :
	sf::Text * getLetters();
};