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
    QString digits;
    QString letters;

    QRegularExpression re("([1-9]+)([a-z]+)"); //
    QRegularExpressionMatch match = re.match(objektweite);

    if (match.hasMatch()) {
        digits = match.captured(1); // "1234"
        letters = match.captured(2); // "mm"
    }
    else
    {
        return 1; // theoretisch Error bei no match .. aktuell 2 Fehler
    }

    this->int_brennweite = digits.toDouble();
    this->str_brennweite = letters;

    string str = this->str_brennweite.toStdString();

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

    //cout << letters.toStdString()<< endl; //testAusgabe

    //TODO: correct response

    return 0;
}

/**
 * @brief   Fehlermeldung mit QMessageBox
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
 * @brief   Berechnung und Anzeige der Bildweite
 * @param   TODO
 * @return  -
 */
void Berechnung::calcBildweite(QLineEdit *l, const int brennweite, const QString objektweite)
{
    //float einheitenfaktor = 0;
    double bildweite;

    /*
     switch (str2int(str))
     {
     case "mm":
      einheitenfaktor=1;
      break;
     case "cm":
      einheitenfaktor=10;
      break;
     case "dm":
      einheitenfaktor=100;
      break;
     case "m":
      ©
      break;
     default:
      this->fehlermeldung();
      */
    double double_brennweite = double(brennweite);


     bildweite = 1/(1/double_brennweite)-(1/(this->int_brennweite*this->einheitenfaktor));
             //((-brennweite*this->einheitenfaktor) * int_objektweite / (int_objektweite - brennweite*this->einheitenfaktor));

     l->setText(QString::number(bildweite) + " mm ");

}
