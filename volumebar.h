#ifndef VOLUMEBAR_H
#define VOLUMEBAR_H

#include <QWidget>

namespace Ui {
class VolumeBar;
}

class VolumeBar : public QWidget
{
    Q_OBJECT
    //Q_PROPERTY是一个宏，用来在一个类中声明一个属性property
    //1.必须有一个read函数
    //2.有一个可选的write函数
    Q_PROPERTY(double value READ getValue WRITE setValue)

public:
    explicit VolumeBar(QWidget *parent = nullptr);
    ~VolumeBar();

protected:
    //protected对于子女、朋友来说，就是public的，可以自由使用，没有任何限制，而对于其他的外部class，protected就变成private
    void paintEvent(QPaintEvent *);      //绘画事件，由系统调用，可通过update()函数进行更新
    void drawBorder(QPainter *painter);  //绘制边框
    void drawBg(QPainter *painter);

private:
    Ui::VolumeBar *ui;

    int value;                      //目标值
    int pillarNum;                  //柱形的个数

    int gapSize;                    //每个柱形的间隔大小
    int minPillarHeight;            //最低柱形高度
    int volumeWidth;                //整个控件的宽度
    int borderWidth;                //边框粗细

    int slope;                      //斜率

    QColor borderColorStart;        //边框渐变开始颜色
    QColor borderColorEnd;          //边框渐变结束颜色

    QColor normalColorStart;        //渐变开始颜色
    QColor normalColorEnd;          //渐变结束颜色
public:
    int getValue()          const;

public Q_SLOTS:
    void setValue(int value);

Q_SIGNALS:
    void valueChanged(int value);
};

#endif // VOLUMEBAR_H
