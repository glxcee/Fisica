#include <cmath>
#include <stdexcept>
#include <vector>

namespace pr {

struct Result {
  double x;
  double y;
  double h;
};

struct Point {
  double x;
  double y;
};

class Simulation {
  std::vector<Point> results{};

  double dt = 0.001;
  bool autoCorrect;

  double get_distance(double x, double y);
  bool gettingClose = false;

  double H(double x, double y);

 public:
  double A, B, C, D;
  Simulation(double x0 = 1, double y0 = 1, double A0 = 1, double B0 = 1,
             double C0 = 1, double D0 = 1, bool correction = true);
  void evolve();
  Result get_latest_result();
  Result get_result(int i);
};

}  // namespace pr
