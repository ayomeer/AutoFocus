#include "grafik.h"
#include <QPainter>

QPainterPath horizontalMeasurement(QString letter, QPoint p1, QPoint p2, int height, int arrowVertOffset=5, int noVert=0);


/**
 * @brief   Konstruktor Grafik-Klasse
 * @param   -
 * @return  -
 */
Grafik::Grafik(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

/**
 * @brief   Diese Slot-Methode wird aufgerufen, wenn die Grafik neu gezeichnet werden muss
 *          da sich ihr highlight Zustand geändert hat.
 * @param   hlTarget: "None", "Bildweite", "Objektweite".
 * @return  -
 */
void Grafik::redraw(HighlightTarget hlTarget)
{
    this->highlighted = hlTarget;
    update();
}


/**
 * @brief   Neuimplementierung der QWidget Methode zum Zeichnen der Grafik.
 *          Wird von Qt Hintergrundprozessen aufgerufen, nie direkt im Code.
 * @param   -
 * @return  -
 */
void Grafik::paintEvent(QPaintEvent *)
{
    //Create lense path using rectangle and quadratic bezier curves

    enum LenseProperties {LenseHeight = 100, LenseWidth = 11, CurveDistance = 25};

    QRect lenseRect(QPoint(-LenseWidth/2,-LenseHeight/2), QSize(LenseWidth, LenseHeight)); //Rectangle holding corner points of lense
    QPoint ctrlR(CurveDistance, 0); //Right bezier control point
    QPoint ctrlL(-CurveDistance, 0); //Left bezier control point

    // lense geometry
    QPainterPath lensePath;
    lensePath.moveTo(lenseRect.topLeft());
    lensePath.lineTo(lenseRect.topRight());
    lensePath.quadTo(ctrlR, lenseRect.bottomRight());
    lensePath.lineTo(lenseRect.bottomLeft());
    lensePath.quadTo(ctrlL, lenseRect.topLeft());

    // fill set-up
    QLinearGradient linearGrad(QPointF(0,0), QPointF(0,100));
    linearGrad.setColorAt(1, Qt::lightGray);
    linearGrad.setColorAt(0, Qt::white);
    QBrush brush(linearGrad);

    // paint lense
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);
    painter.translate(200,75); // position center of coordinate system where we want center of lense
    painter.setBrush(brush);
    painter.drawPath(lensePath);

    // focal point boxes
    enum {FocalLength = 50, FocalBoxSize = 6};
    QSize fSize(FocalBoxSize, FocalBoxSize);
    QRect fRectL(QPoint(-FocalLength-FocalBoxSize/2, -FocalBoxSize/2), fSize);
    QRect fRectR(QPoint(FocalLength-FocalBoxSize/2, -FocalBoxSize/2), fSize);
    QPen bluePen(Qt::blue);
    painter.setPen(bluePen);
    painter.drawRect(fRectL);
    painter.drawRect(fRectR);

    // dashed lines
    QPen dashPen(Qt::DashLine);
    dashPen.setColor(Qt::darkGreen);
    painter.setPen(dashPen);
    QPoint l1_top(0, -LenseHeight/2-20);
    QPoint l1_bottom(0, LenseHeight/2 + 20);
    QLine lenseCenterLine(l1_top, l1_bottom);
    painter.drawLine(lenseCenterLine);

    QPen dashDotPen(Qt::DashDotLine);
    dashDotPen.setColor(Qt::darkGray);
    painter.setPen(dashDotPen);
    QPoint l2_left(-200, 0);
    QPoint l2_right(200, 0);
    QLine lenseHorizontalLine(l2_left, l2_right);
    painter.drawLine(lenseHorizontalLine);

    // object and virtual image


    bluePen.setWidth(2);
    painter.setPen(bluePen);
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));

    enum LineProperties {ObjHeight = -40, ImageHeight = 20};

    QPoint p1(-150,0);
    QPoint p2(80,0);

    QLine objectLine(p1, QPoint(p1.x(), ObjHeight));
    painter.drawLine(objectLine);

    QLine imageLine(p2, QPoint(p2.x(), ImageHeight));
    painter.drawLine(imageLine);

    QPen blackPen(Qt::SolidLine);
    blackPen.setColor(Qt::black);
    blackPen.setWidth(1);
    painter.setPen(blackPen);

    // measurements
    QPainterPath path = horizontalMeasurement("f", QPoint(-FocalLength, 0), QPoint(0,0), 60, 5, 2);
    path.addPath(horizontalMeasurement("f", QPoint(0,0), QPoint(FocalLength, 0), 60, 5, 1));
    path.addPath(horizontalMeasurement("b", p1, QPoint(0,0), -60, -5, 2));
    path.addPath(horizontalMeasurement("g", QPoint(0,0),p2, -60, -5, 1));
    painter.drawPath(path);

    // light trace lines
    QPen redPen(Qt::red);
    painter.setPen(redPen);
    painter.drawLine(objectLine.p2(), QPoint(0, objectLine.p2().y()));
    painter.drawLine(QPoint(0,ObjHeight), imageLine.p2());
    painter.drawLine(objectLine.p2(), imageLine.p2());
    painter.drawLine(objectLine.p2(), QPoint(0, ImageHeight));
    painter.drawLine(QPoint(0, ImageHeight), imageLine.p2());
}

