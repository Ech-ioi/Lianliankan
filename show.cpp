#include "show.h"
#include <fstream>
#include <iostream>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QtGui>
using namespace std;
//构造函数后面括号内的参数表列中只有参数但无参数类型，因为在这里
//不是定义基类构造函数，而是调用基类构造函数，因此这些参数是实参
//而不是形参。他们可以是常量、全局变量和派生类构造函数总参数表中
//的参数。 先初始化父类成员变量，从而间接初始化子类从父类继承过
//来的成员变量。
//    这个问题就是使用上面的那行代码来解决的。首先QMainWindow
//是父类（基类）而MainWindow是子类（派生类），他们是继承关系；
//MainWindow(QWidget *parent)是类MainWindow的构造函数，
//QMainwindow(parent)是类QMainwindow的构造函数。类Mainwindow
//在实现构造函数时，要初始化基类QMainwindow的数据成员但是因为
//无法继承基类的构造函数，所以才用这种方式初始化基类的数据成员。
Show::Show(QWidget *parent):QDialog(parent)
{
    label=new QLabel;
    char* name[5];
    int time[5];
    char *Name=(char*)malloc(10*sizeof(char));
    int Time;
    int rank=0;
    ifstream out("F:/Lianliankan/grade/Grade.txt",ios::in);
    while(out>>Name>>Time){
        name[rank]=Name;
        time[rank]=Time;
        if(rank<=5){
            rank++;
            Name=(char*)malloc(10*sizeof(char));
        }
        else
            break;
    }
    out.close();
    label->setText("Best Grade\n\n1."+
                    QString(name[0])+" "+QString::number(time[0])+"\n2."+
                    QString(name[1])+" "+QString::number(time[1])+"\n3."+
                    QString(name[2])+" "+QString::number(time[2])+"\n4."+
                    QString(name[3])+" "+QString::number(time[3])+"\n5."+
                    QString(name[4])+" "+QString::number(time[4])+"\n"
                   );
    closeButton=new QPushButton(tr("Close"));
    closeButton->setDefault(true);
    closeButton->setEnabled(true);

    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addWidget(label);
    mainLayout->addWidget(closeButton);

    QHBoxLayout *window=new QHBoxLayout;
    window->addStretch();
    window->addLayout(mainLayout);
    window->addStretch();//在拉伸时保持布局
    setLayout(window);

    int width=280;
    int height=320;
    setWindowTitle("Show Grade");
    setFixedSize(width,height);

}
