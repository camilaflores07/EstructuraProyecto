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

    //SimpleList
    sceneLS = new QGraphicsScene(this);
    ui->graphicsViewLS->setScene(sceneLS);
    ui->graphicsViewLS->setRenderHint(QPainter::Antialiasing, true);
    pincel = new Pincel(sceneLS);

    //Queue
    sceneQueue = new QGraphicsScene(this);
    ui->graphicsViewQueue->setScene(sceneQueue);
    ui->graphicsViewQueue->setRenderHint(QPainter::Antialiasing, true);
    queue = new Queue();
    pincelQueue = new PincelQueue(sceneQueue);

    //Stack
    sceneStack = new QGraphicsScene(this);
    ui->graphicsViewStack->setScene(sceneStack);
    ui->graphicsViewStack->setRenderHint(QPainter::Antialiasing, true);
    stack = new Stack();
    pincelStack = new PincelStack(sceneStack);

    //connect SimpleList
    connect(ui->btnInsertarLS_2, &QPushButton::clicked, this, &MainWindow::onInsertarLS);
    connect(ui->btnBorrarLS_2,   &QPushButton::clicked, this, &MainWindow::onBorrarLS);
    connect(ui->btnBuscarLS_2,   &QPushButton::clicked, this, &MainWindow::onBuscarLS);

    //connect Queue
    connect(ui->btnInsertarQueue, &QPushButton::clicked, this, &MainWindow::onEnqueueClicked);
    connect(ui->btnBorrarrDequeue, &QPushButton::clicked, this, &MainWindow::onDequeueClicked);
    connect(ui->btnBuscarQ0ueue, &QPushButton::clicked, this, &MainWindow::onPeekClicked);

    //connect Stack
    connect(ui->btnInsertarStack, &QPushButton::clicked, this, &MainWindow::onPushClicked);
    connect(ui->btnPop, &QPushButton::clicked, this, &MainWindow::onPopClicked);
    connect(ui->btnPeekStack, &QPushButton::clicked, this, &MainWindow::onPeekStackClicked);

    actualizarDibujo();
    actualizarDibujoQueue();
    actualizarDibujoStack();
}

MainWindow::~MainWindow()
{
    delete queue;
    delete pincelQueue;
    delete stack;
    delete pincelStack;
    delete ui;
}

//==========================SimpleList============================================
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

//==========================Queue=================================================
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

    queue->enqueue(value);
    ui->editNumQueue->clear();
    actualizarDibujoQueue();
}

void MainWindow::onDequeueClicked()
{
    if (queue->isEmpty()) {
        QMessageBox::information(this, "Información", "La cola está vacía");
        return;
    }

    int removedValue = queue->dequeue();
    actualizarDibujoQueue();
    QMessageBox::information(this, "Dequeue", QString("Elemento removido: %1").arg(removedValue));
}

void MainWindow::onPeekClicked()
{
    if (queue->isEmpty()) {
        QMessageBox::information(this, "Información", "La cola está vacía");
        return;
    }

    int frontValue = queue->peek();

    QMessageBox::information(this, "Peek", QString("Primer elemento: %1").arg(frontValue));
}

void MainWindow::actualizarDibujoQueue()
{
    pincelQueue->redraw(queue);
}

//==========================Stack==============================================

void MainWindow::onPushClicked()
{
    QString text = ui->editNumStack->text();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese un número para agregar al stack");
        return;
    }

    bool ok;
    int value = text.toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Error", "Ingrese un número válido");
        return;
    }

    stack->push(value);
    ui->editNumStack->clear();
    actualizarDibujoStack();
}

void MainWindow::onPopClicked()
{
    if (stack->isEmpty()) {
        QMessageBox::information(this, "Información", "El stack está vacío");
        return;
    }

    // Remover elemento del top
    int removedValue = stack->pop();

    // Actualizar la vista
    actualizarDibujoStack();

    // Mostrar mensaje
    QMessageBox::information(this, "Pop", QString("Elemento removido del top: %1").arg(removedValue));
}

void MainWindow::onPeekStackClicked()
{
    if (stack->isEmpty()) {
        QMessageBox::information(this, "Información", "El stack está vacío");
        return;
    }

    // Ver el elemento del top sin removerlo
    int topValue = stack->peek();

    // Mostrar el elemento del top
    QMessageBox::information(this, "Peek", QString("Elemento en el top: %1").arg(topValue));
}

void MainWindow::actualizarDibujoStack()
{
    // Redibujar el stack
    pincelStack->redraw(stack);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
}
