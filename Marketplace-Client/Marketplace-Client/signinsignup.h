#ifndef SIGNINSIGNUP_H
#define SIGNINSIGNUP_H

#include <QWidget>

namespace Ui {
class SignInSignUp;
}

class SignInSignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignInSignUp(QWidget *parent = nullptr);
    ~SignInSignUp();

private:
    Ui::SignInSignUp *ui;
};

#endif // SIGNINSIGNUP_H
