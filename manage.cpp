#include "manage.h"
#include "QWidget"
#include "QPalette"
#include "QBrush"
#include "QPixmap"
#include "QPushButton"
#include "enter.h"
#include <iostream>


//Manage::Manage(QObject *parent) : QObject(parent)
Manage::Manage()
{
    window=0;
    isStart=2;
    setStartWindow();
}
Manage::~Manage(){
    if(isStart==0){
        del_start();
        delete window;
    }
}

void Manage::setStartWindow(){
    isStart=0;
    window=new QWidget;
    window->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap("F:/Lianliankan/pic_manage/window.png")));
    window->setPalette(palette);

    startbutton=new QPushButton("开始游戏");
    gradebutton=new QPushButton("查看排名");
    debugbutton=new QPushButton("开始游戏（debug版）");
    quitbutton=new QPushButton("退出游戏");

    vlayout=new QVBoxLayout;
    hlayout1=new QHBoxLayout;
    hlayout2=new QHBoxLayout;
    hlayout3=new QHBoxLayout;
    hlayout4=new QHBoxLayout;

    hlayout1->addStretch();//设置距离
    hlayout1->addWidget(startbutton);
    hlayout1->addStretch();

    hlayout2->addStretch();
    hlayout2->addWidget(gradebutton);
    hlayout2->addStretch();

    hlayout3->addStretch();
    hlayout3->addWidget(debugbutton);
    hlayout3->addStretch();

    hlayout4->addStretch();
    hlayout4->addWidget(quitbutton);
    hlayout4->addStretch();

    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);

    window->setLayout(vlayout);
    window->setFixedSize(1200,900);
    window->show();

}

void Manage::del_start()
{
    std::cout<<"game::~game()"<<std::endl;
    delete startbutton;
    delete gradebutton;
    delete hlayout1;
    delete hlayout2;
    delete hlayout3;
    delete vlayout;
}

void Manage::start_normal(){
    isAI=false;
    Enter *start=new Enter;
    start.show();

}
