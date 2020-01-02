#include "playsence.h"
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"dataconfig.h"
#include<QDebug>
#include<QPropertyAnimation>
#include<QSound>

void PlaySence::change(int x,int y)
{
    if(x+1<=3)
    {
        CoinBtn[x+1][y]->ChangeFlag();
        this->gameArray[x+1][y]= this->gameArray[x+1][y]==0 ? 1:0;
    }
    if(y+1<=3)
    {
        CoinBtn[x][y+1]->ChangeFlag();
        this->gameArray[x][y+1]= this->gameArray[x][y+1]==0 ? 1:0;
    }
    if(x-1>=0)
    {
        CoinBtn[x-1][y]->ChangeFlag();
        this->gameArray[x-1][y]= this->gameArray[x-1][y]==0 ? 1:0;
    }
    if(y-1>=0)
    {
        CoinBtn[x][y-1]->ChangeFlag();
        this->gameArray[x][y-1]= this->gameArray[x][y-1]==0 ? 1:0;
    }
}

PlaySence::PlaySence(int level)
{
    this->levelIndex=level;
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QIcon(":/res/da.jpeg"));
    //设置标题
    this->setWindowTitle("翻金币");
    //设置菜单栏
    QMenuBar*bar=menuBar();
    setMenuBar(bar);
    QMenu *startmenu= bar->addMenu("开始");
    QAction*quitAction=startmenu->addAction("退出");
    //退出按钮实现
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //加音效
    //返回按钮音效
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/win.wav",this);

    MyPushButton *backbtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->move(this->width()-backbtn->width(),this->height()-backbtn->height());

    connect(backbtn,&MyPushButton::clicked,[=](){
        backSound->play();
        QTimer::singleShot(500,this,[=](){
              emit this->ChooseBack();

        });
    });
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str1 = QString("Leavel:%1").arg(this->levelIndex);
    label->setText(str1);
    label->setGeometry(QRect(30, this->height() - 50,125, 50));



    dataConfig coinfig;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=coinfig.mData[this->levelIndex][i][j];
        }
    }

    QLabel* winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());


    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel * label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);

            QString str;
            if(this->gameArray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                str=":/res/Coin0008.png";
            }
            MyCoin * coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posx=i;
            coin->posy=j;
            coin->flag=this->gameArray[i][j];
            CoinBtn[coin->posx][coin->posy]=coin;
            connect(coin,&MyCoin::clicked,[=](){
                flipSound->play();
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        this->CoinBtn[i][j]->CoinWin=true;
                    }
                }
                coin->ChangeFlag();
                this->gameArray[i][j]= this->gameArray[i][j]==0 ? 1:0;
                QTimer::singleShot(300,this,[=](){
                    change(coin->posx,coin->posy);
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            this->CoinBtn[i][j]->CoinWin=false;
                        }
                    }

                    this->Iswin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(CoinBtn[i][j]->flag==0)
                            {
                                this->Iswin=false;
                                break;
                            }
                        }
                    }
                    if(this->Iswin==true)
                    {

                        winSound->play();
                        winSound->setLoops(-1);
                        emit this->Win();
//                        if(level%2==0)
//                        {
//                            QTimer::singleShot(500,this,[=](){
//                                //emit this->winback();
//                                //emit this->WinNext1();
//                                emit this->WinNext();
//                                winSound->stop();
//                             });
//                        }
//                        else
//                        {
//                            QTimer::singleShot(500,this,[=](){
//                                //emit this->winback();
//                                emit this->WinNext1();

//                                winSound->stop();
//                             });
//                             }



                        connect(backbtn,&MyPushButton::clicked,[=](){
                            emit this->winback();
                        });
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                CoinBtn[i][j]->CoinWin=true;
                            }
                        }
                        QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();

                    }


                });


            });
        }
    }
}

void PlaySence::paintEvent(QPaintEvent * )
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);




    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);
}



