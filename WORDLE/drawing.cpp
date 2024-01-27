#include "drawing.hpp"
#include "sfmlObjects.hpp"
#include "assets.hpp"
#include "game.hpp"

void draw()
{
    sfmlObjects.getWindow()->clear();
    sfmlObjects.getWindow()->draw(assets.getTitleText());
    for (int attempt = 0; attempt < game.getPossibleAttempts(); attempt++)
    {
        for (int letter = 0; letter < game.getWordLength(); letter++)
        {
            sfmlObjects.getWindow()->draw(game.getEntries()[attempt][letter]);
        }
    }
    sfmlObjects.getWindow()->display();
    
}