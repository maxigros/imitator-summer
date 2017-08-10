#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter_left = 0;
    counter_right = 0;
    ui->label_left->setText(QString::number(0));
    ui->label_right->setText(QString::number(0));

    left = new LoopClass();
    thread_left = new QThread();
    left->moveToThread(thread_left);
    connect(thread_left, SIGNAL(started()), left, SLOT(process()));
    connect(left, SIGNAL(gogo()), this, SLOT(update_left()));
    thread_left->start();

    right = new LoopClass();
    thread_right = new QThread();
    right->moveToThread(thread_right);
    connect(thread_right, SIGNAL(started()), right, SLOT(process()));
    connect(right, SIGNAL(gogo()), this, SLOT(update_right()));
    thread_right->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_left()
{
    counter_left++;
    ui->label_left->setText(QString::number(counter_left));
}

void MainWindow::update_right()
{
    counter_right++;
    ui->label_right->setText(QString::number(counter_right));
}

