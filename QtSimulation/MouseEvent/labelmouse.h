#ifndef LABELMOUSE_H
#define LABELMOUSE_H

#include <QLabel>
#include <QWidget>
#include <QPoint>

class LabelMouse : public QLabel
{
    Q_OBJECT
public:
    explicit LabelMouse(QWidget *parent = nullptr);
    ~LabelMouse();

signals:
    void mainwindowInit(QPoint *point);
    void mianWindowsMove(QPoint point);

protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
};


#endif // LABELMOUSE_H
