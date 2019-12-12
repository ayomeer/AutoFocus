#ifndef LINSE_H
#define LINSE_H

#include <QDialog>

#include <QComboBox>
#include <QAbstractButton>
#include <QPushButton>
#include <qmessagebox.h>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Linse;
}

class Linse : public QDialog
{
    Q_OBJECT

public:
    explicit Linse(QWidget *parent = nullptr);
    ~Linse();

    void setComboBox(QComboBox *cb);
    void loadDaten(QComboBox *cb);

private slots:
    void on_pbSpeichern_clicked();
    void on_pbAbbrechen_clicked();

private:
    Ui::Linse *ui;

    QComboBox *cbLinse;

    void fehlermeldung();
    void addLinseTxtFile(int brennweite);
};

#endif // LINSE_H
