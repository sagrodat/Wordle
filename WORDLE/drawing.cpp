#include "drawing.hpp"
#include "sfmlObjects.hpp"
#include "assets.hpp"
#include "game.hpp"

void draw()
{
    sfmlObjects.getWindow()->clear();

    sfmlObjects.getWindow()->draw(assets.getBackgroundRect());
    //draw boxes and letters on top
    for (int attempt = 0; attempt < game.getPossibleAttempts(); attempt++)
    {
        for (int letter = 0; letter < game.getWordLength(); letter++)
        {
            sfmlObjects.getWindow()->draw(game.getBoxes()[attempt][letter]);
            sfmlObjects.getWindow()->draw(game.getAttempts()[attempt].getLetters()[letter]);
        }
    }

    //draw title
    sfmlObjects.getWindow()->draw(assets.getTitleText());
   
    sfmlObjects.getWindow()->display();
    
}