#include "Pincel.h"
#include <QPen>
#include <QString>
#include <QGraphicsTextItem>

Pincel::Pincel(QGraphicsScene *scene) : scene(scene) {}

void Pincel::redraw(const QList<int> &valores)
{
    scene->clear();

    if (valores.isEmpty()) {
        scene->addText("Lista vacía")->setPos(10, 10);
        return;
    }

    qreal x = 60, y = 80;
    for (int i = 0; i < valores.size(); ++i) {
        drawNode(valores[i], x, y);
        if (i < valores.size() - 1)
            drawArrow(x + 60, y + 20, x + 120, y + 20);
        x += 120;
    }
    drawNull(x, y + 14);
}

void Pincel::drawNode(int val, qreal x, qreal y)
{
    const qreal w = 60, h = 40;
    QPen pen; pen.setWidthF(2.0);

    scene->addRect(x, y, w, h, pen);
    scene->addText(QString::number(val))->setPos(x + 18, y + 8);
}

void Pincel::drawArrow(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QPen pen; pen.setWidthF(2.0);

    scene->addLine(x1, y1, x2, y2, pen);
    const qreal s = 6; // punta
    scene->addLine(x2, y2, x2 - s, y2 - s, pen);
    scene->addLine(x2, y2, x2 - s, y2 + s, pen);
}

void Pincel::drawNull(qreal x, qreal y)
{
    QPen pen; pen.setWidthF(2.0);
    scene->addEllipse(x, y, 12, 12, pen);
}
