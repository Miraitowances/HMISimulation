#include "mainwindow.h"
#include <QApplication>



//#define  LoginSwitch_ON

#ifdef LoginSwitch_ON
#include "userlogin.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef LoginSwitch_ON
    #if SafeStareApp
        /*--------创建一个登录界面----------*/
        UserLogin QtLogin;
        MainWindow QtMain;

        QObject::connect(&QtLogin, SIGNAL(StareApplication()),
                     &QtMain,  SLOT(StareKeyDisplayHandle()));

        QtLogin.show();
        /*--------创建一个登录界面----------*/
    #else
        UserLogin QtLogin;
        QtLogin.show();
    #endif
#else
    MainWindow QtMain;
    QtMain.show();
#endif
    return a.exec();
}
