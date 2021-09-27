#ifndef CURRENTTRIP_H
#define CURRENTTRIP_H
#include "client_socket.h"

#include <QWidget>
class InterFace;

namespace Ui {
class CurrentTrip;
}

class CurrentTrip : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentTrip(InterFace* Previous,ClientSocket* cur,std::string Info,bool Status,QWidget *parent = 0);
    ~CurrentTrip();

private slots:
    void on_BackBtn_clicked();

    void on_ArrivedBtn_clicked();

    void on_EndTripBtn_clicked();

private:
    Ui::CurrentTrip *ui;
    InterFace* Previous;
    ClientSocket* socket;
    bool Status;
    std::string last_place;
};

#endif // CURRENTTRIP_H
