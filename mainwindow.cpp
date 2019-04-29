#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    rnd_1 = nullptr;


    this->setMinimumSize(400,400);
    this->setMaximumSize(1920,1080);

    setState(STOP);

    ui->widget->addGraph();
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    ui->widget->xAxis->setRange(0, 100);
    ui->widget->yAxis->setRange(0, 100);

    ui->widget->graph()->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->widget->replot();

    ui->pushButton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_2->setIcon(this->style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_3->setIcon(this->style()->standardIcon(QStyle::SP_MediaStop));




}

MainWindow::~MainWindow()
{
    if(thread_1->isRunning())
        thread_1->terminate();
    delete ui;
}

void MainWindow::setState(int state)
{
    State = state;
    switch (state)
    {
    case STOP:
        ui->pushButton->setDisabled(false);
        ui->pushButton_2->setDisabled(true);
        ui->pushButton_3->setDisabled(true);

        ui->pushButton->setDefault(true);
        ui->pushButton_2->setDefault(false);
        ui->pushButton_3->setDefault(false);
        break;
    case RUN:
        ui->pushButton->setDisabled(true);
        ui->pushButton_2->setDisabled(false);
        ui->pushButton_3->setDisabled(false);

        ui->pushButton->setDefault(false);
        ui->pushButton_2->setDefault(false);
        ui->pushButton_3->setDefault(false);
        break;
    case PAUSE:
        ui->pushButton->setDisabled(false);
        ui->pushButton_2->setDisabled(true);
        ui->pushButton_3->setDisabled(false);

        ui->pushButton->setDefault(false);
        ui->pushButton_2->setDefault(false);
        ui->pushButton_3->setDefault(false);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    //Push start
    if(rnd_1==nullptr)
    {
        rnd_1 = new (RandomThread);
        thread_1 = new(QThread);

        connect(thread_1,&QThread::started, rnd_1,&RandomThread::run);
        connect(rnd_1,&RandomThread::finished, thread_1,&QThread::terminate);
        connect(rnd_1,&RandomThread::arrayXY,this,&MainWindow::newArrayData);


        rnd_1->moveToThread(thread_1);
    }
    if(!rnd_1->running())
    {
        rnd_1->setRunning(true);
    }
    rnd_1->setPaused(false);
    setState(RUN);
    if(!thread_1->isRunning())
        thread_1->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    //Push pause
    rnd_1->setPaused(true);
    setState(PAUSE);
}

void MainWindow::on_pushButton_3_clicked()
{
    //Push stop
    setState(STOP);

    rnd_1->setRunning(false);
    rnd_1=nullptr;

    thread_1->terminate();

    ui->widget->graph()->data()->clear();
    ui->widget->replot();
}

void MainWindow::newArrayData(QVector<QPoint> *array)
{
    ui->widget->graph()->data()->clear();
    for(int i =0; i< array->count(); i++)
    {
        ui->widget->graph()->addData(array->at(i).x(),array->at(i).y());
    }
    ui->widget->replot();
}

void MainWindow::resizeEvent(QResizeEvent * event)
{
    int w,h;
    w = event->size().width();
    h = event->size().height();

    ui->widget->setGeometry(20,20,w-40,h-130);
    ui->widget->replot();

    ui->pushButton->move(w-210,h-90);
    ui->pushButton_2->move(w-140,h-90);
    ui->pushButton_3->move(w-70,h-90);

}
