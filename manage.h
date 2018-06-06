#ifndef MANAGE_H
#define MANAGE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include "enter.h"

class Manage : public QObject
{
    Q_OBJECT
private:
    QWidget *window;//主窗口
    void setStartWindow();
    int isStart;//保存目前窗口的位置
    bool isAI;//是否开启debug模式
    QPushButton *startbutton;
    QPushButton *gradebutton;
    QPushButton *debugbutton;
    QPushButton *quitbutton;
    QVBoxLayout *vlayout;//垂直布局
    QHBoxLayout *hlayout1,*hlayout2,*hlayout3,*hlayout4;
    void del_start();
    void start_normal();

public:
    //explicit Manage(QObject *parent = 0);
    Manage();
    virtual ~Manage();


signals:

public slots:
};

#endif // MANAGE_H
