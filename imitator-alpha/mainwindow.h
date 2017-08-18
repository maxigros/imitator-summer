#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imitator/imitator_headers.h"
#include "common/writers/boxwriter.h"
#include "imitator/boxgenerate.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_connection_start_clicked();
    void on_pushButton_connection_stop_clicked();
    void on_pushButton_generation_start_clicked();
    void on_pushButton_generation_stop_clicked();

    void on_pushButton_config_file_clicked();

    void on_comboBox_write_mode_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    /**************************************************************************
     *  Конфигурация
     *************************************************************************/
    QString configFilename;
    QString configWriterMode;

    /**************************************************************************
     *  Соединение
     *************************************************************************/
    BoxWriter *moduleWriter;
    QThread *threadNetwork;
    bool connection_on_off = false;

    /**************************************************************************
     *  Генерация
     *************************************************************************/
    BoxGenerate *moduleGenerate;
    QThread *threadGenerate;
    bool generation_on_off = false;

};

#endif // MAINWINDOW_H
