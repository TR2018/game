#ifndef PLAYSENCE_H
#define PLAYSENCE_H

#include <QMainWindow>
#include"mycoin.h"

class PlaySence : public QMainWindow
{
    Q_OBJECT
public:
   PlaySence(int level);
   int levelIndex;
   void paintEvent(QPaintEvent * );
   int gameArray[4][4];
   MyCoin * CoinBtn[4][4];

   void change(int x,int y);

   bool Iswin;

signals:
  void ChooseBack();
  void Win();
  void winback();
//  void WinNext();
//  void WinNext1();


public slots:
};

#endif // PLAYSENCE_H
