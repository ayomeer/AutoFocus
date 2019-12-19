#ifndef GRAFIK_H
#define GRAFIK_H

#include <QWidget>
#include <QBrush>
#include <QPen>

class Grafik : public QWidget
{
    Q_OBJECT
public:
    enum HighlightTarget {None, Bildweite, Objektweite};

    explicit Grafik(QWidget *parent = nullptr);

signals:

public slots:
    void redraw(HighlightTarget target);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    HighlightTarget highlighted;
    QPen pen;
    QBrush brush;
};

#endif // GRAFIK_H
