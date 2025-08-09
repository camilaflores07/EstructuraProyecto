#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Insertamos valores
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    list.push_back(40);
    list.push_back(50);

    cout << "Contenido de la lista:" << endl;
    list.print();
}

MainWindow::~MainWindow()
{
    delete ui;
}
