#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QDebug>

#include <QThread>
#include "randomthread.h"


#define STOP 0
#define RUN 1
#define PAUSE 2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setState(int state);

protected:
    void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void newArrayData(QVector<QPoint> *array);

private:
    Ui::MainWindow *ui;
    QCustomPlot *wGraphic;
    int State;
    QThread *thread_1;
    RandomThread *rnd_1;
};

#endif // MAINWINDOW_H
