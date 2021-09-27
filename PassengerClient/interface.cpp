#include "interface.h"
#include "ui_interface.h"
#include "QMessageBox"
#include "loginwindow.h"
#include "chargewin.h"
#include "ratewin.h"
#include "triprequest.h"
#include <time.h>
using namespace std;

InterFace::InterFace(ClientSocket* cur,string UserName,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterFace)
{
    ui->setupUi(this);
    this->socket=cur;
    this->UserName=UserName;
    ui->CancelTrip->setVisible(false);
    ui->Cost->hide();
    ui->Cost_2->hide();
    ui->DriverName->hide();
    ui->DriverName_2->hide();
    ui->Distance->hide();
    ui->Distance_2->hide();
    ui->TripStatus->hide();
    ui->TripStatus_2->hide();
    ui->Model->hide();
    ui->Model_2->hide();
    ui->Color->hide();
    ui->Color_2->hide();
    ui->RateBtn->setVisible(false);
    ui->Code->hide();
    ui->CodeNum->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->UserName->setText(QString::fromStdString(this->UserName));
    this->socket->send(string("get_credit"));
    bool a;
    string output=socket->GetEROR(a);
    ui->Credit->setText(QString::fromStdString(output));
    this->socket->send("GET_TIME");
    output=socket->GetEROR(a);
    this->ui->SystemTime->setText(QString::fromStdString(output));
    ui->label_3->setPixmap(QPixmap("/home/amin/TaxiClient/b1.jpg"));
}

InterFace::~InterFace()
{
    delete ui;
    socket->send("logout");
    bool EROR;
    socket->GetEROR(EROR);
}

void InterFace::on_Refresh_clicked()
{
    this->hide_items();
    this->socket->send(string("get_credit"));
    bool a;
    string output=socket->GetEROR(a);
    ui->Credit->setText(QString::fromStdString(output));
    this->socket->send("GET_TIME");
    output=socket->GetEROR(a);
    this->ui->SystemTime->setText(QString::fromStdString(output));
}

void InterFace::on_commandLinkButton_clicked()
{
    this->hide_items();
    this->socket->send("logout");
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
    LoginWindow* PreviousWin=new LoginWindow(this->socket);
    this->hide();
    PreviousWin->show();
    MsgWin.exec();
}

void InterFace::on_LastTrip_clicked()
{
    ui->label->hide();
    ui->Code->hide();
    ui->label_2->hide();
    ui->CodeNum->hide();
    if(! ui->Cost->isHidden()){
        ui->Cost->hide();
        ui->Cost_2->hide();
        ui->Distance->hide();
        ui->Distance_2->hide();
        ui->TripStatus->hide();
        ui->TripStatus_2->hide();
        ui->CancelTrip->setVisible(false);
        ui->Color->hide();
        ui->Color_2->hide();
        ui->DriverName->hide();
        ui->DriverName_2->hide();
        ui->Model->hide();
        ui->Model_2->hide();
        ui->RateBtn->setVisible(false);
        return;
    }
    this->socket->send("trip_status");
    bool EROR;
    string output=this->socket->GetEROR(EROR);
    if(EROR){
        QMessageBox ErorMsg;
        ErorMsg.setText(QString::fromStdString(output));
        ErorMsg.setWindowTitle(QString::fromStdString("EROR"));
        ErorMsg.exec();
        return;
    }
    ui->Cost->setText(QString::fromStdString(this->cost));
    ui->Distance->setText(QString::fromStdString(this->distance));
    ui->Cost->show();
    ui->Cost_2->show();
    ui->Distance->show();
    ui->Distance_2->show();
    if(output.find("waiting ...")!=string::npos){
        ui->TripStatus->setText(QString::fromStdString("waiting"));
        ui->TripStatus->show();
        ui->TripStatus_2->show();
        ui->CancelTrip->setVisible(true);
    }
    else{
        vector<string> input_array=socket->standard_input(output);
        ui->TripStatus->setText(QString::fromStdString(input_array[0]));
        ui->TripStatus->show();
        ui->TripStatus_2->show();
        if(ui->DriverName->text().toStdString()!=input_array[1]){
            ui->DriverName->setText(QString::fromStdString(input_array[1]));
            ui->Model->setText(QString::fromStdString(input_array[3]));
            ui->Color->setText(QString::fromStdString(input_array[4]));
        }
        if(output.find("not_rated")!=string::npos)
            ui->RateBtn->setVisible(true);
        ui->DriverName->show();
        ui->DriverName_2->show();
        ui->Color->show();
        ui->Color_2->show();
        ui->Model->show();
        ui->Model_2->show();
    }
}

