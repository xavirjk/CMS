#include "databasecontroller.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonDocument>
namespace cm {
namespace controllers {
class DatabaseController::Implementation{
public:
    Implementation(DatabaseController* _dataBaseController)
        :dataBaseController(_dataBaseController)
    {
        if(initialise()){
            qDebug()<<"Database created using SQlite Version:" + sqliteVersion();
            if(createTables()){
                qDebug()<<"Database Tables Created";
            }
            else{
                qDebug()<<"ERROR: unable to create Database Tables";
            }
        }
        else {
            qDebug()<<"ERROR: Creating the DataBase";
        }
    }
    DatabaseController* dataBaseController{nullptr};
    QSqlDatabase database;
private:
    bool initialise(){
        database = QSqlDatabase::addDatabase("QSQLITE","c-m");
        database.setDatabaseName("c-m.sqlite");
        return  database.open();
    }
    bool createTables(){
        return createJsonTable("client");
    }
    bool createJsonTable(const QString& tableName) const{
        QSqlQuery query(database);
        QString sqlStatement = "CREATE TABLE IF NOT EXISTS " + tableName + " (id text primary key, json text not null)";
        if(!query.prepare(sqlStatement)) return false;
        return  query.exec();
    }
    QString sqliteVersion() const{
        QSqlQuery query(database);
        query.exec("SELECT sqlite_version()");
        if(query.next()) return query.value(0).toString();
        return  QString::number(-1);
    }
};
}
namespace controllers {
DatabaseController::DatabaseController(QObject* parent):
    IDatabaseController(parent)
{
    implementation.reset(new Implementation(this));
}
DatabaseController::~DatabaseController(){}
bool DatabaseController::createRow(const QString& tableName, const QString& id,const QJsonObject& jsonObject) const{
    if (tableName.isEmpty()) return  false;
    if (id.isEmpty()) return  false;
    if (jsonObject.isEmpty()) return  false;
    QSqlQuery query(implementation ->database);
    QString sqlStatement = "INSERT OR REPLACE INTO "+ tableName +" (id, json) VALUES (:id, :json)";
    if(!query.prepare(sqlStatement)) return false;
    query.bindValue(":id", QVariant(id));
    query.bindValue(":json",
                    QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));
    if(!query.exec()) return false;
    return  query.numRowsAffected() > 0;
}
bool DatabaseController::deleteRow(const QString& tableName, const QString& id) const{
    if (tableName.isEmpty()) return false;
    if (id.isEmpty()) return false;
    QSqlQuery query(implementation ->database);
    QString sqlStatement = "DELETE FROM " + tableName + " WHERE id=:id";
    if(!query.prepare(sqlStatement)) return false;
    query.bindValue(":id", QVariant(id));
    if(!query.exec()) return false;
    return query.numRowsAffected() > 0;
}
QJsonObject DatabaseController::readRow(const QString& tableName, const QString& id) const{
    if (tableName.isEmpty()) return {};
    if (id.isEmpty()) return {};
    QSqlQuery query(implementation ->database);
    QString sqlStatement = "SELECT json FROM " + tableName + " WHERE id=:id";
    if(!query.prepare(sqlStatement)) return {};
    query.bindValue(":id", QVariant(id));
    if(!query.exec()) return {};
    if(!query.first()) return  {};
    auto json = query.value(0).toByteArray();
    auto jsonDocument = QJsonDocument::fromJson(json);
    if(!jsonDocument.isObject()) return {};
    return jsonDocument.object();
}
bool DatabaseController::updateRow(const QString& tableName, const QString& id,const QJsonObject& jsonObject) const{
    qDebug()<<tableName<<" "<<id<<" "<<jsonObject;
    if (tableName.isEmpty()) return false;
    if (id.isEmpty()) return false;
    if (jsonObject.isEmpty()) return false;
    QSqlQuery query(implementation ->database);
    QString sqlStatement = "UPDATE " + tableName + " SET json=:json WHERE id=:id";
    if(!query.prepare(sqlStatement)) return false;
    query.bindValue(":id", QVariant(id));
    query.bindValue(":json",
                     QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));
    if(!query.exec()) return false;
    return query.numRowsAffected() > 0;
}
QJsonArray DatabaseController::find(const QString& tableName, const QString& searchtext) const{
    if (tableName.isEmpty()) return {};
    if (searchtext.isEmpty()) return {};
    QSqlQuery query(implementation ->database);
    QString sqlStatement = "SELECT json FROM " + tableName + " WHERE lower(json) LIKE :searchtext";
    if(!query.prepare(sqlStatement)) return {};
    query.bindValue(":searchtext",QVariant("%"+ searchtext.toLower()+"%"));
    if (!query.exec()) return {};
    QJsonArray returnValue;
    while (query.next()) {
        auto json = query.value(0).toByteArray();
        auto jsonDocument = QJsonDocument::fromJson(json);
        if(jsonDocument.isObject()){
            returnValue.append(jsonDocument.object());
        }
    }
    return returnValue;
}
}}

