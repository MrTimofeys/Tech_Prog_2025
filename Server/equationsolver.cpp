#include "equationsolver.h"
#include <cmath>

equationSolver::equationSolver() {}

double equationSolver::solveIterationMethod(double (*phi)(double), double x0, double tolerance, int maxIterations) {
    double x = x0;
    for (int i = 0; i < maxIterations; i++) {
        double newX = phi(x); // Итерационный процесс: x_(n+1) = phi(x_n)

        if (fabs(newX - x) < tolerance) {
            return newX; // Условие остановки
        }

        x = newX;
    }
    return NAN; // Возвращаем NaN, если метод не сошёлся
}
