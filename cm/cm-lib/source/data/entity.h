#ifndef ENTITY_H
#define ENTITY_H

#include <map>

#include <QObject>
#include <QScopedPointer>

#include <cm-lib_global.h>
#include <data/data-decorator.h>
#include <data/entity-collection.h>
#include <data/string-decorator.h>

namespace cm {
namespace data {

class CMLIBSHARED_EXPORT Entity : public QObject
{
	Q_OBJECT

public:
    Entity(QObject* parent = nullptr, const QString& key = "SomeEntityKey");
	Entity(QObject* parent, const QString& key, const QJsonObject& jsonObject);
	virtual ~Entity();

public:
	const QString& key() const;
    const QString& id() const;
	void update(const QJsonObject& jsonObject);
    void setPrimaryKey(StringDecorator* primarykey);
	QJsonObject toJson() const;

signals:
	void childCollectionsChanged(const QString& collectionKey);
	void childEntitiesChanged();
	void dataDecoratorsChanged();

protected:
	Entity* addChild(Entity* entity, const QString& key);
	EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);
	DataDecorator* addDataItem(DataDecorator* dataDecorator);

protected:
	class Implementation;
	QScopedPointer<Implementation> implementation;
};

}}

#endif
