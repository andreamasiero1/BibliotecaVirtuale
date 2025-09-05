#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPixmap>
#include "UserAuthenticator.h"

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void attemptLogin();
    void onUsernameChanged();
    void onPasswordChanged();
    void addUser();

private:
    void setupUI();
    void setStyleSheet();

    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *cancelButton;
    QPushButton *addUserButton;
    QLabel *titleLabel;
    QLabel *logoLabel;
    QLabel *statusLabel;

    UserAuthenticator authenticator;
};

#endif // LOGINDIALOG_H
