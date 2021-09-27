#include "currenttrip.h"
#include "ui_currenttrip.h"
#include "interface.h"
#include "qmessagebox.h"

using namespace std;

CurrentTrip::CurrentTrip(InterFace* Previous,ClientSocket* cur,string Info,bool Status,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrentTrip)
{
    ui->setupUi(this);
    this->Previous=Previous;
    this->socket=cur;
    this->Status=Status;
    vector<string> input_array=this->socket->standard_input(Info);
    ui->Passenger->setText(QString::fromStdString(input_array[0]));
    ui->Cost->setText(QString::fromStdString(input_array[input_array.size()-2]));
    ui->Distance->setText(QString::fromStdString(input_array[input_array.size()-1]));
    ui->Status->setText(QString::fromStdString(Status?"arrived":"not arrived"));
    this->last_place=input_array[input_array.size()-3];
    string Destination;
    for(int i=0;i<input_array.size()-2;i++){
        Destination.append(input_array[i]);
        Destination.append(" ");
    }
    ui->Destination->setText(QString::fromStdString(Destination));
    if(Status){
        ui->ArrivedBtn->hide();
    }
    else{
        ui->EndTripBtn->hide();
    }
    ui->label_6->setPixmap(QPixmap("/home/amin/TaxiClient/c4.jpg"));
}

CurrentTrip::~CurrentTrip()
{
    this->hide();
    Previous->setEnabled(true);
    delete ui;
}

void CurrentTrip::on_BackBtn_clicked()
{
    this->hide();
    Previous->setEnabled(true);
    Previous->RefreshItem();
}

void CurrentTrip::on_ArrivedBtn_clicked()
{
    this->socket->send("arrived");
    bool EROR;
    string output=this->socket->GetEROR(EROR);
    QMessageBox MsgWin;
    MsgWin.setText(QString::fromStdString(output));
    if(EROR){
        MsgWin.setWindowTitle(QString::fromStdString("EROR"));
        MsgWin.exec();
        return;
    }
    MsgWin.setWindowTitle(QString::fromStdString("SUCCESS"));
    MsgWin.exec();
    ui->ArrivedBtn->hide();
    ui->EndTripBtn->show();
    Previous->set_arrived(true);
    ui->Status->setText(QString::fromStdString("arrived"));
}

void CurrentTrip::on_EndTripBtn_clicked()
{
    this->socket->send("end_trip");
    bool EROR;
    string output=this->socket->GetEROR(EROR);
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
    Previous->setEnabled(true);
    Previous->set_status("available");
    Previous->set_address(this->last_place);
    Previous->set_statusbtn(true);
    string a="";
    Previous->set_tripinfo(a);
    Previous->RefreshItem();
}
