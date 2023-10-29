#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QStyleOption>
#include <QMenu>
#include <QSystemTrayIcon>

#include "extconnect.h"
#include "extcfunction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Miraitowance");
    this->setWindowIcon(QIcon(":/Other/18.png"));
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(1200,800));
    this->MainWindowSystemTray();

    connect(ui->HeadTitle,SIGNAL(mainwindowInit(QPoint*)),
            this, SLOT(MainWindowInitHandle(QPoint*)));

    connect(ui->HeadTitle,SIGNAL(mianWindowsMove(QPoint)),
            this, SLOT(MainWindowMoveHandle(QPoint)));

    ExtConnect *Econnect = new ExtConnect(this);
    QPushButton *Instruct = ui->Exevent->findChild<QPushButton*>("Instructions");
    connect(Instruct,SIGNAL(clicked()),Econnect,SLOT(PBInfoInstructions()));

    InitConfig_extcfunction();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_HeadPBCls_clicked()
{
    qApp->quit();
}


void MainWindow::on_HeadPBMIn_clicked()
{
    this->showMinimized();
}

void MainWindow::MainWindowMoveHandle(QPoint point)
{
    this->move(point);
}

void MainWindow::MainWindowInitHandle(QPoint *point)
{
    *point = this->frameGeometry().topLeft();
}


