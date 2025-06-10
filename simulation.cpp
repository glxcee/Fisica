#include "simulation.hpp"
#include <cmath>

namespace pr {

    double Simulation::H(double x, double y) {
        return - D * std::log(x) + C * x + B * y - A * std::log(y);
    }

    Simulation::Simulation(double x0, double y0, double A0, double B0, double C0, double D0) {
        A = A0;
        B = B0;
        C = C0;
        D = D0;

        double xrel = x0*(C/D); 
        double yrel = y0*(B/A); 

        results.push_back(Result{xrel, yrel, H(xrel,yrel)});
    }

    Result Simulation::get_result(int i) {
        if(i >= results.size()) { // optional? : misura di sicurezza per evitare un "Index Out of Bounds"
            return results[results.size()-1];
        }

        return results[i];
    }

    Result Simulation::get_latest_result() {
        return results[results.size()-1];
    }

    void Simulation::evolve() {
        Result latest = get_latest_result();
        double x = latest.X;
        double y = latest.Y;

        double xnew = x + A*(1-y)*x*dt;
        double ynew = y + D*(x-1)*y*dt;
        
        results.push_back(Result{xnew, ynew, H(xnew, ynew)});
    }

}