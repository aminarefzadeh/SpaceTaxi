#ifndef ERORMESSAGE_H
#define ERORMESSAGE_H

#include <QWidget>

namespace Ui {
class ErorMessage;
}

class ErorMessage : public QWidget
{
    Q_OBJECT

public:
    explicit ErorMessage(QWidget *parent = 0);
    ~ErorMessage();

private:
    Ui::ErorMessage *ui;
};

#endif // ERORMESSAGE_H
