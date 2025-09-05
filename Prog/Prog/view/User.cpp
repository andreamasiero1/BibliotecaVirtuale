#include "User.h"

User::User(const QString &username, const QString &password)
    : username(username), password(password) {}

QString User::getUsername() const
{
    return username;
}

QString User::getPassword() const
{
    return password;
}
