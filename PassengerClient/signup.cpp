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
    ui->label_8->setPixmap(QPixmap("/home/amin/TaxiClient/b2.jpg"));
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
    ui->PasswordInput->setStyleSheet(QString::fromStdString(" "));
    ui->UsernameInput->setStyleSheet(QString::fromStdString(" "));
    ui->PhoneInput->setStyleSheet(QString::fromStdString(" "));
    bool Eror=false;
    if(ui->PasswordInput->toPlainText().toStdString().empty()){
        ui->PasswordInput->setStyleSheet(QString::fromStdString("background : \'red\'"));
        Eror=true;
    }
    if(ui->UsernameInput->toPlainText().toStdString().empty()){
        ui->UsernameInput->setStyleSheet(QString::fromStdString("background : 'red'"));
        Eror=true;
    }
    if(ui->PhoneInput->toPlainText().toStdString().empty()){
        ui->PhoneInput->setStyleSheet(QString::fromStdString("background : 'red'"));
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
    SendMessage.append(ui->PhoneInput->toPlainText().toStdString());
    if(! ui->CodeInput->toPlainText().toStdString().empty()){
        SendMessage.append(" ");
        SendMessage.append(ui->CodeInput->toPlainText().toStdString());
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
