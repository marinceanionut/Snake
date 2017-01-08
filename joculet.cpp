#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

sf::VideoMode VMode(840, 564, 32);
sf::RenderWindow win(VMode, "Snake");

void play_mode();

int main()
{

//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);


    sf::Texture Menu;
    Menu.loadFromFile("MENU.png");


    sf::Sprite sprite(Menu);


    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                win.close();
            }
            else if( event.type == sf::Event::MouseButtonPressed)
            {
                if( ( 356<event.mouseButton.x && event.mouseButton.x<466 ) && ( 314<event.mouseButton.y && event.mouseButton.y<355 ) )
                {
                    //play
                    //1 player
                    play_mode();


                }
                else if( ( 251<event.mouseButton.x && event.mouseButton.x<564 ) && ( 381<event.mouseButton.y && event.mouseButton.y<418 ) )
                {
                    //scoreboard
                    cout<<"Scorurile record\n";
                }
                else if( ( 356<event.mouseButton.x && event.mouseButton.x<460 ) && ( 448<event.mouseButton.y && event.mouseButton.y<485 ) )
                {
                    //help
                    cout<<"Pagina de ajutor.\n";
                }
                else if( ( 361<event.mouseButton.x && event.mouseButton.x<457 ) && ( 513<event.mouseButton.y && event.mouseButton.y<546 ) )
                {
                    cout<<"Iesire din program.\n";
                   //exit
                   win.close();
                }

            }
        }

        win.clear();
        win.draw(sprite);
        win.display();
    }

    return 0;
}


void play_mode()
{
    sf::Texture mod_joc;
    mod_joc.loadFromFile("play_mode.png");
    sf::Sprite sprite(mod_joc);
    while (win.isOpen() )
    {

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            else if( event.type == sf::Event::MouseButtonPressed)
            {
                if( ( 230<event.mouseButton.x && event.mouseButton.x<590 ) && ( 268<event.mouseButton.y && event.mouseButton.y<306 ) )
                {
                    cout<<"Single player mode.\n";
                }
                else if( ( 154<event.mouseButton.x && event.mouseButton.x<661 ) && ( 445<event.mouseButton.y && event.mouseButton.y<478 ) )
                {
                    cout<<"Player vs computer mode.\n";
                }
                else if( ( 194<event.mouseButton.x && event.mouseButton.x<623 ) && ( 356<event.mouseButton.y && event.mouseButton.y<393 ) )
                {
                    cout<<"Player vs player mode.\n";
                }
            }
        }

        win.clear();
        win.draw(sprite);
        win.display();

    }
}
