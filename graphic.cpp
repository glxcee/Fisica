#include <SFML/Graphics.hpp>
#include <cmath>

int start_window() {
    //std::cout<<"STARTING WINDOW\n\n";

    sf::RenderWindow window(sf::VideoMode({500, 500}), "Volterra Simulation");

    

    
    double i = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        //processa 1 ad 1 tutti gli eventi in coda accaduti in quel tick
        {
            if (event.type == sf::Event::Closed) //click sulla X
                window.close();
        }

        window.clear();

        sf::CircleShape shape(5.f);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(200.f + 100*std::cos(i), 200.f + 100*std::sin(i));
        window.draw(shape);
        window.display();
        i+=0.005;
    }

    return 0;
}