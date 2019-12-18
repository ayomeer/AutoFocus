#ifndef BERECHNUNG_H
#define BERECHNUNG_H

#include <QObject>
#include <QComboBox>
#include <QLineEdit>
#include <QMessageBox>
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

class Berechnung : public QObject
{
    Q_OBJECT
public:
    explicit Berechnung(QObject *parent = nullptr);

    bool testEingabe(QString objektweite ); //1. int brennweite
    void fehlermeldung();
    void calcBildweite(QLineEdit *l, const int brennweite);  // const QString objektweite

private:
    volatile double double_brennweite;
    volatile double einheitenfaktor;
};

#endif // BERECHNUNG_H
