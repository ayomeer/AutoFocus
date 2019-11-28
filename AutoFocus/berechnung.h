#ifndef BERECHNUNG_H
#define BERECHNUNG_H

#include <QObject>

#include <QLineEdit>

class Berechnung : public QObject
{
    Q_OBJECT
public:
    explicit Berechnung(QObject *parent = nullptr);

    bool testEingabe(int brennweite, QString objektweite);
    void fehlermeldung();
    void calcBildweite(QLineEdit *l, const int brennweite, const QString objektweite);
};

#endif // BERECHNUNG_H