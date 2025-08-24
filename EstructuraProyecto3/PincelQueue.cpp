#include "PincelQueue.h"
#include <QPen>
#include <QBrush>
#include <QString>
#include <QGraphicsTextItem>
#include <QFont>

PincelQueue::PincelQueue(QGraphicsScene *scene) : scene(scene) {}

void PincelQueue::redraw(Queue* queue) {
    scene->clear();

    if (queue->isEmpty()) {
        scene->addText("Queue vacía")->setPos(10, 10);
        return;
    }

    // Contar nodos para determinar posiciones
    int nodeCount = 0;
    Node* temp = queue->getFront();
    while (temp != nullptr) {
        nodeCount++;
        temp = temp->next;
    }

    qreal x = 60, y = 100;

    // Dibujar etiquetas FRONT y REAR
    drawLabel("FRONT", x, y - 40);
    if (nodeCount > 1) {
        drawLabel("REAR", x + (nodeCount - 1) * 120, y - 40);
    }

    // Dibujar nodos
    Node* current = queue->getFront();
    int index = 0;

    while (current != nullptr) {
        bool isFront = (index == 0);
        bool isRear = (index == nodeCount - 1);

        drawNode(current->data, x, y, isFront, isRear);

        if (current->next != nullptr) {
            drawArrow(x + 60, y + 20, x + 120, y + 20);
        }

        current = current->next;
        x += 120;
        index++;
    }

    // Dibujar NULL al final
    drawNull(x, y + 14);
    drawLabel("NULL", x - 10, y + 35);
}

void PincelQueue::drawNode(int val, qreal x, qreal y, bool isFront, bool isRear) {
    const qreal w = 60, h = 40;
    QPen pen;
    pen.setWidthF(2.0);

    // Colores diferentes para front y rear
    QBrush brush;
    if (isFront && isRear) {
        brush.setColor(QColor(255, 255, 0, 100)); // Amarillo si es el único elemento
    } else if (isFront) {
        brush.setColor(QColor(0, 255, 0, 100)); // Verde para front
    } else if (isRear) {
        brush.setColor(QColor(255, 0, 0, 100)); // Rojo para rear
    } else {
        brush.setColor(QColor(200, 200, 200, 100)); // Gris para elementos intermedios
    }
    brush.setStyle(Qt::SolidPattern);

    scene->addRect(x, y, w, h, pen, brush);

    // Texto del valor
    QGraphicsTextItem* text = scene->addText(QString::number(val));
    QFont font = text->font();
    font.setPointSize(12);
    font.setBold(true);
    text->setFont(font);
    text->setPos(x + 18, y + 8);
}

void PincelQueue::drawArrow(qreal x1, qreal y1, qreal x2, qreal y2) {
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(0, 0, 255)); // Azul para las flechas

    scene->addLine(x1, y1, x2, y2, pen);

    // Punta de la flecha
    const qreal s = 8;
    scene->addLine(x2, y2, x2 - s, y2 - s, pen);
    scene->addLine(x2, y2, x2 - s, y2 + s, pen);
}

void PincelQueue::drawNull(qreal x, qreal y) {
    QPen pen;
    pen.setWidthF(2.0);
    pen.setColor(QColor(255, 0, 0)); // Rojo para NULL

    // Círculo con una X adentro
    scene->addEllipse(x, y, 12, 12, pen);
    scene->addLine(x + 2, y + 2, x + 10, y + 10, pen);
    scene->addLine(x + 10, y + 2, x + 2, y + 10, pen);
}

void PincelQueue::drawLabel(const QString &text, qreal x, qreal y) {
    QGraphicsTextItem* label = scene->addText(text);
    QFont font = label->font();
    font.setPointSize(10);
    font.setBold(true);
    label->setFont(font);
    label->setDefaultTextColor(QColor(0, 0, 255));
    label->setPos(x, y);
}
