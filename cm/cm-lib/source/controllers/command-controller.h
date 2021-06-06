#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <cm-lib_global.h>
#include <framework/command.h>
#include "I-database-controller.h"
#include "navigation-controller.h"
#include <models/client.h>
#include <models/clientsearch.h>
#include <network/i-web-request.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT CommandController : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_createClientViewContextCommands READ ui_createClientViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_findClientViewContextCommands READ ui_findClientViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_editClientViewContextCommands READ ui_editClientViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<cm::framework::Command> ui_rssViewContextCommands READ ui_rssViewContextCommands CONSTANT)
public:
    explicit CommandController(QObject* _parent = nullptr, IDatabaseController* databaseController = nullptr, models::Client* newClient = nullptr, models::ClientSearch* clientSearch = nullptr, NavigationController* navigationController = nullptr, networking::IWebRequest* rssWebRequest = nullptr);
	~CommandController();

	QQmlListProperty<framework::Command> ui_createClientViewContextCommands();
    QQmlListProperty<framework::Command> ui_findClientViewContextCommands();
    QQmlListProperty<framework::Command> ui_editClientViewContextCommands();
    QQmlListProperty<framework::Command> ui_rssViewContextCommands();

public slots:
	void onCreateClientSaveExecuted();
    void onFindClientSearchExecuted();
    void onEditClientSaveExecuted();
    void onEditClientDeleteExecuted();
    void setSelectedClient(cm::models::Client* client);
    void onRssRefreshExecuted();

private:
	class Implementation;
	QScopedPointer<Implementation> implementation;
};

}}

#endif
