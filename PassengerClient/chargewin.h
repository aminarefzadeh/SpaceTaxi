#ifndef CHARGEWIN_H
#define CHARGEWIN_H
#include "client_socket.h"
#include "interface.h"

#include <QWidget>

namespace Ui {
class ChargeWin;
}

class ChargeWin : public QWidget
{
    Q_OBJECT

public:
    explicit ChargeWin(InterFace* PreviousWin,ClientSocket* cur,QWidget *parent = 0);
    ~ChargeWin();

private slots:
    void on_ChargeBtn_clicked();

    void on_BackBtn_clicked();

private:
    Ui::ChargeWin *ui;
    ClientSocket* socket;
    InterFace* PreviousWin;
};

#endif // CHARGEWIN_H
