#include "externevent.h"
#include "ui_externevent.h"

#include <QDebug>
#include <QFile>
#include <QAxObject>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QTextStream>

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QSize>
#include <QWidget>
#include <QProcess>

#include <QDesktopServices>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "InterfaceDefine.h"

QLineEdit *DigitalTipsSprt = nullptr;

QLabel *extLastDisplaySprt = nullptr;
ExternEvent::ExternEvent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExternEvent)
{
    ui->setupUi(this);
    extLastDisplaySprt = ui->LastDisplay;
    DigitalTipsSprt = ui->EditTips;
}

ExternEvent::~ExternEvent()
{
    delete ui;
}


void ExternEvent::on_PB_EXCEL_Color_clicked()
{
   QString filePath  = QFileDialog::getOpenFileName(this,
                                                    tr("打开文件"),
                                                    QDir::rootPath(),
                                                    tr("excel files(*.xls *.xlsx)"));

    if(filePath.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("读取路径错误!")); return;
    }

    QString outfPath= QFileDialog::getExistingDirectory(this, "获取路径", filePath);
    if(outfPath.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("写入路径错误!")); return;
    }

    if (!filePath.isEmpty() && !outfPath.isEmpty())
    {
        QAxObject *Excel = new QAxObject("Excel.Application");
        Excel->setProperty("Visible", false);
        QAxObject *workbooks = Excel->querySubObject("Workbooks");
        QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", filePath);
        QAxObject *worksheet = workbook->querySubObject("Worksheets(int)", 1);

        QAxObject *usedRange=worksheet->querySubObject("UsedRange");
        QVariant var=usedRange->dynamicCall("value");
        QVariantList varRowContents=var.toList();
        const int rowCount=varRowContents.size();
        QString outfile = outfPath + "/OutDefRGB565.txt";
        QFile filesprt(outfile);
        filesprt.open(QIODevice::WriteOnly);
        filesprt.close();
        if(!filesprt.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QMessageBox::critical(this,tr("错误"),tr("打开文件失败,数据保存失败"));
            return ;
        }
        else
        {
            QTextStream out(&filesprt);
            QString name,color,data;
            for(int i=0; i<rowCount; ++i)
            {

                name=varRowContents[i].toStringList().at(0);
                color=varRowContents[i].toStringList().at(1);
                data=varRowContents[i].toStringList().at(2);
                out << "#define         "<<"Drv_"<<color<<"            "<<data<<"//"<<name<<"\r\n";
            }
            filesprt.close();
            QMessageBox::warning(this, tr("Sucessful"), tr("转化成功!"));
        }
        Excel->dynamicCall("Quit(void)");
        delete Excel;
        QDesktopServices::openUrl(QUrl(outfile));
    }
}


void ExternEvent::on_PB_IMAGE_Change_clicked()
{
    QString filePath  = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    QDir::rootPath(),
                                                    tr("Images (*.png *.BMP *.jpg)"));

    if(filePath.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("读取路径错误!")); return;
    }
    QWidget * IMGShow=new QWidget;
    QImage *Images = new QImage(filePath);
    if(Images->isNull())
    { QMessageBox::warning(this, tr("警告"), tr("读取路径错误!")); delete IMGShow; return;}

    IMGShow->resize(QSize(Images->width(),Images->height()));
    IMGShow->setAttribute(Qt::WA_DeleteOnClose);
    QLabel *ShowImage = new QLabel(IMGShow);
    ShowImage->setPixmap(QPixmap::fromImage(*Images));
    IMGShow->show();

    QString outfile = filePath + ".txt";
    QFile filesprt(outfile);
    filesprt.open(QIODevice::WriteOnly);
    filesprt.close();


    if(!filesprt.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        return ;
    }
    else
    {
        QTextStream out(&filesprt);

        unsigned char r, g, b;
        unsigned short data;
        unsigned char count = 0;
        QColor colorsprt;
        int h = Images->height();
        int w = Images->width();

        out << "IMG:Name"<<outfile<<"\r\n";
        out << "IMG:W-"<<Images->width() << "   H-"<<Images->height()<<"\r\n";

        QFileInfo info(outfile);
        QString dataname = info.fileName().replace(".","_");

        out << "ShowImage_DrvFunction("<< dataname << ",0,0,"<< w <<"," << h <<");";
        out << "\r\n--------------------------------------\r\n";
        out << "extern const unsigned short " << dataname<<"[" << (h*w) << "];\r\n";
        out << "const unsigned short " << dataname<<"[" << (h*w) << "] = \r\n";

        out << "{\r\n";
        for(int y = 0; y < h; y++)
        {
            for(int x = 0; x < w; x++)
            {
                colorsprt = Images->pixelColor(x,y);
                r = colorsprt.red();
                g = colorsprt.green();
                b = colorsprt.blue();
                data = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
                out << " 0x"<<QString::number(data, 16).rightJustified(4, '0') << ',';
                if(++count >= 8)
                {
                    count = 0;
                    out << "\r\n";
                }
            }
        }
        out <<"};\r\n";
        filesprt.close();
        QMessageBox::warning(this, tr("Sucessful"), tr("转化成功!"));
        QDesktopServices::openUrl(QUrl(outfile));
    }
}


