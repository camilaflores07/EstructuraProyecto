#include "PincelQueue.h"
#include <QPen>
#include <QBrush>
#include <QString>
#include <QGraphicsTextItem>
#include <QFont>

PincelQueue::PincelQueue(QGraphicsScene *scene) : scene(scene) {}

void PincelQueue::redraw(Queue* queue) {
    scene->clear();


    int nodeCount = 0;
    Node* temp = queue->getFront();
    while (temp != nullptr) {
        nodeCount++;
        temp = temp->next;
    }


    qreal totalWidth = nodeCount * 120 - 60 + 120;


    scene->setSceneRect(0, 0, totalWidth + 120, 200);


    qreal startX = 20;
    qreal y = 100;


    drawLabel("FRONT", startX, y - 40);
    if (nodeCount > 1) {
        drawLabel("REAR", startX + (nodeCount - 1) * 120, y - 40);
    }


    Node* current = queue->getFront();
    int index = 0;
    qreal x = startX;

    while (current != nullptr) {
        bool isFront = (index == 0);
        bool isRear = (index == nodeCount - 1);

        drawNode(current->data, x, y, isFront, isRear);

        if (current->next != nullptr) {

            drawArrow(x + 60, y + 30, x + 120, y + 30);
        }

        current = current->next;
        x += 120;
        index++;
    }


    drawNull(x, y + 24);
    drawLabel("NULL", x - 10, y + 45);
}

void PincelQueue::drawNode(int val, qreal x, qreal y, bool isFront, bool isRear) {
    const qreal diameter = 60;
    const qreal radius = diameter / 2;

    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(0, 0, 0));

    QBrush brush;
    brush.setColor(QColor(255, 255, 255));
    brush.setStyle(Qt::SolidPattern);


    scene->addEllipse(x, y, diameter, diameter, pen, brush);

    QGraphicsTextItem* text = scene->addText(QString::number(val));
    QFont font = text->font();
    font.setPointSize(14);
    font.setBold(true);
    text->setFont(font);


    QRectF textRect = text->boundingRect();
    qreal textX = x + radius - (textRect.width() / 2);
    qreal textY = y + radius - (textRect.height() / 2);

    text->setPos(textX, textY);
    text->setDefaultTextColor(QColor(0, 0, 0));
}

void PincelQueue::drawArrow(qreal x1, qreal y1, qreal x2, qreal y2) {
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(255, 255, 255));

    scene->addLine(x1, y1, x2, y2, pen);


    const qreal s = 8;
    scene->addLine(x2, y2, x2 - s, y2 - s, pen);
    scene->addLine(x2, y2, x2 - s, y2 + s, pen);
}

void PincelQueue::drawNull(qreal x, qreal y) {
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(255, 255, 255));


   // scene->addEllipse(x, y, 12, 12, pen);
   // scene->addLine(x + 2, y + 2, x + 10, y + 10, pen);
   // scene->addLine(x + 10, y + 2, x + 2, y + 10, pen);
}

void PincelQueue::drawLabel(const QString &text, qreal x, qreal y) {
    QGraphicsTextItem* label = scene->addText(text);
    QFont font = label->font();
    font.setPointSize(10);
    font.setBold(true);
    label->setFont(font);

    if (text == "FRONT" || text == "REAR") {
        label->setDefaultTextColor(QColor(255, 105, 180));
    } else {
        label->setDefaultTextColor(QColor(255, 255, 255));
    }

    label->setPos(x, y);
}
