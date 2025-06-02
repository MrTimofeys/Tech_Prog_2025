#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <cmath>
// #include "equationsolver.h"
#include "clientmanager.h"

using namespace std;

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

private slots:
    void on_pushButton_solve_clicked();
    void on_comboBox_function_currentIndexChanged(int index);
    void onEquationSolved(bool success, double root, const QString& message);

private:
    Ui::HomeWindow *ui;
    // equationSolver solver;
    
    // Вспомогательная функция для проверки ввода
    bool validateInput(double &x0, double &tolerance, int &maxIterations);
    
    // Функции для решения
    static double phi_exp(double x) { return exp(-x); }
    static double phi_quadratic(double x) { return (x*x + 6.0) / 5.0; }
    static double phi_cos(double x) { return 0.5 * cos(x); }
    
    // Указатель на текущую функцию
    double (*currentPhi)(double);
    
    // Обновление начального приближения в зависимости от выбранной функции
    void updateInitialValue(int functionIndex);
};

#endif // HOMEWINDOW_H 