void InterFace::on_CancelTrip_clicked()
{
    socket->send("cancel_trip_request");
    bool EROR;
    string output=socket->GetEROR(EROR);
    QMessageBox MsgWin;
    MsgWin.setText(QString::fromStdString(output));
    if(EROR){
        MsgWin.setWindowTitle(QString::fromStdString("EROR"));
        ui->Cost->hide();
        ui->Cost_2->hide();
        ui->Distance->hide();
        ui->Distance_2->hide();
        ui->TripStatus->hide();
        ui->TripStatus_2->hide();
        ui->CancelTrip->setVisible(false);
        ui->Color->hide();
        ui->Color_2->hide();
        ui->DriverName->hide();
        ui->DriverName_2->hide();
        ui->Model->hide();
        ui->Model_2->hide();
    }
    else{
        MsgWin.setWindowTitle(QString::fromStdString("SUCCESS"));
    }
    MsgWin.exec();
}

void InterFace::on_CodeBtn_clicked()
{
    ui->Cost->hide();
    ui->Cost_2->hide();
    ui->Distance->hide();
    ui->Distance_2->hide();
    ui->TripStatus->hide();
    ui->TripStatus_2->hide();
    ui->CancelTrip->setVisible(false);
    ui->Color->hide();
    ui->Color_2->hide();
    ui->DriverName->hide();
    ui->DriverName_2->hide();
    ui->Model->hide();
    ui->Model_2->hide();
    ui->RateBtn->hide();
    if(!ui->label->isHidden()){
        ui->label->hide();
        ui->Code->hide();
        ui->label_2->hide();
        ui->CodeNum->hide();
        return;
    }
    socket->send("get_discount_code");
    bool EROR;
    string output=socket->GetEROR(EROR);
    if(EROR){
        QMessageBox ErorMsg;
        ErorMsg.setText(QString::fromStdString(output));
        ErorMsg.setWindowTitle(QString::fromStdString("EROR"));
        ErorMsg.exec();
        return;
    }
    vector<string>input_array=socket->standard_input(output);
    ui->Code->setText(QString::fromStdString(input_array[0]));
    ui->CodeNum->setText(QString::fromStdString(input_array[1]));
    ui->label->show();
    ui->Code->show();
    ui->label_2->show();
    ui->CodeNum->show();
}

void InterFace::hide_items()
{
    ui->label->hide();
    ui->Code->hide();
    ui->label_2->hide();
    ui->CodeNum->hide();
    ui->Cost->hide();
    ui->Cost_2->hide();
    ui->Distance->hide();
    ui->Distance_2->hide();
    ui->TripStatus->hide();
    ui->TripStatus_2->hide();
    ui->CancelTrip->setVisible(false);
    ui->Color->hide();
    ui->Color_2->hide();
    ui->DriverName->hide();
    ui->DriverName_2->hide();
    ui->Model->hide();
    ui->Model_2->hide();
    ui->RateBtn->setVisible(false);
}

void InterFace::on_ChargeBtn_clicked()
{
    this->hide_items();
    ChargeWin* NewWin=new ChargeWin(this,this->socket);
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::on_RateBtn_clicked()
{
    RateWin* NewWin=new RateWin(ui->DriverName->text().toStdString(),ui->Model->text().toStdString(),ui->Color->text().toStdString(),this,socket);
    NewWin->show();
    this->hide_items();
    this->setEnabled(false);
}

void InterFace::on_RequestBtn_clicked()
{
    this->hide_items();
    TripRequest* NewWin=new TripRequest(true,this,this->socket);
    NewWin->show();
    this->setEnabled(false);
}

void InterFace::on_EstimateBtn_clicked()
{
    this->hide_items();
    TripRequest* NewWin=new TripRequest(false,this,this->socket);
    NewWin->show();
    this->setEnabled(false);
}
