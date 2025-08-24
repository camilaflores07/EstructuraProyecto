#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>


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

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;

    LinkedList list;
    QGraphicsScene *sceneLS = nullptr;
    Pincel *pincel = nullptr;

    void actualizarDibujo();
};

#endif // MAINWINDOW_H
