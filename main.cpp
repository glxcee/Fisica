#include <doctest.h>
#include <.clang-format>
#include <fstream>
#include <sstream>
#include <iomanip>

/* 
x == densità di prede
y == densità predatori
A == tasso di crescita prede
B == tasso di mortalità prede --> dipende da numero prede e numero predatori
C == tasso di crescita predatori
D == tasso di mortalità predatori --> dipende da numero prede e numero predatori

e1 = (0, 0) = punto di equilibrio/stazionario
e2 = (D/C, A/B) = punto di equilibrio/stazionario

*/


using namespace std;
const double A = 0.05;
const double B = 0.002;
const double C = 0.06;
const double D = 0.004;

const double step = 0.1;

const int numberOfLoops = 4000;

double dxdt(double x, double y) {
    return x*(A - B*y);
}

double dydt(double x, double y) {
    return y*(C - D*x);
}

