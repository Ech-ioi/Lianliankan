//version-2.0.0
//实现对消
//待实现：音乐播放 提示功能 倒计时 用户成绩记录

#include <QApplication>
#include <QWidget>
#include "game.h"
#include "home.h"
#include "manage.h"
int main(int argc,char *argv[]){
    QApplication a(argc,argv);
    Manage manage;
    return a.exec();

}
