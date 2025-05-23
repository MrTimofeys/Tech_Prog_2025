#ifndef EQUATIONSOLVER_H
#define EQUATIONSOLVER_H

#include <QString>

class equationSolver {
public:
    static double solveIterationMethod(const QString &funcName, double x0, double tolerance, int maxIterations);

    static double phi_exp(double x);
    static double phi_quadratic(double x);
    static double phi_cos(double x);
};

#endif // EQUATIONSOLVER_H
