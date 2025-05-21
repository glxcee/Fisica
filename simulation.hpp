#include <stdexcept>
#include <vector>

namespace pr {

struct Result {
  double X;
  double Y;
  double H;
};

/*struct Point {
  double x;
  double y;
};*/

class Simulation {
  // std::vector<Point> points_;

  double A, B, C, D;
  double n;

 public:
  /*int pr::Simulation::*/ void evolve(int x, int y);  //non so se basta il void o se serve pr::Simulation:
  double x{};
  double y{};
  for (int i = 1; i < n; ++i) {
    x[i] = x[i - 1] + A * (1 - y[i - 1]) * x[i - 1] * t;
    y[i] = y[i - 1] + D * (x[i - 1] - 1) * y[i - 1] * t;
  }
  if (i == n) {
    for (int i = 0; i <= n; ++i) {
      
      double H = - D * std::log(x) + C * x + B * y - A * std::log(y); // calcolo H_i, credo
    }
  }

  ;
}; 


} // namespace pr
