#include <iostream>
#include "Dyhotomia_class.h"

using namespace std;

int main() {
    double v_a = 2.0;
    double v_b = 3.0;
    double v_eps = 0.0001;
    double result_x;

    Dyhotomia_class *dyh = new Dyhotomia_class();

    dyh->setVolumes(v_a, v_b);
    dyh->setTolerance(v_eps);

    if (dyh->count(result_x) == 0) {
        cout << "Dichotomy: " << result_x << endl;
    }

    dyh->newton();

    delete dyh;

    return 0;
}