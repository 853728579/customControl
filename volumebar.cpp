#include <qpainter.h>
#include "volumebar.h"
#include "ui_volumebar.h"

VolumeBar::VolumeBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeBar)
{
    value = 1;
    pillarNum = 5;
    gapSize = 5;
    minPillarHeight = 20;
    volumeWidth = 100;
    borderWidth = 3;

    borderColorStart = QColor(100, 100, 100);
    borderColorEnd = QColor(80, 80, 80);
    normalColorStart = QColor(50, 205, 51);
    normalColorEnd = QColor(60, 179, 133);

    ui->setupUi(this);
}

VolumeBar::~VolumeBar()
{
    delete ui;
}

void VolumeBar::paintEvent(QPaintEvent *)
{
    //创建一个绘画人
    QPainter painter(this);
    //反锯齿现象
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //绘制边框图形
    drawBorder(&painter);
    //绘制背景图形
    drawBg(&painter);
}

void VolumeBar::drawBorder(QPainter *painter)
{
    painter->save();

    int pillarWidth = (width() - borderWidth - (gapSize * (pillarNum - 1))) / pillarNum;

    slope = ((height()-minPillarHeight)*100)/(width()-pillarWidth);

    painter->setPen(QPen(borderColorStart, borderWidth));
    painter->setBrush(Qt::NoBrush);

    for (int index=0; index<pillarNum; index++)
    {
        int drawX = borderWidth + (pillarWidth + gapSize) * index;
        int pillarHeight = minPillarHeight + ((drawX * slope) / 100) - borderWidth;
        int drawY = height() - pillarHeight - borderWidth;

        painter->drawRect(drawX, drawY, pillarWidth, pillarHeight);
    }

    painter->restore();
}

void VolumeBar::drawBg(QPainter *painter)
{
    if ((value <= 0) || (value > pillarNum)){
        return ;
    }
    painter->save();

    QLinearGradient volumeGradient(QPointF(0, 0), QPointF(0, height()));
    volumeGradient.setColorAt(0.0, normalColorStart);

    painter->setPen(Qt::NoPen);
    painter->setBrush(volumeGradient);

    int pillarWidth = (width() - borderWidth - (gapSize * (pillarNum - 1))) / pillarNum;
    for (int index=0; index<value; index++)
    {
        int drawX = borderWidth + (pillarWidth + gapSize) * index;
        int pillarHeight = minPillarHeight- borderWidth + ((drawX * slope) / 100);
        int drawY = height() - pillarHeight - borderWidth;

        painter->drawRect(drawX, drawY, pillarWidth, pillarHeight);
    }

    painter->restore();
}

int VolumeBar::getValue() const
{
    return this->value;
}

void VolumeBar::setValue(int value)
{
    if (value == this->value){
        return ;
    }

    if (value < 0)
        value = 0;

    if (value > pillarNum)
        value = pillarNum;

    this->value = value;
    this->update();

    emit valueChanged(value);
}


