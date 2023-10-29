#include "information.h"
#include "ui_information.h"

QTextEdit *extctrlsprt = nullptr;

Information::Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
    extctrlsprt = ui->textEdit;
    ui->textEdit->setOverwriteMode(false);
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->textEdit->setTextColor(Qt::green);
    ui->textEdit->setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    ui->textEdit->setTextInteractionFlags(Qt::TextEditorInteraction);
    ui->textEdit->setPlaceholderText("@Authour:Miraitowance");
    ui->textEdit->setReadOnly(true);
}

Information::~Information()
{
    delete ui;
}
