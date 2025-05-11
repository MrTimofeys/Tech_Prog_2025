#include "homewindow.h"
#include "ui_homewindow.h"
#include <QMessageBox>
#include <cmath>

// Пример функции для решения уравнения x = cos(x)
double phi(double x) {
    return cos(x);
}

HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Решение уравнений");
    
    // Устанавливаем значения по умолчанию
    ui->lineEdit_x0->setText("0.5");
    ui->lineEdit_tolerance->setText("0.0001");
    ui->lineEdit_maxIter->setText("100");
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

bool HomeWindow::validateInput(double &x0, double &tolerance, int &maxIterations)
{
    bool ok;
    
    // Проверяем начальное приближение
    x0 = ui->lineEdit_x0->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Неверное значение начального приближения");
        return false;
    }
    
    // Проверяем точность
    tolerance = ui->lineEdit_tolerance->text().toDouble(&ok);
    if (!ok || tolerance <= 0) {
        QMessageBox::warning(this, "Ошибка", "Точность должна быть положительным числом");
        return false;
    }
    
    // Проверяем максимальное число итераций
    maxIterations = ui->lineEdit_maxIter->text().toInt(&ok);
    if (!ok || maxIterations <= 0) {
        QMessageBox::warning(this, "Ошибка", "Максимальное число итераций должно быть положительным целым числом");
        return false;
    }
    
    return true;
}

void HomeWindow::on_pushButton_solve_clicked()
{
    double x0, tolerance;
    int maxIterations;
    
    // Проверяем корректность ввода
    if (!validateInput(x0, tolerance, maxIterations)) {
        return;
    }
    
    // Решаем уравнение
    double result = solver.solveIterationMethod(phi, x0, tolerance, maxIterations);
    
    // Выводим результат
    if (std::isnan(result)) {
        ui->label_result->setText("Решение не найдено за указанное число итераций");
    } else {
        ui->label_result->setText(QString("Решение: x = %1").arg(result, 0, 'g', 10));
    }
} 