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


void Engine::drawText(int i, int n, Result latest) {
    double x = std::round(latest.x * 100.f) / 100.f;
    double y = std::round(latest.y * 100.f) / 100.f;

    std::ostringstream xCoords;
    xCoords << "x: " << x;

    std::ostringstream yCoords;
    yCoords << "y: " << y;

    std::ostringstream hVal;
    hVal << "H: " << latest.h;

    std::ostringstream params;
    params << "A: " << sim.A << " B: " << sim.B << " C: " << sim.C << " D: " << sim.D;

    std::ostringstream steps;
    steps << "N: " << i << "/" << n;

    sf::Text nText(steps.str(), font, 24);
    sf::Text xText(xCoords.str(), font, 24);
    sf::Text yText(yCoords.str(), font, 24);
    sf::Text hText(hVal.str(), font, 24);
    sf::Text pText(params.str(), font, 24);

    nText.setFillColor(sf::Color::Yellow);
    nText.setPosition(200.f, 10.f);

    xText.setFillColor(sf::Color::Yellow);
    xText.setPosition(710.f, 10.f);

    yText.setFillColor(sf::Color::Yellow);
    yText.setPosition(710.f, 35.f);

    hText.setFillColor(sf::Color::Yellow);
    hText.setPosition(10.f, 10.f);

    pText.setFillColor(sf::Color::Green);
    pText.setPosition(200.f, 760.f);

    window->draw(nText);
    window->draw(xText);
    window->draw(yText);
    window->draw(hText);
    window->draw(pText);
}

void Engine::drawTail(int i) {
    int len = 300;
    double radius = 10.f;

    if(i < len) len = i;
    for(int j = 1; j <= len; j++) {
        if(j%2 == 0) continue; // draw solo ogni 2 risultati (ottimizzazione)
        auto point = sim.get_result(i - j);
        Point videoPoint = toVideoCoords(point.x, point.y);
        sf::CircleShape tailPoint(radius - (j/(len/radius)));
        tailPoint.setFillColor(sf::Color::White);
        tailPoint.setPosition(videoPoint.x, videoPoint.y);
        window->draw(tailPoint);
    }

    auto latest = sim.get_latest_result();
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Yellow);
    Point videoCoords = toVideoCoords(latest.x, latest.y);
    shape.setPosition(videoCoords.x, videoCoords.y);
    window->draw(shape);
}


void Engine::drawFixedPoints() {

    sf::CircleShape centerPoint(5.f);
    centerPoint.setFillColor(sf::Color::Green);
    Point centerCoords = toVideoCoords(sim.D/sim.C, sim.A/sim.B);
    centerPoint.setPosition(centerCoords.x, centerCoords.y);
    window->draw(centerPoint);
}


Engine::Engine(double A, double B, double C, double D, double x0, double y0, int n, bool autoCorrect) {
    
    sf::RenderWindow ogWindow(sf::VideoMode({800, 800}), "Volterra Simulation");
    window = &ogWindow;
    
    bool visualizeText = true;
    if (!font.loadFromFile("arial.ttf")) {
        visualizeText = false;
        // gestione errore
    }

    sim = Simulation(x0, y0, A, B, C, D, autoCorrect);

    windowLoop(n);
}

Point Engine::toVideoCoords(double x, double y) {
    // cordinate assolute in cordinate video -> (10,10) è l'angolo in alto a destra della finestra
    Point p;
    p.x = 50 + (x * 70);
    p.y = 750 - (y * 70); 
    return p;
}


int Engine::windowLoop(int n) {

    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::ostringstream filename;
    filename << "logs/"
        << std::put_time(std::localtime(&t), "%Y-%m-%d_%H-%M-%S")
        << ".txt";

    std::ofstream outfile{filename.str()};

    if (!outfile) {
        throw std::runtime_error{"Impossible to open file!"};
    }

    outfile << "A: " << sim.A << " | B: " << sim.B << " | C: " << sim.C << " | D: " << sim.D << " (" << n << " steps)\n";


    int i=0;
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) 
        //processa 1 ad 1 tutti gli eventi in coda accaduti in quel tick
        {

            if (event.type == sf::Event::Closed) //click sulla X
                window->close();
        }
        
        window->clear();
        
        Result latest = sim.get_latest_result();
        

        drawAxis();
        if(visualizeText) drawText(i,n,latest);
    
        drawFixedPoints();

        drawTail(i);

        window->display();
        

        if(i<n) {
            outfile << "n = " << i << " -> x: " << latest.x << ", y: " << latest.y << ", h: " << latest.h << '\n';

            sim.evolve();
            i++;
        }
    }

    return 0;
}

}