void MainWindow::on_HeadHide_clicked()
{
    this->hide();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void MainWindow::MainWindowSystemTray(void)
{
    QSystemTrayIcon *m_systemTray = new QSystemTrayIcon(this);
    m_systemTray->setToolTip(QString("Miraitowance"));
    m_systemTray->setIcon(QIcon(":/Other/18.png"));

    myMenu = new QMenu(this);

    showWidget =    new QAction(tr("显示窗口 "),     this);
    minWidget =     new QAction(tr("隐藏窗口 "),     this);
    InfoSoftWare =  new QAction(tr("Miraitowance"), this);
    exitSoftWare =  new QAction(tr("退出软件 "),     this);

    myMenu->addAction(showWidget);
    myMenu->addSeparator();
    myMenu->addAction(minWidget);
    myMenu->addSeparator();
    myMenu->addAction(InfoSoftWare);
    myMenu->addSeparator();
    myMenu->addAction(exitSoftWare);

    m_systemTray->setContextMenu(myMenu);

    connect(exitSoftWare, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(showWidget,   SIGNAL(triggered(bool)), this, SLOT(showNormal()));
    connect(minWidget,    SIGNAL(triggered(bool)), this, SLOT(hide()));
    connect(m_systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    m_systemTray->show();
}

//#define         InterruptMode

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    #ifdef InterruptMode

    if(event->isAutoRepeat() == false)
    {
        _ImitateKey.ImitateKey_Up = 0;
        //模拟中断 当进入中断之后入栈 然后自锁可以直接关掉中断
        switch(event->key())
        {
            case Qt::Key_W:
//                _ImitateKey.ImitateKey_Up = 0; //模拟GPIO
                KeyPushQueen_HMIPushButton(HMIPB_KEYUP);
                break;
            case Qt::Key_S:
//                _ImitateKey.ImitateKey_Dn = 0;
                KeyPushQueen_HMIPushButton(HMIPB_KEYDN);
//                qDebug() << "HMIPB_KEYDN";
                break;
            case Qt::Key_A:
//                _ImitateKey.ImitateKey_LE = 0;
                KeyPushQueen_HMIPushButton(HMIPB_KEYLE);
                break;
            case Qt::Key_D:
//                _ImitateKey.ImitateKey_RD = 0;
                KeyPushQueen_HMIPushButton(HMIPB_KEYRD);
                break;
            case Qt::Key_E:
//                _ImitateKey.ImitateKey_SG = 0;
                KeyPushQueen_HMIPushButton(HMIPB_KEYSG);
                break;
            default:
                break;
        }
    }
    #elif 1
    if(event->isAutoRepeat() == false)
    {
//        qDebug() << "input keyvalue";
        switch(event->key())
        {
            case Qt::Key_W:
                GPIOLimitateIO[HMIPB_KEYUP] = 0;
                pxListInsertEnd_HMIPushButton(HMIPB_KEYUP);
                break;
            case Qt::Key_S:
                GPIOLimitateIO[HMIPB_KEYDN] = 0;
                pxListInsertEnd_HMIPushButton(HMIPB_KEYDN);
                break;
            case Qt::Key_A:
                GPIOLimitateIO[HMIPB_KEYLE] = 0;
                pxListInsertEnd_HMIPushButton(HMIPB_KEYLE);
                break;
            case Qt::Key_D:
                GPIOLimitateIO[HMIPB_KEYRD] = 0;
                pxListInsertEnd_HMIPushButton(HMIPB_KEYRD);
                break;
            case Qt::Key_E:
                GPIOLimitateIO[HMIPB_KEYSG] = 0;
                pxListInsertEnd_HMIPushButton(HMIPB_KEYSG);
                break;
            default:
                break;
        }
    }
    #else

    if(event->isAutoRepeat() == false)
    {
        qDebug() << "keyPressEvent";
        switch(event->key())
        {
            case Qt::Key_W:
                _ImitateKey.ImitateKey_Up = 0;
                break;
            case Qt::Key_S:
                _ImitateKey.ImitateKey_Dn = 0;
                break;
            case Qt::Key_A:
                _ImitateKey.ImitateKey_LE = 0;
                break;
            case Qt::Key_D:
                _ImitateKey.ImitateKey_RD = 0;
                break;
            case Qt::Key_E:
                _ImitateKey.ImitateKey_SG = 0;
                break;
            default:
                break;
        }
    }
    #endif
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

    #ifdef InterruptMode

    if(event->isAutoRepeat() == false)
    {
        _ImitateKey.ImitateKey_Up = 1;

    }

#elif 1
    if(event->isAutoRepeat() == false)
    {
       
        switch(event->key())
        {
            case Qt::Key_W:
//                    qDebug() << "output HMIPB_KEYUP";
                    GPIOLimitateIO[HMIPB_KEYUP] = 1;
                    // pxListDelectEle_HMIPushButton(HMIPB_KEYUP);
                    break;
            case Qt::Key_S:
//                    qDebug() << "output HMIPB_KEYDN";
                    GPIOLimitateIO[HMIPB_KEYDN] = 1;
                    // pxListDelectEle_HMIPushButton(HMIPB_KEYDN);
                    break;
            case Qt::Key_A:
//                    qDebug() << "output HMIPB_KEYLE";
                    GPIOLimitateIO[HMIPB_KEYLE] = 1;
                    // pxListDelectEle_HMIPushButton(HMIPB_KEYLE);
                    break;
            case Qt::Key_D:
//                    qDebug() << "output HMIPB_KEYRD";
                    GPIOLimitateIO[HMIPB_KEYRD] = 1;
                    // pxListDelectEle_HMIPushButton(HMIPB_KEYRD);
                    break;
            case Qt::Key_E:
//                    qDebug() << "output HMIPB_KEYSG";
                    GPIOLimitateIO[HMIPB_KEYSG] = 1;
                    // pxListDelectEle_HMIPushButton(HMIPB_KEYSG);
                    break;
            default:
                    break;
        }
    }
    #else
    if(event->isAutoRepeat() == false)
    {
         qDebug() << "keyReleaseEvent";
        switch(event->key())
        {
            case Qt::Key_W:
                    _ImitateKey.ImitateKey_Up = 1;
                    break;
            case Qt::Key_S:
                    _ImitateKey.ImitateKey_Dn = 1;
                    break;
            case Qt::Key_A:
                    _ImitateKey.ImitateKey_LE = 1;
                    break;
            case Qt::Key_D:
                    _ImitateKey.ImitateKey_RD = 1;
                    break;
            case Qt::Key_E:
                    _ImitateKey.ImitateKey_SG = 1;
                    break;
            default:
                    break;
        }
    }
    #endif
}


void MainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
        case QSystemTrayIcon::Trigger:
            this->show();
            break;
        case QSystemTrayIcon::DoubleClick:
            this->showNormal();
            break;
        default:
            break;
        }
}

void MainWindow::StareKeyDisplayHandle()
{
    this->show();
}


