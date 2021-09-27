#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "loginwindow.h"
#include "qmessagebox.h"
#include "signup.h"
#include "interface.h"
using namespace std;

LoginWindow::LoginWindow(ClientSocket* cur,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->label_4->hide();
    ui->label_5->hide();
    this->socket=cur;
    ui->label_6->setPixmap(QPixmap("/home/amin/TaxiClient/b2.jpg"));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_SignInBtn_clicked()
{
    ui->label_4->hide();
    ui->label_5->hide();
    bool Login_Eror=false;
    if(ui->UsernName->toPlainText().toStdString().empty()){
        ui->label_4->show();
        Login_Eror=true;
    }
    if(ui->PassWord->toPlainText().toStdString().empty()){
        ui->label_5->show();
        Login_Eror=true;
    }
    if(Login_Eror)
        return;
    string Input_Message;
    Input_Message.append("login ");
    Input_Message.append(ui->UsernName->toPlainText().toStdString());
    Input_Message.append(" ");
    Input_Message.append(ui->PassWord->toPlainText().toStdString());
    socket->send(Input_Message);
    bool EROR;
    string Msg=this->socket->GetEROR(EROR);
    QMessageBox Message;
    Message.setText(QString::fromStdString(Msg));
    if(EROR)
        Message.setWindowTitle(QString::fromStdString("EROR"));
    else
        Message.setWindowTitle(QString::fromStdString("SUCCESS"));
    Message.exec();
    if(EROR)
        return;
    //build the main window
    InterFace* MainWin=new InterFace(this->socket,ui->UsernName->toPlainText().toStdString());
    this->hide();
    MainWin->show();
}

void LoginWindow::on_SignUpBtn_clicked()
{
    signup* SignupWin=new signup(this->socket);
    this->hide();
    SignupWin->show();
}
