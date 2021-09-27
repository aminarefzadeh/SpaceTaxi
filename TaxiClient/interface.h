#ifndef INTERFACE_H
#define INTERFACE_H
#include "client_socket.h"

#include <QWidget>

namespace Ui {
class InterFace;
}

class InterFace : public QWidget
{
    Q_OBJECT

public:
    explicit InterFace(ClientSocket* cur,std::string name,QWidget *parent = 0);
    ~InterFace();
    void set_status(std::string S){this->Status=S;}
    void set_arrived(bool a){this->arrived=a;}
    void set_address(std::string S){this->Address=S;}
    void set_tripinfo(std::string i){this->TripInfo=i;}
    void set_statusbtn(bool a);
    void RefreshItem();

private slots:
    void on_RefreshBtn_clicked();

    void on_LogOutBtn_clicked();

    void on_SetStatusBtn_clicked();

    void on_AccptRequestBtn_clicked();

    void on_Passenger1_clicked();

    void on_Passenger2_clicked();

    void on_Passenger3_clicked();

    void on_Passenger4_clicked();

    void on_SeeMore_clicked();

    void on_CurrentTripBtn_clicked();

private:
    Ui::InterFace *ui;
    ClientSocket* socket;
    std::string UserName;
    void hide_item();

    std::string Status;
    std::string Address;
    std::string TripInfo;
    bool arrived;
};

#endif // INTERFACE_H
