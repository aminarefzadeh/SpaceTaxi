#ifndef SIGNUP_H
#define SIGNUP_H
#include "client_socket.h"
#include <QWidget>

namespace Ui {
class signup;
}

class signup : public QWidget
{
    Q_OBJECT

public:
    explicit signup(ClientSocket* cur,QWidget *parent = 0);
    ~signup();

private slots:
    void on_pushButton_clicked();

    void on_RegisterBtn_clicked();

    void on_BackBtn_clicked();

private:
    Ui::signup *ui;
    ClientSocket* socket;
};

#endif // SIGNUP_H
