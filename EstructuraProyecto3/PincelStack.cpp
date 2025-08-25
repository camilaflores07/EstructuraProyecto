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

    // Dibujar etiqueta TOP
    drawLabel("TOP", 150, 50);

    // Recorrer el stack y dibujar cada nodo
    Node* current = stack->getTop();
    qreal y = 80;  // Posición inicial Y
    qreal x = 100; // Posición X fija
    bool isFirst = true;

    while (current != nullptr) {
        // Dibujar el nodo
        drawNode(current->data, x, y, isFirst);

        // Dibujar flecha al siguiente nodo (si existe)
        if (current->next != nullptr) {
            drawArrow(x + 40, y + 40, x + 40, y + 60);
        } else {
            // Dibujar NULL al final
            drawNull(x + 40, y + 50);
        }

        current = current->next;
        y += 60; // Espacio entre nodos
        isFirst = false;
    }
}

void PincelStack::drawNode(int val, qreal x, qreal y, bool isTop) {
    // Configurar colores - TODOS los nodos blancos
    QPen pen(Qt::white, 2);  // Borde blanco
    QBrush brush(Qt::white, Qt::SolidPattern);  // Fondo blanco

    // Dibujar rectángulo
    QGraphicsRectItem* rect = scene->addRect(x, y, 80, 40, pen, brush);

    // Dibujar texto con el valor
    QGraphicsTextItem* texto = scene->addText(QString::number(val), QFont("Arial", 12, QFont::Bold));
    texto->setDefaultTextColor(Qt::black);  // Texto negro para que se vea en fondo blanco

    // Centrar el texto
    QRectF textBounds = texto->boundingRect();
    texto->setPos(x + (80 - textBounds.width()) / 2,
                  y + (40 - textBounds.height()) / 2);
}

void PincelStack::drawArrow(qreal x1, qreal y1, qreal x2, qreal y2) {
    // Línea principal - BLANCA
    QPen pen(Qt::white, 2);
    scene->addLine(x1, y1, x2, y2, pen);

    // Punta de flecha - BLANCA
    qreal arrowSize = 8;
    QPolygonF arrowHead;
    arrowHead << QPointF(x2, y2)
              << QPointF(x2 - arrowSize/2, y2 - arrowSize)
              << QPointF(x2 + arrowSize/2, y2 - arrowSize);

    scene->addPolygon(arrowHead, QPen(Qt::white), QBrush(Qt::white));
}

void PincelStack::drawNull(qreal x, qreal y) {
    // Dibujar "NULL" al final del stack
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

    // Rosa para TOP, blanco para NULL
    if (text == "TOP") {
        label->setDefaultTextColor(QColor(255, 105, 180)); // Rosa/pink
    } else {
        label->setDefaultTextColor(QColor(255, 255, 255)); // Blanco para NULL y otros
    }
    label->setPos(x, y);
}
