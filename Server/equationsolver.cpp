#include "equationsolver.h"
#include <cmath>

equationSolver::equationSolver() {}

double equationSolver::solveIterationMethod(double (*phi)(double), double x0, double tolerance, int maxIterations) {
    double x = x0;
    for (int i = 0; i < maxIterations; i++) {
        double newX = phi(x);

        if (fabs(newX - x) < tolerance) {
            return newX;
        }

        x = newX;
    }
    return NAN;
}
