#ifndef EXTERNEVENT_H
#define EXTERNEVENT_H

#include <QWidget>
//#include <QKeyEvent>
namespace Ui {
class ExternEvent;
}

class ExternEvent : public QWidget
{
    Q_OBJECT

public:
    explicit ExternEvent(QWidget *parent = nullptr);
    ~ExternEvent();

private slots:
    void on_PB_EXCEL_Color_clicked();

    void on_PB_IMAGE_Change_clicked();

    void on_PB_Squart_clicked();

    void on_PB_Tool_P2L_clicked();

    void on_PB_ConnectUser_clicked();

    void on_fastPB_ConnectUser_clicked();

    void on_GentCode_clicked();

private:
    Ui::ExternEvent *ui;
};

#endif // EXTERNEVENT_H
