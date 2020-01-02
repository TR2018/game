#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include<chooselavelsence.h>
#include"playsence.h"


namespace Ui {
class mainscene;
}

class mainscene : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainscene(QWidget *parent = 0);
    ~mainscene();
    //重写paintevent事件,画背景图
    void paintEvent(QPaintEvent * );



    ChooseLavelSence * ChooseSence=NULL;

private:
    Ui::mainscene *ui;
};

#endif // MAINSCENE_H
