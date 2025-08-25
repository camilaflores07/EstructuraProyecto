#include "Pincel.h"
#include <QPen>
#include <QString>
#include <QGraphicsTextItem>

Pincel::Pincel(QGraphicsScene *scene) : scene(scene) {}

void Pincel::redraw(const QList<int> &valores)
{
    scene->clear();

    qreal x = 20, y = 70;
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

    const qreal diameter = 60; // Diámetro del círculo
    const qreal radius = diameter / 2;

    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(0, 0, 0)); // Borde negro

    // Todos los nodos blancos
    QBrush brush;
    brush.setColor(QColor(255, 255, 255)); // Blanco
    brush.setStyle(Qt::SolidPattern);

    // Dibujar círculo
    scene->addEllipse(x, y, diameter, diameter, pen, brush);

    // Texto del valor - centrado en el círculo
    QGraphicsTextItem* text = scene->addText(QString::number(val));
    QFont font = text->font();
    font.setPointSize(14);
    font.setBold(true);
    text->setFont(font);

    // Calcular posición centrada
    QRectF textRect = text->boundingRect();
    qreal textX = x + radius - (textRect.width() / 2);
    qreal textY = y + radius - (textRect.height() / 2);

    text->setPos(textX, textY);
    text->setDefaultTextColor(QColor(0, 0, 0)); // Texto negro

    //const qreal w = 60, h = 40;
  //  QPen pen; pen.setWidthF(2.0);

  //  scene->addRect(x, y, w, h, pen);
   // scene->addText(QString::number(val))->setPos(x + 18, y + 8);
}

void Pincel::drawArrow(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(255, 255, 255)); // Flechas blancas

    scene->addLine(x1, y1, x2, y2, pen);

    // Punta de la flecha
    const qreal s = 8;
    scene->addLine(x2, y2, x2 - s, y2 - s, pen);
    scene->addLine(x2, y2, x2 - s, y2 + s, pen);
    //QPen pen; pen.setWidthF(2.0);

    //scene->addLine(x1, y1, x2, y2, pen);
    //const qreal s = 6; // punta
    //scene->addLine(x2, y2, x2 - s, y2 - s, pen);
   // scene->addLine(x2, y2, x2 - s, y2 + s, pen);

}

void Pincel::drawNull(qreal x, qreal y)
{
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(255, 255, 255)); // Blanco para NULL

}
