#ifndef DYHOTOMIA_CLASS_H
#define DYHOTOMIA_CLASS_H

#include <functional>

class Dyhotomia_class {
private:
    double a;
    double b;
    double eps;

    // Лямбди зберігаються як поля класу
    // Це дозволяє підміняти функцію ззовні без зміни класу
    std::function<double(double)> f;   // рівняння
    std::function<double(double)> df;  // похідна (числова)

public:
    Dyhotomia_class();
    ~Dyhotomia_class();

    void setVolumes(double &vol_a, double &vol_b);
    void setTolerance(double &vol_eps);

    // Дозволяє передати свою функцію ззовні (лямбду)
    void setFunction(std::function<double(double)> func);

    int count(double &x);   // дихотомія
    void newton();          // метод Ньютона
};

#endif