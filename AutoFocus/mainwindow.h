#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "daten.h"
#include "linse.h"
#include "berechnung.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbLinseHinzufuegen_clicked();
    void on_leObjektweite_editingFinished();
    void on_cbBrennweite_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    Daten *data;
    Linse *lens;
    Berechnung *calc;
    //Grafik *grafic;

};
#endif // MAINWINDOW_H
