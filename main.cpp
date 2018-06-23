//version-3.5.0
//实现 对消 音乐播放 音乐播放 用户成绩记录
//待实现：消除路线显示 难度关卡设置 时间进度条

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
