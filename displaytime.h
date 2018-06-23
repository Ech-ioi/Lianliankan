#ifndef DISPLAYTIME_H
#define DISPLAYTIME_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QString>
#include <QLabel>
#include <class.h>

class Displaytime : public QWidget
{
    Q_OBJECT
public:
    long count;
    QString time;
    Displaytime(QWidget *parent = 0);
    virtual ~Displaytime();
    void end();
private:
    QPushButton *timeLabel;
    QTimer *timer;
public slots:
    void timerEvent(QTimerEvent *event);
};

#endif // DISPLAYTIME_H
