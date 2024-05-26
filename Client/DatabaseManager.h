#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QList>
#include <QVariantMap>

void initializeDatabase(const QString& dbName);
void saveChatMessage(const QString& sender, const QString& receiver, const QString& message);
QList<QVariantMap> retrieveChatMessages();

#endif // DATABASEMANAGER_H
