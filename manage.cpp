#include "manage.h"
#include "QWidget"
#include "QPalette"
#include "QBrush"
#include "QPixmap"
#include "QPushButton"
#include "enter.h"
#include <QMessageBox>
#include <iostream>
#include <time.h>
using namespace std;

//Manage::Manage(QObject *parent) : QObject(parent)
Manage::Manage()
{
    cout<<"Manage"<<endl;
    window=0;
    isStart=2;
    soundnum=1;
    setStartWindow();
}
Manage::~Manage(){
    cout<<"~Manage"<<endl;
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
    std::cout<<"createmap"<<std::endl;
    int b[MaxSizeX*MaxSizeY];
    int i,j,k;

    for(int i=0;i<MaxSizeX*MaxSizeY;i+=4){
        b[i]=b[i+1]=b[i+2]=b[i+3]=i/4+1;//1~36
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
        for(j=1;j<=MaxSizeY;j++){
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
            b[k]=map[i][j];
            k++;
        }
    }
    srand((unsigned)time(NULL));
    for(i=1;i<MaxSizeX*MaxSizeY;i++){//选出两个不为空的块并交换
        if(b[i]==0)
            continue;
        j=rand()%(i+1);
        k=2;
        while(b[j]==0){
            j=rand()%(i+k);
            k++;
        }
        temp=b[i];
        b[i]=b[j];
        b[j]=temp;
    }
    k=0;
    for(i=1;i<=MaxSizeX;i++){
        for(j=1;j<=MaxSizeY;j++){
            map[i][j]=b[k];
            k++;
        }
    }
    for(i=0;i<MaxSizeX;i++){
        for(j=0;j<MaxSizeY;j++){
            if(map[i+1][j+1]!=0){
                delete image[i][j];
                delete signalMapper[i][j];
            }
        }
    }
    setimage();
    initialbucket();
    if(!judge()) recreate();
}

void Manage::del_game(){
    std::cout<<"del_game"<<std::endl;
    int i,j;
    for(i=0;i<MaxSizeX;i++){
        for(j=0;j<MaxSizeY;j++){
            if(map[i+1][j+1]!=0){
                delete image[i][j];
                delete signalMapper[i][j];
            }
        }
    }
    for(i=0;i<2*MaxSizeX+2*MaxSizeY+4;i++){
        delete block[i];
    }
    delete changebutton;
    delete tipbutton;
    if(isAI)delete aibutton;
    delete timer;
    delete menubutton;
    delete musicbutton;
    sound->stop();

    delete gridlayout;
    delete vlayout;
    delete hlayout1;
    delete window;
}

void Manage::del_start()
{
    std::cout<<"del_start"<<std::endl;
    delete startbutton;
    delete gradebutton;
    delete hlayout1;
    delete hlayout2;
    delete hlayout3;
    delete vlayout;
}

void Manage::change(int num){//接收点击图片的坐标并作出判断
    std::cout<<"change"<<std::endl;
    int x=num/100+1;
    int y=num%100+1;
    double ftime;
    enum{first,second};
    static int vis=first;
    if(vis==first){
        x1=x;
        y1=y;
        vis=second;
        sound->play1();
        sound->stop1();
    }
    else if(vis==second){
        x2=x;
        y2=y;
        if(x1==x2&&y1==y2){//防止在一个点重复两次选择
        sound->play1();
        sound->stop1();
        }
        else if(ok()){//可以消去
            del(map[x1][y1],x1,y1);
            del(map[x1][y1],x2,y2);
            delete image[x1-1][y1-1];//删除图片
            delete image[x2-1][y2-1];
            delete signalMapper[x1-1][y1-1];//删除中转站
            delete signalMapper[x2-1][y2-1];
            map[x1][y1]=0;//修改地图
            map[x2][y2]=0;
            imageNum-=2;
            std::cout<<imageNum<<std::endl;
            if(imageNum==0){//游戏结束
                QMessageBox msg;
                timer->end();
                sound->stop();
                ftime=timer->count;
                eUser::user.Game_End(eUser::user.qname,ftime);
                cout<<"time:"<<ftime<<endl;
                msg.setText(tr("You win!"));
                msg.exec();
                del_game();
                setStartWindow();
                return;
            }
            if(!judge()){
                QMessageBox msg;
                msg.setText(tr("地图上无可连接的图标，\n系统将自动生成新地图"));
                msg.exec();
                recreate();
            }
        }
        else{//不可以消去
            sound->play1();
            sound->stop1();
        }
        vis=first;
    }
}

