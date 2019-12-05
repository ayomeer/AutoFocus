#include "berechnung.h"

Berechnung::Berechnung(QObject *parent) : QObject(parent)
{

}

/**
 * @brief   Ueberpruefung der Eingabeparameter
 * @param   TODO
 * @return  0: kein Fehler
 *          1: Fehler
 */
bool Berechnung::testEingabe(int brennweite, QString objektweite)
{
    // Example
    return 0;
    //
}

/**
 * @brief   Fehlermeldung mit QMessageBox
 * @param   -
 * @return  -
 */
void Berechnung::fehlermeldung()
{
	QMessageBox msgBox;
	msgBox.setText("Bitte eine positive Zahl eingeben");
	msgBox.exec();
	abc
}

/**
 * @brief   Berechnung und Anzeige der Bildweite
 * @param   TODO
 * @return  -
 */
void Berechnung::calcBildweite(QLineEdit *l, const int brennweite, const QString objektweite)
{
  l->((-brennweite)* objektweite / (objektweite - brennweite));
}
