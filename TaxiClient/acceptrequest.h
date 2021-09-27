#ifndef ACCEPTREQUEST_H
#define ACCEPTREQUEST_H
#include "client_socket.h"

#include <QWidget>

class InterFace;
namespace Ui {
class AcceptRequest;
}

class AcceptRequest : public QWidget
{
    Q_OBJECT

public:
    explicit AcceptRequest(InterFace* Previous,ClientSocket* socket,std::string Passenger="");
    ~AcceptRequest();

private slots:
    void on_FindBtn_clicked();

    void on_Passenger_textChanged();

    void on_AcceptBtn_clicked();

    void on_CancelBtn_clicked();

private:
    Ui::AcceptRequest *ui;
    InterFace* Previous;
    ClientSocket* socket;
    std::string Passenger;
};

#endif // ACCEPTREQUEST_H
