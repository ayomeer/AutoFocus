#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Objekte erzeugen
    data = new Daten(parent);
    calc = new Berechnung(parent);
    lens = new Linse(parent);
    //grafic = new Grafik(parent);

    data->initComboBox(ui->cbBrennweite);
    lens->loadDaten(ui->cbBrennweite);

    connect(ui->cbBrennweite, &QLineEdit::returnPressed,
            this, &MainWindow::on_returnPressed);
}

MainWindow::~MainWindow()
{
    // Objekte loeschen
    delete data;
    delete calc;
    delete lens;
    // delete grafic;

    delete ui;
}

/**
 * @brief   Bereitet das Hinzufügen einer neuen Linse vor
 * @param   -
 * @return  -
 */
void MainWindow::on_pbLinseHinzufuegen_clicked()
{
    // Example
    ui->leBildweite->setText("+");
    //

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
        // Example
        ui->leBildweite->setText("1");
        //

        bool fehler = 0;

        fehler = calc->testEingabe(data->getBrennweite(ui->cbBrennweite), data->getObjektweite(ui->leObjektweite));

        if (fehler) {
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
    if (!this->first_init) {
        this->first_init = 1;
    }
    else {
        MainWindow::on_returnPressed();
    }
}
