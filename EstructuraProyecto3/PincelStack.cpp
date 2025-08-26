#include "PincelStack.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include <QFont>

PincelStack::PincelStack(QGraphicsScene *scene) : scene(scene) {
}

void PincelStack::redraw(Stack* stack) {
    if (!scene || !stack) return;

    scene->clear();
    drawLabel("TOP", 150, 50);

    Node* current = stack->getTop();
    qreal y = 80;
    qreal x = 100;
    bool isFirst = true;

    while (current != nullptr) {
        drawNode(current->data, x, y, isFirst);

        if (current->next != nullptr) {
            drawArrow(x + 30, y + 60, x + 30, y + 80);
        } else {
            drawNull(x + 30, y + 70);
        }

        current = current->next;
        y += 80;
        isFirst = false;
    }
}

void PincelStack::drawNode(int val, qreal x, qreal y, bool isTop) {
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

void PincelStack::drawArrow(qreal x1, qreal y1, qreal x2, qreal y2) {
    QPen pen(Qt::white, 2);
    scene->addLine(x1, y1, x2, y2, pen);
    qreal arrowSize = 8;
    QPolygonF arrowHead;
    arrowHead << QPointF(x2, y2)  << QPointF(x2 - arrowSize/2, y2 - arrowSize) << QPointF(x2 + arrowSize/2, y2 - arrowSize);
    scene->addPolygon(arrowHead, QPen(Qt::white), QBrush(Qt::white));
}

void PincelStack::drawNull(qreal x, qreal y) {
    QGraphicsTextItem* nullText = scene->addText("NULL", QFont("Arial", 10, QFont::Bold));
    nullText->setPos(x - 15, y);
    nullText->setDefaultTextColor(Qt::white);
}

void PincelStack::drawLabel(const QString &text, qreal x, qreal y) {
    QGraphicsTextItem* label = scene->addText(text);
    QFont font = label->font();
    font.setPointSize(10);
    font.setBold(true);
    label->setFont(font);
    if (text == "TOP") {
        label->setDefaultTextColor(QColor(255, 105, 180));
    } else {
        label->setDefaultTextColor(QColor(255, 255, 255));
    }
    label->setPos(x, y);
}
