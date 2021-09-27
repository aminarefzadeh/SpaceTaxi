#include "connectwindow.h"
#include "ui_connectwindow.h"
#include "client_socket.h"
#include "qmessagebox.h"
#include "loginwindow.h"
#include <cstdlib>
using namespace std;

ConnectWindow::ConnectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
    ui->IPEror->hide();
    ui->PortEror->hide();
    ui->label_3->setPixmap(QPixmap("/home/amin/TaxiClient/b3.jpg"));
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void ConnectWindow::on_ConnectBtn_clicked()
{
    bool input_eror=false;
    ui->IPEror->hide();
    ui->PortEror->hide();
    if(ui->ServerIP->toPlainText().toUtf8().isEmpty()){
        ui->IPEror->show();
        input_eror=true;
    }
    if(ui->ServerPort->toPlainText().toUtf8().isEmpty()){
        ui->PortEror->show();
        input_eror=true;
    }
    if(input_eror)
        return;
    try{
        ClientSocket* new_socket=new ClientSocket(ui->ServerIP->toPlainText().toStdString(), Tools::mystoi(ui->ServerPort->toPlainText().toStdString()));
        new_socket->send("CUSTOMER CLIENT");
        LoginWindow* Loginwin = new LoginWindow(new_socket);
        this->hide();
        Loginwin->show();
    }
    catch(NetworkException& e){
        QMessageBox Erormsg;
        Erormsg.setText(QString::fromStdString(e.get_message()));
    }
}
