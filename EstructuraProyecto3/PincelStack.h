#ifndef PINCELSTACK_H
#define PINCELSTACK_H

#include <QGraphicsScene>
#include "Stack.h"

class PincelStack {
public:
    explicit PincelStack(QGraphicsScene *scene);
    void redraw(Stack* stack);
    void drawNode(int val, qreal x, qreal y, bool isTop = false);
    void drawArrow(qreal x1, qreal y1, qreal x2, qreal y2);
    void drawNull(qreal x, qreal y);
    void drawLabel(const QString &text, qreal x, qreal y);

private:
    QGraphicsScene *scene;
};
#endif
