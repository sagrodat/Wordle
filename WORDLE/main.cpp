#include <SFML/Graphics.hpp>
#include "drawing.hpp"
#include "sfmlObjects.hpp"
#include "game.hpp"
#include <cctype>

int main()
{
 
    sf::Event event;
    while (sfmlObjects.getWindow()->isOpen())
    {  
        while (sfmlObjects.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                sfmlObjects.getWindow()->close();

            if (event.type == sf::Event::KeyPressed && game.getWasKeyReleased(event.key.code))
            {
                if (event.key.code == sf::Keyboard::Backspace)
                {
                    if (game.getCurrentAttempt().getLetters()[game.getCurrentLetterIndex()].getString() == "")
                        game.moveToPreviousLetter();
                    game.getCurrentAttempt().getLetters()[game.getCurrentLetterIndex()].setString("");
                }
                else if (event.key.code == sf::Keyboard::Enter 
                    && game.getCurrentAttempt().getLetters()[game.getWordLength()-1].getString() != "")
                {
                    game.confirmAttempt();
                }
                else if(game.isLetterValid(event.key.code))
                {
                    game.setWasKeyReleased(event.key.code, false);

                    //avoid overwriting character in last box ( you have to backsapce first )
                    if (!(game.getCurrentLetterIndex() == game.getWordLength() - 1 
                        && game.getCurrentAttempt().getLetters()[game.getCurrentLetterIndex()].getString() != ""))
                    {
                        game.putLetterInCurrentBox(event.key.code);
                    }
                    game.moveToNextLetter();
                  
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                game.setWasKeyReleased(event.key.code, true);
            }
        }

        
        

       
        draw();
        
    }

    return 0;
}