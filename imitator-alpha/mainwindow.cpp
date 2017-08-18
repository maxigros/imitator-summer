#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Конфигурация
    configWriterMode = ui->comboBox_write_mode->currentText();

    // Соединение
    ui->pushButton_connection_start->setEnabled(true);
    ui->pushButton_connection_stop->setEnabled(false);
    ui->label_status_connection->setText(QString::fromUtf8("Статус: НЕТ"));

    // Генерация
    ui->pushButton_generation_start->setEnabled(true);
    ui->pushButton_generation_stop->setEnabled(false);
    ui->label_status_generation->setText(QString::fromUtf8("Статус: НЕТ"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_connection_start_clicked()
{
    /**************************************************************************
     * GUI
     *************************************************************************/
    ui->pushButton_connection_start->setEnabled(false);
    ui->pushButton_connection_stop->setEnabled(true);
    ui->label_status_connection->setText(QString::fromUtf8("Статус: ДА"));
    connection_on_off = true;

    /**************************************************************************
     * Функционал
     *************************************************************************/
    moduleWriter = new BoxWriter(configWriterMode);
    threadNetwork = new QThread;
    moduleWriter->moveToThread(threadNetwork);
    connect(threadNetwork, SIGNAL(started()), moduleWriter, SLOT(process()));
    connect(moduleWriter, SIGNAL(finish()), threadNetwork, SLOT(quit()));
    connect(threadNetwork, SIGNAL(finished()), moduleWriter, SLOT(deleteLater()));
    connect(threadNetwork, SIGNAL(finished()), threadNetwork, SLOT(deleteLater()));
    threadNetwork->start();
}

void MainWindow::on_pushButton_connection_stop_clicked()
{
    /**************************************************************************
     * GUI
     *************************************************************************/
    ui->pushButton_connection_start->setEnabled(true);
    ui->pushButton_connection_stop->setEnabled(false);
    ui->label_status_connection->setText(QString::fromUtf8("Статус: НЕТ"));
    connection_on_off = false;
    if (generation_on_off == true){
        emit ui->pushButton_generation_stop->clicked();
        ui->statusBar->showMessage(QString::fromUtf8("Отключено!"), 2000);
    }

    /**************************************************************************
     * Функционал
     *************************************************************************/
    moduleWriter->stop_box();
}

void MainWindow::on_pushButton_generation_start_clicked()
{
    /**************************************************************************
     * GUI
     *************************************************************************/
    if (connection_on_off == false){
        ui->statusBar->showMessage(QString::fromUtf8("Нет соединения!"), 2000);
        return;
    }
    ui->pushButton_generation_start->setEnabled(false);
    ui->pushButton_generation_stop->setEnabled(true);
    ui->label_status_generation->setText(QString::fromUtf8("Статус: ДА"));
    generation_on_off = true;

    /**************************************************************************
     * Функционал
     *************************************************************************/
    moduleGenerate = new BoxGenerate(ui->lineEdit_config_file->text());
    threadGenerate = new QThread;
    moduleGenerate->moveToThread(threadGenerate);
    connect(threadGenerate, SIGNAL(started()),
            moduleGenerate, SLOT(process()));
    connect(moduleGenerate, SIGNAL(finish()),
            threadGenerate, SLOT(quit()));
    connect(threadGenerate, SIGNAL(finished()),
            moduleGenerate, SLOT(deleteLater()));
    connect(threadGenerate, SIGNAL(finished()),
            threadGenerate, SLOT(deleteLater()));
    // Обмен данными между BoxNetwork и BoxGenerate
    // Коннектим здесь, т.к. moduleGenerate точно создается после moduleWriter
    connect(moduleGenerate, SIGNAL(sendConfigParams(Storage*)),
            moduleWriter,   SLOT(getConfigParams(Storage*)),
            Qt::DirectConnection);
    connect(moduleGenerate, SIGNAL(sendData(int,double,complex<double>*)),
            moduleWriter,   SLOT(getData(int,double,complex<double>*)),
            Qt::DirectConnection);
    connect(moduleWriter,   SIGNAL(sendInfo(int)),
            moduleGenerate, SLOT(getInfo(int)),
            Qt::DirectConnection);

    threadGenerate->start();
}

void MainWindow::on_pushButton_generation_stop_clicked()
{
    /**************************************************************************
     * GUI
     *************************************************************************/
    ui->pushButton_generation_start->setEnabled(true);
    ui->pushButton_generation_stop->setEnabled(false);
    ui->label_status_generation->setText(QString::fromUtf8("Статус: НЕТ"));
    generation_on_off = false;

    /**************************************************************************
     * Функционал
     *************************************************************************/
    moduleGenerate->stop();
}


void MainWindow::on_pushButton_config_file_clicked()
{
    QFileDialog dial;
    configFilename = dial.getOpenFileName(0, "Файл конфигурации", QDir::currentPath());
    ui->lineEdit_config_file->setText(configFilename);
}

void MainWindow::on_comboBox_write_mode_currentTextChanged(const QString &arg1)
{
    configWriterMode = arg1;
}
