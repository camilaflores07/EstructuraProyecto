#ifndef PINCELQUEUE_H
#define PINCELQUEUE_H

#include <QGraphicsScene>
#include "Queue.h"

class PincelQueue {
public:
    explicit PincelQueue(QGraphicsScene *scene);
    void redraw(Queue* queue);
    void drawNode(int val, qreal x, qreal y, bool isFront = false, bool isRear = false);
    void drawArrow(qreal x1, qreal y1, qreal x2, qreal y2);
    void drawNull(qreal x, qreal y);
    void drawLabel(const QString &text, qreal x, qreal y);

private:
    QGraphicsScene *scene;
};

#endif // PINCELQUEUE_H
