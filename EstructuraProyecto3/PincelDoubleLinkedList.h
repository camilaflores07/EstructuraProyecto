#ifndef PINCELDOUBLELINKEDLIST_H
#define PINCELDOUBLELINKEDLIST_H

#include <QGraphicsScene>
#include <QList>

class PincelDoubleLinkedList {
public:
    explicit PincelDoubleLinkedList(QGraphicsScene *scene);
    void redraw(const QList<int> &valores);
    void drawNode(int val, qreal x, qreal y);
    void drawDoubleArrow(qreal x1, qreal y1, qreal x2, qreal y2);
    void drawNull(qreal x, qreal y);
    void drawHeadLabel(qreal x, qreal y);
    void drawTailLabel(qreal x, qreal y);

private:
    QGraphicsScene *scene;
};

#endif // PINCELDOUBLELINKEDLIST_H