void Manage::show()//用红圈标出两个可连接的图标
{
    std::cout<<"show"<<std::endl;
    QString str3[]={"F:/Lianliankan/game/1_1.png",
                    "F:/Lianliankan/game/2_1.png",
                    "F:/Lianliankan/game/3_1.png",
                    "F:/Lianliankan/game/4_1.png",
                    "F:/Lianliankan/game/5_1.png",
                    "F:/Lianliankan/game/6_1.png",
                    "F:/Lianliankan/game/7_1.png",
                    "F:/Lianliankan/game/8_1.png",
                    "F:/Lianliankan/game/9_1.png",
                    "F:/Lianliankan/game/10_1.png",
                    "F:/Lianliankan/game/11_1.png",
                    "F:/Lianliankan/game/12_1.png",
                    "F:/Lianliankan/game/13_1.png",
                    "F:/Lianliankan/game/14_1.png",
                    "F:/Lianliankan/game/15_1.png",
                    "F:/Lianliankan/game/16_1.png",
                    "F:/Lianliankan/game/17_1.png",
                    "F:/Lianliankan/game/18_1.png",
                    "F:/Lianliankan/game/19_1.png",
                    "F:/Lianliankan/game/20_1.png",
                    "F:/Lianliankan/game/21_1.png",
                    "F:/Lianliankan/game/22_1.png",
                    "F:/Lianliankan/game/23_1.png",
                    "F:/Lianliankan/game/24_1.png",
                    "F:/Lianliankan/game/25_1.png",
                    "F:/Lianliankan/game/26_1.png",
                    "F:/Lianliankan/game/27_1.png",
                    "F:/Lianliankan/game/28_1.png",
                    "F:/Lianliankan/game/29_1.png",
                    "F:/Lianliankan/game/30_1.png",
                    "F:/Lianliankan/game/31_1.png",
                    "F:/Lianliankan/game/32_1.png",
                    "F:/Lianliankan/game/33_1.png",
                    "F:/Lianliankan/game/34_1.png",
                    "F:/Lianliankan/game/35_1.png",
                    "F:/Lianliankan/game/36_1.png"};
    QString str1[]={"F:/Lianliankan/game/1_2.png",
                    "F:/Lianliankan/game/2_2.png",
                    "F:/Lianliankan/game/3_2.png",
                    "F:/Lianliankan/game/4_2.png",
                    "F:/Lianliankan/game/5_2.png",
                    "F:/Lianliankan/game/6_2.png",
                    "F:/Lianliankan/game/7_2.png",
                    "F:/Lianliankan/game/8_2.png",
                    "F:/Lianliankan/game/9_2.png",
                    "F:/Lianliankan/game/10_2.png",
                    "F:/Lianliankan/game/11_2.png",
                    "F:/Lianliankan/game/12_2.png",
                    "F:/Lianliankan/game/13_2.png",
                    "F:/Lianliankan/game/14_2.png",
                    "F:/Lianliankan/game/15_2.png",
                    "F:/Lianliankan/game/16_2.png",
                    "F:/Lianliankan/game/17_2.png",
                    "F:/Lianliankan/game/18_2.png",
                    "F:/Lianliankan/game/19_2.png",
                    "F:/Lianliankan/game/20_2.png",
                    "F:/Lianliankan/game/21_2.png",
                    "F:/Lianliankan/game/22_2.png",
                    "F:/Lianliankan/game/23_2.png",
                    "F:/Lianliankan/game/24_2.png",
                    "F:/Lianliankan/game/25_2.png",
                    "F:/Lianliankan/game/26_2.png",
                    "F:/Lianliankan/game/27_2.png",
                    "F:/Lianliankan/game/28_2.png",
                    "F:/Lianliankan/game/29_2.png",
                    "F:/Lianliankan/game/30_2.png",
                    "F:/Lianliankan/game/31_2.png",
                    "F:/Lianliankan/game/32_2.png",
                    "F:/Lianliankan/game/33_2.png",
                    "F:/Lianliankan/game/34_2.png",
                    "F:/Lianliankan/game/35_2.png",
                    "F:/Lianliankan/game/36_2.png"};

    delete image[x3-1][y3-1];
    delete image[x4-1][y4-1];
    delete signalMapper[x3-1][y3-1];
    delete signalMapper[x4-1][y4-1];
    signalMapper[x3-1][y3-1]=new QSignalMapper;
    signalMapper[x4-1][y4-1]=new QSignalMapper;
    image[x3-1][y3-1]=createButton(str1[map[x3][y3]-1],str1[map[x3][y3]-1],str3[map[x3][y3]-1]);
    image[x4-1][y4-1]=createButton(str1[map[x4][y4]-1],str1[map[x4][y4]-1],str3[map[x4][y4]-1]);
    gridlayout->addWidget(image[x3-1][y3-1],x3,y3);
    gridlayout->addWidget(image[x4-1][y4-1],x4,y4);
    connect(image[x3-1][y3-1],SIGNAL(clicked()),signalMapper[x3-1][y3-1],SLOT(map()));
    connect(image[x4-1][y4-1],SIGNAL(clicked()),signalMapper[x4-1][y4-1],SLOT(map()));
    signalMapper[x3-1][y3-1]->setMapping(image[x3-1][y3-1],100*(x3-1)+y3-1);
    signalMapper[x4-1][y4-1]->setMapping(image[x4-1][y4-1],100*(x4-1)+y4-1);
    connect(signalMapper[x3-1][y3-1],SIGNAL(mapped(int)),this,SLOT(change(int)));
    connect(signalMapper[x4-1][y4-1],SIGNAL(mapped(int)),this,SLOT(change(int)));

}

