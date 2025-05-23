#include "homewindow.h"
#include "ui_homewindow.h"
#include <QMessageBox>
#include <cmath>

// Функция exp(-x) выбрана потому что:
// 1. Имеет единственное решение x ≈ 0.567
// 2. Метод итераций гарантированно сходится для любого начального приближения
// 3. Производная функции всегда меньше 1 по модулю
// 4. Решение легко проверить
double phi(double x) {
    return exp(-x);
}

HomeWindow::HomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeWindow)
    , currentPhi(phi_exp) // По умолчанию используем exp(-x)
{
    ui->setupUi(this);
    this->setWindowTitle("Решение уравнений методом последовательных приближений");
    
    // Устанавливаем значения по умолчанию
    updateInitialValue(0); // Устанавливаем начальные значения для exp(-x)
    ui->lineEdit_tolerance->setText("0.0001");
    ui->lineEdit_maxIter->setText("100");

    connect(ClientManager::getInstance(), &ClientManager::equationSolved,
            this, &HomeWindow::onEquationSolved);
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::updateInitialValue(int functionIndex)
{
    switch(functionIndex) {
        case 0: // exp(-x)
            ui->lineEdit_x0->setText("0.0");
            currentPhi = phi_exp;
            break;
        case 1: // (x² + 6)/5
            ui->lineEdit_x0->setText("1.0");
            currentPhi = phi_quadratic;
            break;
        case 2: // 0.5 * cos(x)
            ui->lineEdit_x0->setText("0.0");
            currentPhi = phi_cos;
            break;
    }
}

void HomeWindow::on_comboBox_function_currentIndexChanged(int index)
{
    updateInitialValue(index);
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

// void HomeWindow::on_pushButton_solve_clicked()
// {
//     double x0, tolerance;
//     int maxIterations;
    
//     // Проверяем корректность ввода
//     if (!validateInput(x0, tolerance, maxIterations)) {
//         return;
//     }
    
//     // Решаем уравнение
//     double result = solver.solveIterationMethod(currentPhi, x0, tolerance, maxIterations);
    
//     // Выводим результат
//     if (std::isnan(result)) {
//         ui->label_result->setText("Решение не найдено за указанное число итераций");
//     } else {
//         ui->label_result->setText(QString("Решение: x = %1").arg(result, 0, 'g', 10));
//     }
// }

void HomeWindow::on_pushButton_solve_clicked()
{
    double x0, tolerance;
    int maxIterations;

    if (!validateInput(x0, tolerance, maxIterations)) {
        return;
    }

    if (!ClientManager::getInstance()->isConnected()) {
        ui->label_result->setText("Нет подключения к серверу.");
        return;
    }

    ClientManager::getInstance()->solveEquation("phi_exp", x0, tolerance, maxIterations);
    ui->label_result->setText("Выполняется вычисление...");
}

void HomeWindow::onEquationSolved(bool success, double root, const QString& message)
{
    if (success) {
        ui->label_result->setText(QString("Решение: x = %1").arg(root, 0, 'g', 10));
    } else {
        ui->label_result->setText("Ошибка: " + message);
    }
}

