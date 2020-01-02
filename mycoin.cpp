#include "mycoin.h"
#include<QDebug>

MyCoin::MyCoin(QString btnIng)
{
    QPixmap pix;
    bool ref=pix.load(btnIng);
    if(!ref)
    {
        QString str=QString("图片%1加载失败").arg(btnIng);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    time1=new QTimer(this);
    time2=new QTimer(this);
    connect(time1,&QTimer::timeout,[=](){
        QString str;
        str=QString(":/res/Coin000%1.png").arg(this->min++);
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>8)
        {
            this->min=1;
            IsAnimation=false;
            time1->stop();
        }
    });

    connect(time2,&QTimer::timeout,[=](){
        QString str;
        str=QString(":/res/Coin000%1.png").arg(this->max--);
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max<1)
        {
            this->max=8;
            IsAnimation=false;
            time2->stop();
        }
    });

}
 void MyCoin::mousePressEvent(QMouseEvent *e)
 {
     if(this->IsAnimation||this->CoinWin)
     {
         return;
     }
     else
     {
         QPushButton::mousePressEvent(e);
     }
 }

 void MyCoin::ChangeFlag()
 {
     if(this->flag)
     {
         time1->start(30);
         IsAnimation=true;
         this->flag=0;
     }
     else
     {
         time2->start(30);
         IsAnimation=true;
         this->flag=1;
     }

 }



