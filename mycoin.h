#ifndef MYCOIN_H
#define MYCOIN_H
#include<QTimer>

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnIng);
    int posx;
    int posy;
    bool flag;
    QTimer * time1;
    QTimer * time2;
    int min=1;
    int max=8;
    bool IsAnimation=false;

    bool CoinWin=false;

    void ChangeFlag();
    void mousePressEvent(QMouseEvent *e);



signals:

public slots:
};

#endif // MYCOIN_H
