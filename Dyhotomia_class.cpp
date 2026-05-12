#include "Dyhotomia_class.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

Dyhotomia_class::Dyhotomia_class() {
    // Лямбда для рівняння: 3*sin(sqrt(x)) + 0.35*x - 3.8
    // Захоплення [] — не потребує нічого зовнішнього,
    // все передається через параметр x
    f = [](double x) {
        return 3 * sin(sqrt(x)) + 0.35 * x - 3.8;
    };

    // Лямбда для числової похідної
    // Захоплює f за посиланням [&f] — використовує вже визначену лямбду f
    // Це приклад лямбди, яка використовує іншу лямбду
    df = [this](double x) {
        double dx = 0.000001;
        return (f(x + dx) - f(x)) / dx;
    };
}

Dyhotomia_class::~Dyhotomia_class() {}

void Dyhotomia_class::setVolumes(double &vol_a, double &vol_b) {
    a = vol_a;
    b = vol_b;
}

void Dyhotomia_class::setTolerance(double &vol_eps) {
    eps = vol_eps;
}

// Дозволяє передати власну функцію ззовні — наприклад іншу лямбду
// Після зміни f — df автоматично рахує похідну для нової функції
void Dyhotomia_class::setFunction(std::function<double(double)> func) {
    f = func;
    // df перераховується автоматично через [this] — бере оновлений f
    df = [this](double x) {
        double dx = 0.000001;
        return (f(x + dx) - f(x)) / dx;
    };
}

int Dyhotomia_class::count(double &x) {
    double ta = a;
    double tb = b;
    int iter = 0;

    // Лямбда-предикат для перевірки знаку
    // Захоплює f за [this] — доступ до поля класу
    auto sameSign = [this](double x1, double x2) {
        return f(x1) * f(x2) > 0;
    };

    if (sameSign(ta, tb)) {
        cout << "No solution on interval" << endl;
        return -1;
    }

    // Лямбда для одного кроку дихотомії
    // Захоплює ta, tb за посиланням [&] — бо змінює їх на кожному кроці
    auto step = [&]() {
        double c = (ta + tb) / 2.0;
        if (f(ta) * f(c) < 0)
            tb = c;
        else
            ta = c;
        iter++;
    };

    while (abs(tb - ta) > eps) {
        step(); // викликаємо лямбду замість тіла циклу
    }

    x = (ta + tb) / 2.0;
    cout << "Iterations: " << iter << endl;
    return 0;
}

void Dyhotomia_class::newton() {
    double xn = 1000.0; // стартова точка — як в оригіналі

    cout << "\n--- Newton's Method Iterations ---" << endl;
    cout << setprecision(6);

    // Лямбда для одного кроку методу Ньютона
    // Захоплює [this] — щоб використовувати f і df
    auto newtonStep = [this](double x) -> double {
        double f_val  = f(x);
        double df_val = df(x);

        if (abs(df_val) < 1e-10) return x; // захист від ділення на 0
        return x - f_val / df_val;
    };

    // Лямбда для корекції якщо вийшли за межі інтервалу
    // Захоплює a, b за [this]
    auto clamp = [this](double x_next, double x_curr) -> double {
        if (x_next > b) return (x_curr + b) / 2.0;
        if (x_next < a) return (x_curr + a) / 2.0;
        return x_next;
    };

    for (int i = 0; i < 100; i++) {
        double x_next = newtonStep(xn);  // крок Ньютона
        x_next = clamp(x_next, xn);      // корекція меж

        cout << "Step " << i + 1 << ": x = " << x_next << endl;

        // Лямбда-умова зупинки — IIFE стиль
        // Захоплює x_next, xn, eps за [&]
        auto shouldStop = [&]() {
            return abs(x_next - xn) < eps;
        };

        if (shouldStop()) {
            cout << "Newton Final Result: " << x_next << endl;
            return;
        }

        xn = x_next;
    }
}