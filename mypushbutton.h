#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = 0);
    //重载构造函数，参数1是正常图片，参数2是按下时图片
    MyPushButton(QString normalimg,QString pressimg="");
    //成员属性，保存
    QString normalimgpath;
    QString pressimgpath;

    //弹跳
    void zoom1();
    void zoom2();


   void mousePressEvent(QMouseEvent *e);
   void mouseReleaseEvent(QMouseEvent *e);




signals:

public slots:
};

#endif // MYPUSHBUTTON_H
