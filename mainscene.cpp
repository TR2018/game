#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QSound>
mainscene::mainscene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainscene)
{
    ui->setupUi(this);
    //配置主场景
    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/da.jpeg"));
    //设置标题
    setWindowTitle("翻金币");
    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);
    QSound *bgm = new QSound(":/res/teacher.wav",this);
    bgm->play();
    bgm->setLoops(-1);



    //设置开始按钮
    MyPushButton  * startbtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);

    ChooseSence=new ChooseLavelSence();
    connect(ChooseSence,&ChooseLavelSence::ChooseBack,[=](){
        this->setGeometry(ChooseSence->geometry());
        ChooseSence->hide();

        this->show();
    });
    connect(ChooseSence,&ChooseLavelSence::WIn,[=](){
        bgm->stop();
    });
    connect(ChooseSence,&ChooseLavelSence::MusicBcak,[=](){
        bgm->play();
        bgm->setLoops(-1);
    });

    connect(startbtn,&MyPushButton::clicked,[=](){

        startSound->play();
        startbtn->zoom1();
        startbtn->zoom2();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            ChooseSence->setGeometry(this->geometry());
            ChooseSence->show();
        });

    });
}


void mainscene::paintEvent(QPaintEvent * )
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
   painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
    painter.drawPixmap(10,30,pix);
    //    pix.load(":/res/wz.jpg");
    //    painter.drawPixmap(60,150,200,200,pix);



}


mainscene::~mainscene()
{
    delete ui;
}

