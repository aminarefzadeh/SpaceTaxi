#include "interface.h"
#include "ui_interface.h"
#include "qmessagebox.h"
#include "loginwindow.h"
#include "setstatus.h"
#include "acceptrequest.h"
#include "showrequests.h"
#include "currenttrip.h"
#include <sstream>

using namespace std;

InterFace::InterFace(ClientSocket* cur,string name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterFace)
{
    ui->setupUi(this);
    this->socket=cur;
    this->UserName=name;
    ui->Name1->hide();
    ui->Name2->hide();
    ui->Name3->hide();
    ui->Name4->hide();
    ui->source1->hide();
    ui->source2->hide();
    ui->source3->hide();
    ui->source4->hide();
    ui->cost1->hide();
    ui->cost2->hide();
    ui->cost3->hide();
    ui->cost4->hide();
    ui->distance1->hide();
    ui->distance2->hide();
    ui->distance3->hide();
    ui->distance4->hide();
    ui->label_1->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_8->hide();
    ui->AccptRequestBtn->hide();
    ui->Address->hide();
    ui->CurrentTripBtn->hide();

    ui->UserName->setText(QString::fromStdString(name));
    ui->Status->setText(QString::fromStdString("unavailable"));
    this->Status="unavailable";
    this->socket->send("GET_TIME");
    bool EROR;
    ui->Time->setText(QString::fromStdString(socket->GetEROR(EROR)));
    ui->label->setPixmap(QPixmap("/home/amin/TaxiClient/b1.jpg"));
}

InterFace::~InterFace()
{
    socket->send("logout");
    bool EROR;
    socket->GetEROR(EROR);
    delete ui;
}

void InterFace::hide_item(){
    ui->Name1->hide();
    ui->Name2->hide();
    ui->Name3->hide();
    ui->Name4->hide();
    ui->source1->hide();
    ui->source2->hide();
    ui->source3->hide();
    ui->source4->hide();
    ui->cost1->hide();
    ui->cost2->hide();
    ui->cost3->hide();
    ui->cost4->hide();
    ui->distance1->hide();
    ui->distance2->hide();
    ui->distance3->hide();
    ui->distance4->hide();
    ui->label_1->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_8->hide();
    ui->AccptRequestBtn->hide();
    ui->Address->hide();
    ui->CurrentTripBtn->hide();
    ui->Passenger1->hide();
    ui->Passenger2->hide();
    ui->Passenger3->hide();
    ui->Passenger4->hide();
}

void InterFace::RefreshItem()
{
    this->hide_item();
    ui->Status->setText(QString::fromStdString(this->Status));
    if(this->Status.compare("on_trip")!=0){
        ui->SetStatusBtn->setEnabled(true);
    }
    socket->send("GET_TIME");
    bool EROR;
    ui->Time->setText(QString::fromStdString(socket->GetEROR(EROR)));
    if(TripInfo.size()==0){
        if(Status.compare("unavailable")==0)
            return;
        ui->Address->setText(QString::fromStdString(this->Address));
        ui->label_1->show();
        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        this->socket->send("show_trip_requests");
        bool EROR;
        stringstream a(this->socket->GetEROR(EROR));
        if(EROR)
            return;
        ui->AccptRequestBtn->show();
        int n=1;
        string output;
        while(getline(a,output)){
            vector<string> output_array=socket->standard_input(output);
            switch (n) {
            case 1:
                ui->Name1->setText(QString::fromStdString(output_array[0]));
                ui->source1->setText(QString::fromStdString(output_array[1]));
                ui->cost1->setText(QString::fromStdString(output_array[output_array.size()-2]));
                ui->distance1->setText(QString::fromStdString(output_array[output_array.size()-1]));
                ui->Name1->show();
                ui->source1->show();
                ui->cost1->show();
                ui->distance1->show();
                ui->Passenger1->show();
                break;
            case 2:
                ui->Name2->setText(QString::fromStdString(output_array[0]));
                ui->source2->setText(QString::fromStdString(output_array[1]));
                ui->cost2->setText(QString::fromStdString(output_array[output_array.size()-2]));
                ui->distance2->setText(QString::fromStdString(output_array[output_array.size()-1]));
                ui->Name2->show();
                ui->source2->show();
                ui->cost2->show();
                ui->distance2->show();
                ui->Passenger2->show();
                break;
            case 3:
                ui->Name3->setText(QString::fromStdString(output_array[0]));
                ui->source3->setText(QString::fromStdString(output_array[1]));
                ui->cost3->setText(QString::fromStdString(output_array[output_array.size()-2]));
                ui->distance3->setText(QString::fromStdString(output_array[output_array.size()-1]));
                ui->Name3->show();
                ui->source3->show();
                ui->cost3->show();
                ui->distance3->show();
                ui->Passenger3->show();
                break;
            case 4:
                ui->Name4->setText(QString::fromStdString(output_array[0]));
                ui->source4->setText(QString::fromStdString(output_array[1]));
                ui->cost4->setText(QString::fromStdString(output_array[output_array.size()-2]));
                ui->distance4->setText(QString::fromStdString(output_array[output_array.size()-1]));
                ui->Name4->show();
                ui->source4->show();
                ui->cost4->show();
                ui->distance4->show();
                ui->Passenger4->show();
                break;
            default:
                ui->SeeMore->show();
                ui->label_8->show();
                return;
            }
            n++;
        }
    }
    else{
        ui->CurrentTripBtn->show();
    }
}

void InterFace::on_RefreshBtn_clicked()
{
    this->RefreshItem();
}

void InterFace::on_LogOutBtn_clicked()
{
    socket->send("logout");
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
    LoginWindow* PreviousWin=new LoginWindow(socket);
    MsgWin.exec();
    PreviousWin->show();
}

void InterFace::on_SetStatusBtn_clicked()
{
    SetStatus* NewWin=new SetStatus(this,socket);
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::on_AccptRequestBtn_clicked()
{
    AcceptRequest* NewWin=new AcceptRequest(this,this->socket);
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::on_Passenger1_clicked()
{
    AcceptRequest* NewWin=new AcceptRequest(this,this->socket,ui->Name1->text().toStdString());
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::set_statusbtn(bool a){
    ui->SetStatusBtn->setEnabled(a);
}

void InterFace::on_Passenger2_clicked()
{
    AcceptRequest* NewWin=new AcceptRequest(this,this->socket,ui->Name2->text().toStdString());
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::on_Passenger3_clicked()
{
    AcceptRequest* NewWin=new AcceptRequest(this,this->socket,ui->Name3->text().toStdString());
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::on_Passenger4_clicked()
{
    AcceptRequest* NewWin=new AcceptRequest(this,this->socket,ui->Name4->text().toStdString());
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::on_SeeMore_clicked()
{
    ShowRequests* NewWin=new ShowRequests(this,this->socket);
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::on_CurrentTripBtn_clicked()
{
    CurrentTrip* NewWin=new CurrentTrip(this,this->socket,this->TripInfo,this->arrived);
    NewWin->show();
    this->setEnabled(false);
}
