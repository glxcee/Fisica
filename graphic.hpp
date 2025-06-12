
#include <SFML/Graphics.hpp>
#include <sstream>
#include <cmath>
#pragma once

namespace pr {

class Engine {
    sf::RenderWindow *window;
    sf::Font font;

    void draw_axis();
    void draw_text(int x, int y);
    
    public:
    Engine();
    int window_loop();
};



}