#ifndef CHOOSELAVELSENCE_H
#define CHOOSELAVELSENCE_H

#include <QMainWindow>
#include"playsence.h"
class ChooseLavelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLavelSence(QWidget *parent = 0);
    //重写paintevent事件,画背景图
    void paintEvent(QPaintEvent * );
    PlaySence*play=NULL;
//    PlaySence*play1=NULL;
//    int n;
signals:
    void ChooseBack();
    void WIn();
    void MusicBcak();

public slots:
//   void winnext();
//   void winnext1();
};

#endif // CHOOSELAVELSENCE_H
