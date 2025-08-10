#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Conectar botón Insertar (Lista Simple)
    connect(ui->btnInsertarLS, &QPushButton::clicked,
            this, &MainWindow::onInsertarLS);
    connect(ui->btnBorrarLS, &QPushButton::clicked,
            this, &MainWindow::onBorrarLS);
    connect(ui->btnBuscarLS, &QPushButton::clicked,
            this, &MainWindow::onBuscarLS);



    // DEMO: poblar lista para probar (puedes comentar estas líneas si quieres)
    list.push_front(0, 10);
    list.push_front(0, 20);
    list.push_front(0, 30);
    list.push_back(0, 40);
    list.push_back(0, 50);
    list.print();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onInsertarLS() {
    // 1) Leer valores de la UI con validación
    bool okPos = false, okNum = false;
    int pos = ui->editFindValLS->text().toInt(&okPos);
    int val = ui->editNumLS->text().toInt(&okNum);

    if (!okPos || !okNum) {
        QMessageBox::warning(this, "Datos inválidos", "Escribe números válidos en Posición y Número.");
        return;
    }

    // 2) Insertar en la lista
    list.insert_value(pos, val);

    // 3) Ver en consola (confirmación)
    qDebug() << "Inserté pos:" << pos << "valor:" << val;
    list.print();

    // 4) Limpiar campo de valor (opcional)
    ui->editNumLS->clear();
}
void MainWindow::onBorrarLS() {
    bool ok = false;
    int pos = ui->editDelPosLS->text().toInt(&ok);
    if (!ok || pos < 0) {
        QMessageBox::warning(this, "Posición inválida", "Escribe una posición válida (0, 1, 2…).");
        return;
    }

    // eliminar por posición
    list.remove_at(pos);
    list.print();
    ui->editDelPosLS->clear();
}

void MainWindow::onBuscarLS() {
    bool ok = false;
    int val = ui->editFindValLS->text().toInt(&ok);

    if (!ok) {
        QMessageBox::warning(this, "Buscar", "Escribe un número válido.");
        return;
    }

    int pos = list.find(val);

    if (pos == -1) {
        QMessageBox::information(this, "Buscar",
                                 QString("El valor %1 no está en la lista.").arg(val));
    } else {
        QMessageBox::information(this, "Buscar",
                                 QString("Encontrado: valor %1 en posición %2.")
                                     .arg(val).arg(pos));
    }
}

