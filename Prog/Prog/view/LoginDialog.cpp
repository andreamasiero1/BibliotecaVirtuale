
#include "LoginDialog.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDir>
#include <QInputDialog>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), authenticator(QDir::currentPath() + "/data/users.json")
{
    setupUI();
    setStyleSheet();
    setWindowTitle("Biblioteca Virtuale - Login");
    setFixedSize(400, 300);
}

LoginDialog::~LoginDialog() {}

void LoginDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(40, 30, 40, 30);

    // Logo/Title section
    titleLabel = new QLabel("Biblioteca Virtuale");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");

    mainLayout->addWidget(titleLabel);

    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(15);

    usernameEdit = new QLineEdit();
    usernameEdit->setPlaceholderText("Inserisci username");
    usernameEdit->setText("admin");
    connect(usernameEdit, &QLineEdit::textChanged, this, &LoginDialog::onUsernameChanged);

    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setPlaceholderText("Inserisci password");
    passwordEdit->setText("admin");
    connect(passwordEdit, &QLineEdit::textChanged, this, &LoginDialog::onPasswordChanged);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginDialog::attemptLogin);

    formLayout->addRow("Username:", usernameEdit);
    formLayout->addRow("Password:", passwordEdit);

    mainLayout->addLayout(formLayout);

    statusLabel = new QLabel("");
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("color: #e74c3c; font-size: 12px;");
    mainLayout->addWidget(statusLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    loginButton = new QPushButton("Accedi");
    cancelButton = new QPushButton("Annulla");
    addUserButton = new QPushButton("Registra");

    loginButton->setDefault(true);
    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::attemptLogin);
    connect(cancelButton, &QPushButton::clicked, this, &LoginDialog::reject);
    connect(addUserButton, &QPushButton::clicked, this, &LoginDialog::addUser);

    buttonLayout->addWidget(cancelButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(addUserButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(loginButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    mainLayout->addStretch();
}

void LoginDialog::setStyleSheet()
{
    QDialog::setStyleSheet(R"(
        QDialog {
            background-color: #ecf0f1;
        }
        QLineEdit {
            padding: 10px;
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            font-size: 14px;
            background-color: white;
            color: #000000; /* testo nero per visibilità su sfondo bianco */
        }
        QLineEdit::placeholder {
            color: #7f8c8d; /* placeholder grigio ben visibile */
        }
        QLineEdit:focus {
            border-color: #3498db;
        }
        QPushButton {
            padding: 10px 20px;
            border: none;
            border-radius: 5px;
            font-size: 10px;
            font-weight: bold;
            min-width: 70px;
        }
        QPushButton#loginButton {
            background-color: #3498db;
            color: white;
        }
        QPushButton#loginButton:hover {
            background-color: #2980b9;
        }
        QPushButton#loginButton:pressed {
            background-color: #21618c;
        }
        QPushButton#cancelButton {
            background-color: #95a5a6;
            color: white;
        }
        QPushButton#cancelButton:hover {
            background-color: #7f8c8d;
        }
        QPushButton#addUserButton {
            background-color: #27ae60;
            color: white;
        }
        QPushButton#addUserButton:hover {
            background-color: #229954;
        }
        QLabel {
            color: #2c3e50;
        }
    )");

    loginButton->setObjectName("loginButton");
    cancelButton->setObjectName("cancelButton");
    addUserButton->setObjectName("addUserButton");
}

void LoginDialog::attemptLogin()
{
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty())
    {
        statusLabel->setText("Inserisci username e password");
        return;
    }

    if (authenticator.authenticate(username, password))
    {
        statusLabel->setText("Login effettuato con successo!");
        statusLabel->setStyleSheet("color: #27ae60; font-size: 12px;");
        accept(); // Close dialog with accepted result
    }
    else
    {
        QMessageBox::warning(this, "Login Fallito", "Username o password non corretti.\nRiprova.");
        passwordEdit->clear();
        passwordEdit->setFocus();
    }
}

void LoginDialog::onUsernameChanged()
{
    statusLabel->clear();
}

void LoginDialog::onPasswordChanged()
{
    statusLabel->clear();
}

void LoginDialog::addUser()
{
    bool ok;
    QString username = QInputDialog::getText(this, "Aggiungi Utente",
                                             "Username:", QLineEdit::Normal, "", &ok);
    if (!ok || username.isEmpty())
        return;

    QString password = QInputDialog::getText(this, "Aggiungi Utente",
                                             "Password:", QLineEdit::Password, "", &ok);
    if (!ok || password.isEmpty())
        return;

    if (authenticator.addUser(username, password))
    {
        QMessageBox::information(this, "Successo", "Utente aggiunto con successo!");
        statusLabel->setText("Utente aggiunto. Puoi ora effettuare il login.");
        statusLabel->setStyleSheet("color: #27ae60; font-size: 12px;");
    }
    else
    {
        QMessageBox::warning(this, "Errore", "Utente già esistente o errore nell'aggiunta.");
    }
}
