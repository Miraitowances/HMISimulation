#include "extconnect.h"

#include <QLabel>
#include <QDebug>
#include <QTextEdit>
#include <QMessageBox>

#include "externevent.h"
#include "information.h"
#include "screendispaly.h"


extern QLabel    *extLastDisplaySprt;
extern QTextEdit *extctrlsprt;
extern QLabel    *extShowDisplaySpet;

QWidget *parentsprt = nullptr;

ExtConnect::ExtConnect(MainWindow *parent) : QObject(parent)
{
    parentsprt = static_cast<QWidget *>(parent);

}

ExtConnect::~ExtConnect()
{

}

void ExtConnect::PBInfoInstructions(void)
{
    QMessageBox::information(parentsprt,tr("-_0.0_~Instructions"),
                             tr("@Authour   Miraitowance/Mirawance\n"
                                "@Function  help development MUI!"),
                             QMessageBox::Ok,
                             QMessageBox::Ok);
}
