#include <doctest.h>
#include <.clang-format>
#include <fstream>
#include <iomanip>
#include <iostream>

// Parametri del modello
const double alpha = 1.0;  // Tasso di crescita delle prede
const double beta = 0.1;   // Tasso di predazione
const double gamma = 1.5;  // Tasso di mortalità dei predatori
const double delta =
    0.075;  // Tasso di crescita dei predatori per preda consumata

// Parametri di simulazione
const double dt = 0.01;   // Passo temporale
const int steps = 10000;  // Numero di passi di simulazione

int main() {
  // Condizioni iniziali
  double x = 40.0;  // Popolazione iniziale delle prede (conigli)
  double y = 9.0;   // Popolazione iniziale dei predatori (volpi)

  std::ofstream output("lotka_volterra_output.csv");
  output << "Tempo,Prede,Predatori\n";

  for (int i = 0; i <= steps; ++i) {
    double t = i * dt;
    output << std::fixed << std::setprecision(5) << t << "," << x << "," << y
           << "\n";

    // Calcolo dei tassi di variazione
    double dx = (alpha * x - beta * x * y) * dt;
    double dy = (delta * x * y - gamma * y) * dt;

    // Aggiornamento delle popolazioni
    x += dx;
    y += dy;
  }

  output.close();
  std::cout << "Simulazione completata. Dati salvati in "
               "'lotka_volterra_output.csv'.\n";
  return 0;
}
