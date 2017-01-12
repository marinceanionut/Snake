#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

sf::VideoMode VMode(840, 564, 32);
sf::RenderWindow win(VMode, "Snake");
struct coordonate
{
    int x, y;
};
int Map[1000][1000];
int prim, ultim, prim_second, ultim_second;
coordonate worm[200000], worm_second[200000];
coordonate mar;
int vdir[10000];
int Mlee[100][100];

void play_mode();
bool single_player();
bool multiplayer();
bool vs_computer();

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
    mod_joc.loadFromFile("play_modes.png");
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
                     if(!single_player()) win.close();
                }
                else if( ( 154<event.mouseButton.x && event.mouseButton.x<661 ) && ( 445<event.mouseButton.y && event.mouseButton.y<478 ) )
                {
                    if(!vs_computer()) win.close();
                }
                else if( ( 194<event.mouseButton.x && event.mouseButton.x<623 ) && ( 356<event.mouseButton.y && event.mouseButton.y<393 ) )
                {
                    if(!multiplayer()) win.close();
                }
            }
        }

        win.clear();
        win.draw(sprite);
        win.display();

    }
}
bool single_player()
{
    int dir=1, i, prim, ultim;
    char nume[]="head0.png";
    coordonate nou;
    sf::Texture background;
    background.loadFromFile("BACKGROUND.jpg");
    sf::Sprite sprite1(background);
    sf::Clock clock;
    sf::Texture pen;
    pen.loadFromFile("mar.png");
    sf::Sprite apple(pen);
    sf::Texture body;
    body.loadFromFile("interior_segment.png");
    sf::Sprite segm(body);
    sf::Texture head;

    coordonate d[10];

    d[0].x=0; d[1].x=1; d[2].x=0; d[3].x=-1;
    d[0].y=-1; d[1].y=0; d[2].y=1; d[3].y=0;


    mar.x=10;
    mar.y=10;
    prim=0;
    ultim=1;
    nou.x=12;
    nou.y=5;
    worm[0]=nou;
    nou.x=13;
    nou.y=5;
    worm[1]=nou;
    Map[5][13]=Map[5][12]=1;

    while(win.isOpen())
    {

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                //win.close();
                return 0;
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Up && dir!=2)
                    dir=0;
                else if(event.key.code == sf::Keyboard::Down && dir!=0)
                    dir=2;
                else if(event.key.code == sf::Keyboard::Right && dir!=3)
                    dir=1;
                else if(event.key.code == sf::Keyboard::Left && dir!=1)
                    dir=3;

            }


        }
        if(clock.getElapsedTime().asMilliseconds()>=75)
        {
            clock.restart();
            nou.x=worm[ultim].x+d[dir].x;
            nou.y=worm[ultim].y+d[dir].y;

            if(nou.x==-1) nou.x=21;
            else if (nou.x==21 ) nou.x=0;

            if(nou.y==-1) nou.y=14;
            else if (nou.y==14) nou.y=0;

            worm[++ultim]=nou;

            if(Map[worm[ultim].y][worm[ultim].x])
            {
                //game over

                return 0;

            }
            else Map[worm[ultim].y][worm[ultim].x]=1;

            if(worm[ultim].x==mar.x && worm[ultim].y==mar.y)
            {


                do{
                    mar.x = rand() % 20 + 1;
                    mar.y = rand() % 13 + 1;
                }
                while ( Map[mar.y][mar.x]);
            }
            else
            {
                Map[ worm[prim].y ] [worm[prim].x ]=0;
                ++prim;
            }
        }
         nume[4]=dir+'0';
        head.loadFromFile(nume);
        sf::Sprite capet(head);
        win.clear();
        win.draw(sprite1);
        apple.setPosition(40*mar.x, 40*mar.y);
        win.draw(apple);
        //desenez rama


        for(i=prim; i<ultim; ++i)
        {
            segm.setPosition(40*worm[i].x, 40*worm[i].y);
            win.draw(segm);
        }

        capet.setPosition(40*worm[ultim].x, 40*worm[ultim].y);
        win.draw(capet);



        win.display();
    }

    return 0;

}


