#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_UI(new Ui::MainWindow)
{
    m_UI->setupUi(this);

    // Initialize the member variables with values from UI elements
    m_Person.setWeight(m_UI->doubleSpinBoxWeight->value());
    m_Time = m_UI->doubleSpinBoxTime->value();
    m_Speed = m_UI->doubleSpinBoxSpeed->value();

    // Connect to spinboxes
    connect(m_UI->doubleSpinBoxWeight, &QDoubleSpinBox::valueChanged,
            this, &MainWindow::weightChanged);
    connect(m_UI->doubleSpinBoxTime, &QDoubleSpinBox::valueChanged,
            this, &MainWindow::timeChanged);
    connect(m_UI->doubleSpinBoxSpeed, &QDoubleSpinBox::valueChanged,
            this, &MainWindow::speedChanged);

    // Update calorie count display
    connect(this, &MainWindow::calorieCountChanged, [=]() {
        m_UI->labelCalorieCountNumber->setText(QString::number(m_CalorieCount));
    });

    // Testing
    connect(m_UI->pushButtonTest, &QPushButton::clicked,
            this, &MainWindow::openFileDialog);

    calculateCalories();
}

MainWindow::~MainWindow()
{
    delete m_UI;
}

void MainWindow::calculateCalories() {
    m_CalorieCount = ( (0.0215 * (m_Speed * m_Speed * m_Speed)) - (0.1765 * (m_Speed * m_Speed))
                      + (0.8710) + 1.4577) * m_Person.weight() * m_Time;
    emit calorieCountChanged(m_CalorieCount);

    qDebug() << "New calorie count: " << QString::number(m_CalorieCount);
}

void MainWindow::weightChanged(double weight) {
    m_Person.setWeight(weight);
    calculateCalories();
    qDebug() << "Weight changed to " << QString::number(weight);
}

void MainWindow::timeChanged(double time) {
    m_Time = time;
    calculateCalories();
    qDebug() << "Time changed to " << QString::number(time);
}

void MainWindow::speedChanged(double speed) {
    m_Speed = speed;
    calculateCalories();
    qDebug() << "Speed changed to " << QString::number(speed);
}

void MainWindow::openFileDialog() {
    QFileDialog f(this);
    f.setFileMode(QFileDialog::AnyFile);
    QString file = f.getOpenFileName(this, "Test", "/");
    qDebug() << "This should have opened a file dialog...";
    m_UI->pushButtonTest->setText(file)
}