void Manage::setStartWindow(){
    cout<<"setStartWindow"<<endl;
    isStart=0;
    window=new QWidget;
    window->setAutoFillBackground(true);
    QPalette palette;//?
    palette.setBrush(QPalette::Background,QBrush(QPixmap("F:/Lianliankan/pic_manage/window.png")));
    window->setPalette(palette);

    startbutton=new QPushButton("开始游戏");
    gradebutton=new QPushButton("查看排名");
    debugbutton=new QPushButton("开始游戏（debug版）");
    quitbutton=new QPushButton("退出游戏");

    vlayout=new QVBoxLayout;//界面布局
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
    
    connect(startbutton,SIGNAL(clicked()),this,SLOT(start_normal()));
    connect(debugbutton,SIGNAL(clicked()),this,SLOT(start_debug()));
    connect(gradebutton,SIGNAL(clicked()),this,SLOT(showGrade()));
    connect(quitbutton,SIGNAL(clicked()),this,SLOT(quitGame()));

}

void Manage::ai()
{
    cout<<"ai"<<endl;
    change(100*(x3-1)+y3-1);
    change(100*(x4-1)+y4-1);
}

void Manage::start_normal(){
    cout<<"start_normal"<<endl;
    isAI=false;
    Enter *start=new Enter;
    start->show();
    connect(start->startButton,SIGNAL(clicked()),this,SLOT(startGame()));
}

void Manage::start_debug(){
    cout<<"start_debug"<<endl;
    isAI=true;
    Enter *start=new Enter;
    start->show();
    connect(start->startButton,SIGNAL(clicked()),this,SLOT(startGame()));
}

