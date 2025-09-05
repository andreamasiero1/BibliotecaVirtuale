#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(const QString &username, const QString &password);

    QString getUsername() const;
    QString getPassword() const;

private:
    QString username;
    QString password;
};

#endif // USER_H
