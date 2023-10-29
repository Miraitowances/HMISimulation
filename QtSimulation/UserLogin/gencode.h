#ifndef GENCODE_H
#define GENCODE_H

#include <QWidget>

namespace Ui {
class GenCode;
}

class GenCode : public QWidget
{
    Q_OBJECT

public:
    explicit GenCode(QWidget *parent = nullptr);
    ~GenCode();


protected:
     bool eventFilter(QObject *obj, QEvent *event);

signals:
     void AcquarePath_SignalFunc(void);
     void AcquareFunc_SignalFunc(void);
private slots:
     void AcquarePath_HandleFunc(void);
     void AcquareFunc_HandleFunc(void);

    void on_FileName_returnPressed();

     void on_Output_clicked();

 private:
    Ui::GenCode *ui;
    QString path;
    QString func;
    QString filename;
};

#endif // GENCODE_H