bool multiplayer ()
{
    int dir=1, dir_second=1, i, prim, ultim, prim_second, ultim_second;
    char nume[]="head0.png";
    char nume1[]="header0.png";
    coordonate nou;
    sf::Texture background;
    background.loadFromFile("BACKGROUND.jpg");
    sf::Sprite sprite1(background);
    sf::Clock clock;
    sf::Texture pen;
    pen.loadFromFile("mar.png");
    sf::Sprite apple(pen);

    sf::Texture body;
    body.loadFromFile("interior_segment.png");
    sf::Sprite segm(body);
    sf::Texture head;

    sf::Texture body1;
    body1.loadFromFile("interior_segmenth.png");
    sf::Sprite segm1(body1);
    sf::Texture header;

    coordonate d[10];

    d[0].x=0; d[1].x=1; d[2].x=0; d[3].x=-1;
    d[0].y=-1; d[1].y=0; d[2].y=1; d[3].y=0;


    //adaug corpul
    mar.x=10;
    mar.y=10;

    prim=0;
    ultim=1;
    nou.x=12;
    nou.y=5;
    worm[0]=nou;
    nou.x=13;
    nou.y=5;
    worm[1]=nou;
    Map[5][13]=Map[5][12]=1;


    prim_second=0;
    ultim_second=1;
    nou.x=12;
    nou.y=3;
    worm_second[0]=nou;
    nou.x=13;
    nou.y=3;
    worm_second[1]=nou;
    Map[3][13]=Map[3][12]=2;

    while(win.isOpen())
    {

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                //win.close();
                return 0;
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Up && dir!=2)
                    dir=0;
                else if(event.key.code == sf::Keyboard::Down && dir!=0)
                    dir=2;
                else if(event.key.code == sf::Keyboard::Right && dir!=3)
                    dir=1;
                else if(event.key.code == sf::Keyboard::Left && dir!=1)
                    dir=3;
                else if(event.key.code == sf::Keyboard::W && dir_second!=2)
                    dir_second=0;
                else if(event.key.code == sf::Keyboard::S && dir_second!=0)
                    dir_second=2;
                else if(event.key.code == sf::Keyboard::D && dir_second!=3)
                    dir_second=1;
                else if(event.key.code == sf::Keyboard::A && dir_second!=1)
                    dir_second=3;
            }


        }


        //delay

        if(clock.getElapsedTime().asMilliseconds()>=75)
        {
            ///primul sarpe
            clock.restart();

            nou.x=worm[ultim].x+d[dir].x;
            nou.y=worm[ultim].y+d[dir].y;

            if(nou.x==-1) nou.x=21;
            else if (nou.x==21 ) nou.x=0;

            if(nou.y==-1) nou.y=14;
            else if (nou.y==14) nou.y=0;

            worm[++ultim]=nou;

            if(Map[worm[ultim].y][worm[ultim].x]==1)
            {
                //game over
                return 0;

            }
            else Map[worm[ultim].y][worm[ultim].x]=1;

            if(worm[ultim].x==mar.x && worm[ultim].y==mar.y)
            {

                do{
                    mar.x = rand() % 20 + 1;
                    mar.y = rand() % 13 + 1;
                }
                while ( Map[mar.y][mar.x]);
            }
            else
            {
                Map[ worm[prim].y ] [worm[prim].x ]=0;
                ++prim;
            }

            ///al doilea sarpe

            nou.x=worm_second[ultim_second].x+d[dir_second].x;
            nou.y=worm_second[ultim_second].y+d[dir_second].y;

            if(nou.x==-1) nou.x=21;
            else if (nou.x==21 ) nou.x=0;

            if(nou.y==-1) nou.y=14;
            else if (nou.y==14) nou.y=0;

            worm_second[++ultim_second]=nou;

            if(Map[worm_second[ultim_second].y][worm_second[ultim_second].x]==2)
            {
                //game over
                return 0;

            }
            else Map[worm_second[ultim_second].y][worm_second[ultim_second].x]=2;


            if(worm_second[ultim_second].x==mar.x && worm_second[ultim_second].y==mar.y)
            {

                do{
                    mar.x = rand() % 20 + 1;
                    mar.y = rand() % 13 + 1;
                }
                while ( Map[mar.y][mar.x]);
            }
            else
            {
                Map[ worm_second[prim_second].y ] [worm_second[prim_second].x ]=0;
                ++prim_second;
            }

        }

        ///primul sarpe

        nume[4]=dir+'0';
        head.loadFromFile(nume);
        sf::Sprite capet(head);
        win.clear();
        win.draw(sprite1);
        apple.setPosition(40*mar.x, 40*mar.y);
        win.draw(apple);
        //desenez rama


        for(i=prim; i<ultim; ++i)
        {
            segm.setPosition(40*worm[i].x, 40*worm[i].y);
            win.draw(segm);
        }

        capet.setPosition(40*worm[ultim].x, 40*worm[ultim].y);
        win.draw(capet);


        ///al doilea sarpe

        nume1[6]=dir_second+'0';
        header.loadFromFile(nume1);
        sf::Sprite capet2(header);
        //desenez rama


        for(i=prim_second; i<ultim_second; ++i)
        {
            segm1.setPosition(40*worm_second[i].x, 40*worm_second[i].y);
            win.draw(segm1);
        }

        capet2.setPosition(40*worm_second[ultim_second].x, 40*worm_second[ultim_second].y);
        win.draw(capet2);



        win.display();
    }
    return 1;
}

