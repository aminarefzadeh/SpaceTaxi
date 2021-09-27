#include "showrequests.h"
#include "ui_showrequests.h"
#include "interface.h"
#include "QMessageBox"

using namespace std;
ShowRequests::ShowRequests(InterFace* Previous,ClientSocket* cur,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowRequests)
{
    ui->setupUi(this);
    this->Previous=Previous;
    this->socket=cur;
    this->socket->send("show_trip_requests");
    bool EROR;
    string output=this->socket->GetEROR(EROR);
    if(EROR){
        QMessageBox ErorMsg;
        ErorMsg.setText(QString::fromStdString(output));
        ErorMsg.setWindowTitle(QString::fromStdString("EROR"));
        this->hide();
        ErorMsg.exec();
        Previous->setEnabled(true);
        return;
    }
    ui->info->setText(QString::fromStdString(output));
    ui->label_2->setPixmap(QPixmap("/home/amin/TaxiClient/c4.jpg"));
}

ShowRequests::~ShowRequests()
{
    this->hide();
    Previous->setEnabled(true);
    delete ui;
}

void ShowRequests::on_OkBtn_clicked()
{
    this->hide();
    Previous->setEnabled(true);
}
