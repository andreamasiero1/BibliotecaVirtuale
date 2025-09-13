#include "UserAuthenticator.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>

UserAuthenticator::UserAuthenticator(const QString &usersFilePath)
    : usersFilePath(usersFilePath)
{
    loadUsers();
}

UserAuthenticator::~UserAuthenticator()
{
    qDeleteAll(users);
}

bool UserAuthenticator::authenticate(const QString &username, const QString &password)
{
    for (User *user : users)
    {
        if (user->getUsername() == username && user->getPassword() == password)
        {
            return true;
        }
    }
    return false;
}

bool UserAuthenticator::addUser(const QString &username, const QString &password)
{
    for (User *user : users)
    {
        if (user->getUsername() == username)
        {
            qDebug() << "Utente" << username << "esiste già.";
            return false;
        }
    }

    users.append(new User(username, password));
    saveUsers();
    qDebug() << "Utente" << username << "aggiunto con successo.";
    return true;
}

void UserAuthenticator::loadUsers()
{
    QFile file(usersFilePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "File utenti non trovato, ne creo uno nuovo:" << usersFilePath;
        addUser("admin", "admin");
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isArray())
    {
        qDebug() << "Errore nel parsing del file utenti JSON.";
        return;
    }

    QJsonArray userArray = doc.array();
    for (const QJsonValue &value : userArray)
    {
        QJsonObject obj = value.toObject();
        users.append(new User(obj["username"].toString(), obj["password"].toString()));
    }
}

void UserAuthenticator::saveUsers()
{
    QJsonArray userArray;
    for (User *user : users)
    {
        QJsonObject obj;
        obj["username"] = user->getUsername();
        obj["password"] = user->getPassword();
        userArray.append(obj);
    }

    QJsonDocument doc(userArray);
    QFileInfo fi(usersFilePath);
    QDir().mkpath(fi.dir().absolutePath());
    QFile file(usersFilePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Errore nel salvataggio del file utenti:" << usersFilePath;
        return;
    }
    file.write(doc.toJson());
    file.close();
}
