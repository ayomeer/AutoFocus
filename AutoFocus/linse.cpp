#include "linse.h"
#include "ui_linse.h"

/**
 * @brief   Konstruktor - erstellt ein Objekt
 * @param   QWidget *parent - aktuelle Anwendung
 * @return  -
 */
Linse::Linse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Linse)
{
    ui->setupUi(this);
}

/**
 * @brief   Destruktor - zerstoert eigenes Objekt
 * @param   -
 * @return  -
 */
Linse::~Linse()
{
    delete ui;
}

/**
 * @brief   Definiert die ComboBox, welche für die Speicherung
 *          der neuen Linsen benötigt wird
 * @param   QComboBox *cb - Addresse der benötigten ComboBox
 *          für die Methoden
 * @return  -
 */
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
        addLinseTxtFile(brennweite);
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

/**
 * @brief   Speichert den Wert in einem Text-File ab (zeilenweise)
 * @param   Wert der Brennweite in int
 * @return  -
 */
void Linse::addLinseTxtFile(int brennweite)
{
    QFile file("brennweite_storage.txt");
    if(file.open(QIODevice::WriteOnly   |
                 QIODevice::Append      |
                 QIODevice::Text))
    {
        // We're going to write text to the file
        QString outString = QString::number(brennweite);

        QTextStream out(&file);
        out << outString << "\n";

        file.close();
    }
}

/**
 * @brief   Laedt alle Daten aus dem Textfile auf die ComboBox
 * @param   Pointer zu QComboBox cbBrennweite
 * @return  -
 */
void Linse::loadDaten(QComboBox *cb)
{
    QFile file("brennweite_storage.txt");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // We're going to read text from the file
        QTextStream in(&file);

        int i = 1;
        QString inString;

        while (!in.atEnd()) {
            inString = in.readLine();

            QString name = (QString)inString + " mm";
            cb->addItem(name, (QVariant)inString);

            ++i;
        }

        file.close();
    }
}
