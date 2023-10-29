#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QSystemTrayIcon>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void MainWindowSystemTray(void);

    void keyPressEvent(QKeyEvent *event); //键盘按下事件
    void keyReleaseEvent(QKeyEvent *event); //键盘松开事件

protected:
    virtual void paintEvent(QPaintEvent *event) override;
signals:
//    void MainDebugUpdata(void);
private slots:
    void on_HeadPBCls_clicked();
    void on_HeadPBMIn_clicked();
    void on_HeadHide_clicked();

    void MainWindowMoveHandle(QPoint point);
    void MainWindowInitHandle(QPoint *point);
    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void StareKeyDisplayHandle(void);
private:
    Ui::MainWindow *ui;
    QMenu *myMenu;
    QAction* showWidget;
    QAction* minWidget;
    QAction* InfoSoftWare;
    QAction* exitSoftWare;
};



#endif // MAINWINDOW_H
