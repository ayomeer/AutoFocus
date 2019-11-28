#ifndef LINSE_H
#define LINSE_H

#include <QObject>

#include <QComboBox>

class Linse : public QObject
{
    Q_OBJECT
public:
    explicit Linse(QObject *parent = nullptr);

    void addLinse(QComboBox *cb);
};

#endif // LINSE_H
