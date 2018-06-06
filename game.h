#ifndef GAME_H
#define GAME_H
//主界面
#include <QWidget>

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();

private:
    Ui::game *ui;
public slots:
    void on_showLowGame_clicked();
private slots:
    void on_go_home_clicked();
};

#endif // GAME_H
