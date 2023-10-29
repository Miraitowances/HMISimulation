#include "screendispaly.h"
#include "ui_screendispaly.h"
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include "extcfunction.h"



QLabel *extShowDisplaySpet = nullptr;
ScreenDispaly::ScreenDispaly(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenDispaly)
{
    ui->setupUi(this);
    extShowDisplaySpet = ui->ShowDisplay;

    CurntDisplay = new QTimer();
    CurntDisplay->setInterval(20); //大约20ms跟新一次可以根据实际情况
    connect(CurntDisplay, SIGNAL(timeout()), this, SLOT(CurrentDisplay_UpdataFunction()));
    CurntDisplay->start();

    this->setMouseTracking(true);
}

ScreenDispaly::~ScreenDispaly()
{
    delete ui;
}

#include <QLineEdit>
#include "externevent.h"
unsigned char flag = 0;
extern QLineEdit *DigitalTipsSprt;
typedef struct
{
    quint32 _Mouse_X;
    quint32 _Mouse_Y;
}MouseEventTypedef;
MouseEventTypedef _Mouse_info;

void ScreenDispaly::mousePressEvent(QMouseEvent *event)
{
    _Mouse_info._Mouse_X=event->position().x();
    _Mouse_info._Mouse_Y=event->position().y();
    _Mouse_info._Mouse_X *= (WScreen / 960.0f);
    _Mouse_info._Mouse_Y *= (HScreen / 540.0f);

    if(_Mouse_info._Mouse_X > 0 && _Mouse_info._Mouse_Y > 0)
    {
        DigitalTipsSprt->setText(QString("X:%1 Y:%2  (%3,%4)") \
                                     .arg(_Mouse_info._Mouse_X)                 \
                                     .arg(_Mouse_info._Mouse_Y)                 \
                                     .arg(_Mouse_info._Mouse_X)                 \
                                     .arg(_Mouse_info._Mouse_Y)
                                 );
    }
}


#define RGB565_RED      0xf800
#define RGB565_GREEN    0x07e0
#define RGB565_BLUE     0x001f
#include "externevent.h"
extern QLabel *extLastDisplaySprt;
int LastScreen[HScreen][WScreen] = {0};
int pLastScreen[HScreen][WScreen] = {0};
void ScreenDispaly::CurrentDisplay_UpdataFunction()
{
    Implement_extcfunction();
    if(ImitateUpdataFlag)
    {
        QImage images = QImage((unsigned char*)pLastScreen,WScreen,HScreen,QImage::Format_RGB32);
        extLastDisplaySprt->setPixmap(QPixmap::fromImage(images));

        QImage screens = QImage(WScreen, HScreen, QImage::Format_RGB32);
        int n888Color, cRed, cGreen, cBlue;
        for(int i = 0; i < WScreen; i++)
        {
            for(int j = 0; j < HScreen; j++)
            {
                cRed   = (_ImitScreen.Screen[j][i] & RGB565_RED)    << 8;
                cGreen = (_ImitScreen.Screen[j][i] & RGB565_GREEN)  << 5;
                cBlue  = (_ImitScreen.Screen[j][i] & RGB565_BLUE)   << 3;
                n888Color = cRed | cGreen | cBlue ;
                screens.setPixel(i,j,n888Color);
                pLastScreen[j][i] = LastScreen[j][i];
                LastScreen[j][i] = n888Color;
            }
        }
        ui->ShowDisplay->setPixmap(QPixmap::fromImage(screens));
        ImitateUpdataFlag = 0;
    }
}
