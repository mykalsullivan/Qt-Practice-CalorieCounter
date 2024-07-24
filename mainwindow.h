#pragma once

#include "person.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void calculateCalories();
    void weightChanged(double weight);
    void timeChanged(double time);
    void speedChanged(double speed);

    // Testing
    void openFileDialog();

signals:
    void calorieCountChanged(int);

private:
    Ui::MainWindow* m_UI;
    Person m_Person;
    int m_CalorieCount = 0;
    double m_Time = 0.0f, m_Speed = 0.0f;
};
