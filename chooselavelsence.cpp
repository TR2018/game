#include "chooselavelsence.h"
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<QDebug>
#include<QSound>
ChooseLavelSence::ChooseLavelSence(QWidget *parent) : QMainWindow(parent)
{
    //配置主场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QIcon(":/res/da.jpeg"));
    //设置标题
    this->setWindowTitle("关卡选择");
    //设置菜单栏
    QMenuBar*bar=menuBar();
    setMenuBar(bar);
    QMenu *startmenu= bar->addMenu("开始");
    QAction*quitAction=startmenu->addAction("退出");
    //退出按钮实现
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);

    MyPushButton *backbtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&MyPushButton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(500,this,[=](){
              emit this->ChooseBack();

        });
    });


    for(int i=0;i<20;i++)
    {
        MyPushButton *MenuBtn=new MyPushButton(":/res/LevelIcon.png");
        MenuBtn->setParent(this);
        MenuBtn->move(25 + (i%4)*70 , 130+ (i/4)*70);
        connect(MenuBtn,&MyPushButton::clicked,[=](){
            chooseSound->play();
            QString str=QString("choose %1").arg(i+1);
            qDebug()<<str;
            this->hide();
            play=new PlaySence(i+1);
            play->setGeometry(this->geometry());
            play->show();
            connect(play,&PlaySence::Win,[=](){
                emit this->WIn();
            });
            connect(play,&PlaySence::winback,[=](){
                emit this->MusicBcak();
            });


//            n=i;
//            connect(play,&PlaySence::WinNext,this,&ChooseLavelSence::winnext);
//            connect(play,&PlaySence::WinNext1,this,&ChooseLavelSence::winnext1);

            connect(play,&PlaySence::ChooseBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
                    });

                });


        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(MenuBtn->width(),MenuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25 + (i%4)*70 , 130+ (i/4)*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }


}
//void ChooseLavelSence::winnext()
//{
//     n=n+1;

//     play1=new PlaySence(n+1);
//     play1->show();
//     delete play;
//     play=NULL;
//    // connect(play,&PlaySence::WinNext1,this,&ChooseLavelSence::winnext1);
//}

//void ChooseLavelSence::winnext1()
//{
//     n=n+1;

//     play=new PlaySence(n+1);
//     play->show();
//     delete play1;
//     play1=NULL;


//     //connect(play,&PlaySence::WinNext,this,&ChooseLavelSence::winnext);


//}

void ChooseLavelSence::paintEvent(QPaintEvent * )
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);

}

