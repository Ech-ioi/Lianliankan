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
signals:
    void EnterGame(const QString &str,Qt::CaseSensitivity cs);
    void EnterPrevious(const QString &str,Qt::CaseSensitivity cs);

private slots:
    void enableFindButton(const QString &text);
    void startClicked();

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *returnButton;

};

#endif // ENTER_H
