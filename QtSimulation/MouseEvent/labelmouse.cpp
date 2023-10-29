#include "labelmouse.h"

#include <QDebug>
#include <QMouseEvent>


LabelMouse::LabelMouse(QWidget *parent)
{
    m_bDrag = false;
    this->setParent(parent);
}

LabelMouse::~LabelMouse()
{

}

void LabelMouse::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //获得鼠标的初始位置
        mouseStartPoint = event->globalPosition().toPoint();
        emit this->mainwindowInit(&windowTopLeftPoint);
        m_bDrag = true;
    }
}

void LabelMouse::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
        QPoint distance = event->globalPosition().toPoint() - mouseStartPoint;
        QPoint move = windowTopLeftPoint + distance;
        emit this->mianWindowsMove(move);
    }

}

void LabelMouse::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}


