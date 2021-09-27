#include "chargewin.h"
#include "ui_chargewin.h"
#include "QMessageBox"
using namespace std;

ChargeWin::ChargeWin(InterFace* PreviousWin,ClientSocket* cur,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChargeWin)
{
    ui->setupUi(this);
    this->socket=cur;
    ui->label_2->hide();
    this->PreviousWin=PreviousWin;
    ui->label_3->setPixmap(QPixmap("/home/amin/TaxiClient/c4.jpg"));
}

ChargeWin::~ChargeWin()
{
    this->hide();
    this->PreviousWin->setEnabled(true);
    delete ui;
}

void ChargeWin::on_ChargeBtn_clicked()
{
    ui->label_2->hide();
    if(ui->AmountInput->toPlainText().toStdString().empty()){
        ui->label_2->show();
        return;
    }
    string SendMessage("charge_account ");
    SendMessage.append(ui->AmountInput->toPlainText().toStdString());
    socket->send(SendMessage);
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
    MsgWin.exec();
    PreviousWin->setEnabled(true);
}

void ChargeWin::on_BackBtn_clicked()
{
    this->hide();
    this->PreviousWin->setEnabled(true);
}
