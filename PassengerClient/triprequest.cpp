#include "triprequest.h"
#include "ui_triprequest.h"
#include "interface.h"
#include "QMessageBox"
using namespace std;

TripRequest::TripRequest(bool Request,InterFace* PreviousWin,ClientSocket* cur,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TripRequest)
{
    ui->setupUi(this);
    ui->label_2->hide();
    ui->label_3->hide();
    ui->Cost->hide();
    ui->Distance->hide();
    ui->label_4->hide();
    this->socket=cur;
    this->PreviousWin=PreviousWin;
    this->Request=Request;
    ui->label_5->setPixmap(QPixmap("/home/amin/TaxiClient/c4.jpg"));
}

TripRequest::~TripRequest()
{
    this->hide();
    this->PreviousWin->setEnabled(true);
    delete ui;
}

void TripRequest::on_BackBtn_clicked()
{
    this->hide();
    this->PreviousWin->setEnabled(true);
}

void TripRequest::on_OkBtn_clicked()
{
    ui->label_4->hide();
    if(ui->Destination->toPlainText().toStdString().empty()){
        ui->label_4->show();
        return;
    }
    string input;
    if(this->Request)
        input.append("request_trip ");
    else
        input.append("estimate_trip ");
    input.append(ui->Destination->toPlainText().toStdString());
    socket->send(input);
    bool EROR;
    string output=socket->GetEROR(EROR);
    if(EROR){
        QMessageBox ErorMsg;
        ErorMsg.setText(QString::fromStdString(output));
        ErorMsg.setWindowTitle(QString::fromStdString("EROR"));
        ErorMsg.exec();
        return;
    }
    vector<string>output_array=socket->standard_input(output);
    ui->label_2->show();
    ui->label_3->show();
    ui->Cost->setText(QString::fromStdString(output_array[0]));
    ui->Distance->setText(QString::fromStdString(output_array[1]));
    ui->Cost->show();
    ui->Distance->show();
    if(this->Request){
        QMessageBox MsgWin;
        MsgWin.setText(QString::fromStdString("Request sended succesfully wait for driver accept"));
        MsgWin.setWindowTitle(QString::fromStdString("SUCCESS"));
        this->hide();
        MsgWin.exec();
        PreviousWin->setEnabled(true);
        PreviousWin->set_cost(output_array[0]);
        PreviousWin->set_distance(output_array[1]);
    }
}
