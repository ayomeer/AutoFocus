#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPaintEvent>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Objekte erzeugen
    data = new Daten(parent);
    lens = new Linse(parent);
    calc = new Berechnung(parent);
    //grafic = new Grafik(parent);

    data->initComboBox(ui->cbBrennweite);
}

MainWindow::~MainWindow()
{
    // Objekte loeschen
    delete data;
    delete lens;
    delete calc;
    // delete grafic;

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
    // Example
    ui->leBildweite->setText("+");
    //

    lens->addLinse(ui->cbBrennweite);
}

/**
 * @brief   Berechnung der Bildweite mit Überprüfung der Eingabewerte
 * @todo    Überprüfung der Eingabewerte (Linse - Linse ausgewählt (siehe getBrennweite), Objektweite - positive Zahl (QString))
 *          Ausgabe der Bildweite und der Visualisierung
 * @param   -
 * @return  -
 */
void MainWindow::on_leObjektweite_editingFinished()
{
    // ToDo: Set up QPainter Object and use it in widgets render method: ui->wgtRenderArea.render(QPainter* painter)
    QPainter painter(ui->wgtRenderArea);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    painter.drawText(rect(), Qt::AlignCenter, "Hello?");
    painter.end();


    QPainter *p = &painter;

    ui->wgtRenderArea->render(p);

    //Something seems wrong with this v
    if (data->getBrennweite(ui->cbBrennweite) == 0 || data->getObjektweite(ui->leObjektweite) == "") {
        ui->leBildweite->setText("");
        calc->fehlermeldung();

    }
    else {
        // Example
        ui->leBildweite->setText("1");
        //

        bool fehler = 0;

        fehler = calc->testEingabe(data->getBrennweite(ui->cbBrennweite), data->getObjektweite(ui->leObjektweite));

        if(fehler) {
            //Fehlermeldung mit QMessageBox
            calc->fehlermeldung();
        }
        else {
            // Berechnung und Anzeige, da alle Eingabeparameter gültig sind
            calc->calcBildweite(ui->leBildweite, data->getBrennweite(ui->cbBrennweite), data->getObjektweite(ui->leObjektweite));
            //grafic->updateGrafik(ui->openGLGrafik, data->getBrennweite(ui->cbBrennweite), data->getObjektweite(ui->leObjektweite));
        }
    }
}

/**
 * @brief   Überprüfung und Berechnung mit der neuen Linse
 * @param   - (index nicht notwendig)
 * @return  -
 */
void MainWindow::on_cbBrennweite_currentIndexChanged(int index)
{
    // Ruft direkt die Event-Methode on_leObjektweite_editingFinished() auf
	// Kommentarversuch
    MainWindow::on_leObjektweite_editingFinished();
}
