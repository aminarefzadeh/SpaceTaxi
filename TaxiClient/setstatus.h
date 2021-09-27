#ifndef SETSTATUS_H
#define SETSTATUS_H
#include "client_socket.h"
#include <QWidget>

class InterFace;
namespace Ui {
class SetStatus;
}

class SetStatus : public QWidget
{
    Q_OBJECT

public:
    explicit SetStatus(InterFace* Previous,ClientSocket* cur,QWidget *parent = 0);
    ~SetStatus();

private slots:
    void on_radioButton_clicked();

    void on_UnavailableBtn_clicked();

    void on_AvailableBtn_clicked();

    void on_Back_clicked();

    void on_OkBtn_clicked();

private:
    Ui::SetStatus *ui;
    InterFace* PreviousWin;
    ClientSocket* socket;
};

#endif // SETSTATUS_H