void ExternEvent::on_PB_Squart_clicked()
{
    QString filePath  = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    QDir::rootPath(),
                                                    tr("Images (*.png *.BMP *.jpg)"));

    if(filePath.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("读取路径错误!")); return;
    }
    QWidget * IMGShow=new QWidget;
    QImage *Images = new QImage(filePath);
    if(Images->isNull())
    { QMessageBox::warning(this, tr("警告"), tr("读取路径错误!")); delete IMGShow; return;}

    IMGShow->resize(QSize(Images->width(),Images->height()));
    IMGShow->setAttribute(Qt::WA_DeleteOnClose);
    QLabel *ShowImage = new QLabel(IMGShow);
    ShowImage->setPixmap(QPixmap::fromImage(*Images));
    IMGShow->show();

    QString outfile = filePath + ".txt";
    QFile filesprt(outfile);
    filesprt.open(QIODevice::WriteOnly);
    filesprt.close();


    if(!filesprt.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        return ;
    }
    else
    {
        *Images = Images->convertToFormat(QImage::Format_Grayscale8);

        unsigned char *data = Images->bits();
        unsigned temp = 0x00;
        int w = Images->width();
        int h = Images->height();
        int bytePerLine = Images->bytesPerLine();
        unsigned char g = 0, num = 0, count = 0;

        QTextStream out(&filesprt);
        out << "HandleMode:shape\n";
        out << "IMG:Name"<<outfile<<"\r\n";
        out << "IMG:W-"<< w<< "   H-"<<h<<"\r\n";
        out << "{\r\n";

         for (int i = 0; i < h; ++i)
         {
            for (int j = 0; j < w; ++j)
            {
                g = *(data + i * bytePerLine + j);
                if(g > 100)
                {
                    temp |= 0x01;
                }
                count++;
                if(count >= 8)
                {
                    count = 0;
                    out << " 0x"<<QString::number(temp, 16).rightJustified(2, '0') << ',';
                    temp = 0x00;
                    num++;
                    if(num % 8 == 0)
                    {
                        out <<"\n";
                    }
                }

                temp = temp << 1;
            }
         }

         if(temp != 0)
         {
            temp = temp << (7 - count);
            out << " 0x"<<QString::number(temp, 16).rightJustified(2, '0') << ',';
            num++;
         }

         out <<"};\r\n";
         out << "Number:" << num;

         out << "\r\n--------------------------------------\r\n";
         QFileInfo info(outfile);
         QString dataname = info.fileName().replace(".","_");
         out << "const unsigned char " << dataname<<"[" << num << "] = \r\n";
         out << "extern const unsigned char " << dataname<<"[" << num << "];\r\n";

         out << "ShowSquare_DrvFunction("<<dataname<<",0,0,Drv_WHITE,Drv_BLACK,"<<w<<","<<h<<");";
         filesprt.close();
         QMessageBox::warning(this, tr("Sucessful"), tr("转化成功!"));
         QDesktopServices::openUrl(QUrl(outfile));
    }
}

void ExternEvent::on_PB_Tool_P2L_clicked()
{
    QProcess process(this);
    QString str ="../QtSimulation/HMIResources/Tool/PCtoLCD2002/PCtoLCD2002.exe";//加可执行文件路径
    process.startDetached(str);//启动可执行文件
    process.waitForStarted(); //等待程序启动
    process.waitForFinished();//等待程序关闭
}


