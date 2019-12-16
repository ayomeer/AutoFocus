#include "berechnung.h"

Berechnung::Berechnung(QObject *parent) : QObject(parent)
{

}

/**
 * @brief   Ueberpruefung der Eingabeparameter
 * @param   Objektweite Input-Feld der Distanz zwischen Linse und Objekt
 * @return  0: kein Fehler
 *          1: Fehler (falsche Einheit, unpassender String nach Regex ZahlLetters)
 */
bool Berechnung::testEingabe(int brennweite, QString objektweite)
{
    QString digits;
    QString letters;

    QRegularExpression re("([0-9]+)([a-z]+)"); // Regexmuster: ZahlEinheit
    QRegularExpressionMatch match = re.match(objektweite);

    if (match.hasMatch()) {
        digits = match.captured(1);  // "1234"
        letters = match.captured(2); // "mm"
    }
    else
    {
        return 1;
    }

    this->int_brennweite = digits.toDouble();

    string str = letters.toStdString();

    if (!str.compare("mm"))
    {
        this->einheitenfaktor=1;
    }
    else if(!str.compare("cm"))
    {
        this->einheitenfaktor=10;
    }
    else if(!str.compare("dm"))
    {
        this->einheitenfaktor=100;
    }
    else if(!str.compare("m"))
    {
        this->einheitenfaktor=100;
    }
    else
    {
        return 1;
    }
    return 0;
}

/**
 * @brief   Fehlermeldung mit QMessageBox bei falscher Eingabe
 * @param   -
 * @return  -
 */
void Berechnung::fehlermeldung()
{
    QMessageBox msgBox;
    msgBox.setText("Bitte eine positive, ganze Zahl in den vorgegebenen Einheiten eingeben");
    msgBox.exec();
}

/**
 * @brief   Berechnung und Anzeige der Bildweite nach Basis Formel: 1/f = 1/g + 1/g
 *          f = Brennweite, g = Gegenstandsweite, b = Bildweite
 *          verwendet Formel aufgelöst nach Bildweite
 * @param   QLineEdit *l, const int brennweite, const QString objektweite
 * @return  double bildweite
 */
void Berechnung::calcBildweite(QLineEdit *l, const int brennweite, const QString objektweite)
{
    double bildweite;
    double double_brennweite = double(brennweite);

    bildweite = 1/(1/double_brennweite)-(1/(this->int_brennweite*this->einheitenfaktor));

    l->setText(QString::number(bildweite) + " mm ");
}
