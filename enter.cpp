//储存所有在class.h和enter.h两个头文件定义的函数

#include "enter.h"
#include "class.h"
#include <QByteArray>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <iostream>
#include <fstream>
using namespace  std;

User::User(char* name="NULL",double time=10000)
{
    this->name=(char*)malloc(strlen(name)+1);
    strcpy(this->name,name);
    this->time=time;
}
User::~User(){
    if(name!=NULL)
        free(name);
}

char* User::Get_Name() const{
    return name;
}

double User::Get_Time() const{
    return time;
}

void User::set_name(char *name){
    this->name=name;
}

void User::set_time(double Time){
    this->time=time;
}

//?为什么多写此函数
void User::point(char *Name, double Time){
    this->name=Name;
    this->time=Time;
}


//游戏结束后的分值处理\游戏结束后读取进行排名
void User::Game_End(QString qname,double now_time){
    char *ch;
    QByteArray ba=qname.toLatin1();//QString转char*
    ch=ba.data();

    User allname[6];//只显示5个排名，但是多出一个参数用来保存当前用户
    User temp(ch,now_time);

    double Time;
    char* Name=(char*)malloc(10*sizeof(char));
    int rank=0;

    ifstream out("F:/Lianliankan/grade/Grade.txt",ios::in);
    while(out>>Name>>Time){
        allname[rank].point(Name,Time);
        if(rank<=5){
            rank++;
            Name=(char*)malloc(10);
        }
        else
            break;
    }
    out.close();
    allname[5]=temp;

    //冒泡排序
    for(int i=0;i<5;i++){
        for(rank=0;rank<5-i;rank++){
            if(allname[rank].Get_Time()>allname[rank+1].Get_Time()){
                temp=allname[rank];
                allname[rank]=allname[rank+1];
                allname[rank+1]=temp;
            }
        }
    }
    ofstream file;
    file.open("F:/Lianliankan/grade/Grade.txt",ios::out);
    for(rank=0;rank<5;rank++){
        file<<allname[rank].Get_Name()<<" "<<allname[rank].Get_Time()<<endl;
    }
    file.close();

}

User eUser::user;

Enter::Enter(QWidget *parent):
    QDialog(parent)
{
    label=new QLabel(tr("Please input your name:"));
    lineEdit=new QLineEdit;
    label->setBuddy(lineEdit);

    startButton=new QPushButton(tr("Start!"));
    startButton->setDefault(true);//绑定键盘的回车键
    startButton->setEnabled(false);

    returnButton=new QPushButton(tr("Return"));

    connect(lineEdit,SIGNAL(textChanged(const QString &)),this,SLOT(enableFindButton(const QString &)));
    connect(startButton,SIGNAL(clicked()),this,SLOT(startClicked()));
    connect(returnButton,SIGNAL(clicked()),this,SLOT(close()));

    QHBoxLayout *lastButton=new QHBoxLayout;
    lastButton->addWidget(returnButton);
    lastButton->addWidget(startButton);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(lastButton);
    setLayout(mainLayout);

    setWindowTitle(tr("Enter"));
    setFixedHeight(sizeHint().height());
}

void Enter::startClicked(){
    QString text=lineEdit->text();
    char* ch;
    QByteArray ba=text.toLatin1();
    ch=ba.data();
    eUser::user.set_name(ch);
    eUser::user.qname=text;
    std::cout<<"now user's name is "<<eUser::user.Get_Name()<<std::endl;
    close();
}

void Enter::enableFindButton(const QString &text){
    startButton->setEnabled(!text.isEmpty());
}













