#ifndef DATEN_H
#define DATEN_H

#include <QObject>

#include <QComboBox>
#include <QLineEdit>

class Daten : public QObject
{
public:
    explicit Daten(QObject *parent = nullptr);

    void initComboBox(QComboBox *cb);
    int getBrennweite(const QComboBox *cb);
    QString getObjektweite(const QLineEdit *l);
private:
    int int_brennweite;
};

#endif // DATEN_H
