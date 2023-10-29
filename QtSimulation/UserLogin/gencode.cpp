#include "gencode.h"
#include "ui_gencode.h"

#include <QFileDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileInfo>
#include <QRegularExpression>
#include <QValidator>
#include <QDesktopServices>
GenCode::GenCode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GenCode)
{
    ui->setupUi(this);
    this->setFixedSize(466,300);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("Output");
    ui->FileName->installEventFilter(this);
    ui->PathEdit->installEventFilter(this);
    ui->Function->installEventFilter(this);
    static QRegularExpression inputre("([a-zA-Z0-9]|_)+$");
    ui->FileName->setValidator(new QRegularExpressionValidator(inputre));
    connect(this,SIGNAL(AcquarePath_SignalFunc()),this,SLOT(AcquarePath_HandleFunc()));
    connect(this,SIGNAL(AcquareFunc_SignalFunc()),this,SLOT(AcquareFunc_HandleFunc()));
}

GenCode::~GenCode()
{
    delete ui;
}

bool GenCode::eventFilter(QObject *obj, QEvent *event)
{
    QMouseEvent *mouseevent=(QMouseEvent *)event;

    if(obj == ui->PathEdit && event->type() == QEvent::MouseButtonPress)
    {
        if(mouseevent->button() == Qt::LeftButton)
        {
            emit this->AcquarePath_SignalFunc();
            return true;
        }
        return false;
    }

    if(obj == ui->FileName && event->type() == QEvent::MouseButtonPress)
    {
        if(mouseevent->button() == Qt::LeftButton)
        {
            ui->FileName->clear();
            return true;
        }
        return false;

    }
    else if(obj == ui->FileName && event->type() == QEvent::FocusOut)
    {
        if(ui->FileName->text().isEmpty())
        {
            ui->FileName->setText("输入名称");
            return true;
        }
        return false;

    }

    if(obj == ui->Function && event->type() == QEvent::MouseButtonPress)
    {
        if(mouseevent->button() == Qt::LeftButton)
        {
            emit this->AcquareFunc_SignalFunc();
            return true;
        }
        return false;
    }

    return QWidget::eventFilter(obj,event);
}

void GenCode::AcquarePath_HandleFunc()
{
    path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "../",
                                                QFileDialog::ShowDirsOnly);

    if(path.isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        ui->PathEdit->setText("选择路径");
    }
    else
    {
        QFileInfo fileinfo(path);
        ui->PathEdit->setText(fileinfo.baseName());
    }
}

void GenCode::AcquareFunc_HandleFunc()
{
    func = QFileDialog::getOpenFileName(this, tr("open file"),"../",tr("Text files (*.gs)"));
    if(func.isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败"));
        ui->Function->setText("导入文件");
        return;
    }
    QFileInfo fileinfo(func);
    ui->Function->setText(fileinfo.fileName());
}

void GenCode::on_FileName_returnPressed()
{
    if(path.isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("请先设置路径"));
        return;
    }

    filename = ui->FileName->text();
    if(filename.isEmpty())
    {
        ui->FileName->setText("输入名称");
        QMessageBox::critical(this,tr("错误"),tr("请输入有效的数据"));
        return;
    }

    if(filename.left(1) >= '0' && filename.left(1) <= '9')
    {
        filename = NULL;
        ui->FileName->setText("输入名称");
        QMessageBox::critical(this,tr("错误"),tr("请输入有效不能以数字开头"));
        return;
    }
}

