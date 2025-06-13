#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "simulation.hpp"
#include "doctest.h"

namespace pr = pr;

/*
TEST_CASE("Testing basics") {
  CHECK(1 == 1);
}
  */

TEST_CASE("Testing Simulation class") {
  const double A = 1.0, B = 0.5, C = 0.75, D = 1.5;
  const double x0 = 10.0, y0 = 5.0;

  pr::Simulation sim(x0, y0, A, B, C, D);

  SUBCASE("Test initialization") {
    auto first_result = sim.get_result(0);

    // Verifica che i valori relativi siano corretti
    CHECK(first_result.X == doctest::Approx(x0 * (C / D)));
    CHECK(first_result.Y == doctest::Approx(y0 * (B / A)));

    // Verifica che H sia calcolato correttamente
    double expected_H = -D * std::log(first_result.X) + C * first_result.X +
                        B * first_result.Y - A * std::log(first_result.Y);
    CHECK(first_result.H == doctest::Approx(expected_H));
  }

  SUBCASE("Test evolve() method") {
    sim.evolve();
    auto second_result = sim.get_result(1);

    // Dovrebbe esserci esattamente 2 risultati ora
    CHECK(sim.get_latest_result().X == doctest::Approx(second_result.X));

    // Verifica che l'indice fuori range ritorni l'ultimo risultato
    CHECK(sim.get_result(100).X == doctest::Approx(second_result.X));
  }

  SUBCASE("Test conservation of H (should be approximately constant)") {
    const double initial_H = sim.get_result(0).H;

    for (int i = 0; i < 10; ++i) {
      sim.evolve();
    }

    auto latest = sim.get_latest_result();
    CHECK(latest.H == doctest::Approx(initial_H).epsilon(0.01));
  }
}

TEST_CASE("Edge cases") {
  SUBCASE("Zero initial populations") {
    pr::Simulation sim(0.0, 0.0, 1.0, 0.5, 0.75, 1.5);

    // Verifica che il sistema rimanga a zero
    for (int i = 0; i < 5; ++i) {
      sim.evolve();
      auto result = sim.get_latest_result();
      CHECK(result.X == doctest::Approx(0.0));
      CHECK(result.Y == doctest::Approx(0.0));
    }
  }

  SUBCASE("Extreme parameter values") {
    pr::Simulation sim(100.0, 100.0, 1e-6, 1e-6, 1e-6, 1e-6);

    // Verifica che il sistema cambi molto lentamente
    sim.evolve();
    auto result = sim.get_latest_result();
    CHECK(result.X == doctest::Approx(100.0 * (1e-6 / 1e-6)).epsilon(0.0001));
  }
}

// i test usano tutti .epsilon, non ricordo se l'abbiamo fatto con il giacoms
