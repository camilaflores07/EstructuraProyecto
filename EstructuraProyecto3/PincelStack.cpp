#include "PincelStack.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
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
            drawArrow(x + 40, y + 40, x + 40, y + 60);
        } else {

            drawNull(x + 40, y + 50);
        }

        current = current->next;
        y += 60;
        isFirst = false;
    }
}


void PincelStack::drawNode(int val, qreal x, qreal y, bool isTop) {

    QPen pen(Qt::white, 2);
    QBrush brush(Qt::white, Qt::SolidPattern);

    //hacer circulito
    QGraphicsRectItem* rect = scene->addRect(x, y, 80, 40, pen, brush);


    QGraphicsTextItem* texto = scene->addText(QString::number(val), QFont("Arial", 12, QFont::Bold));
    texto->setDefaultTextColor(Qt::black);

    QRectF textBounds = texto->boundingRect();
    texto->setPos(x + (80 - textBounds.width()) / 2,
                  y + (40 - textBounds.height()) / 2);
}

void PincelStack::drawArrow(qreal x1, qreal y1, qreal x2, qreal y2) {

    QPen pen(Qt::white, 2);
    scene->addLine(x1, y1, x2, y2, pen);

    qreal arrowSize = 8;
    QPolygonF arrowHead;
    arrowHead << QPointF(x2, y2)
              << QPointF(x2 - arrowSize/2, y2 - arrowSize)
              << QPointF(x2 + arrowSize/2, y2 - arrowSize);

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
