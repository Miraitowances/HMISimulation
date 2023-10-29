#ifndef EXTCONNECT_H
#define EXTCONNECT_H

#include <QObject>
#include "mainwindow.h"

class ExtConnect : public QObject
{
    Q_OBJECT
public:
     ExtConnect(MainWindow *parent = nullptr);
    ~ExtConnect();

private slots:
    void PBInfoInstructions(void);

};

#endif // EXTCONNECT_H
