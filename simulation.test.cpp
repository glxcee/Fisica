#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "simulation.hpp"

#include <cmath>

#include "doctest.h"

TEST_CASE("Testing Simulation class basic functionality") {
  const double A = 1.0, B = 1.0, C = 1.0, D = 1.0;
  const double x0 = 1.0, y0 = 1.0;

  pr::Simulation sim(x0, y0, A, B, C, D);

  SUBCASE("Initial values are set correctly") {
    auto result = sim.get_latest_result();
    CHECK(result.X == doctest::Approx(1.0));
    CHECK(result.Y == doctest::Approx(1.0));
    CHECK(result.H == doctest::Approx(2.0));
  }

  SUBCASE("Evolution at equilibrium point doesn't change values") {
    sim.evolve();
    auto result = sim.get_latest_result();
    CHECK(result.X == doctest::Approx(1.0));
    CHECK(result.Y == doctest::Approx(1.0));
  }
}

TEST_CASE("Testing Simulation with non-equilibrium initial conditions") {
  const double A = 1.0, B = 1.0, C = 1.0, D = 1.0;
  const double x0 = 2.0, y0 = 0.5;

  pr::Simulation sim(x0, y0, A, B, C, D);

  SUBCASE("Initial values are set correctly") {
    auto result = sim.get_latest_result();
    CHECK(result.X == doctest::Approx(2.0));
    CHECK(result.Y == doctest::Approx(0.5));
  }

  SUBCASE("Single evolution step changes values correctly") {
    sim.evolve();
    auto result = sim.get_latest_result();
    CHECK(result.X ==
          doctest::Approx(2.0 + 0.001));  // dx = 1*(1-0.5)*2*0.001 = 0.001
    CHECK(result.Y ==
          doctest::Approx(0.5 + 0.0005));  // dy = 1*(2-1)*0.5*0.001 = 0.0005
  }

  SUBCASE("Multiple evolution steps change values") {
    const double initial_x = sim.get_latest_result().X;
    const double initial_y = sim.get_latest_result().Y;

    for (int i = 0; i < 10; ++i) {
      sim.evolve();
    }

    auto result = sim.get_latest_result();
    CHECK(result.X != doctest::Approx(initial_x));
    CHECK(result.Y != doctest::Approx(initial_y));
  }
}

TEST_CASE("Testing result retrieval") {
  const double A = 1.0, B = 1.0, C = 1.0, D = 1.0;
  const double x0 = 1.0, y0 = 1.0;

  pr::Simulation sim(x0, y0, A, B, C, D);

  SUBCASE("get_latest_result returns correct initial values") {
    auto result = sim.get_latest_result();
    CHECK(result.X == doctest::Approx(1.0).epsilon(0.1));
    CHECK(result.Y == doctest::Approx(1.0).epsilon(0.1));
  }

  SUBCASE("get_result with index works correctly") {
    // Evolve a few times
    for (int i = 0; i < 5; ++i) {
      sim.evolve();
    }

    // Check initial state
    auto initial = sim.get_result(0);
    CHECK(initial.X == doctest::Approx(1.0).epsilon(0.1));
    CHECK(initial.Y == doctest::Approx(1.0).epsilon(0.1));

    // Check latest state
    auto latest = sim.get_latest_result();
    CHECK(latest.X == doctest::Approx(1.0).epsilon(0.1));
    CHECK(latest.Y == doctest::Approx(1.0).epsilon(0.1));
  }
}

TEST_CASE("Testing with different parameters") {
  const double A = 2.0, B = 0.5, C = 1.5, D = 0.8;
  const double x0 = 1.0, y0 = 4.0;

  pr::Simulation sim(x0, y0, A, B, C, D);

  SUBCASE("Initial H value is calculated correctly") {
    auto result = sim.get_latest_result();
    double expected_H = -D * log(x0) + C * x0 + B * y0 - A * log(y0);
    CHECK(result.H == doctest::Approx(expected_H).epsilon(0.1));
  }

  SUBCASE("Evolution at equilibrium point doesn't change values") {
    sim.evolve();
    auto result = sim.get_latest_result();
    CHECK(result.X == doctest::Approx(1.0).epsilon(0.1));
    CHECK(result.Y == doctest::Approx(4.0).epsilon(0.1));
  }
}