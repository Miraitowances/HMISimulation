#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QWidget>

#include <QPoint>
#include <QMouseEvent>
#include <QKeyEvent>

#define Main_ON         0
#define Main_OFF        1
#define SafeStareApp    Main_ON

namespace Ui {
class UserLogin;
}

class UserLogin : public QWidget
{
    Q_OBJECT

public:
    explicit UserLogin(QWidget *parent = nullptr);
    ~UserLogin();
signals:
    void StareApplication(void);
protected:
    virtual void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_PB_Exit_clicked();

    void on_PB_Login_clicked();

private:
    Ui::UserLogin *ui;

    bool isPressedWidget;
    QPoint last;
};

#endif // USERLOGIN_H
