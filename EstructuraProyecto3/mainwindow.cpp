#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LinkedList.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Configuración para LinkedList (código original)
    sceneLS = new QGraphicsScene(this);
    ui->graphicsViewLS->setScene(sceneLS);
    ui->graphicsViewLS->setRenderHint(QPainter::Antialiasing, true);
    pincel = new Pincel(sceneLS);

    // Configuración para Queue (nuevo)
    sceneQueue = new QGraphicsScene(this);
    ui->graphicsViewQueue->setScene(sceneQueue);
    ui->graphicsViewQueue->setRenderHint(QPainter::Antialiasing, true);
    queue = new Queue();
    pincelQueue = new PincelQueue(sceneQueue);

    // Conexiones para LinkedList (código original)
    connect(ui->btnInsertarLS_2, &QPushButton::clicked, this, &MainWindow::onInsertarLS);
    connect(ui->btnBorrarLS_2,   &QPushButton::clicked, this, &MainWindow::onBorrarLS);
    connect(ui->btnBuscarLS_2,   &QPushButton::clicked, this, &MainWindow::onBuscarLS);

    // Conexiones para Queue (nuevo) - usando nombres de la imagen
    connect(ui->btnInsertarQueue, &QPushButton::clicked, this, &MainWindow::onEnqueueClicked);
    connect(ui->btnBorrarrDequeue, &QPushButton::clicked, this, &MainWindow::onDequeueClicked);
    connect(ui->btnBuscarQ0ueue, &QPushButton::clicked, this, &MainWindow::onPeekClicked);

    // Actualizar vistas iniciales
    actualizarDibujo();
    actualizarDibujoQueue();
}

MainWindow::~MainWindow()
{
    delete queue;
    delete pincelQueue;
    delete ui;
}

// Métodos originales para LinkedList
void MainWindow::onInsertarLS()
{
    bool okPos=false, okNum=false;
    int pos = ui->editPosLS_2->text().toInt(&okPos);
    int val = ui->editNumLS_2->text().toInt(&okNum);
    if (!okPos || !okNum) {
        QMessageBox::warning(this, "Datos inválidos", "Escribe números válidos en Posición y Número.");
        return;
    }
    list.insert_value(pos, val);
    ui->editNumLS_2->clear();
    actualizarDibujo();
}

void MainWindow::onBorrarLS()
{
    bool ok=false;
    int pos = ui->editDelPosLS_2->text().toInt(&ok);
    if (!ok || pos < 0) {
        QMessageBox::warning(this, "Posición inválida", "Escribe una posición válida (0, 1, 2 …).");
        return;
    }
    list.remove_at(pos);
    ui->editDelPosLS_2->clear();
    actualizarDibujo();
}

void MainWindow::onBuscarLS()
{
    bool ok=false;
    int val = ui->editFindValLS_2->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Buscar", "Escribe un número válido.");
        return;
    }
    int pos = list.find(val);
    if (pos == -1)
        QMessageBox::information(this, "Buscar", "No encontrado.");
    else
        QMessageBox::information(this, "Buscar", QString("Encontrado en posición %1").arg(pos));
}

void MainWindow::actualizarDibujo()
{
    QList<int> valores = list.toList();
    pincel->redraw(valores);
}

// Métodos nuevos para Queue
void MainWindow::onEnqueueClicked()
{
    QString text = ui->editNumQueue->text();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese un número para agregar a la cola");
        return;
    }

    bool ok;
    int value = text.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Error", "Ingrese un número válido");
        return;
    }

    // Agregar a la cola
    queue->enqueue(value);

    // Limpiar el campo de entrada
    ui->editNumQueue->clear();

    // Actualizar la vista
    actualizarDibujoQueue();
}

void MainWindow::onDequeueClicked()
{
    if (queue->isEmpty()) {
        QMessageBox::information(this, "Información", "La cola está vacía");
        return;
    }

    // Remover elemento
    int removedValue = queue->dequeue();

    // Actualizar la vista
    actualizarDibujoQueue();

    // Mostrar mensaje
    QMessageBox::information(this, "Dequeue", QString("Elemento removido: %1").arg(removedValue));
}

void MainWindow::onPeekClicked()
{
    if (queue->isEmpty()) {
        QMessageBox::information(this, "Información", "La cola está vacía");
        return;
    }

    // Ver el primer elemento sin removerlo
    int frontValue = queue->peek();

    // Mostrar el elemento del frente
    QMessageBox::information(this, "Peek", QString("Primer elemento: %1").arg(frontValue));
}

void MainWindow::actualizarDibujoQueue()
{
    // Redibujar la cola directamente desde la estructura de nodos
    pincelQueue->redraw(queue);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
}
