#include "signup.h"
#include "ui_signup.h"
#include "QMessageBox"
#include "loginwindow.h"
using namespace std;

signup::signup(ClientSocket* cur,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    this->socket=cur;
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_11->hide();
    ui->label_12->hide();
    ui->label_14->setPixmap(QPixmap("/home/amin/TaxiClient/b2.jpg"));
}

signup::~signup()
{
    LoginWindow* PreviousWin=new LoginWindow(this->socket);
    this->hide();
    PreviousWin->show();
    delete ui;
}

void signup::on_RegisterBtn_clicked()
{
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_11->hide();
    ui->label_12->hide();
    bool Eror=false;
    if(ui->PasswordInput->toPlainText().toStdString().empty()){
        ui->label_6->show();
        Eror=true;
    }
    if(ui->UsernameInput->toPlainText().toStdString().empty()){
        ui->label_5->show();
        Eror=true;
    }
    if(ui->CarNum->toPlainText().toStdString().empty()){
        ui->label_7->show();
        Eror=true;
    }
    if(ui->CarModel->toPlainText().toStdString().empty()){
        ui->label_8->show();
        Eror=true;
    }
    if(ui->CarYear->toPlainText().toStdString().empty()){
        ui->label_11->show();
        Eror=true;
    }
    if(ui->Color->toPlainText().toStdString().empty()){
        ui->label_12->show();
        Eror=true;
    }
    if(Eror){
        return;
    }
    string SendMessage("register ");
    SendMessage.append(ui->UsernameInput->toPlainText().toStdString());
    SendMessage.append(" ");
    SendMessage.append(ui->PasswordInput->toPlainText().toStdString());
    SendMessage.append(" ");
    SendMessage.append(ui->CarNum->toPlainText().toStdString());
    SendMessage.append(" ");
    SendMessage.append(ui->CarModel->toPlainText().toStdString());
    SendMessage.append(" ");
    SendMessage.append(ui->CarYear->toPlainText().toStdString());
    SendMessage.append(" ");
    SendMessage.append(ui->Color->toPlainText().toStdString());

    if(ui->VIP->isChecked()){
        SendMessage.append(" VIP");
    }
    this->socket->send(SendMessage);
    bool EROR;
    string output=this->socket->GetEROR(EROR);
    QMessageBox outputMsg;
    outputMsg.setText(QString::fromStdString(output));
    if(EROR)
        outputMsg.setWindowTitle(QString::fromStdString("EROR"));
    else
        outputMsg.setWindowTitle(QString::fromStdString("SUCCESS"));
    outputMsg.exec();
    if(EROR)
        return;
    LoginWindow* PreviousWin=new LoginWindow(this->socket);
    this->hide();
    PreviousWin->show();
}

void signup::on_BackBtn_clicked()
{
    LoginWindow* PreviousWin=new LoginWindow(this->socket);
    this->hide();
    PreviousWin->show();
}
