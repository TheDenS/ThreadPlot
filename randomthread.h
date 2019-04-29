#ifndef RANDOMTHREAD_H
#define RANDOMTHREAD_H

#include <QObject>
#include <QDebug>
#include <QPoint>
#include <QTimer>
#include <QVector>


class RandomThread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(QPoint XY READ XY WRITE setXY NOTIFY XYChanged)
    Q_PROPERTY(bool paused READ paused WRITE setPaused NOTIFY pausedChanged)

    bool m_running;
    bool m_paused;

    QPoint m_XY;
    QTimer *timer;
    QVector<QPoint> vector_1;




public:

    explicit RandomThread(QObject *parent = nullptr);
    bool running() const;
    QPoint XY() const;

    bool paused() const;

signals:

    void finished();
    void runningChanged(bool running);
    void XYChanged(QPoint XY);

    void arrayXY(QVector<QPoint> *array);
    void pausedChanged(bool paused);

public slots:

    void run();
    void setRunning(bool running);
    void setXY(QPoint XY);
    void setPaused(bool paused);
};

#endif // RANDOMTHREAD_H
