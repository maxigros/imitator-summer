#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QThread>

#include "loopclass.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int counter_left;
    int counter_right;

    LoopClass *left;
    LoopClass *right;
    QThread *thread_left;
    QThread *thread_right;

private slots:
    void update_left();
    void update_right();
};

#endif // MAINWINDOW_H
