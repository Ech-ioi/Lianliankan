//version-1.0.0

#include <QApplication>
#include <QWidget>
#include "game.h"
#include "home.h"
#include "manage.h"
int main(int argc,char *argv[]){
    QApplication a(argc,argv);
//    game g;
//    g.resize(1200,900);
//    g.setWindowTitle("连连看");
//    Home home;
//    if(home.exec()==QDialog::Accepted){
//        g.show();
//        return a.exec();
//    }
//    else{
//        return 0;
//    }
    Manage manage;
    return a.exec();

}
