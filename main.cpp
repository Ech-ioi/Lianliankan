//version-3.0.0
//实现 对消 音乐播放 音乐播放
//待实现：用户成绩记录 消除路线显示

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
