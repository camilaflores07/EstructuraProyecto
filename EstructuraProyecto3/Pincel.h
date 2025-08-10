#ifndef PINCEL_H
#define PINCEL_H

#include <QGraphicsScene>
#include <QList>

class Pincel {
public:
    explicit Pincel(QGraphicsScene *scene);

    void redraw(const QList<int> &valores);
    void drawNode(int val, qreal x, qreal y);
    void drawArrow(qreal x1, qreal y1, qreal x2, qreal y2);
    void drawNull(qreal x, qreal y);

private:
    QGraphicsScene *scene;
};

#endif // PINCEL_H
