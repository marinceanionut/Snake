#include <ctime>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string.h>
using namespace std;

sf::VideoMode VMode(880, 604, 32);
sf::RenderWindow win(VMode, "Snake");
struct coordonate
{
    int x, y;
};

struct scoreboard{
char nume[200];
int score;
};

scoreboard actual;
scoreboard record[5];

int remained_time=45;
int Map[1000][1000];
int prim, ultim, prim_second, ultim_second;
coordonate worm[200000], worm_second[200000];
coordonate mar;
int vdir[10000];
int Mlee[100][100];
char* int_to_a(int x);
void play_mode();
bool single_player();
int multiplayer();
bool vs_computer();
bool lee(coordonate start, coordonate stop);
void help();
void read();
void new_record();
void highscore();
void afisare();

int main()
{

    read();

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
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                win.close();

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
                    highscore();
                }
                else if( ( 356<event.mouseButton.x && event.mouseButton.x<460 ) && ( 448<event.mouseButton.y && event.mouseButton.y<485 ) )
                {
                    //help
                    help();
                }
                else if( ( 361<event.mouseButton.x && event.mouseButton.x<457 ) && ( 513<event.mouseButton.y && event.mouseButton.y<546 ) )
                {
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

void read()
{
    ifstream fin ("scoruri_record.txt");

    int i=0;
    while(fin>>record[i].nume>>record[i].score)
        ++i;
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
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                win.close();
            else if( event.type == sf::Event::MouseButtonPressed)
            {
                if( ( 230<event.mouseButton.x && event.mouseButton.x<590 ) && ( 268<event.mouseButton.y && event.mouseButton.y<306 ) )
                {
                     if(!single_player()) win.close();
                }
                else if( ( 154<event.mouseButton.x && event.mouseButton.x<725 ) && ( 445<event.mouseButton.y && event.mouseButton.y<478 ) )
                {
                    int rez0=vs_computer();
                    if(!rez0)
                    {
                        sf::Texture cwon;
                        cwon.loadFromFile("C_won.png");
                        sf::Sprite sprite1(cwon);
                        while(win.isOpen())
                        {
                            sf::Event event;
                            while (win.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    win.close();
                                }
                            }
                            win.clear();
                            win.draw(sprite1);
                            win.display();
                        }

                        sf::Texture pwon;
                        pwon.loadFromFile("P1_won.png");
                        sf::Sprite sprite(pwon);
                        while(win.isOpen())
                        {
                            sf::Event event;
                            while (win.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    win.close();
                                }
                            }
                            win.clear();
                            win.draw(sprite);
                            win.display();
                        }
                    }
                    else
                    {
                        sf::Texture pwon;
                        pwon.loadFromFile("P1_won.png");
                        sf::Sprite sprite(pwon);
                        while(win.isOpen())
                        {
                            sf::Event event;
                            while (win.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    win.close();
                                }
                            }
                            win.clear();
                            win.draw(sprite);
                            win.display();
                        }
                    }
                }
                else if( ( 194<event.mouseButton.x && event.mouseButton.x<623 ) && ( 356<event.mouseButton.y && event.mouseButton.y<393 ) )
                {
                    int rez=multiplayer();
                    if(!rez)
                    {
                        sf::Texture draw;
                        draw.loadFromFile("D_game.png");
                        sf::Sprite sprite1(draw);
                        while(win.isOpen())
                        {
                            sf::Event event;
                            while (win.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    win.close();
                                }
                            }
                            win.clear();
                            win.draw(sprite1);
                            win.display();
                        }
                    }
                    else if(rez==1)
                    {
                        sf::Texture p1won;
                        p1won.loadFromFile("P1_won.png");
                        sf::Sprite sprite2(p1won);
                        while(win.isOpen())
                        {
                            sf::Event event;
                            while (win.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                {
                                    win.close();
                                }
                            }
                            win.clear();
                            win.draw(sprite2);
                            win.display();
                        }
                    }
                        else if(rez==-1)
                        {
                            sf::Texture p2won;
                            p2won.loadFromFile("P2_won.png");
                            sf::Sprite sprite3(p2won);
                            while(win.isOpen())
                            {
                                sf::Event event;
                                while (win.pollEvent(event))
                                {
                                    if (event.type == sf::Event::Closed)
                                    {
                                        win.close();
                                    }
                                }
                                win.clear();
                                win.draw(sprite3);
                                win.display();
                            }
                        }

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
    char scor_actual[10];
    scor_actual[0]=0;
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

        sf::Text text;
        sf::Font font;
        font.loadFromFile("msjh.ttc");
        strcpy(scor_actual, "Score: ");
        strcat(scor_actual, int_to_a(actual.score));
        text.setString(scor_actual);
        text.setFont(font);
        text.setPosition(0, 0);

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                //win.close();
                return 0;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                win.close();
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
        if(clock.getElapsedTime().asMilliseconds()>=100)
        {
            clock.restart();
            nou.x=worm[ultim].x+d[dir].x;
            nou.y=worm[ultim].y+d[dir].y;

            if(nou.x==-1) nou.x=21;
            else if (nou.x==22 ) nou.x=0;

            if(nou.y==-1) nou.y=14;
            else if (nou.y==15) nou.y=0;

            worm[++ultim]=nou;

            if(Map[worm[ultim].y][worm[ultim].x])
            {
                //game over
                if(actual.score>record[2].score)
                    new_record();
                return 0;

            }
            else Map[worm[ultim].y][worm[ultim].x]=1;

            if(worm[ultim].x==mar.x && worm[ultim].y==mar.y)
            {
                actual.score+=5;
                srand(time(0));
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
        win.draw(text);

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


int multiplayer ()
{
    int dir=1, dir_second=1, i, prim, ultim, prim_second, ultim_second,scor_prim=0, scor_second=0;
     char string_score1[10], string_score2[10], string_time_elapse[5];
    char nume[]="head0.png";
    char nume1[]="header0.png";
    coordonate nou;
    sf::Texture background;
    background.loadFromFile("BACKGROUND.jpg");
    sf::Sprite sprite1(background);
    sf::Clock clock;
    sf::Clock clock1;
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
    sf::Text text;
    sf::Font font;
    font.loadFromFile("msjh.ttc");
    text.setFont(font);
    text.setPosition(0, 0);

    while(win.isOpen())
    {

        if(clock1.getElapsedTime().asSeconds()>=1&&remained_time>0)
            {
                clock1.restart();
                remained_time--;
            }
            else if(remained_time==0)
            {
                if(scor_prim>scor_second)
                {
                    return 1;
                }
                else
                    if(scor_prim<scor_second)
                    {
                        return -1;
                    }
                    else
                        {
                            return 0;
                        }
            }

        sf::Event event;
        while (win.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                //win.close();
                return 0;
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                win.close();
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
                return -1;

            }
            else Map[worm[ultim].y][worm[ultim].x]=1;

            if(worm[ultim].x==mar.x && worm[ultim].y==mar.y)
            {
                scor_prim+=5;

                srand(time(0));
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
            else if (nou.x==22 ) nou.x=0;

            if(nou.y==-1) nou.y=14;
            else if (nou.y==15) nou.y=0;

            worm_second[++ultim_second]=nou;

            if(Map[worm_second[ultim_second].y][worm_second[ultim_second].x]==2)
            {
                //game over
                return 1;

            }
            else Map[worm_second[ultim_second].y][worm_second[ultim_second].x]=2;


            if(worm_second[ultim_second].x==mar.x && worm_second[ultim_second].y==mar.y)
            {
                scor_second+=5;
                srand(time(0));
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
          sf::Text text1;
        strcpy(string_score1, "Score P1: ");
        text1.setFont(font);
        text1.setPosition(0, 0);
        strcat(string_score1, int_to_a(scor_prim));
        text1.setString(string_score1);
        win.draw(text1);

        sf::Text text2;
        strcpy(string_score2, "Score P2: ");
        text2.setFont(font);
        text2.setPosition(700, 0);
        strcat(string_score2, int_to_a(scor_second));
        text2.setString(string_score2);
        win.draw(text2);

        sf::Text text3;
        text3.setFont(font);
        text3.setPosition(400, 0);
        strcpy(string_time_elapse, int_to_a(remained_time));
        text3.setString(string_time_elapse);
        win.draw(text3);




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
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                win.close();
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

                srand(time(0));
                do{
                    mar.x = rand() % 20 + 1;
                    mar.y = rand() % 13 + 1;
                }
                while ( Map[mar.y][mar.x]);
               if(!lee(mar, worm_second[ultim_second]))
                    return 1;
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
                return 1;

            }
            else Map[worm_second[ultim_second].y][worm_second[ultim_second].x]=2;


            if(worm_second[ultim_second].x==mar.x && worm_second[ultim_second].y==mar.y)
            {

                srand(time(0));
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

bool lee(coordonate start, coordonate stop)
{
    coordonate actual, next, coada[10000], d[10];
    int prim, ultim, i, j, nr=0;

    d[0].x=0; d[1].x=1; d[2].x=0; d[3].x=-1;
    d[0].y=-1; d[1].y=0; d[2].y=1; d[3].y=0;

    for(i=0; i<=15; ++i)
        for(j=0; j<=22; ++j)
        Mlee[i][j]=0;

    for(i=prim_second; i<ultim_second; ++i)
        Mlee[ worm_second[i].y ][ worm_second[i].x ]=-1;

    prim=ultim=0;
    coada[0]=start;
    Mlee[start.y][start.x]=1;
    while(prim<=ultim &&!Mlee[stop.y][stop.x])
    {
        actual=coada[prim++];
        for(i=0; i<4; ++i)
        {
            next.y=actual.y+d[i].y;
            next.x=actual.x+d[i].x;
            if(next.y>=0 && next.x>=0 && next.y<15 && next.x<22 && Mlee[next.y][next.x]==0)
            {
                Mlee[next.y][next.x]=Mlee[actual.y][actual.x]+1;
                coada[++ultim]=next;
            }

        }
        if(actual.y==0 )
        {
            next.x=actual.x;
            next.y=14;
            if(Mlee[next.y][next.x]==0)
            {
                Mlee[next.y][next.x]=Mlee[actual.y][actual.x]+1;
                coada[++ultim]=next;
            }

        }
        if(actual.x==0 )
        {
            next.y=actual.y;
            next.x=21;
            if(Mlee[next.y][next.x]==0)
            {
                Mlee[next.y][next.x]=Mlee[actual.y][actual.x]+1;
                coada[++ultim]=next;
            }

        }
        if(actual.y==14 )
        {
            next.x=actual.x;
            next.y=0;
            if(Mlee[next.y][next.x]==0)
            {
                Mlee[next.y][next.x]=Mlee[actual.y][actual.x]+1;
                coada[++ultim]=next;
            }

        }
        if(actual.x==21 )
        {
            next.y=actual.y;
            next.x=0;
            if(Mlee[next.y][next.x]==0)
            {
                Mlee[next.y][next.x]=Mlee[actual.y][actual.x]+1;
                coada[++ultim]=next;
            }

        }
    }
    if(prim>ultim) return 0;

    actual=stop;
    while(Mlee[actual.y][actual.x]!=1)
    {
        for(i=0; i<4; ++i)
        {
            next.y=actual.y+d[i].y;
            next.x=actual.x+d[i].x;
            if(Mlee[next.y][next.x]==Mlee[actual.y][actual.x]-1)
            {
                actual=next;
                vdir[++nr]=i;
                break;
            }
        }
        if(i!=4)
            continue;

        if(actual.y==0 )
        {
            next.x=actual.x;
            next.y=14;
            if(Mlee[next.y][next.x]==Mlee[actual.y][actual.x]-1)
            {
                actual=next;
                vdir[++nr]=0;
                continue;
            }

        }
        if(actual.x==0 )
        {
            next.y=actual.y;
            next.x=21;
            if(Mlee[next.y][next.x]==Mlee[actual.y][actual.x]-1)
            {
                actual=next;
                vdir[++nr]=3;
                continue;
            }

        }
        if(actual.y==14 )
        {
            next.x=actual.x;
            next.y=0;
            if(Mlee[next.y][next.x]==Mlee[actual.y][actual.x]-1)
            {
                actual=next;
                vdir[++nr]=2;
                continue;
            }

        }
        if(actual.x==21 )
        {
            next.y=actual.y;
            next.x=0;
            if(Mlee[next.y][next.x]==Mlee[actual.y][actual.x]-1)
            {
                actual=next;
                vdir[++nr]=1;
                continue;
            }

        }

    }
    return 1;
}

void help()
{
    sf::Texture background;
    background.loadFromFile("help.png");
    sf::Sprite sprite(background);
     while (win.isOpen() )
    {

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
             if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                win.close();

            else if( event.type == sf::Event::MouseButtonPressed)
            {
                if( ( 611<event.mouseButton.x && event.mouseButton.x<721 ) && ( 514<event.mouseButton.y && event.mouseButton.y<539 ) )
                    return;
            }
        }

        win.clear();
        win.draw(sprite);
        win.display();

    }
}

char* int_to_a(int x)
{
    char sir[8]; int numar[10], i=0, j;
    if(x==0) {sir[0]='0'; sir[1]=0; return sir;}
    while(x)
    {
        numar[i++]=x%10;
        x/=10;
    }
    for(j=0;j<i;++j)
        sir[j]=numar[i-j-1]+'0';
    sir[j]=0;
    return sir;

}

void new_record()
{
    int lg=0;
    sf::Texture background;
    background.loadFromFile("BACKGROUND.jpg");
    sf::Sprite sprite1(background);
    sf::Text text;
    sf::Font font;
    font.loadFromFile("msjh.ttc");
    text.setString("Introduceti numele si apoi apasati enter!");
    text.setFont(font);
    text.setPosition(100, 200);



    while(win.isOpen())
                {
                    sf::Event event;
                    win.clear();
                    win.draw(sprite1);
                    win.draw(text);
                    sf::Text text1;
                    text1.setFont(font);
                    text1.setPosition(300, 300);
                    text1.setString(actual.nume);
                        win.draw(text1);
                    while(win.pollEvent(event))
                    {
                        if(event.type==sf::Event::TextEntered)
                        {
                            if(lg==12)
                            {
                                if(event.text.unicode==13)
                                {
                                    actual.nume[lg]=NULL;
                                    if(actual.score>record[0].score)
                                    {
                                        record[2]=record[1];
                                        record[1]=record[0];
                                        record[0]=actual;
                                    }
                                    else if(actual.score>record[1].score)
                                    {
                                        record[2]=record[1];
                                        record[1]=actual;

                                    }
                                    else if(actual.score>record[2].score)
                                        record[2]=actual;
                                    afisare();
                                    return;
                                }
                                if(event.text.unicode==8)
                                {
                                    lg--;
                                    actual.nume[lg]=NULL;
                                }
                            }
                            else
                            {
                                    if( (event.text.unicode==32||event.text.unicode>=65&&event.text.unicode<=90) || (event.text.unicode>=97&&event.text.unicode<=122) )
                                {
                                    actual.nume[lg++]=static_cast<char>(event.text.unicode);
                                    actual.nume[lg]=NULL;
                                }
                                if(event.text.unicode==8&&lg>0)
                                {
                                    lg--;
                                    actual.nume[lg]=NULL;
                                }

                                if(event.text.unicode==13)
                                {
                                    actual.nume[lg]=NULL;
                                    if(actual.score>record[0].score)
                                    {
                                        record[2]=record[1];
                                        record[1]=record[0];
                                        record[0]=actual;
                                    }
                                    else if(actual.score>record[1].score)
                                    {
                                        record[2]=record[1];
                                        record[1]=actual;

                                    }
                                    else if(actual.score>record[2].score)
                                        record[2]=actual;
                                    afisare();
                                    return;
                                }
                            }
                        }
                    }

                    win.display();
                }

}

void afisare()
{
    int i;
    ofstream fout("scoruri_record.txt");
    for(i=0;i<3;++i)
    {
        if(record[i].nume[0])
        fout<< record[i].nume<<' '<<record[i].score<<'\n';
    }
    fout.close();
}

void highscore()
{

    sf::Texture background;
    background.loadFromFile("SCOREBOARD.png");
    sf::Sprite sprite(background);
    sf::Text record0, record1, record2;
    sf::Text record00, record11, record22;
    sf::Font font;
    font.loadFromFile("msjh.ttc");
    record0.setCharacterSize(50);
    record0.setString(record[0].nume);
    record0.setFont(font);
    record0.setPosition(150, 200);
    record1.setCharacterSize(50);
    record1.setString(record[1].nume);
    record1.setFont(font);
    record1.setPosition(150, 275);
    record2.setCharacterSize(50);
    record2.setString(record[2].nume);
    record2.setFont(font);
    record2.setPosition(150, 350);

    record00.setCharacterSize(50);
    record00.setString(int_to_a(record[0].score));
    record00.setFont(font);
    record00.setPosition(650, 200);
    record11.setCharacterSize(50);
    record11.setString(int_to_a(record[1].score));
    record11.setFont(font);
    record11.setPosition(650, 275);
    record22.setCharacterSize(50);
    record22.setString(int_to_a(record[2].score));
    record22.setFont(font);
    record22.setPosition(650, 350);





    while (win.isOpen() )
    {

        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            else if( event.type == sf::Event::MouseButtonPressed)
            {
                if( ( 548<event.mouseButton.x && event.mouseButton.x<725 ) && ( 424<event.mouseButton.y && event.mouseButton.y<471 ) )
                    return;
            }
        }

        win.clear();
        win.draw(sprite);
        win.draw(record0);
        win.draw(record1);
        win.draw(record2);
        win.draw(record00);
        win.draw(record11);
        win.draw(record22);
        win.display();

    }

}
