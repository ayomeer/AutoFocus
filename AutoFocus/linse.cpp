#include "linse.h"
#include "ui_linse.h"

Linse::Linse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Linse)
{
    ui->setupUi(this);
}

Linse::~Linse()
{
    delete ui;
}

void Linse::setComboBox(QComboBox *cb)
{
    cbLinse = cb;
}

/**
 * @brief   Fehlermeldung mit QMessageBox
 * @param   -
 * @return  -
 */
void Linse::fehlermeldung()
{
    QMessageBox::warning(this, "Fehler bei Eingabe",
                         "Eingabe muss eine positive Ganzzahl sein!",
                         QMessageBox::Ok);
}

/**
 * @brief   Ueberpruefung der Eingabe mit Fehlermeldung oder Speicherung in ComboBox
 *          brennweite > 0  : nur positive Zahlen
 *          sonst           : ungültige Eingabe
 * @param   -
 * @return  -
 */
void Linse::on_pbSpeichern_clicked()
{
    int brennweite = ui->leBrennweite->text().toInt();

    if (brennweite <= 0) {
        //Fehlermeldung mit QMessageBox
        fehlermeldung();
    }
    else {
        // neue Linse hinzufuegen
        cbLinse->addItem((ui->leBrennweite->text() + " mm"), (QVariant)brennweite);
        // Fenster schliessen
        Linse::close();
    }
}

/**
 * @brief   Hinzufuegen einer neuen Linse abbrechen
 * @param   -
 * @return  -
 */
void Linse::on_pbAbbrechen_clicked()
{
    // Fenster schliessen
    Linse::close();
}
