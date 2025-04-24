#ifndef EQUATIONSOLVER_H
#define EQUATIONSOLVER_H

class equationSolver
{
public:
    equationSolver();
    static double solveIterationMethod(double (*phi)(double), double x0, double tolerance, int maxIterations);
};

#endif // EQUATIONSOLVER_H
