#include "manage.h"
#include "QWidget"
#include "QPalette"
#include "QBrush"
#include "QPixmap"
#include "QPushButton"
#include "enter.h"
#include <iostream>
#include <time.h>


//Manage::Manage(QObject *parent) : QObject(parent)
Manage::Manage()
{
    window=0;
    isStart=2;
    setStartWindow();
}
Manage::~Manage(){
    if(isStart==1){
        del_game();
        delete window;
    }
    else if(isStart==0){
        del_start();
        delete window;
    }
}

void Manage::createmap(){
    std::count<<"createmap"<<std::endl;
    int b[MaxSizeX*MaxSizeY];
    int i,j,k;

    for(int i=0;i<MaxSizeX*MaxSizeY;i+=4){
        b[i]=b[i+1]=b[i+2]=b[i+3]=i/4+1;//35*4=140
    }
    //产生这样的序列：
    //[1 1 1 1] [2 2 2 2]....用来在后面打乱并插入图片
    srand((unsigned)time(NULL));
    std::random_shuffle(b,b+MaxSizeX*MaxSizeY);//对元素序列进行重新排序（随机的）
    //随机数是通过一个算法产生的，当它的初始种子确定后，后面的序列是一定的
    //。要让它变化，只能通过srand重设种子，同时种子要与时间相关，这样就达到随机了。
    k=0;
    memset(map,0,sizeof(map));
    for(i=1;i<=MaxSizeX;i++){
        for(j=1;j<MaxSizeY;j++){
            map[i][j]=b[k++];
        }
    }
}

void Manage::recreate(){
    std::cout<<"recreate map"<<std::endl;
    int b[MaxSizeX*MaxSizeY];
    int i,j;
    int k=0;
    int temp;

    for(i=1;i<=MaxSizeX;i++){
        for(j=1;j<=MaxSizeY;j++){
            b[k++]=map[i][j];
        }
    }
    srand((unsigned)time(NULL));
    for(i=1;i<MaxSizeX*MaxSizeY;i++){
        if(b[i]==0)
            continue;
        j=rand()%(i+1);
        k=2;

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
    start->show();
    connect(start->startButton,SIGNAL(clicked()),this,SLOT(startGame()));
}

void Manage::start_de














