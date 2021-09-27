#include "acceptrequest.h"
#include "ui_acceptrequest.h"
#include "interface.h"
#include "QMessageBox"
#include <sstream>

using namespace std;

AcceptRequest::AcceptRequest(InterFace* Previous,ClientSocket* socket,string Passenger) :
    QWidget(0),
    ui(new Ui::AcceptRequest)
{
    ui->setupUi(this);
    this->Previous=Previous;
    this->socket=socket;
    ui->label_2->hide();
    if(Passenger.size()==0){
        ui->AcceptBtn->setEnabled(false);
        return;
    }
    this->Passenger=Passenger;
    ui->Passenger->setPlainText(QString::fromStdString(Passenger));
    ui->AcceptBtn->setEnabled(true);
    this->socket->send("show_trip_requests");
    bool EROR;
    stringstream a(this->socket->GetEROR(EROR));
    string output;
    while(getline(a,output)){
        vector<string> output_array=this->socket->standard_input(output);
        if((output_array[0]).compare(Passenger)==0)
            break;
    }
    ui->Info->setText(QString::fromStdString(output));
    ui->label_3->setPixmap(QPixmap("/home/amin/TaxiClient/c4.jpg"));
}

AcceptRequest::~AcceptRequest()
{
    this->hide();
    this->Previous->setEnabled(true);
    delete ui;
}

void AcceptRequest::on_FindBtn_clicked()
{
    ui->label_2->hide();
    if(ui->Passenger->toPlainText().toStdString().empty()){
        ui->label_2->show();
        return;
    }
    this->socket->send("show_trip_requests");
    bool EROR;
    string socket_output=this->socket->GetEROR(EROR);
    if(EROR){
        QMessageBox ErorWin;
        ErorWin.setText(QString::fromStdString(socket_output));
        ErorWin.setWindowTitle(QString::fromStdString("EROR"));
        ErorWin.exec();
        return;
    }
    stringstream a(socket_output);
    string output;
    string Info;
    while(getline(a,output)){
        vector<string> output_array=this->socket->standard_input(output);
        if((output_array[0]).compare(ui->Passenger->toPlainText().toStdString())==0){
            Info=output;
            break;
        }
    }
    if(Info.size()){
        ui->Info->setText(QString::fromStdString(Info));
        ui->AcceptBtn->setEnabled(true);
        this->Passenger=ui->Passenger->toPlainText().toStdString();
        return;
    }
    QMessageBox ErorMsg;
    ErorMsg.setText(QString::fromStdString("you don't have request with this name"));
    ErorMsg.setWindowTitle(QString("EROR"));
    ErorMsg.exec();
}

void AcceptRequest::on_Passenger_textChanged()
{
    ui->AcceptBtn->setEnabled(false);
}

void AcceptRequest::on_AcceptBtn_clicked()
{
    string input("accept_trip_request ");
    input.append(this->Passenger);
    this->socket->send(input);
    bool EROR;
    string output=this->socket->GetEROR(EROR);
    QMessageBox ErorMsg;
    ErorMsg.setText(QString::fromStdString(output));
    if(EROR){
        ErorMsg.setWindowTitle(QString::fromStdString("EROR"));
        ErorMsg.exec();
        return;
    }
    ErorMsg.setWindowTitle(QString::fromStdString("SUCCESS"));
    this->hide();
    ErorMsg.exec();
    this->Previous->setEnabled(true);
    Previous->set_tripinfo(ui->Info->toPlainText().toStdString());
    Previous->set_arrived(false);
    Previous->set_status("on_trip");
    Previous->set_statusbtn(false);
    Previous->RefreshItem();
}

void AcceptRequest::on_CancelBtn_clicked()
{
    this->hide();
    this->Previous->setEnabled(true);
}
