#include <stdexcept>
#include <vector>

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
  Simulation(double x0, double y0, double A0, double B0, double C0, double D0);
  void evolve();
  Result get_latest_result();
  Result get_result(int i);


  /*void evolve(int x, int y);  //non so se basta il void o se serve pr::Simulation:
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

  ;*/
}; 


} // namespace pr
