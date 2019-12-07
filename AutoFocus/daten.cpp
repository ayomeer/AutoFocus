#include "daten.h"

Daten::Daten(QObject *parent) : QObject(parent)
{

}

/**
 * @brief   Initialisierung der ComboBox mit Grundeinstellung
 * @param   Pointer zu QComboBox cbBrennweite
 * @return  -
 */
void Daten::initComboBox(QComboBox *cb)
{
    cb->addItem("Auswahl", QVariant(0));
    cb->addItem("20 mm", QVariant(20));
    cb->addItem("35 mm", QVariant(35));
    cb->addItem("50 mm", QVariant(50));
}

/**
 * @brief   Rueckgabe der Brennweite als int sowie Laengeneinheit als str
 * @param   Pointer zu QComboBox cbBrennweite
 * @return  0: keine gewaehlte Linse
 *          sonst: ?? Brennweite der gewaehlten Linse in mm
 */
int Daten::getBrennweite(const QComboBox *cb)
{
    QString temp = cb->currentData().toString();
    QRegularExpression re("(\\d+) (\\w+)");
    QRegularExpressionMatch match = re.match(temp);  // "1234 mm"

    QString digits;
    QString letters;

    if (match.hasMatch()) {
        digits = match.captured(1); // "1234"
        letters = match.captured(2); // "mm"
    }

    this->int_brennweite = digits.toInt();
    this->str_brennweite = letters;

    return cb->currentData().toInt();
}

/**
 * @brief   Rueckgabe der Brennweite der ausgewählten Linse
 * @param   Pointer zu QLineEdit leObjektweite
 * @return  Eingabe der QLineEdit leObjektweite im String-Format
 */
QString Daten::getObjektweite(const QLineEdit *l)
{
    return (l->text());
}
