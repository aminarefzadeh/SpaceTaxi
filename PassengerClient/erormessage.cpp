#include "erormessage.h"
#include "ui_erormessage.h"

ErorMessage::ErorMessage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErorMessage)
{
    ui->setupUi(this);
}

ErorMessage::~ErorMessage()
{
    delete ui;
}