void Manage::startGame(){
    std::cout<<"startGame"<<std::endl;
    isStart=1;
    delete startbutton;
    delete gradebutton;
    delete hlayout1;
    delete hlayout2;
    delete hlayout3;
    delete vlayout;
    delete window;
    isStart=true;
    imageNum=MaxSizeX*MaxSizeY;
    createmap();
    initialbucket();
    setlayout();


}

void Manage::showGrade(){
    std::cout<<"showGrade"<<std::endl;
    Show *p=new Show();
    p->show();
}

void Manage::quitGame(){
    std::cout<<"quitGame"<<std::endl;
    isStart=3;
    del_start();
    delete window;
}

void Manage::setlayout(){
    std::cout<<"setlayout"<<std::endl;
    QString str1("F:/Lianliankan/game/map2.png");
    QString str2("F:/Lianliankan/game/tip3.png");
    QString str3("F:/Lianliankan/game/volume1.png");

    window=new QWidget;
    window->setWindowTitle("连连看");
    window->resize(1250,900);

    gridlayout=new QGridLayout;
    hlayout1=new QHBoxLayout;
    vlayout=new QVBoxLayout;

    QPixmap img1(str1),img2(str2),img3(str3);
    timer=new Displaytime;
    sound->play();
    changebutton=new QPushButton;
    changebutton->setIcon(img1);
    changebutton->setIconSize(QSize(50,50));
    changebutton->setFlat(true);
    tipbutton=new QPushButton;
    tipbutton->setIcon(img2);
    tipbutton->setIconSize(QSize(50,50));
    tipbutton->setFlat(true);
    musicbutton=new QPushButton;
    musicbutton->setIcon(img3);
    musicbutton->setIconSize(QSize(50,50));
    musicbutton->setFlat(true);
    menubutton=new QPushButton(tr("Menu"));
    if(isAI)aibutton=new QPushButton(tr("人工智能"));
    else{
        aibutton=new QPushButton;
        aibutton->setFlat(true);
    }

    vlayout->addWidget(timer);
    vlayout->addWidget(changebutton);
    vlayout->addWidget(tipbutton);
    vlayout->addWidget(musicbutton);
    vlayout->addWidget(menubutton);
    vlayout->addWidget(aibutton);

    connect(tipbutton,SIGNAL(clicked()),this,SLOT(show()));
    connect(tipbutton,SIGNAL(clicked()),this,SLOT(changetext()));
    connect(changebutton,SIGNAL(clicked()),this,SLOT(recreate()));
    connect(changebutton,SIGNAL(clicked()),this,SLOT(changetext2()));
    connect(musicbutton,SIGNAL(clicked()),this,SLOT(changeMusicVol()));
    connect(menubutton,SIGNAL(clicked()),this,SLOT(gotoMenu()));
    if(isAI)connect(aibutton,SIGNAL(clicked()),this,SLOT(ai()));
    setblock();
    setimage();

    window->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap("F:/Lianliankan/game/background3.jpg")));
    window->setPalette(palette);
    hlayout1->addLayout(gridlayout);//水平布局设置
    hlayout1->addLayout(vlayout);//水平布局设置
    window->setLayout(hlayout1);
    window->show();
    judge();
}

