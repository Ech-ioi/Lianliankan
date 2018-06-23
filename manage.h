#ifndef MANAGE_H
#define MANAGE_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSignalMapper>
#include "enter.h"
#include "button.h"
#include "player.h"
#include "displaytime.h"
#include "iostream"
#include "player.h"
#include "show.h"

//一个库是二进制兼容的，如果一个程序和某个库的某个版本动态链接，并且不需要重新编译，即可在安装有该库较新版本的环境中运行。为什么要保证二进制兼容性？
//如果不能保证库的二进制兼容性，就意味着每次发布新版本时，依赖该库的所有程序都必须重新编译才能正常运行。显然，这对于像Qt这样被广泛采用的库而言是完全不可接受的。
class Manage : public QObject
{
    Q_OBJECT
private:
    enum{Null,Right,Left,Up,Down};
    enum{MaxSizeX=10,MaxSizeY=14};
    enum{imagenum=36};
    int x1,y1,x2,y2,x3,y3,x4,y4;
    int count;//连线拐弯次数
    bool flag;//两个图片能否被消去
    int isStart;//保存目前窗口的位置
    bool isAI;//是否开启debug模式

    int map[MaxSizeX+2][MaxSizeY+2];//地图
    int num[imagenum+1];//不同类型图片的个数
    struct{
        int x;
        int y;
    }bucket[imagenum+1][5];
    //存放不同类型图片的坐标
    //bucket[x][y]代表第i种图片的第j个图的坐标
    //用于辅助judge（）函数

    QGridLayout *gridlayout;//表格布局
    QHBoxLayout *hlayout1,*hlayout2,*hlayout3,*hlayout4;
    QVBoxLayout *vlayout;//垂直布局
    QSignalMapper *signalMapper[MaxSizeX][MaxSizeY];//信号中继站
    QPushButton *block[2*MaxSizeX + 2*MaxSizeY + 4];//地图边缘
    Button *image[MaxSizeX][MaxSizeY];//图片按钮
    QWidget *window;//主窗口
    QPushButton *changebutton,*tipbutton,*aibutton,*menubutton,*musicbutton;
    Displaytime *timer;

    QPushButton *startbutton;
    QPushButton *gradebutton;
    QPushButton *debugbutton;
    QPushButton *quitbutton;

    Player *sound;
    int soundnum;

    void createmap();
    void setlayout();
    void setimage();
    void setblock();


    inline void initialbucket(){
        std::cout<<"initialbucket"<<std::endl;
        memset(num,0,sizeof(num));
        memset(bucket,0,sizeof(bucket));
        for(int i=1;i<=MaxSizeX;i++){
            for(int j=1;j<=MaxSizeY;j++){
                if(map[i][j]!=0){
                    bucket[ map[i][j] ][ num[ map[i][j] ]].x=i;
                    bucket[ map[i][j] ][ num[map[i][j]]++].y=j;
                }
            }
        }
    }//初始化bucket数组

    bool ok();//判断两个图片能否消去（接口函数）
    bool judge();//判断地图上是否还存在可消的图片，如果有，记录坐标存入(x3,y3)(x4,y4)
    void dfs(int x,int y,int x2,int y2,int type);
    void del(int k,int x,int y);
    Button *createButton(QString &str1,QString &str2,QString &str3);
    QPushButton *createButton(QString &str);//给地图边缘创建普通按钮
    void del_start();//清除开始界面
    void del_game();//清除游戏界面

public:
    Manage();
    virtual ~Manage();
    int imageNum;////记录屏幕上图片个数

//槽
private slots:
    void change(int num);//接收点击图片的坐标并作出判断
    void show();//显示提示图片
    void recreate();//重建生成地图
    void changetext();//重新生成地图和提示次数更新
    void changetext2();
    void setStartWindow(); //游戏开始界面
    void ai();//人工智能
    void start_normal();//普通的开始游戏（接口函数）
    void start_debug();//debug版的开始游戏（接口函数）
    void showGrade();//显示成绩
    void startGame();//开始游戏
    void quitGame();//退出游戏
    void gotoMenu();
    void changeMusicVol();
};

#endif // MANAGE_H
