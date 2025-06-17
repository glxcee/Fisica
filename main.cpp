#include <iostream>

#include "graphic.hpp"

using namespace std;

int main() {
  
  double A0;
  cout << "\nEnter a value for A, prey growth rate: ";
  cin >> A0;
  if (A0 <= 0) {
    cout << "A can't be a non-positive number" << endl;
  } else {
    double B0;
    cout << "Excelent, now enter a value for B, prey mortality rate: ";
    cin >> B0;
    if (B0 <= 0) {
      cout << "B can't be a non-positive number" << endl;
    } else {
      double C0;
      cout << "Perfect, now enter a value for C, predator growth rate: ";
      cin >> C0;
      if (C0 <= 0) {
        cout << "C can't be a non-positive number" << endl;
      } else {
        double D0;
        cout << "OK, now enter a value for D, predator mortality rate: ";
        cin >> D0;
        if (D0 <= 0) {
          cout << "D can't be a non-positive number" << endl;
        } else {
          double x0;
          cout
              << "Perfect, now enter a value for X0, the initial prey number: ";
          cin >> x0;
          if (x0 < 0) {
            cout << "x0 can't be a negative number" << endl;
          } else {
            double y0;
            cout << "Great, now enter a value for y0, the initial predator number: ";
            cin >> y0;
            if (y0 < 0) {
              cout << "y0 can't be a negative number" << endl;
            } else {
              int N;
              cout << "Perfect, now enter the number of iterations you want to perform: ";
              cin >> N;
              if (N <= 0) {
                cout << "N can't be a non-positive number" << endl;
              } else {
                bool autoCorrect;
                cout << "Do you want to enable auto-correction for perfect cycles? (1 for yes, 0 for no): ";
                cin >> autoCorrect;
                if (autoCorrect != 0 && autoCorrect != 1) {
                  cout << "Invalid input for auto-correction, defaulting to no." << endl;
                  autoCorrect = false;
                }

                // starto la parte grafica
                pr::Engine engine(A0,B0,C0,D0,x0,y0,N,autoCorrect);
                cout<<"\nSimulation results succesfully saved in the \"logs\" folder!"<<endl;
              
              }
              
            }
          }
        }
      }
    }
  }
  return 0;
}