bool vs_computer()
{
    int dir=1, dir_second=1, i, nr;
    char nume[]="head0.png";
    char nume1[]="header0.png";
    int lg=0;
    coordonate nou;
    sf::Texture background;
    background.loadFromFile("BACKGROUND.jpg");
    sf::Sprite sprite1(background);
    sf::Clock clock;
    sf::Texture pen;
    pen.loadFromFile("mar.png");
    sf::Sprite apple(pen);

    sf::Texture body;
    body.loadFromFile("interior_segment.png");
    sf::Sprite segm(body);
    sf::Texture head;

    sf::Texture body1;
    body1.loadFromFile("interior_segmenth.png");
    sf::Sprite segm1(body1);
    sf::Texture header;

    coordonate d[10];

    d[0].x=0; d[1].x=1; d[2].x=0; d[3].x=-1;
    d[0].y=-1; d[1].y=0; d[2].y=1; d[3].y=0;


    //adaug corpul
    mar.x=10;
    mar.y=10;

    prim=0;
    ultim=1;
    nou.x=12;
    nou.y=5;
    worm[0]=nou;
    nou.x=13;
    nou.y=5;
    worm[1]=nou;
    Map[5][13]=Map[5][12]=1;


    prim_second=0;
    ultim_second=1;
    nou.x=12;
    nou.y=3;
    worm_second[0]=nou;
    nou.x=13;
    nou.y=3;
    worm_second[1]=nou;
    Map[3][13]=Map[3][12]=2;

    lee(mar, worm_second[ultim]);
    nr=0;

    while(win.isOpen())
    {

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                //win.close();
                return 0;
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Up && dir!=2)
                    dir=0;
                else if(event.key.code == sf::Keyboard::Down && dir!=0)
                    dir=2;
                else if(event.key.code == sf::Keyboard::Right && dir!=3)
                    dir=1;
                else if(event.key.code == sf::Keyboard::Left && dir!=1)
                    dir=3;

            }


        }


        //delay

        if(clock.getElapsedTime().asMilliseconds()>=100)
        {
            ///primul sarpe
            clock.restart();

            nou.x=worm[ultim].x+d[dir].x;
            nou.y=worm[ultim].y+d[dir].y;

            if(nou.x==-1) nou.x=21;
            else if (nou.x==22 ) nou.x=0;

            if(nou.y==-1) nou.y=14;
            else if (nou.y==15) nou.y=0;

            worm[++ultim]=nou;

            if(Map[worm[ultim].y][worm[ultim].x]==1)
            {
                //game over
                return 0;

            }
            else Map[worm[ultim].y][worm[ultim].x]=1;

            if(worm[ultim].x==mar.x && worm[ultim].y==mar.y)
            {

                do{
                    mar.x = rand() % 20 + 1;
                    mar.y = rand() % 13 + 1;
                }
                while ( Map[mar.y][mar.x]);
                lee(mar, worm_second[ultim_second]);
                nr=0;
            }
            else
            {
                Map[ worm[prim].y ] [worm[prim].x ]=0;
                ++prim;
            }

            ///al doilea sarpe

            dir_second=vdir[++nr];
            nou.x=worm_second[ultim_second].x+d[dir_second].x;
            nou.y=worm_second[ultim_second].y+d[dir_second].y;



            if(nou.x==-1)
                nou.x=21;
            else if (nou.x==22 )
                nou.x=0;

            if(nou.y==-1) nou.y=14;
            else if (nou.y==15) nou.y=0;

            worm_second[++ultim_second]=nou;


            if(Map[worm_second[ultim_second].y][worm_second[ultim_second].x]==2)
            {

                //game over
                return 0;

            }
            else Map[worm_second[ultim_second].y][worm_second[ultim_second].x]=2;


            if(worm_second[ultim_second].x==mar.x && worm_second[ultim_second].y==mar.y)
            {

                do{
                    mar.x = rand() % 20 + 1;
                    mar.y = rand() % 13 + 1;
                }
                while ( Map[mar.y][mar.x]);
                lee(mar, worm_second[ultim_second]);
                nr=0;
                for(int i=0;i<15;++i)
                {
                    for(int j=0;j<22;++j)
                        if(Mlee[i][j]/10==0) cout<<Mlee[i][j]<<"  ";
                        else                 cout<<Mlee[i][j]<<' ';
                    cout<<'\n';
                }
            }
            else
            {
                Map[ worm_second[prim_second].y ] [worm_second[prim_second].x ]=0;
                ++prim_second;
            }

        }

        ///primul sarpe

        nume[4]=dir+'0';
        head.loadFromFile(nume);
        sf::Sprite capet(head);
        win.clear();
        win.draw(sprite1);
        apple.setPosition(40*mar.x, 40*mar.y);
        win.draw(apple);
        //desenez rama


        for(i=prim; i<ultim; ++i)
        {
            segm.setPosition(40*worm[i].x, 40*worm[i].y);
            win.draw(segm);
        }

        capet.setPosition(40*worm[ultim].x, 40*worm[ultim].y);
        win.draw(capet);


        ///al doilea sarpe

        nume1[6]=dir_second+'0';
        header.loadFromFile(nume1);
        sf::Sprite capet2(header);
        //desenez rama


        for(i=prim_second; i<ultim_second; ++i)
        {
            segm1.setPosition(40*worm_second[i].x, 40*worm_second[i].y);
            win.draw(segm1);
        }

        capet2.setPosition(40*worm_second[ultim_second].x, 40*worm_second[ultim_second].y);
        win.draw(capet2);



        win.display();
    }
    return 1;
}
