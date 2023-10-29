#include "userlogin.h"
#include "ui_userlogin.h"



#include <QPainter>
#include <QStyleOption>
#include <QMessageBox>

#if !SafeStareApp
    #include "mainwindow.h"
#endif

#define  InputName      "Miraitowance"
#define  InputPawd      "ws181413"

UserLogin::UserLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserLogin)
{
    ui->setupUi(this);
    this->setWindowTitle("LOGIN");
    this->setWindowIcon(QIcon(":/Other/18.png"));
    this->setFixedSize(500,400);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->Password->setEchoMode(QLineEdit::Password);
}

UserLogin::~UserLogin()
{
    delete ui;
}

void UserLogin::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void UserLogin::on_PB_Exit_clicked()
{
    qApp->quit();
}

void UserLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isPressedWidget = true;
        last = event->globalPosition().toPoint();
    }
}

void UserLogin::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget)
    {
        QPoint distance = event->globalPosition().toPoint() - last;
        last = event->globalPosition().toPoint();
        this->move(pos() + distance);
    }
}

void UserLogin::mouseReleaseEvent(QMouseEvent *event)
{
    if(isPressedWidget)
    {
        QPoint distance = event->globalPosition().toPoint() - last;
        this->move(pos() + distance);
        isPressedWidget = false;
    }
}

void UserLogin::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            {
                if(ui->Authour->text() == InputName && ui->Password->text() == InputPawd)
                {
                    #if !SafeStareApp
                                this->close();
                                MainWindow *QtMain = new MainWindow;
                                QtMain->show();
                    #else
                                this->close();
                                emit this->StareApplication();
                    #endif
                }else{
                    QMessageBox::warning(this,tr("登录失败"),tr("用户名或密码输入错误！"),QMessageBox::Ok);
                    ui->Authour->clear();
                    ui->Password->clear();
                    ui->Authour->setFocus();
                }
            }
            break;
        default:
            break;
    }
}


void UserLogin::on_PB_Login_clicked()
{
    if(ui->Authour->text() == InputName && ui->Password->text() == InputPawd)
    {
        #if !SafeStareApp
            this->close();
            MainWindow *QtMain = new MainWindow;
            QtMain->show();
        #else
            this->close();
            emit this->StareApplication();
        #endif
    }
    else
    {
        QMessageBox::warning(this,tr("登录失败"),tr("用户名或密码输入错误！"),QMessageBox::Ok);
        ui->Authour->clear();
        ui->Password->clear();
        ui->Authour->setFocus();
    }
}

