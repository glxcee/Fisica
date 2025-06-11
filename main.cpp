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

#include <iostream>
#include <simulation.hpp>

#include "graphic.hpp"

using namespace std;

int main() {
  start_window();

  int A0;
  cout << "\nEnter a value for A, prey growth rate: ";
  cin >> A0;
  if (A0 <= 0) {
    cout << "A can't be a non-positive number" << endl;
  } else {
    int B0;
    cout << "Excelent, now enter a value for B, prey mortality rate: ";
    cin >> B0;
    if (B0 <= 0) {
      cout << "B can't be a non-positive number" << endl;
    } else {
      int C0;
      cout << "Perfect, now enter a value for C, predator growth rate: ";
      cin >> C0;
      if (C0 <= 0) {
        cout << "C can't be a non-positive number" << endl;
      } else {
        int D0;
        cout << "OK, now enter a value for D, predator mortality rate: ";
        cin >> D0;
        if (D0 <= 0) {
          cout << "D can't be a non-positive number" << endl;
        } else {
          int x0;
          cout
              << "Perfect, now enter a value for X0, the initial prey number: ";
          cin >> x0;
          if (x0 < 0) {
            cout << "x0 can't be a negative number" << endl;
          } else {
            int y0;
            cout << "Great, now enter a value for y0, the initial predator "
                    "number: "
                 << endl;
            cin >> y0;
            if (y0 < 0) {
              cout << "y0 can't be a negative number" << endl;
            } else {
              pr::Simulation sim(A0, B0, C0, D0, x0, y0);
            }
          }
        }
      }
    }
  }
}

