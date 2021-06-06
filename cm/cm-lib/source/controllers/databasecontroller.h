#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include "cm-lib_global.h"
#include "controllers/I-database-controller.h"

#include <QScopedPointer>
#include <QObject>
namespace cm {
namespace controllers {
class CMLIBSHARED_EXPORT DatabaseController: public IDatabaseController{
    Q_OBJECT
public:
    DatabaseController(QObject* parent = nullptr);
    ~DatabaseController();
    bool createRow(const QString& tableName, const QString& id,const QJsonObject& jsonObject) const override;
    QJsonObject readRow(const QString& tableName, const QString& id) const override;
    QJsonArray find(const QString& tableName, const QString& searchtext) const override;
    bool updateRow(const QString& tableName, const QString& id,const QJsonObject& jsonObject) const override;
    bool deleteRow(const QString& tableName, const QString& id) const override;
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};
}}
#endif // DATABASECONTROLLER_H
