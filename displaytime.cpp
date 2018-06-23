#include "displaytime.h"
#include <iostream>

static int flag=0;
Displaytime::Displaytime(QWidget *parent)
    : QWidget(parent)
{
    count=-1;
    timeLabel=new QPushButton(this);
    timer=new QTimer(this);
    timeLabel->setText("时间：");
    timerEvent(0);
    timer->setInterval(1000);//转换毫秒单位为秒
    startTimer(1000);
    timeLabel->show();
}

Displaytime::~Displaytime(){
    std::cout<<"diaplaytime::~diaplaytime"<<std::endl;
    flag=0;
    delete timer;
    delete timeLabel;
}

void Displaytime::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);
    if(!flag){
        count++;
    }
    QString time=QString::number(count,10);//转换数据类型
    timeLabel->setText("时间："+time+"s");
    timeLabel->adjustSize();//自动调整文本大小
//    timeLabel->resize(300,50);
}

void Displaytime::end(){
    flag=1;
}
