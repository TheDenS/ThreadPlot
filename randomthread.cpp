#include "randomthread.h"
#include <QThread>
#include <QTimer>
#include <QEventLoop>
#include <QRandomGenerator>


RandomThread::RandomThread(QObject *parent) :
    QObject(parent)
{
}

bool RandomThread::running() const
{
    return m_running;
}

QPoint RandomThread::XY() const
{
    return m_XY;
}

bool RandomThread::paused() const
{
    return m_paused;
}

void RandomThread::run()
{
    int i;
    QEventLoop loop;
    QRandomGenerator generator;
    while (m_running)
    {
        if(!m_paused)
        {
            vector_1.clear();
            vector_1.resize(100);
            for(i=0;i<100;i++)
            {
                m_XY.setX(i);
                m_XY.setY(generator.bounded(0,100));
                vector_1<<m_XY;
            }
            emit arrayXY(&vector_1);
            QTimer::singleShot(500, &loop, SLOT(quit()));
            loop.exec();

        }
        else
        {
            QTimer::singleShot(100, &loop, SLOT(quit()));
            loop.exec();
        }
    }
    emit finished();
}

void RandomThread::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}

void RandomThread::setXY(QPoint XY)
{
    if (m_XY == XY)
        return;

    m_XY = XY;
    emit XYChanged(m_XY);
}

void RandomThread::setPaused(bool paused)
{
    if (m_paused == paused)
        return;

    m_paused = paused;
    emit pausedChanged(m_paused);
}

