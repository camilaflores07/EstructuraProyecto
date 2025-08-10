#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPainter>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sceneLS = new QGraphicsScene(this);
    ui->graphicsViewLS->setScene(sceneLS);
    ui->graphicsViewLS->setRenderHint(QPainter::Antialiasing, true);

    pincel = new Pincel(sceneLS);

    connect(ui->btnInsertarLS_2, &QPushButton::clicked, this, &MainWindow::onInsertarLS);
    connect(ui->btnBorrarLS_2,   &QPushButton::clicked, this, &MainWindow::onBorrarLS);
    connect(ui->btnBuscarLS_2,   &QPushButton::clicked, this, &MainWindow::onBuscarLS);

    actualizarDibujo();
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
