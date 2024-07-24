#pragma once
#include <QObject>

class Person : public QObject {
    Q_OBJECT

public:
    double weight() const { return m_Weight; }
    void setWeight(double weight);

signals:
    void weightChange();

private:
    double m_Weight = 0.0f;
};
