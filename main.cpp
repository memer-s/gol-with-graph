#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <ctime>

int main()
{

    int tempwidth;
    int tempheight;
    int temppxsize;
    int randor;

    int fps;

    int gen = 0;
    int living;

    std::cout << "width (1080): ";
    std::cin >> tempwidth;
    std::cout << "height (800): ";
    std::cin >> tempheight;
    std::cout << "pxsize (1): ";
    std::cin >> temppxsize;
    std::cout << "fps (0 for uncapped): ";
    std::cin >> fps;
    std::cout << "pattern (0 for set pattern, 1 for random pattern): ";
    std::cin >> randor;

    // fonts and shit
    sf::Font font;
    if(!font.loadFromFile("ARIAL.TTF")) 
    {
        std::cout << "error loading font!!!!!! EPICU BRUH MOMENTO";
    }

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(22);
    text.setPosition(sf::Vector2f(10.0f, 10.0f));


    const int pxsize = temppxsize;
    const int height = tempheight;
    const int width = tempwidth;

    sf::RenderWindow window(sf::VideoMode(width*pxsize, height*pxsize), "Game of Life.");
    sf::RenderWindow graphwindow(sf::VideoMode(800, 500), "Graph");
    sf::RectangleShape shape(sf::Vector2f(pxsize,pxsize));
    
    
    window.setFramerateLimit(fps);

    time_t current_time;
    current_time = time(NULL);
    int cfps = 0;
    int cofps = 0;
    int sec = 0;

    int8_t pg[width][height] = {0};
    int8_t pgf[width][height] = {0};

    sf::VertexArray lines(sf::LinesStrip,4);

    if (randor == 0)
    {
        int pat[10][50] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

        };
        
        for (int x = 0; x < 16; x++)
        {
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 50; j++)
                {
                    pg[i+20][j+x*50] = pat[i][j];
                }
                
            }
        }
    }
    else if (randor == 1)
    {
        srand(1337);

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                pg[i][j] = rand()%2;
            }
        }
    }
    

    
    

    

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            pgf[i][j]=pg[i][j];
        }
    }
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        time_t timestamp;
        timestamp = time(NULL);

        // delta time was here


        

        window.clear();
        graphwindow.clear();



        

        graphwindow.draw(lines);

        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                if(pg[i][j]==1) {
                    shape.setFillColor(sf::Color::White);
                    shape.setPosition(sf::Vector2f(i*pxsize, j*pxsize));
                    window.draw(shape);
                    living++;
                }
                
                if(pg[i][j]==2) {
                    shape.setFillColor(sf::Color::Blue);
                    shape.setPosition(sf::Vector2f(i*pxsize, j*pxsize));
                    window.draw(shape);
                    living++;
                }

                int n = 0;

                if (pg[i-1][j-1]==1){n++;}
                if (pg[i-1][j]==1) {n++;}
                if(pg[i-1][j+1]==1) {n++;}
                if (pg[i][j-1]==1) {n++;} 
                if (pg[i][j+1]==1) {n++;} 
                if(pg[i+1][j-1]==1) {n++;}
                if (pg[i+1][j]==1) {n++;} 
                if(pg[i+1][j+1]==1) {n++;}

                /*
                if (pg[i][j]==0 && n==2)
                {
                    pgf[i][j] = 1;
                }

                else if (pg[i][j]==1) {
                    pgf[i][j] = 2;
                }

                else if (pg[i][j]==2) {
                    pgf[i][j] = 0;
                }
                */
                if (pg[i][j] == 1 && n<2) {
                    pgf[i][j] = 0;
                }

                else if (pg[i][j] == 1 && n>3) {
                    pgf[i][j] = 0;
                }

                else if (pg[i][j] == 0 && n==3) {
                    pgf[i][j] = 1;
                }

                else {

                } 

                
            }
        }

        // delta time
        if(current_time != timestamp) {
            lines.append(sf::Vertex(sf::Vector2f(sec*4, 500-(living/200))));
            std::cout << living/200 << std::endl;
            current_time = timestamp;
            cfps = cofps;
            cofps = 0;
            sec++;
        }

        std::string strgen = "Generation: " + std::to_string(gen)+"\nTotal living cells: "+std::to_string(living)+"\nFPS: "+std::to_string(cfps);
        living = 0;
        text.setString(strgen);

        window.draw(text);

        window.display();
        graphwindow.display();
        cofps++;

        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                pg[i][j] = pgf[i][j];
            }
        }


        gen++;
    }

    return 0;
}

// g++ -c main.cpp
// g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system