void Manage::setimage()
{
    std::cout<<"setimage"<<std::endl;
    QString str1[]={"F:/Lianliankan/game/1.png",
                    "F:/Lianliankan/game/2.png",
                    "F:/Lianliankan/game/3.png",
                    "F:/Lianliankan/game/4.png",
                    "F:/Lianliankan/game/5.png",
                    "F:/Lianliankan/game/6.png",
                    "F:/Lianliankan/game/7.png",
                    "F:/Lianliankan/game/8.png",
                    "F:/Lianliankan/game/9.png",
                    "F:/Lianliankan/game/10.png",
                    "F:/Lianliankan/game/11.png",
                    "F:/Lianliankan/game/12.png",
                    "F:/Lianliankan/game/13.png",
                    "F:/Lianliankan/game/14.png",
                    "F:/Lianliankan/game/15.png",
                    "F:/Lianliankan/game/16.png",
                    "F:/Lianliankan/game/17.png",
                    "F:/Lianliankan/game/18.png",
                    "F:/Lianliankan/game/19.png",
                    "F:/Lianliankan/game/20.png",
                    "F:/Lianliankan/game/21.png",
                    "F:/Lianliankan/game/22.png",
                    "F:/Lianliankan/game/23.png",
                    "F:/Lianliankan/game/24.png",
                    "F:/Lianliankan/game/25.png",
                    "F:/Lianliankan/game/26.png",
                    "F:/Lianliankan/game/27.png",
                    "F:/Lianliankan/game/28.png",
                    "F:/Lianliankan/game/29.png",
                    "F:/Lianliankan/game/30.png",
                    "F:/Lianliankan/game/31.png",
                    "F:/Lianliankan/game/32.png",
                    "F:/Lianliankan/game/33.png",
                    "F:/Lianliankan/game/34.png",
                    "F:/Lianliankan/game/35.png",
                    "F:/Lianliankan/game/36.png"};
    QString str2[]={"F:/Lianliankan/game/1_1.png",
                    "F:/Lianliankan/game/2_1.png",
                    "F:/Lianliankan/game/3_1.png",
                    "F:/Lianliankan/game/4_1.png",
                    "F:/Lianliankan/game/5_1.png",
                    "F:/Lianliankan/game/6_1.png",
                    "F:/Lianliankan/game/7_1.png",
                    "F:/Lianliankan/game/8_1.png",
                    "F:/Lianliankan/game/9_1.png",
                    "F:/Lianliankan/game/10_1.png",
                    "F:/Lianliankan/game/11_1.png",
                    "F:/Lianliankan/game/12_1.png",
                    "F:/Lianliankan/game/13_1.png",
                    "F:/Lianliankan/game/14_1.png",
                    "F:/Lianliankan/game/15_1.png",
                    "F:/Lianliankan/game/16_1.png",
                    "F:/Lianliankan/game/17_1.png",
                    "F:/Lianliankan/game/18_1.png",
                    "F:/Lianliankan/game/19_1.png",
                    "F:/Lianliankan/game/20_1.png",
                    "F:/Lianliankan/game/21_1.png",
                    "F:/Lianliankan/game/22_1.png",
                    "F:/Lianliankan/game/23_1.png",
                    "F:/Lianliankan/game/24_1.png",
                    "F:/Lianliankan/game/25_1.png",
                    "F:/Lianliankan/game/26_1.png",
                    "F:/Lianliankan/game/27_1.png",
                    "F:/Lianliankan/game/28_1.png",
                    "F:/Lianliankan/game/29_1.png",
                    "F:/Lianliankan/game/30_1.png",
                    "F:/Lianliankan/game/31_1.png",
                    "F:/Lianliankan/game/32_1.png",
                    "F:/Lianliankan/game/33_1.png",
                    "F:/Lianliankan/game/34_1.png",
                    "F:/Lianliankan/game/35_1.png",
                    "F:/Lianliankan/game/36_1.png"};
    QString str3[]={"F:/Lianliankan/game/1_2.png",
                    "F:/Lianliankan/game/2_2.png",
                    "F:/Lianliankan/game/3_2.png",
                    "F:/Lianliankan/game/4_2.png",
                    "F:/Lianliankan/game/5_2.png",
                    "F:/Lianliankan/game/6_2.png",
                    "F:/Lianliankan/game/7_2.png",
                    "F:/Lianliankan/game/8_2.png",
                    "F:/Lianliankan/game/9_2.png",
                    "F:/Lianliankan/game/10_2.png",
                    "F:/Lianliankan/game/11_2.png",
                    "F:/Lianliankan/game/12_2.png",
                    "F:/Lianliankan/game/13_2.png",
                    "F:/Lianliankan/game/14_2.png",
                    "F:/Lianliankan/game/15_2.png",
                    "F:/Lianliankan/game/16_2.png",
                    "F:/Lianliankan/game/17_2.png",
                    "F:/Lianliankan/game/18_2.png",
                    "F:/Lianliankan/game/19_2.png",
                    "F:/Lianliankan/game/20_2.png",
                    "F:/Lianliankan/game/21_2.png",
                    "F:/Lianliankan/game/22_2.png",
                    "F:/Lianliankan/game/23_2.png",
                    "F:/Lianliankan/game/24_2.png",
                    "F:/Lianliankan/game/25_2.png",
                    "F:/Lianliankan/game/26_2.png",
                    "F:/Lianliankan/game/27_2.png",
                    "F:/Lianliankan/game/28_2.png",
                    "F:/Lianliankan/game/29_2.png",
                    "F:/Lianliankan/game/30_2.png",
                    "F:/Lianliankan/game/31_2.png",
                    "F:/Lianliankan/game/32_2.png",
                    "F:/Lianliankan/game/33_2.png",
                    "F:/Lianliankan/game/34_2.png",
                    "F:/Lianliankan/game/35_2.png",
                    "F:/Lianliankan/game/36_2.png"};
    for(int i=0;i<MaxSizeX;i++){
        for(int j=0;j<MaxSizeY;j++){
            int tmp=map[i+1][j+1];
            if(tmp!=0){
                signalMapper[i][j]=new QSignalMapper;
                image[i][j]=createButton(str1[tmp-1],str2[tmp-1],str3[tmp-1]);
                gridlayout->addWidget(image[i][j],i+1,j+1);
                connect(image[i][j],SIGNAL(clicked()),signalMapper[i][j],SLOT(map()));
                signalMapper[i][j]->setMapping(image[i][j],100*i+j);
                connect(signalMapper[i][j],SIGNAL(mapped(int)),this,SLOT(change(int)));
            }
        }
    }
}

