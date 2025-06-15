#include "simulation.hpp"



namespace pr {

double Simulation::H(double x, double y) {
  return -D * std::log(x) + C * x + B * y - A * std::log(y);
}

Simulation::Simulation(double x0, double y0, double A0, double B0, double C0,
                       double D0) {
  A = A0;
  B = B0;
  C = C0;
  D = D0;

  double xrel = x0 * (C / D);
  double yrel = y0 * (B / A);

  results.push_back(Point{xrel, yrel});
}

Result Simulation::get_result(int i) {
  Point rel = results[i];
  double xabs = rel.x * (D / C);
  double yabs = rel.y * (A / B);

  return Result{xabs, yabs, H(xabs, yabs)};
}

Result Simulation::get_latest_result() {
  return get_result(results.size() - 1);
}

void Simulation::evolve() {
  Point latest = results[results.size() - 1];
  double x = latest.x;
  double y = latest.y;

  double xnew = x + A * (1 - y) * x * dt;
  double ynew = y + D * (x - 1) * y * dt;

  double mag = get_distance(xnew, ynew);
  
  if( gettingClose && mag > get_distance(x, y) && mag < 0.5) {
    gettingClose = false;
    results.push_back(results[0]);
    //results.push_back(Point{xnew, ynew});
  }
  else {
    if( !gettingClose && mag < get_distance(x, y)) gettingClose = true;

    results.push_back(Point{xnew, ynew});
  }
    

  
}

double Simulation::get_distance(double x, double y) {
  Point start = results[0];
  return std::sqrt(std::pow(x - start.x, 2) + std::pow(y - start.y, 2));
}

}  // namespace pr

