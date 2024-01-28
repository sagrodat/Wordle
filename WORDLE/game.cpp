#include "Game.hpp"


Game::Game()
{
	//allocating memory
	boxes = new sf::RectangleShape*[possibleAttempts];
	attempts = new Attempt[possibleAttempts];
	
	//key can only be pressed if it was earlier released (otherwise user can spam)
	wasKeyReleased = new bool[ASCII_UNIQUE];
	for (int i = 0; i < ASCII_UNIQUE; i++)
	{
		wasKeyReleased[i] = true;
	}
	
	//setting up boxes(size, pos, colors)
	int entryHeight = (sfmlObjects.getWindowHeight() - sfmlObjects.getTitleSpaceHeight()) / possibleAttempts;
	int entryWidth = (sfmlObjects.getWindowWidth()) / wordLength;

	for (int attempt = 0; attempt < possibleAttempts; attempt++)
	{
		boxes[attempt] = new sf::RectangleShape[wordLength];
		for (int letter = 0; letter < wordLength; letter++)
		{
			

			boxes[attempt][letter].setPosition(sf::Vector2f
			(letter * entryWidth ,
				sfmlObjects.getTitleSpaceHeight() + attempt * entryHeight ));

			boxes[attempt][letter].setSize(sf::Vector2f(
				entryWidth,
				entryHeight));

			boxes[attempt][letter].setOutlineThickness(-5.0f);
			boxes[attempt][letter].setOutlineColor(sf::Color::White);
			boxes[attempt][letter].setFillColor(assets.colors.defaultBox);
		}
	}


	// set attempt's letters in correct positions (in boxes)
	for (int attempt = 0; attempt < possibleAttempts; attempt++)
	{
		for (int letter = 0; letter < wordLength; letter++)
		{
			// done so the string has localBounds rectangle that is used for proper positioning
			game.getAttempts()[attempt].getLetters()[letter].setString("X"); 
			assets.centerTextXYByShape(
				attempts[attempt].getLetters()[letter],
				boxes[attempt][letter]
			);
			//that character has to be then removed
			game.getAttempts()[attempt].getLetters()[letter].setString("");

		}
	}

	//set word to be guessed
	setWordToGuess();

}

Attempt* Game::getAttempts() { return attempts; }
int Game::getWordLength() { return wordLength; }
int Game::getPossibleAttempts() { return possibleAttempts; }
sf::RectangleShape** Game::getBoxes() { return boxes; }
Attempt& Game::getCurrentAttempt() { return attempts[guessIndex]; }
int Game::getCurrentLetterIndex() { return letterIndex; }
void Game::moveToNextLetter() { if (letterIndex < wordLength - 1) letterIndex++; }
void Game::moveToPreviousLetter() { if (letterIndex > 0 ) letterIndex--; }

bool  Game::getWasKeyReleased(int keyID) { return wasKeyReleased[keyID]; }
void Game::setWasKeyReleased(int keyID, bool value) { wasKeyReleased[keyID] = value; }

int Game::getNumberOfKeysPressed()
{
	int keysPressed = 0;

	for (int key = sf::Keyboard::A; key <= sf::Keyboard::KeyCount; ++key) {
		if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
			keysPressed++;
		}
	}

	return keysPressed;
	
}

const int Game::getASCII_UNIQUE() { return ASCII_UNIQUE; }

bool Game::isLetterValid(int keyCodeID)
{
	if (keyCodeID >= 0 && keyCodeID <= alphabetSize)
		return true;
	return false;
}

void Game::putLetterInCurrentBox(int keyCodeID)
{
	char currentlyPressed = keyCodeID + 'A';
	currentlyPressed = std::toupper(currentlyPressed);
	std::string asString = std::string(1, currentlyPressed);
	game.getCurrentAttempt().getLetters()[game.getCurrentLetterIndex()].setString(asString);
}


void Game::confirmAttempt()
{
	if (!guessIsAValidWord())
		return;
	colorBoxes();
	

	//extra draw here to show colors of boxes if game about to end now
	draw();

	updateGameStatus();
	if (gameStatus == LOST || gameStatus == WON)
	{
		drawEndGameScreen();
	}
	else
	{
		guessIndex++;
		letterIndex = 0;
	}
}

