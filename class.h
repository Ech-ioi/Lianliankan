#ifndef CLSS_H
#define CLSS_H
#include <QDialog>

class User
{
public:
    User(char* name,double time);
    char* Get_Name() const;
    double Get_Time() const;
    //const对象只能调用const成员函数。
    //const对象的值不能被修改，在const成员函
    //数中修改const对象数据成员的值是语法错误。
    void point(char* Name,double Time);
    void Game_End(QString qname,double now_time);
    ~User();
    void set_name(char * Name);
    void set_time(double Time);
    QString qname;//?QString
private:
    char* name;
    double time;
};

class eUser
{
public:
    static User user;
};

#endif // CLSS_H
