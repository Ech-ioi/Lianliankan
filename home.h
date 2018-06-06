#ifndef HOME_H
#define HOME_H
//登陆
#include <QDialog>

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = 0);
    ~Home();

private slots:
    void on_go_game_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
