
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cmath>
#include "simulation.hpp"

namespace pr {

struct Point {
    double x;
    double y;
};

class Engine {
    sf::RenderWindow *window;
    sf::Font font;
    Simulation sim;

    void drawAxis();
    void drawText(int x, int y);
    int windowLoop(int n);
    Point toVideoCoords(double x, double y);
    
    public:
    Engine(double A, double B, double C, double D, double x0, double y0, int n);
    
};



}