#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief   Bereitet das Hinzufügen einer neuen Linse vor
 * @todo    addLensWindow öffnen für die Erfassung der neuen Linse
 * @param   -
 * @return  -
 */
void MainWindow::on_pbLinseHinzufuegen_clicked()
{
    // Example, wie man den Text ändert
    ui->leBildweite->setText("Example");
}

/**
 * @brief   Berechnung der Bildweite mit Überprüfung der Eingabewerte
 * @todo    Überprüfung der Eingabewerte (Linse - Linse ausgewählt, Objektweite - positive Zahl)
 *          Ausgabe der Bildweite und der Visualisierung
 * @param   -
 * @return  -
 */
void MainWindow::on_leObjektweite_editingFinished()
{
    // Example, wie man den Text von Objektweite in Bildweite einfügt
    ui->leBildweite->setText(ui->leObjektweite->text());
}