void Manage::setblock()
{
    std::cout<<"setblock"<<std::endl;
    QString str("F:/Lianliankan/game/a.png");
    int cnt=0;
    for(int i=0;i<=MaxSizeX+1;i++){
        block[cnt]=createButton(str);
        gridlayout->addWidget(block[cnt++],i,0);
    }
    for(int j=1;j<=MaxSizeY+1;j++){
        block[cnt]=createButton(str);
        gridlayout->addWidget(block[cnt++],0,j);
    }
    for(int i=1;i<=MaxSizeX+1;i++){
        block[cnt]=createButton(str);
        gridlayout->addWidget(block[cnt++],i,MaxSizeY+1);
    }
    for(int j=1;j<=MaxSizeY+1;j++){
        block[cnt]=createButton(str);
        gridlayout->addWidget(block[cnt++],MaxSizeX+1,j);
    }
}

void Manage::gotoMenu()
{
    cout<<"gotoMenu"<<endl;
    del_game();
    setStartWindow();
}

void Manage::changeMusicVol()
{
    cout<<"changeMusicVol"<<endl;
    QString str[]={"F:/Lianliankan/game/volume1.png",
                   "F:/Lianliankan/game/volume2.png"};
    QPixmap img0(str[0]),img1(str[1]);
    if(soundnum==1){
        soundnum++;
        musicbutton->setIcon(img1);
        sound->stop();
    }
    else if(soundnum==2){
        soundnum--;
        musicbutton->setIcon(img0);
        sound->play();

    }
}

bool Manage::ok()//判断两个图片能否消去（接口函数）
{
    std::cout<<"ok"<<std::endl;
    flag=false;//判断两个图片能否消去的标记
    count=0;//记录连线拐弯次数
    if(map[x1][y1]!=map[x2][y2])
        return false;
    dfs(x1,y1,x2,y2,Null);
    if(flag){
        sound->play2();
        sound->stop2();
        return true;
    }
    return false;
}

