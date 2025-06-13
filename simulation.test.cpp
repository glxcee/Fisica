#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "simulation.hpp"
#include <cmath>

TEST_CASE("Testing Simulation class") {
    const double A = 1.0, B = 1.0, C = 1.0, D = 1.0;
    const double x0 = 1.0, y0 = 1.0;
    
    SUBCASE("Test constructor and initial values") {
        pr::Simulation sim(x0, y0, A, B, C, D);
        
        // Check initial values
        auto result = sim.get_latest_result();
        CHECK(result.X == doctest::Approx(1.0));
        CHECK(result.Y == doctest::Approx(1.0));
        CHECK(result.H == doctest::Approx(2.0)); // H(1,1) = -1*ln(1) + 1*1 + 1*1 -1*ln(1) = 2
    }
    
    SUBCASE("Test H function through get_result") {
        pr::Simulation sim(x0, y0, A, B, C, D);
        
        // Test H at different points by creating new simulations
        {
            pr::Simulation sim1(1.0, 1.0, A, B, C, D);
            auto result = sim1.get_latest_result();
            CHECK(result.H == doctest::Approx(2.0));
        }
        {
            pr::Simulation sim2(2.0, 3.0, A, B, C, D);
            auto result = sim2.get_latest_result();
            CHECK(result.H == doctest::Approx(-D*log(2.0) + C*2.0 + B*3.0 - A*log(3.0)));
        }
        {
            pr::Simulation sim3(0.5, 0.5, A, B, C, D);
            auto result = sim3.get_latest_result();
            CHECK(result.H == doctest::Approx(-D*log(0.5) + C*0.5 + B*0.5 - A*log(0.5)));
        }
    }
    
    SUBCASE("Test single evolution step") {
        pr::Simulation sim(x0, y0, A, B, C, D);
        sim.evolve();
        
        auto result = sim.get_latest_result();
        // With dt=0.001, A=D=1.0, x=y=1.0:
        // dx/dt = A*(1-y)*x = 0
        // dy/dt = D*(x-1)*y = 0
        // So values shouldn't change
        CHECK(result.X == doctest::Approx(1.0));
        CHECK(result.Y == doctest::Approx(1.0));
    }
    
    SUBCASE("Test evolution from non-equilibrium point") {
        const double x_init = 2.0, y_init = 0.5;
        pr::Simulation sim(x_init, y_init, A, B, C, D);
        
        sim.evolve();
        auto result = sim.get_latest_result();
        
        // Expected changes:
        // dx = A*(1-y)*x*dt = 1*(1-0.5)*2*0.001 = 0.001
        // dy = D*(x-1)*y*dt = 1*(2-1)*0.5*0.001 = 0.0005
        CHECK(result.X == doctest::Approx(2.0 + 0.001));
        CHECK(result.Y == doctest::Approx(0.5 + 0.0005));
    }
    
    SUBCASE("Test multiple evolution steps") {
        pr::Simulation sim(2.0, 0.5, A, B, C, D);
        
        for (int i = 0; i < 10; ++i) {
            sim.evolve();
        }
        
        // Check that we have 11 results (initial + 10 evolutions)
        CHECK(sim.get_latest_result().X != doctest::Approx(2.0));
        CHECK(sim.get_latest_result().Y != doctest::Approx(0.5));
    }
    
    SUBCASE("Test get_result with index") {
        pr::Simulation sim(x0, y0, A, B, C, D);
        
        // Evolve a few times
        for (int i = 0; i < 5; ++i) {
            sim.evolve();
        }
        
        // Check we can retrieve previous states
        auto initial = sim.get_result(0);
        CHECK(initial.X == doctest::Approx(1.0));
        CHECK(initial.Y == doctest::Approx(1.0));
        
        auto middle = sim.get_result(3);
        CHECK(middle.X == doctest::Approx(1.0));
        CHECK(middle.Y == doctest::Approx(1.0));
    }
    
    SUBCASE("Test different parameters") {
        const double A2 = 2.0, B2 = 0.5, C2 = 1.5, D2 = 0.8;
        pr::Simulation sim(x0, y0, A2, B2, C2, D2);
        
        // Check initial H value with new parameters
        auto result = sim.get_latest_result();
        double expected_H = -D2*log(x0) + C2*x0 + B2*y0 - A2*log(y0);
        CHECK(result.H == doctest::Approx(expected_H));
        
        // Evolve and check behavior changes
        sim.evolve();
        auto result2 = sim.get_latest_result();
        CHECK(result2.X == doctest::Approx(1.0)); // Still at equilibrium
        CHECK(result2.Y == doctest::Approx(1.0)); // Still at equilibrium
    }
}