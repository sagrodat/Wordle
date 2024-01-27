#include <SFML/Graphics.hpp>
#include "drawing.hpp"
#include "sfmlObjects.hpp"

int main()
{
    while (sfmlObjects.getWindow()->isOpen())
    {
        sf::Event event;
        while (sfmlObjects.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                sfmlObjects.getWindow()->close();
        }
        draw();
        
    }

    return 0;
}