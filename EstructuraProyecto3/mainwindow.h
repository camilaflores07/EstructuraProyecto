#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>  // ← INCLUDE COMPLETO, no forward declaration
#include <QGraphicsView>

// SOLO declaración adelantada aquí
class QGraphicsView;
class QGraphicsScene;

#include "LinkedList.h"
#include "Pincel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onInsertarLS();
    void onBorrarLS();
    void onBuscarLS();

private:
    Ui::MainWindow *ui;

    LinkedList list;
    QGraphicsScene *sceneLS = nullptr;
    Pincel *pincel = nullptr;

    void actualizarDibujo();
};

#endif // MAINWINDOW_H
