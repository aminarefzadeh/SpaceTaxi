#ifndef TRIPREQUEST_H
#define TRIPREQUEST_H
#include "client_socket.h"
#include <QWidget>
class InterFace;

namespace Ui {
class TripRequest;
}

class TripRequest : public QWidget
{
    Q_OBJECT

public:
    explicit TripRequest(bool Request,InterFace* PreviousWin,ClientSocket* cur,QWidget *parent = 0);
    ~TripRequest();

private slots:
    void on_BackBtn_clicked();

    void on_OkBtn_clicked();

private:
    Ui::TripRequest *ui;
    InterFace* PreviousWin;
    ClientSocket* socket;
    bool Request;
};

#endif // TRIPREQUEST_H
