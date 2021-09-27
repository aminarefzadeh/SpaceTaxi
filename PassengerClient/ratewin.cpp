#include "ratewin.h"
#include "ui_ratewin.h"
#include "interface.h"
#include "QMessageBox"
using namespace std;

RateWin::RateWin(string DriverName,string Model,string Color,InterFace* PreviousWin,ClientSocket* cur,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RateWin)
{
    ui->setupUi(this);
    ui->DriverName->setText(QString::fromStdString(DriverName));
    ui->CarModel->setText(QString::fromStdString(Model));
    ui->Color->setText(QString::fromStdString(Color));
    this->PreviosWin=PreviousWin;
    this->socket=cur;
    ui->label->hide();
    ui->label_2->setPixmap(QPixmap("/home/amin/TaxiClient/c4.jpg"));
}

RateWin::~RateWin()
{
    this->hide();
    PreviosWin->setEnabled(true);
    delete ui;
}

void RateWin::on_RateBtn_clicked()
{
    ui->label->hide();
    if(ui->Rate->toPlainText().toStdString().empty()){
        ui->label->show();
        return;
    }
    string input("rate_driver ");
    input.append(ui->Rate->toPlainText().toStdString());
    socket->send(input);
    bool EROR;
    string output=socket->GetEROR(EROR);
    QMessageBox MsgWin;
    MsgWin.setText(QString::fromStdString(output));
    if(EROR){
        MsgWin.setWindowTitle(QString::fromStdString("EROR"));
        MsgWin.exec();
        return;
    }
    MsgWin.setWindowTitle(QString::fromStdString("SUCCESS"));
    this->hide();
    PreviosWin->setEnabled(true);
    MsgWin.exec();
}

void RateWin::on_BackBtn_clicked()
{
    this->hide();
    PreviosWin->setEnabled(true);
}
