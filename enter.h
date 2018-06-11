#ifndef ENTER_H
#define ENTER_H
#include "class.h"
#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class Enter:public QDialog
{
    Q_OBJECT
public:
    Enter(QWidget *parent = 0);
    QPushButton *startButton;
    User *user;

//声明信号
signals://设置某一信号的对应动作
    void EnterGame(const QString &str,Qt::CaseSensitivity cs);
    void EnterPrevious(const QString &str,Qt::CaseSensitivity cs);

//声明槽
private slots:
    void enableFindButton(const QString &text);
    void startClicked();

private:
    QLabel *label;//*?
    QLineEdit *lineEdit;
    QPushButton *returnButton;

};

#endif // ENTER_H
