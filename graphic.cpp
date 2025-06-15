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


void Engine::drawText(double x, double y) {
    Result latest = sim.get_latest_result();
    double distance = sim.get_distance(latest.x, latest.y);

    std::ostringstream xCoords;
    xCoords << "x: " << latest.x;

    std::ostringstream yCoords;
    yCoords << "y: " << latest.y;

    std::ostringstream hVal;
    hVal << "H: " << latest.h;

    std::ostringstream distanceVal;
    distanceVal << "distance: " << distance;
    sf::Text disText(distanceVal.str(), font, 24);
    disText.setFillColor(sf::Color::Yellow);
    disText.setPosition(200.f, 10.f);
    window->draw(disText);

    
    if(!sim.gettingClose) {
        sf::Text fartext("FAR", font, 24);
        fartext.setPosition(400.f, 10.f);
        window->draw(fartext);
    }

    sf::Text xText(xCoords.str(), font, 24); // a font is required to make a text object
    sf::Text yText(yCoords.str(), font, 24);
    sf::Text hText(hVal.str(), font, 24);

    xText.setFillColor(sf::Color::Yellow);
    xText.setPosition(710.f, 10.f);

    yText.setFillColor(sf::Color::Yellow);
    yText.setPosition(710.f, 35.f);

    hText.setFillColor(sf::Color::Yellow);
    hText.setPosition(10.f, 10.f);

    window->draw(xText);
    window->draw(yText);
    window->draw(hText);
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
    p.x = 50 + (x * 70); // scale x to fit in the window
    p.y = 750 - (y * 70); // scale y to fit in the window and invert y-axis
    return p;
}

Point Engine::toNormalCoords(double x, double y) {
    // Convert the video coordinates back to mathematical coordinates
    Point p;
    p.x = (x - 50) / 70; // scale x back to normal
    p.y = (750 - y) / 70; // scale y back to normal and invert y-axis

    p.x = std::round(p.x * 100.f) / 100.f;
    p.y = std::round(p.y * 100.f) / 100.f;
    return p;
}

int Engine::windowLoop(int n) {

    Result start = sim.get_latest_result();

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
        Point mouseCoords = toNormalCoords(mousePos.x, mousePos.y);

        
        window->clear();
        
        
        drawAxis();
        drawText(mouseCoords.x, mouseCoords.y);
        
        auto latest = sim.get_latest_result();
        sf::CircleShape shape(5.f);
        shape.setFillColor(sf::Color::White);
        Point videoCoords = toVideoCoords(latest.x, latest.y);
        shape.setPosition(videoCoords.x, videoCoords.y);
        window->draw(shape);

        sf::CircleShape startingPoint(5.f);
        startingPoint.setFillColor(sf::Color::Green);
        Point startCoords = toVideoCoords(start.x, start.y);
        startingPoint.setPosition(startCoords.x, startCoords.y);
        window->draw(startingPoint);


         // evolve the simulation by one step

        window->display();

        sim.evolve();
    }

    return 0;
}

}