void Game::drawEndGameScreen()
{
	sf::Text endGameText = assets.getEndGameText();
	sf::Text restartText = assets.getRestartText();
	sf::Text correctWordText = assets.getCorrectWordText();
	correctWordText.setString(wordToGuess);

	switch (gameStatus)
	{
	case WON :
		endGameText.setString("You won!");
		endGameText.setFillColor(sf::Color::Green);
		break;
	case LOST :
		endGameText.setString("You lost!");
		endGameText.setFillColor(sf::Color::Red);
		break;
	default :
		break;
	}

	
	
	// text will be visible on top of this box
	sf::RectangleShape endGameBackground;
	endGameBackground.setFillColor(sf::Color(64, 64, 64));

	//center all texts and the background box
	sf::FloatRect restartTextRect = restartText.getLocalBounds();
	sf::FloatRect endGameTextRect = endGameText.getLocalBounds();
	sf::FloatRect correctWordTextRect = correctWordText.getLocalBounds();
	
	endGameBackground.setSize(sf::Vector2f(restartTextRect.width * 1.1, endGameTextRect.height * 2.2 + restartTextRect.height + correctWordTextRect.height));
	endGameBackground.setPosition(sf::Vector2f(
		sfmlObjects.getWindowWidth() / 2- endGameBackground.getSize().x / 2,
		sfmlObjects.getWindowHeight() / 2 - endGameBackground.getSize().y / 2));

	assets.centerTextXByShape(endGameText, endGameBackground);
	assets.centerTextXByShape(restartText, endGameBackground);
	assets.centerTextXByShape(correctWordText, endGameBackground);
	endGameText.setPosition(sf::Vector2f(endGameText.getPosition().x, endGameBackground.getPosition().y));
	correctWordText.setPosition(sf::Vector2f(correctWordText.getPosition().x, endGameBackground.getPosition().y + endGameTextRect.height + 5));
	restartText.setPosition(sf::Vector2f(restartText.getPosition().x, endGameBackground.getPosition().y + endGameTextRect.height + correctWordTextRect.height + 25));

	//draw whole endGameWindow to update colors
	//which would normally be updated in the end part of the main loop
	//(that's going to be reached but with the colors and user input letters reset)
	sfmlObjects.getWindow()->clear();
	draw();
	sfmlObjects.getWindow()->draw(endGameBackground);
	sfmlObjects.getWindow()->draw(endGameText);
	sfmlObjects.getWindow()->draw(restartText);
	sfmlObjects.getWindow()->draw(correctWordText);
	sfmlObjects.getWindow()->display();

	//wait for any user input to start new game
	sf::Event event;
	while (true)
	{
		sfmlObjects.getWindow()->pollEvent(event);
		if (event.type == sf::Event::KeyPressed)
		{
			sfmlObjects.getWindow()->clear();
			resetGame();
			break;
		}
	}
	
}
void Game::resetGame()
{
	guessIndex = 0;
	letterIndex = 0;
	for (int i = 0; i < possibleAttempts; i++)
	{
		for (int j = 0; j < wordLength; j++)
		{
			boxes[i][j].setFillColor(assets.colors.defaultBox);
			attempts[i].getLetters()[j].setString("");
		}
	}
	setWordToGuess();
	gameStatus = PLAYING;
}

void Game::updateGameStatus()
{
	int greenBoxCnt = 0;
	for (int i = 0; i < wordLength; i++) // all boxes green
	{
		if (boxes[guessIndex][i].getFillColor() == assets.colors.correctLetterCorrectSpot)
			greenBoxCnt++;
	}
	if (greenBoxCnt == wordLength)
	{
		gameStatus = WON;
		return;
	}

	if (guessIndex == possibleAttempts - 1) // last guess and not all boxes green
	{
		for (int i = 0; i < wordLength; i++)
		{
			if (boxes[guessIndex][i].getFillColor() != assets.colors.correctLetterCorrectSpot)
			{
				gameStatus = LOST;
				return;
			}
		}
	}

	gameStatus = PLAYING;
}
int Game::getGameStatus() { return gameStatus; }


bool Game::guessIsAValidWord()
{
	std::string guess;
	for (int i = 0; i < wordLength; i++)
	{
		guess += attempts[guessIndex].getLetters()[i].getString();
	}
	for (char& c : guess)
	{
		c = std::tolower(c);
	}
	for (int i = 0; i < assets.getValidWords()->size(); i++)
	{
		if (guess == assets.getValidWords()->at(i))
			return true;
	}
	return false;
}

void Game::colorBoxes()
{
	for (int i = 0; i < wordLength; i++)
	{
		std::string boxInputLetter = attempts[guessIndex].getLetters()[i].getString();

		int tag = getLetterPositionTag(boxInputLetter, i);

		switch (tag)
		{
		case CORRECTLETTER_CORRECTSPOT :
			boxes[guessIndex][i].setFillColor(assets.colors.correctLetterCorrectSpot);
			break;
		case CORRECTLETTER_WRONGSPOT :
			boxes[guessIndex][i].setFillColor(assets.colors.correctLetterWrongSpot);
			break;
		case WRONGLETTER :
			boxes[guessIndex][i].setFillColor(assets.colors.wrongLetter);
			break;
		default : 
			break;
		}
	}

}

int Game::getLetterPositionTag(std::string guessedLetter,int boxID)
{
	char guessedLetterChar = std::tolower(guessedLetter.c_str()[0]);
	if (guessedLetterChar == wordToGuess.at(boxID))
		return CORRECTLETTER_CORRECTSPOT;

	for (int i = 0; i < wordLength; i++)
	{
		if (i == boxID)
			continue;

		if (guessedLetterChar == wordToGuess.at(i))
			return CORRECTLETTER_WRONGSPOT;
	}

	return WRONGLETTER;
}


void Game::setWordToGuess()
{
	srand(time(NULL));
	int wordIndex = rand() % assets.getValidWords()->size();
	wordToGuess = assets.getValidWords()->at(wordIndex);

}
