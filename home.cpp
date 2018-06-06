#include "home.h"
#include "ui_home.h"
//登陆
Home::Home(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}

void Home::on_go_game_clicked()
{
    accept();
}