/**
 * @brief   Hilfsfunktion zum Zeichnen der bezeichneten Messgrössen in der Grafik.
 * @param   QString letter:         Textbuchstabe, mit dem die Messgrösse beschriftet werden soll
 *          QPoint p1:              Linker Messpunkt
 *          QPoint p2:              Rechter Messpunkt
 *          int height:             Höhe des Horizontalbalkens (negativ für Balken unterhalb)
 *          int arrowVertOffset:    Unterschied zwischen Höhe Vertikalbalken und Höhe Horizontalbalken
 *          int noVert:             Einen der Vertikallinien weglassen (0->keinen, 1->linker Balken, 2->rechter Balken)
 * @return  QPainterPath
 */
QPainterPath horizontalMeasurement(QString letter, QPoint p1, QPoint p2, int height, int arrowVertOffset, int noVert)
{
    enum {arrowHorOffset = 3}; // space between vertical bar and start of horizontal bar

    QRect rectOuter(QPoint(p1.x(), -height), p2); // bounding box for vertical bars
    QRect rectInner(QPoint(p1.x()+arrowHorOffset, -height+arrowVertOffset), // bounding box for horizontal bars
                    QPoint(p2.x()-arrowHorOffset, -height+arrowVertOffset));

    QPainterPath path(p1);
    // vertical lines
    if (noVert != 1){ //skip drawing left vertical line if noVert = 1
        path.lineTo(rectOuter.topLeft());
    }
    if (noVert != 2){ //skip drawing right vertical line if noVert = 2
        path.moveTo(rectOuter.topRight());
        path.lineTo(rectOuter.bottomRight());
    }
    // draw horizontal bar and arrowheads
    QPolygon arrowHeadLeft(4);
    arrowHeadLeft << QPoint(0,0) << QPoint(5,3) << QPoint(5,-3) << QPoint(0,0);
    QPolygon arrowHeadRight(4);
    arrowHeadRight << QPoint(0,0) << QPoint(-5,3) << QPoint(-5,-3) << QPoint(0,0);
    path.moveTo(rectInner.topLeft());
    path.addPolygon(arrowHeadLeft.translated(path.currentPosition().x(), path.currentPosition().y()));
    path.lineTo(rectInner.topRight());
    path.addPolygon(arrowHeadRight.translated(path.currentPosition().x(), path.currentPosition().y()));

    QFont arial("Arial", 8);
    QPoint textPos = rectInner.topLeft() + QPoint(rectInner.width()/2, -5);
    path.addText(textPos, arial, letter);
    return path;
}
