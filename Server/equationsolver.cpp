#include "equationsolver.h"
#include <cmath>
#include <QDebug>

double equationSolver::phi_exp(double x) {
    return exp(-x);
}

double equationSolver::phi_quadratic(double x) {
    return (x*x + 6.0) / 5.0;
}

double equationSolver::phi_cos(double x) {
    return 0.5 * cos(x);
}

double equationSolver::solveIterationMethod(const QString &funcName, double x0, double tolerance, int maxIterations) {
    double (*phi)(double) = nullptr;

    if (funcName == "phi_exp") {
        phi = &phi_exp;
    } else if (funcName == "phi_quadratic") {
        phi = &phi_quadratic;
    } else if (funcName == "phi_cos") {
        phi = &phi_cos;
    } else {
        qDebug() << "Unknown function name:" << funcName;
        return NAN;
    }

    double x = x0;
    for (int i = 0; i < maxIterations; ++i) {
        double newX = phi(x);
        if (fabs(newX - x) < tolerance)
            return newX;
        x = newX;
    }

    return NAN;
}
