
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "simulation.hpp"

namespace pr {

class Engine {
  sf::RenderWindow *window;
  sf::Font font;
  Simulation sim;

  void drawAxis();
  void drawText(int i, int n, Result latest);
  void drawTail(int i);
  void drawFixedPoints();
  int windowLoop(int n, bool visualizeText);
  Point toVideoCoords(double x, double y);

 public:
  Engine(double A, double B, double C, double D, double x0, double y0, int n,
         bool autoCorrect);
};

}  // namespace pr