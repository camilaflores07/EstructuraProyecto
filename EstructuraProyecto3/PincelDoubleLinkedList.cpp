#include "PincelDoubleLinkedList.h"
#include <QPen>
#include <QString>
#include <QGraphicsTextItem>

PincelDoubleLinkedList::PincelDoubleLinkedList(QGraphicsScene *scene) : scene(scene) {}

void PincelDoubleLinkedList::redraw(const QList<int> &valores)
{
    scene->clear();
    qreal x = 60, y = 80;

    for (int i = 0; i < valores.size(); ++i) {
        drawNode(valores[i], x, y);


        if (i == 0) {
            drawHeadLabel(x, y - 30);
        }


        if (i == valores.size() - 1) {
            drawTailLabel(x, y + 90);
        }

        if (i < valores.size() - 1) {

            drawDoubleArrow(x + 60, y + 20, x + 120, y + 20);
        }
        x += 120;
    }

    drawNull(x, y + 14);
}

void PincelDoubleLinkedList::drawNode(int val, qreal x, qreal y)
{
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

void PincelDoubleLinkedList::drawDoubleArrow(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(255, 255, 255));

    qreal rightY = y1 - 5;
    scene->addLine(x1, rightY, x2, rightY, pen);

    const qreal s = 8;
    scene->addLine(x2, rightY, x2 - s, rightY - s, pen);
    scene->addLine(x2, rightY, x2 - s, rightY + s, pen);


    qreal leftY = y1 + 5;
    scene->addLine(x2, leftY, x1, leftY, pen);

    scene->addLine(x1, leftY, x1 + s, leftY - s, pen);
    scene->addLine(x1, leftY, x1 + s, leftY + s, pen);
}

void PincelDoubleLinkedList::drawNull(qreal x, qreal y)
{
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(255, 255, 255));

    QGraphicsTextItem* nullText = scene->addText("NULL");
    QFont font = nullText->font();
    font.setPointSize(10);
    nullText->setFont(font);
    nullText->setPos(x, y);
    nullText->setDefaultTextColor(QColor(255, 255, 255));
}

void PincelDoubleLinkedList::drawHeadLabel(qreal x, qreal y)
{
    QGraphicsTextItem* headText = scene->addText("HEAD");
    QFont font = headText->font();
    font.setPointSize(12);
    font.setBold(true);
    headText->setFont(font);
    headText->setDefaultTextColor(QColor(255, 105, 180));

    QRectF textRect = headText->boundingRect();
    qreal textX = x + 30 - (textRect.width() / 2);
    headText->setPos(textX, y);
}

void PincelDoubleLinkedList::drawTailLabel(qreal x, qreal y)
{
    QGraphicsTextItem* tailText = scene->addText("TAIL");
    QFont font = tailText->font();
    font.setPointSize(12);
    font.setBold(true);
    tailText->setFont(font);
    tailText->setDefaultTextColor(QColor(255, 105, 180));

    QRectF textRect = tailText->boundingRect();
    qreal textX = x + 30 - (textRect.width() / 2);
    tailText->setPos(textX, y);
}
