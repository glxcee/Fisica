#include "graphic.hpp"

namespace pr {
void Engine::drawAxis() {
    std::vector<sf::Vertex> x_line;
    x_line.push_back(sf::Vertex(sf::Vector2f(50.f, 750.f), sf::Color::Red));
    x_line.push_back(sf::Vertex(sf::Vector2f(750.f, 750.f), sf::Color::Red));

    x_line.push_back(sf::Vertex(sf::Vector2f(750.f, 750.f), sf::Color::Red));
    x_line.push_back(sf::Vertex(sf::Vector2f(740.f, 740.f), sf::Color::Red));

    x_line.push_back(sf::Vertex(sf::Vector2f(750.f, 750.f), sf::Color::Red));
    x_line.push_back(sf::Vertex(sf::Vector2f(740.f, 760.f), sf::Color::Red));


    std::vector<sf::Vertex> y_line;
    y_line.push_back(sf::Vertex(sf::Vector2f(50.f, 750.f), sf::Color::Red));
    y_line.push_back(sf::Vertex(sf::Vector2f(50.f, 50.f), sf::Color::Red));

    y_line.push_back(sf::Vertex(sf::Vector2f(50.f, 50.f), sf::Color::Red));
    y_line.push_back(sf::Vertex(sf::Vector2f(40.f, 60.f), sf::Color::Red));

    y_line.push_back(sf::Vertex(sf::Vector2f(50.f, 50.f), sf::Color::Red));
    y_line.push_back(sf::Vertex(sf::Vector2f(60.f, 60.f), sf::Color::Red));


    window->draw(x_line.data(), x_line.size(), sf::PrimitiveType::Lines);
    window->draw(y_line.data(), y_line.size(), sf::PrimitiveType::Lines);
}


void Engine::drawText(int x, int y) {
    std::ostringstream xCoords;
    xCoords << "x: " << x;

    std::ostringstream yCoords;
    yCoords << "y: " << y;

    sf::Text xText(xCoords.str(), font, 24); // a font is required to make a text object
    sf::Text yText(yCoords.str(), font, 24);

    xText.setFillColor(sf::Color::Red);
    xText.setPosition(720.f, 10.f);

    yText.setFillColor(sf::Color::Red);
    yText.setPosition(720.f, 35.f);

    window->draw(xText);
    window->draw(yText);
}


Engine::Engine(double A, double B, double C, double D, double x0, double y0, int n) {
    
    sf::RenderWindow ogWindow(sf::VideoMode({800, 800}), "Volterra Simulation");
    window = &ogWindow;
    
    if (!font.loadFromFile("arial.ttf")) {
        //ogWindow.close();
        // gestione errore
    }

    sim = Simulation(x0, y0, A, B, C, D);

    windowLoop(n);
}

Point Engine::toVideoCoords(double x, double y) {
    // Convert the mathematical coordinates to video coordinates
    // Assuming the origin (0,0) is at the bottom left corner of the window
    Point p;
    p.x = 50 + (x * 700 / 10); // scale x to fit in the window
    p.y = 750 - (y * 700 / 10); // scale y to fit in the window and invert y-axis
    return p;
}

int Engine::windowLoop(int n) {

    n=0;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event)) 
        //processa 1 ad 1 tutti gli eventi in coda accaduti in quel tick
        {

            if (event.type == sf::Event::Closed) //click sulla X
                window->close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        int xmouse = mousePos.x;
        int ymouse = mousePos.y;

        
        window->clear();
        
        
        

        
        drawAxis();
        drawText(xmouse, ymouse);
        
        auto latest = sim.get_latest_result();
        sf::CircleShape shape(5.f);
        shape.setFillColor(sf::Color::White);
        Point videoCoords = toVideoCoords(latest.X, latest.Y);
        shape.setPosition(videoCoords.x, videoCoords.y);
        window->draw(shape);

         // evolve the simulation by one step

        window->display();

        sim.evolve();
    }

    return 0;
}

}