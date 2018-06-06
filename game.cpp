#include "game.h"
#include "home.h"
#include "ui_game.h"
#include <QDialog>
//主界面
game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
}

game::~game()
{
    delete ui;
}

void game::on_showLowGame_clicked()
{
    QDialog *dialog=new QDialog(this);
    dialog->show();
}


void game::on_go_home_clicked()
{
    close();
    Home home;
    if(home.exec()==QDialog::Accepted)
        show();

}
