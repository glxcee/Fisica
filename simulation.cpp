#include "simulation.hpp"

namespace pr {

double Simulation::H(double x, double y) {
  if (x == 0 || y == 0) {
    return 0;
  } else {
    return -D * std::log(x) + C * x + B * y - A * std::log(y);
  }
}

Simulation::Simulation(double x0, double y0, double A0, double B0, double C0,
                       double D0, bool correction) {
  A = A0;
  B = B0;
  C = C0;
  D = D0;
  autoCorrect = correction;

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
  if (y == 0) {
    double xnew = x + A * x * dt;  // Per la rescita esponenziale delle prede
    results.push_back(Point{xnew, 0.0});
    return;
  }

  if (x == 0) {
    double ynew = y - D * y * dt;  // Senza prede, predatori --> 0
    if (ynew < 0) ynew = 0;
    results.push_back(Point{0.0, ynew});
    return;
  } else {
    double xnew = x + A * (1 - y) * x * dt;
    double ynew = y + D * (x - 1) * y * dt;

    // salva la simulazione nel caso solo una delle 2 cordinate vada per qualche
    // motivo in negativo, se ci vanno entrambe si blocca
    if (xnew < 0) xnew = x;
    if (ynew < 0) ynew = y;

    double newDist = get_distance(xnew, ynew);
    double oldDist = get_distance(x, y);

    if (autoCorrect && gettingClose && newDist > oldDist &&
        newDist < 0.5) {  // se si stava avvicinando a (x0,y0), ma ha iniziato
                          // ad allontanarsi => riinizia il ciclo
      gettingClose = false;
      results.push_back(results[0]);
    } else {
      if (autoCorrect && !gettingClose &&
          newDist < oldDist)  // si stava allontanado, ma ha iniziato a
                              // avvicinarsi => si sta avvcinando
        gettingClose = true;

      results.push_back(Point{xnew, ynew});
    }
  }
}
  double Simulation::get_distance(double x, double y) {
    Point start = results[0];
    return std::sqrt(std::pow(x - start.x, 2) + std::pow(y - start.y, 2));
  }

}  // namespace pr
