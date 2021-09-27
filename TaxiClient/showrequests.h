#ifndef SHOWREQUESTS_H
#define SHOWREQUESTS_H
#include "client_socket.h"

#include <QWidget>

class InterFace;
namespace Ui {
class ShowRequests;
}

class ShowRequests : public QWidget
{
    Q_OBJECT

public:
    explicit ShowRequests(InterFace* Previous,ClientSocket* cur,QWidget *parent = 0);
    ~ShowRequests();

private slots:
    void on_OkBtn_clicked();

private:
    Ui::ShowRequests *ui;
    InterFace* Previous;
    ClientSocket* socket;
};

#endif // SHOWREQUESTS_H
