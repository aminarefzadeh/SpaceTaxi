#include "setstatus.h"
#include "ui_setstatus.h"
#include "interface.h"
#include "qmessagebox.h"

using namespace std;
SetStatus::SetStatus(InterFace* Previous,ClientSocket* cur,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetStatus)
{
    ui->setupUi(this);
    this->PreviousWin=Previous;
    this->socket=cur;
//    ui->Address->hide();
    ui->label->hide();
    ui->label_2->setPixmap(QPixmap("/home/amin/TaxiClient/c4.jpg"));
}

SetStatus::~SetStatus()
{
    this->hide();
    this->PreviousWin->setEnabled(true);
    delete ui;
}


void SetStatus::on_UnavailableBtn_clicked()
{
    if(!ui->UnavailableBtn->isCheckable()){
        ui->AvailableBtn->setChecked(false);
//       ui->Address->hide();
    }
}

void SetStatus::on_AvailableBtn_clicked()
{
    if(!ui->AvailableBtn->isChecked()){
        ui->UnavailableBtn->setChecked(false);
//        ui->Address->show();
    }
    else{
//        ui->Address->hide();
    }
}

void SetStatus::on_Back_clicked()
{
    this->hide();
    this->PreviousWin->setEnabled(true);
}

void SetStatus::on_OkBtn_clicked()
{
    ui->label->hide();
    if(ui->AvailableBtn->isChecked()){
        if(ui->Address->toPlainText().toStdString().empty()){
            ui->label->show();
            return;
        }
        string input("set_status available ");
        input.append(ui->Address->toPlainText().toStdString());
        this->socket->send(input);
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
        PreviousWin->set_status("available");
        PreviousWin->set_address(ui->Address->toPlainText().toStdString());
        PreviousWin->RefreshItem();
        return;
    }
    if(ui->UnavailableBtn->isChecked()){
        this->socket->send("set_status unavailable");
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
        PreviousWin->set_status("unavailable");
        PreviousWin->RefreshItem();
    }
}