bool Manage::judge()
{
    std::cout<<"judget"<<std::endl;
    flag=false;
    for(int k=1;k<=imagenum;k++){
        for(int i=0;i<num[k]-1;i++){
            for(int j=i+1;j<num[k];j++){
                x3=bucket[k][i].x;
                y3=bucket[k][i].y;
                x4=bucket[k][j].x;
                y4=bucket[k][j].y;
                count=0;
                dfs(x3,y3,x4,y4,Null);
                if(flag){
                    return true;
                }
            }
        }
    }
    return false;
}

void Manage::dfs(int x, int y, int x2, int y2, int type)
{
    if(flag) return;
    if(count>=3) return;
    if(x==MaxSizeX+2||x<0||y==MaxSizeY+2||y<0) return;//点到了边界
    if(x==x2&&y==y2){//两点位置相同（是在已经执行了后面的语句的基础上）
        flag=true;
        return;
    }


    if(map[x][y]!=0&&type!=Null) return;//目前走到的位置有块，回溯
    if(type!=Up&&type!=Null){
        count++;
        dfs(x-1,y,x2,y2,Up);
        count--;
    }
    else{
        dfs(x-1,y,x2,y2,Up);
    }
    if(flag) return;


    if(type!=Down&&type!=Null){
        count++;
        dfs(x+1,y,x2,y2,Down);
        count--;
    }
    else{
        dfs(x+1,y,x2,y2,Down);
    }
    if(flag) return;


    if(type!=Left&&type!=Null){
        count++;
        dfs(x,y-1,x2,y2,Left);
        count--;
    }
    else{
        dfs(x,y-1,x2,y2,Left);
    }
    if(flag) return;

    if(type!=Right&&type!=Null){
        count++;
        dfs(x,y+1,x2,y2,Right);
        count--;
    }
    else{
        dfs(x,y+1,x2,y2,Right);
    }
    if(flag) return;
}


void Manage::del(int k, int x, int y)//消掉图片后更新bucket数组
{
    std::cout<<"del"<<std::endl;
    int i;
    for(i=0;i<num[k];i++){
        if(bucket[k][i].x==x&&bucket[k][i].y==y) break;//找到i则跳出循环
    }
    for(;i<num[k]-1;i++){
        bucket[k][i].x=bucket[k][i+1].x;
        bucket[k][i].y=bucket[k][i+1].y;
    }
    num[k]--;
}

Button *Manage::createButton(QString &str1, QString &str2, QString &str3)
{
    Button *button=new Button;
    button->setGeometry(0,0,0,0);
    QPixmap img1,img2,img3;
    img1.load(str1);
    img2.load(str2);
    img3.load(str3);
    button->setFixedSize(img1.width(),img1.height());
    button->SetButtonIcons(img1,img2,img3);
    button->setIconSize(QSize(img1.width(),img1.height()));
    button->setAutoRaise(true);
    return button;
}

QPushButton *Manage::createButton(QString &str)
{
    QPushButton *button=new QPushButton;
    QPixmap img(str);
    button->setFixedSize(img.width(),img.height());
    button->setFlat(true);
    return button;
}

void Manage::changetext(){
    cout<<"changetext"<<endl;
    QString str[]={"F:/Lianliankan/game/tip0.png",
                   "F:/Lianliankan/game/tip1.png",
                   "F:/Lianliankan/game/tip2.png"};
    QPixmap img0(str[0]),img1(str[1]),img2(str[2]);
    static int cnt=1;
    if(cnt==1){
        tipbutton->setIcon(img2);
    }
    else if(cnt==2){
        tipbutton->setIcon(img1);
    }
    else if(cnt==3){
        tipbutton->setIcon(img0);
        tipbutton->setEnabled(false);
    }
    cnt++;
}

void Manage::changetext2(){
    cout<<"changetext2"<<endl;
    QString str[]={"F:/Lianliankan/game/map0.png",
                   "F:/Lianliankan/game/map1.png"};
    QPixmap img0(str[0]),img1(str[1]);
    static int cnt=1;
    if(cnt==1){
        changebutton->setIcon(img1);
    }
    else if(cnt==2){
        changebutton->setIcon(img0);
        changebutton->setEnabled(false);
    }
    cnt++;
}












