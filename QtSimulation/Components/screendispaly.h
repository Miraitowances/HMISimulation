#ifndef SCREENDISPALY_H
#define SCREENDISPALY_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
namespace Ui {
class ScreenDispaly;
}

class ScreenDispaly : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenDispaly(QWidget *parent = nullptr);
    ~ScreenDispaly();

    void mousePressEvent(QMouseEvent *event);


private slots:
    void CurrentDisplay_UpdataFunction(void);


private:
    Ui::ScreenDispaly *ui;

    QTimer *CurntDisplay;
};

#endif // SCREENDISPALY_H
