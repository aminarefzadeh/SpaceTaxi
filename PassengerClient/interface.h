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
    explicit InterFace(ClientSocket* cur,std::string UserName,QWidget *parent = 0);
    ~InterFace();
    void set_cost(std::string a){cost=a;}
    void set_distance(std::string a){distance=a;}

private slots:
    void on_Refresh_clicked();

    void on_commandLinkButton_clicked();

    void on_LastTrip_clicked();

    void on_CancelTrip_clicked();

    void on_CodeBtn_clicked();

    void on_ChargeBtn_clicked();

    void on_RateBtn_clicked();

    void on_RequestBtn_clicked();

    void on_EstimateBtn_clicked();

private:
    void hide_items();
    Ui::InterFace *ui;
    ClientSocket* socket;
    std::string UserName;
    std::string cost;
    std::string distance;
};

#endif // INTERFACE_H