#include <QRegularExpressionMatch>
void GenCode::on_Output_clicked()
{
    if(path.isEmpty())
    {
        ui->PathEdit->setText("选择路径");
        QMessageBox::critical(this,tr("错误"),tr("路径为空"));
        return;
    }
    static QRegularExpression reg("(^//.|^/|^[a-zA-Z])?:?/.+(/$)?");
    QRegularExpressionMatch match = reg.match(path);
    if(!match.hasMatch())
    {
        ui->PathEdit->setText("选择路径");
        QMessageBox::critical(this,tr("错误"),tr("路径错误，重新选择"));
        return;
    }

    filename = ui->FileName->text();

    if(filename.isEmpty())
    {
        ui->FileName->setText("输入名称");
        QMessageBox::critical(this,tr("错误"),tr("请输入有效的数据"));
        return;
    }

    if(filename.left(1) >= '0' && filename.left(1) <= '9')
    {
        filename = NULL;
        ui->FileName->setText("输入名称");
        QMessageBox::critical(this,tr("错误"),tr("请输入有效不能以数字开头"));
        return;
    }

    if(func.isEmpty())
    {
        QString outfileh = path + '/' + filename + ".h";
        QFile filesprth(outfileh);


        if(!filesprth.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QMessageBox::critical(this,tr("错误"),tr(".h文件打开失败"));
            return ;
        }

        QString outfilec = path + '/' + filename + ".c";
        QFile filesprtc(outfilec);

        if(!filesprtc.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QMessageBox::critical(this,tr("错误"),tr(".c文件打开失败"));
            return ;
        }
        QTextStream outh(&filesprth);
        QTextStream outc(&filesprtc);

        //-----------------------------------------------------------------------
        outh << "\r\n";
        outh << "\r\n";
        outh << "\r\n";
        outh << "/*********************************";
        outh << "\n";
        outh << " * @Authour:Miraitowance/Miraitowa*";
        outh << "\n";
        outh << " * @Function:鲸落の入海 ~(_0.0_)- *";
        outh << "\n";
        outh << " ********************************/";
        outh << "\r\n";
        outh << "\r\n";
        outh << "#ifndef __" + filename + "_H_";
        outh << "\n";
        outh << "#define __" + filename + "_H_";
        outh << "\n";
        outh << "\n";
        outh << "//-------------------------INCLUDE-------------------------";
        outh << "\n";
        outh << "#include \"HMIDispScreen.h\"";
        outh << "\n";
        outh << "//-------------------------INCLUDE-------------------------";
        outh << "\r\n";
        outh << "//-------------------------DEFINE--------------------------";
        outh << "\n";
        outh << "#define        HMI"+filename+"Functions            0";
        outh << "\r\n";
        outh << "//-------------------------DEFINE--------------------------";
        outh << "\r\n";
        outh << "//-------------------------FUNCTION------------------------";
        outh << "\r\n";
        outh << "void           "+filename+"Function_HandlesFunction        (void);";
        outh << "\n";
        outh << "void           "+filename+"Function_DisplayFunction        (void);";
        outh << "\r\n";
        outh << "//-------------------------FUNCTION------------------------";
        outh << "\r\n";
        outh << "#endif /*_@Authour:Miraitowance/Miraitowa*/";
        outh << "\r\n";
        outh << "\r\n";
        outh << "\r\n";
        //---------------------------------------------------------------------
        outc << "\r\n";
        outc << "\r\n";
        outc << "\r\n";
        outc << "/*********************************";
        outc << "\n";
        outc << " * @Authour:Miraitowance/Miraitowa*";
        outc << "\n";
        outc << " * @Function:鲸落の入海 ~(_0.0_)- *";
        outc << "\n";
        outc << " ********************************/";
        outc << "\r\n";
        outc << "#include \"" +filename +".h\"";
        outc << "\r\n";
        outc << "//-------------------------INCLUDE-------------------------";
        outc << "\n";
        outc << "#include \"DriveFunction.h\"";
        outc << "\n";
        outc << "#include \"ImitateFunction.h\"";
        outc << "\n";
        outc << "#include \"HMIPushButton.h\"";
        outc << "\n";
        outc << "#include \"FontFunction.h\"";
        outc << "\n";
        outc << "#include \"FImageFunction.h\"";
        outc << "\n";
        outc << "//-------------------------INCLUDE-------------------------";
        outc << "\r\n";
        outc << "//-------------------------DEFINE--------------------------";
        outc << "\n";
        outc << "#ifdef         HMITaskFunctions\n";
        outc << "#undef         HMITaskFunctions\n";
        outc << "#endif\n";
        outc << "#define        HMITaskFunctions        ";
        outc << "(HMI" + filename + "Functions)";
        outc << "\r\n";
        outc << "#ifdef         _HMITaskMinIndex\n";
        outc << "#undef         _HMITaskMinIndex\n";
        outc << "#endif\n";
        outc << "#ifdef         _HMITaskMaxIndex\n";
        outc << "#undef         _HMITaskMaxIndex\n";
        outc << "#endif\n";
        outc << "\n";
        outc << "#define        _HMITaskMinIndex        0\n";
        outc << "#define        _HMITaskMaxIndex        0\n";
        outc << "//-------------------------DEFINE--------------------------";
        outc << "\r\n";
        outc << "//-------------------------EXTERN--------------------------\n";
        outc << "extern _HMIDispScreen_HMITasksSchedule_Struct TaskSchedule[HMIScrTaskNumber];\n";
        outc << "//-------------------------EXTERN--------------------------\n";
        outc << "//-------------------------VARIABLE------------------------\n";
        outc << "\r\n";
        outc << "//-------------------------VARIABLE------------------------\n";
        outc << "//-------------------------NOTICE--------------------------\n";
        outc << "/***************************************************************************************\n";
        outc << " * @_HMIDispTool.tasksprt                       Function: 页面指针\n";
        outc << " * @_HMIDispTool.dpstatus                       Function：控制是否刷新屏幕开关\n";
        outc << " * @_HMIDispTool.extevent                       Function：触发的按键处理事件\n";
        outc << " * @_HMIDispTool.rfstatus                       Function: 刷新方式 关闭 循环 触发 全刷\n";
        outc << " * @TaskSchedule[HMITaskFunctions].Select       Function: 选择状态 选择 选中 NULL\n";
        outc << " * @TaskSchedule[HMITaskFunctions].TaskSerial   Function: 当前任务下的引导变量\n";
        outc << " * @TaskSchedule[HMITaskFunctions].LastSerial   Function: 记录任务下的引导变量\n";
        outc << " ***************************************************************************************/\n";
        outc << "//-------------------------NOTICE--------------------------\n";
        outc << "//-------------------------FUNCTION------------------------";
        outc << "\r\n";
        outc << "void "+filename+"Function_HandlesFunction(void)\n";
        outc << "{\n";
        outc << "   _HMIDispTool.dpstatus = _HMIScreenStatus_SHOW;\n";
        outc << "   /*  @Note:  If you don't want to refresh the screen.\n";
        outc << "               you can close it under this function _HMIScreenStatus_CLOS*/\n";
        outc << "   switch (_HMIDispTool.extevent)\n";
        outc << "   {\n";
        outc << "       case _HMIPushButtonEvt_PBUP:\n";
        outc << "           if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_SELECT)\n";
        outc << "           {\n";
        outc << "                   /*Add user functions here*/\r\n";
        outc << "           }\n";
        outc << "           else if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_FORCUS)\n";
        outc << "           {\n";
        outc << "                   /*Add user functions here*/\r\n";
        outc << "           }\n";
        outc << "           else\n";
        outc << "           {\n";
        outc << "               if((--TaskSchedule[HMITaskFunctions].TaskSerial < _HMITaskMinIndex))\n";
        outc << "                   TaskSchedule[HMITaskFunctions].TaskSerial = _HMITaskMinIndex;\n";
        outc << "           }\n";
        outc << "           break;\n";
        outc << "       case _HMIPushButtonEvt_PBDN:\n";
        outc << "           if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_SELECT)\n";
        outc << "           {\n";
        outc << "                   /*Add user functions here*/\r\n";
        outc << "           }\n";
        outc << "           else if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_FORCUS)\n";
        outc << "           {\n";
        outc << "                   /*Add user functions here*/\r\n";
        outc << "           }\n";
        outc << "           else\n";
        outc << "           {\n";
        outc << "               if((++TaskSchedule[HMITaskFunctions].TaskSerial >= _HMITaskMaxIndex))\n";
        outc << "                   TaskSchedule[HMITaskFunctions].TaskSerial = _HMITaskMaxIndex;\n";
        outc << "           }\n";
        outc << "           break;\n";
        outc << "       case _HMIPushButtonEvt_PBLE:\n";
        outc << "           if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_FORCUS)\n";
        outc << "               TaskSchedule[HMITaskFunctions].Select = _HMIDSselect_SELECT;\n";
        outc << "           else if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_SELECT)\n";
        outc << "               TaskSchedule[HMITaskFunctions].Select = _HMIDSselect_NONULL;\n";
        outc << "           else\n";
        outc << "           {\n";
        outc << "               _HMIDispTool.tasksprt = HMIMainFunctions;\n";
        outc << "               _HMIDispTool.rfstatus = _HMIRefreshStatus_ALLS;\n";
        outc << "           }\n";
        outc << "           break;\n";
        outc << "       case _HMIPushButtonEvt_PBRD:\n";
        outc << "           if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_NONULL)\n";
        outc << "               TaskSchedule[HMITaskFunctions].Select = _HMIDSselect_SELECT;\n";
        outc << "           else if(TaskSchedule[HMITaskFunctions].Select == _HMIDSselect_SELECT)\n";
        outc << "               TaskSchedule[HMITaskFunctions].Select = _HMIDSselect_FORCUS;\n";
        outc << "           break;\n";
        outc << "       case _HMIPushButtonEvt_PBSG:\n";
        outc << "                   /*Add user functions here*/\r\n";
        outc << "           break;\n";
        outc << "       default:\n";
        outc << "           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;\n";
        outc << "           break;\n";
        outc << "   }\n";
        outc << "}\n";
        outc << "\r\n";
        outc << "void "+filename+"Function_DisplayFunction(void)\n";
        outc << "{\n";
        outc << "   switch (_HMIDispTool.rfstatus)\n";
        outc << "   {\n";
        outc << "       case _HMIRefreshStatus_CLOS:\n";
        outc << "           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;\n";
        outc << "           break;\n";
        outc << "       case _HMIRefreshStatus_NOUN:\n";
        outc << "           /*Add user functions here*/\r\n";
        outc << "           break;\n";
        outc << "       case _HMIRefreshStatus_PART:\n";
        outc << "           /*Add user functions here*/\r\n";
        outc << "           _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;\n";
        outc << "           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;\n";
        outc << "           break;\n";
        outc << "       case _HMIRefreshStatus_ALLS:\n";
        outc << "           /*Add user functions here*/\r\n";
        outc << "           /* @Note: Can add logic to select refresh method. */\n";
        outc << "           _HMIDispTool.rfstatus = _HMIRefreshStatus_PART;\n";
        outc << "           //_HMIDispTool.rfstatus = _HMIRefreshStatus_NOUN;\n";
        outc << "           break;\n";
        outc << "       default:\n";
        outc << "           _HMIDispTool.rfstatus = _HMIRefreshStatus_CLOS;\n";
        outc << "           _HMIDispTool.dpstatus = _HMIScreenStatus_CLOS;\n";
        outc << "           break;\n";
        outc << "   }\n";
        outc << "}\n";
        outc << "//-------------------------FUNCTION------------------------";
        outc << "\r\n";

        outc << "\r\n";
        filesprth.close();
        filesprtc.close();

        QDesktopServices::openUrl(QUrl(outfileh));
        QDesktopServices::openUrl(QUrl(outfilec));
    }
    else
    {

    }
}

