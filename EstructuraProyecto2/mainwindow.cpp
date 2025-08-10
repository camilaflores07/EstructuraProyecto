#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMainWindow>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Insertamos valores
    list.push_front(0, 10); // siempre pone el nuevo valor al inicio de la lista.
    list.push_front(0, 20);
    list.push_front(0, 30);
    list.push_back(0, 40); // siempre pone el nuevo valor al final de la lista.
    list.push_back(0, 50);
    list.print();

}

MainWindow::~MainWindow()
{
    delete ui;
}
