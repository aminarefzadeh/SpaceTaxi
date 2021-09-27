#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "client_socket.h"

#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(ClientSocket* cur,QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_SignInBtn_clicked();

    void on_SignUpBtn_clicked();

private:
    Ui::LoginWindow *ui;
    ClientSocket* socket;
};

#endif // LOGINWINDOW_H
