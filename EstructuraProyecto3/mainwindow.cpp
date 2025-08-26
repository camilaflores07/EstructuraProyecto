#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>

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

    //DLL
    sceneDLL = new QGraphicsScene(this);
    ui->graphicsViewDLL->setScene(sceneDLL);
    pincelDLL = new PincelDoubleLinkedList(sceneDLL);

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
    connect(ui->SaveLS , &QPushButton::clicked, this, &MainWindow::onSaveLS);

    //connect DLL
    connect(ui->btnInsertarDLL, &QPushButton::clicked, this, &MainWindow::onInsertarDLL);
    connect(ui->btnBorrarDLL, &QPushButton::clicked, this, &MainWindow::onBorrarDLL);
    connect(ui->btnBuscarDLL, &QPushButton::clicked, this, &MainWindow::onBuscarDLL);

    //connect Queue
    connect(ui->btnInsertarQueue, &QPushButton::clicked, this, &MainWindow::onEnqueueClicked);
    connect(ui->btnBorrarrDequeue, &QPushButton::clicked, this, &MainWindow::onDequeueClicked);
    connect(ui->btnBuscarQ0ueue, &QPushButton::clicked, this, &MainWindow::onPeekClicked);
    connect(ui->SaveQueue , &QPushButton::clicked, this, &MainWindow::onSaveQueue);

    //connect Stack
    connect(ui->btnInsertarStack, &QPushButton::clicked, this, &MainWindow::onPushClicked);
    connect(ui->btnPop, &QPushButton::clicked, this, &MainWindow::onPopClicked);
    connect(ui->btnPeekStack, &QPushButton::clicked, this, &MainWindow::onPeekStackClicked);

    cargarListaLS();
    cargarListaQueue();

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
    delete pincelDLL;
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

void MainWindow::onSaveLS()
{
    QFile file("lista_guardada.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        QList<int> valores = list.toList();
        for (int valor : valores) {
            out << valor << "\n";
        }
        file.close();
        QMessageBox::information(this, "Guardar", "Lista guardada exitosamente!");
    } else {
        QMessageBox::warning(this, "Error", "No se pudo guardar el archivo.");
    }
}

void MainWindow::cargarListaLS()
{
    QFile file("lista_guardada.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        list.clear();

        while (!in.atEnd()) {
            QString line = in.readLine();
            bool ok;
            int value = line.toInt(&ok);
            if (ok) {
                list.push_back(0, value);
            }
        }
        file.close();
    }
}

void MainWindow::actualizarDibujo()
{
    QList<int> valores = list.toList();
    pincel->redraw(valores);
}

//========================DLL====================================================
void MainWindow::onInsertarDLL()
{
    bool okPos=false, okNum=false;
    int pos = ui->editPosDLL->text().toInt(&okPos);
    int val = ui->editNumDLL->text().toInt(&okNum);
    if (!okPos || !okNum) {
        QMessageBox::warning(this, "Datos inválidos", "Escribe números válidos en Posición y Número.");
        return;
    }
    doubleList.insert_value(pos, val);
    ui->editNumDLL->clear();
    actualizarDibujoDLL();
}

void MainWindow::onBorrarDLL()
{
    bool ok=false;
    int pos = ui->editDelPosDLL->text().toInt(&ok);
    if (!ok || pos < 0) {
        QMessageBox::warning(this, "Posición inválida", "Escribe una posición válida (0, 1, 2 …).");
        return;
    }
    doubleList.remove_at(pos);
    ui->editDelPosDLL->clear();
    actualizarDibujoDLL();
}

void MainWindow::onBuscarDLL()
{
    bool ok=false;
    int val = ui->editFindValDLL->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Buscar", "Escribe un número válido.");
        return;
    }
    int pos = doubleList.find(val);
    if (pos == -1)
        QMessageBox::information(this, "Buscar", "No encontrado.");
    else
        QMessageBox::information(this, "Buscar", QString("Encontrado en posición %1").arg(pos));
}

void MainWindow::actualizarDibujoDLL()
{
    QList<int> valores = doubleList.toList();
    pincelDLL->redraw(valores);
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

// Método para guardar la Queue
void MainWindow::onSaveQueue() {
    QFile file("queue_data.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo crear el archivo.");
        return;
    }

    QTextStream out(&file);
    Node* current = queue->getFront();

    while (current != nullptr) {
        out << current->data << "\n";
        current = current->next;
    }

    file.close();
    QMessageBox::information(this, "Guardar", "Lista guardada exitosamente");
}

// Método para cargar datos automáticamente al iniciar
void MainWindow::cargarListaQueue() {
    QFile file("queue_data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Si no existe el archivo, no hace nada (primera vez)
        return;
    }

    // Limpiar la queue actual
    queue->clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            bool ok;
            int value = line.toInt(&ok);
            if (ok) {
                queue->enqueue(value);
            }
        }
    }

    file.close();

    // Actualizar el dibujo
    actualizarDibujoQueue();
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
    int removedValue = stack->pop();
    actualizarDibujoStack();
    QMessageBox::information(this, "Pop", QString("Elemento removido del top: %1").arg(removedValue));
}

void MainWindow::onPeekStackClicked()
{
    if (stack->isEmpty()) {
        QMessageBox::information(this, "Información", "El stack está vacío");
        return;
    }

    int topValue = stack->peek();
    QMessageBox::information(this, "Peek", QString("Elemento en el top: %1").arg(topValue));
}

void MainWindow::actualizarDibujoStack()
{
    pincelStack->redraw(stack);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
}
