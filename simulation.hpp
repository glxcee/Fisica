#include <stdexcept>
#include <vector>
#include <cmath>

namespace pr {

struct Result {
  double X;
  double Y;
  double H;
};

class Simulation {
  std::vector<Result> results{};
  double A, B, C, D;
  double n;
  double dt = 0.001;

  double H(double x, double y);

 public:
  Simulation(double x0=1, double y0=1, double A0=1, double B0=1, double C0=1, double D0=1);
  void evolve();
  Result get_latest_result();
  Result get_result(int i);
};

}  // namespace pr
