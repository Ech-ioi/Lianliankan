#ifndef SHOW_H
#define SHOW_H
#include <QDialog>
class QLabel;
class QPushButton;
//前置声明会告诉这个类的存在,而不用提供类定义的所有细节,他们通常放在它自己的
//头文件中,下面FindDialog类中使用的都是这几个类的指针,而且没有必要再头文件
//中使用他们,因为编译就无需这些类的完整定义,我们没有使用这些的头文件,
//如<QCheckBox>,<QLabel>等,而是使用前置声明,可以使编译过程更快一些


class Show : public QDialog
{
    Q_OBJECT
public:
    Show(QWidget *parent = 0);//参数 parent 指向父窗口，
            //    如果这个参数为 0，则窗口就成为一个顶级窗口
signals:
    void Close(const QString& std,Qt::CaseSensitivity cs);//输入的大小写要敏感
private:
    QLabel *label;
    QPushButton *closeButton;
};

#endif // SHOW_H
