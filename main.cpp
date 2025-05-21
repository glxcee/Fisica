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


using namespace std;

int main() {
  int A;
  cout << "Enter a value for A, prey growth rate: ";
  cin >> A;
  if (A <= 0) {
    cout << "A can't be a non-positive number" << endl;
  } else {
    int B;
    cout << "Excelent, now enter a value for B, prey mortality rate: ";
    cin >> B;
    if (B <= 0) {
      cout << "B can't be a non-positive number" << endl;
    } else {
      int C;
      cout << "Perfect, now enter a value for C, predator growth rate: ";
      cin >> C;
      if (C <= 0) {
        cout << "C can't be a non-positive number" << endl;
      } else {
        int D;
        cout << "OK, now enter a value for D, predator mortality rate: ";
        cin >> D;
        if (D <= 0) {
          cout << "D can't be a non-positive number" << endl;
        } else {
          int x;
          cout
              << "Perfect, now enter a value for X0, the initial prey number: ";
          cin >> x;
          /* casi possibili --> se uno tra x o y <0; se sia x che y <0; se uno
           * solo tra x o y =0; se sia x che y =0; se sia x che y >0
           */
        }
      }
    }
  }
  return 0;
}
