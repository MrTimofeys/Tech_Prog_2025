#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <cmath>
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
    
    // Вспомогательная функция для проверки ввода
    bool validateInput(double &x0, double &tolerance, int &maxIterations);
    
    // Обновление начального приближения в зависимости от выбранной функции
    void updateInitialValue(int functionIndex);
};

#endif // HOMEWINDOW_H 
