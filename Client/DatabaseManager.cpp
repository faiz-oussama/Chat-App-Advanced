#include "DatabaseManager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void initializeDatabase(const QString& dbName) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Error: Unable to open database" << db.lastError();
        return;
    }

    QSqlQuery query;
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS chats (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            sender TEXT NOT NULL,
            receiver TEXT NOT NULL,
            message TEXT NOT NULL,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Error: Unable to create table" << query.lastError();
    }
}

void saveChatMessage(const QString& sender, const QString& receiver, const QString& message) {
    QSqlQuery query;
    query.prepare("INSERT INTO chats (sender, receiver, message) VALUES (:sender, :receiver, :message)");
    query.bindValue(":sender", sender);
    query.bindValue(":receiver", receiver);
    query.bindValue(":message", message);

    if (!query.exec()) {
        qDebug() << "Error: Unable to insert chat message" << query.lastError();
    }
}

QList<QVariantMap> retrieveChatMessages() {
    QList<QVariantMap> chatList;
    QSqlQuery query("SELECT * FROM chats ORDER BY timestamp ASC");

    while (query.next()) {
        QVariantMap chat;
        chat["id"] = query.value("id");
        chat["sender"] = query.value("sender");
        chat["receiver"] = query.value("receiver");
        chat["message"] = query.value("message");
        chat["timestamp"] = query.value("timestamp");
        chatList.append(chat);
    }
    return chatList;
}
