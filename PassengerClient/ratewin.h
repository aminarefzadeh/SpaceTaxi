#ifndef RATEWIN_H
#define RATEWIN_H
#include "client_socket.h"
#include <QWidget>
class InterFace;

namespace Ui {
class RateWin;
}

class RateWin : public QWidget
{
    Q_OBJECT

public:
    explicit RateWin(std::string DriverName,std::string Model,std::string Color,InterFace* PreviousWin,ClientSocket* cur,QWidget *parent = 0);
    ~RateWin();

private slots:
    void on_RateBtn_clicked();

    void on_BackBtn_clicked();

private:
    Ui::RateWin *ui;
    ClientSocket* socket;
    InterFace* PreviosWin;
};

#endif // RATEWIN_H
