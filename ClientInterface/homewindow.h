#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include "equationsolver.h"

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

private:
    Ui::HomeWindow *ui;
    equationSolver solver;
    
    // Вспомогательная функция для проверки ввода
    bool validateInput(double &x0, double &tolerance, int &maxIterations);
};

#endif // HOMEWINDOW_H 