void ExternEvent::on_PB_ConnectUser_clicked()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "../",
                                                    QFileDialog::ShowDirsOnly);
    if(dir.isEmpty())
    {
         QMessageBox::critical(this,tr("错误"),tr("打开文件失败"));
         return;
    }

    QString path = dir + "/FontManage.txt";
    //------------------------------------------------------------------------------------------------------------
    QFile filesprt(path);
    QTextStream in(&filesprt); //创建输出流
    in.setEncoding(QStringConverter::System);
    QTextStream out(&filesprt); //创建输出流
    out.setEncoding(QStringConverter::System);
    QString commit;
    if(!filesprt.open(QIODevice::ReadWrite | QIODevice::Text))
    {
         QMessageBox::critical(this,tr("错误"),tr("打开文件失败,数据保存失败"));
         return ;
    }
    else
    {
         if(commit.isEmpty())
         {
            out << "{[\n";
            out << "*                                     *\n";
            out << "*                                     *\n";
            out << "*             Font Function           *\n";
            out << "*                                     *\n";
            out << "*                                     *\n";
            out << "]}\n";
            out << "@Authour:Miraitowance/Miraitowan\n";
            out << "@Function: 鲸落の入海 ~(_0.0_)-\n";
            out << "\r\n";
         }
         else
         {
            commit = in.readAll();
         }
    }

    QString codepath = QFileDialog::getOpenFileName(this, tr("open file"),dir,tr("Text files (*.txt)"));

    if(codepath.isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败"));
        return;
    }

    QFile codefile(codepath);
    QTextStream codein(&codefile); //创建输出流
    codein.setEncoding(QStringConverter::System);
    QString fonecode;

    if(!codefile.open(QIODeviceBase::ReadOnly | QIODeviceBase::Text))
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        return ;
    }
    else
    {
        fonecode = codein.readAll();
    }

    if(fonecode.isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("没有读取到数据"));
        return;
    }

    static QRegularExpression datare("({((0x[\\d|\\w]{2})(,?)){16}},)(\n)({((0x[\\d|\\w]{2})(,?)){16}},)/\\*\"[\u4e00-\u9fa5]\",[\\d]+\\*/");
    datare.setPatternOptions(QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator dataiter = datare.globalMatch(fonecode);

    static QRegularExpression re("[\u4e00-\u9fa5]");
    while (dataiter.hasNext())
    {
        QRegularExpressionMatch match = dataiter.next();
        QString dataformat = match.captured(0);
        dataformat.replace("},\n{",",");
        QString data = dataformat.left(161);
        QRegularExpressionMatch namematch = re.match(dataformat);
        QString dataname = namematch.captured(0);
        QString outdata = QString(" {{\"%1\"},%2},").arg(dataname,data);
        out << outdata << "\r\n";
    }

    codefile.close();
    filesprt.close();
    QDesktopServices::openUrl(QUrl(codepath));
    QDesktopServices::openUrl(QUrl(path));
}


void ExternEvent::on_fastPB_ConnectUser_clicked()
{
    QString codepath = QFileDialog::getOpenFileName(this, tr("open file"),"../",tr("Text files (*.txt)"));

    if(codepath.isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败"));
        return;
    }

    QFile codefile(codepath);
    QTextStream codein(&codefile);
    codein.setEncoding(QStringConverter::System);
    QString fonecode;

    if(!codefile.open(QIODeviceBase::ReadOnly | QIODeviceBase::Text))
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        return ;
    }
    else
    {
        fonecode = codein.readAll();
    }

    if(fonecode.isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("没有读取到数据"));
        return;
    }

    QString path = codepath + "Manage.txt";
    //------------------------------------------------------------------------------------------------------------
    QFile filesprt(path);
    QTextStream out(&filesprt); //创建输出流
    out.setEncoding(QStringConverter::System);
    if(!filesprt.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QMessageBox::critical(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        return ;
    }
    else
    {
        out << "{[\n";
        out << "*                                     *\n";
        out << "*                                     *\n";
        out << "*             Font Function           *\n";
        out << "*                                     *\n";
        out << "*                                     *\n";
        out << "]}\n";
        out << "@Authour:Miraitowance/Miraitowan\n";
        out << "@Function: 鲸落の入海 ~(_0.0_)-\n";
        out << "\r\n";
    }

    static QRegularExpression datare("({((0x[\\d|\\w]{2})(,?)){16}},)(\n)({((0x[\\d|\\w]{2})(,?)){16}},)/\\*\"[\u4e00-\u9fa5]\",[\\d]+\\*/");
    datare.setPatternOptions(QRegularExpression::MultilineOption);
    QRegularExpressionMatchIterator dataiter = datare.globalMatch(fonecode);

    static QRegularExpression re("[\u4e00-\u9fa5]");
    while (dataiter.hasNext())
    {
        QRegularExpressionMatch match = dataiter.next();
        QString dataformat = match.captured(0);
        dataformat.replace("},\n{",",");
        QString data = dataformat.left(161);
        QRegularExpressionMatch namematch = re.match(dataformat);
        QString dataname = namematch.captured(0);
        QString outdata = QString(" {{\"%1\"},%2},").arg(dataname,data);
        out << outdata << "\r\n";
    }
    codefile.close();
    QDesktopServices::openUrl(QUrl(path));
}


#include "gencode.h"
void ExternEvent::on_GentCode_clicked()
{
    GenCode *newcode = new GenCode();
    newcode->show();
}

