#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <cm-lib_global.h>
#include <controllers/command-controller.h>
#include <controllers/navigation-controller.h>
#include <controllers/databasecontroller.h>
#include <models/clientsearch.h>
#include <models/client.h>

namespace cm {
namespace controllers {

class CMLIBSHARED_EXPORT MasterController : public QObject
{
	Q_OBJECT

	Q_PROPERTY( QString ui_welcomeMessage READ welcomeMessage CONSTANT )
	Q_PROPERTY( cm::controllers::NavigationController* ui_navigationController READ navigationController CONSTANT )
	Q_PROPERTY( cm::controllers::CommandController* ui_commandController READ commandController CONSTANT )
	Q_PROPERTY( cm::models::Client* ui_newClient READ newClient CONSTANT )
    Q_PROPERTY(cm::controllers::DatabaseController* ui_databaseController READ databaseController CONSTANT)
    Q_PROPERTY(cm::models::ClientSearch* ui_clientSearch READ clientSearch CONSTANT)
public:
	explicit MasterController(QObject* parent = nullptr);
	~MasterController();

	CommandController* commandController();
	NavigationController* navigationController();
    DatabaseController* databaseController();
    models::ClientSearch* clientSearch();
	models::Client* newClient();
	const QString& welcomeMessage() const;

signals:
    void rssChannelChanged();

public slots:
    void selectClient(cm::models:: Client* client);
    void onRssReplyReceived(int statusCode, QByteArray body);

private:
	class Implementation;
	QScopedPointer<Implementation> implementation;
};

}}

#endif
