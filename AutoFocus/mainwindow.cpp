#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grafik.h"

/**
 * @brief   Konstruktor - erstellt ein Objekt
 * @param   QWidget *parent - aktuelle Anwendung
 * @return  -
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Objekte erzeugen
    data = new Daten(parent);
    calc = new Berechnung(parent);
    lens = new Linse(parent);

    data->initComboBox(ui->cbBrennweite);
    lens->loadDaten(ui->cbBrennweite);

    connect(ui->leObjektweite, &QLineEdit::returnPressed,
            this, &MainWindow::on_returnPressed);
}

/**
 * @brief   Destruktor - zerstoert eigenes Objekt
 *          und alle benoetigten Objekte für die Methoden,
 *          welche eine Veraenderung am GUI ausloesen
 * @param   -
 * @return  -
 */
MainWindow::~MainWindow()
{
    // Objekte loeschen
    delete data;
    delete calc;
    delete lens;

    delete ui;
}

/**
 * @brief   Bereitet das Hinzufügen einer neuen Linse vor
 * @param   -
 * @return  -
 */
void MainWindow::on_pbLinseHinzufuegen_clicked()
{
    Linse l;
    l.setComboBox(ui->cbBrennweite);
    l.setModal(true);
    l.exec();
}

/**
 * @brief   Berechnung der Bildweite mit Überprüfung der Eingabewerte
 * @param   -
 * @return  -
 */
void MainWindow::on_returnPressed()
{
    if (data->getBrennweite(ui->cbBrennweite) == 0 || data->getObjektweite(ui->leObjektweite) == "") {
        ui->leBildweite->setText("");
    }
    else {
        bool fehler = 0;

        fehler = calc->testEingabe(data->getObjektweite(ui->leObjektweite));

        if (fehler) {
            //Fehlermeldung mit QMessageBox
            calc->fehlermeldung();
        }
        else {
            // Berechnung und Anzeige, da alle Eingabeparameter gültig sind
            calc->calcBildweite(ui->leBildweite, data->getBrennweite(ui->cbBrennweite));
            ui->wgtRenderArea->redraw(Grafik::Bildweite);
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
    if (!this->first_init) {
        this->first_init = 1;
    }
    else {
        MainWindow::on_returnPressed();
    }
}

