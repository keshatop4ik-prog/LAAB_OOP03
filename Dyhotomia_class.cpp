#include "Dyhotomia_class.h"
#include <iostream>
#include <cmath>

using namespace std;

Dyhotomia_class::Dyhotomia_class(void) {}
Dyhotomia_class::~Dyhotomia_class(void) {}

void Dyhotomia_class::setVolumes(double &vol_a, double &vol_b) {
    a = vol_a;
    b = vol_b;
}

void Dyhotomia_class::setTolerance(double &vol_eps) {
    eps = vol_eps;
}

double Dyhotomia_class::f(double x) {
    // Мій варіант №1
    return 3 * sin(sqrt(x)) + 0.35 * x - 3.8;
}

int Dyhotomia_class::count(double &x) {
    double ta = a;
    double tb = b;

    if (f(ta) * f(tb) > 0) {
        cout << "No solution on interval" << endl;
        return -1;
    }

    while (abs(tb - ta) > eps) {
        double c = (ta + tb) / 2.0;
        if (f(ta) * f(c) < 0) tb = c;
        else ta = c;
    }

    x = (ta + tb) / 2.0;
    return 0;
}

void Dyhotomia_class::newton() {
    double xn = 10.0;

    for (int i = 0; i < 100; i++) {
        double dx = 0.000001;
        double df = (f(xn + dx) - f(xn)) / dx;

        if (abs(df) < 1e-10) break;

        double x_next = xn - f(xn) / df;

        if (x_next > b) {
            x_next = (xn + b) / 2.0;
        } else if (x_next < a) {
            x_next = (xn + a) / 2.0;
        }

        cout << "Iteration " << i + 1 << ": x = " << x_next << endl;

        if (abs(x_next - xn) < eps) {
            cout << "Newton Final: " << x_next << endl;
            return;
        }
        xn = x_next;
    }
}