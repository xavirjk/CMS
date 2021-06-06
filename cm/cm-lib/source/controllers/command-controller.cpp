#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace cm::framework;
using namespace cm::models;
using namespace cm::networking;
namespace cm {
namespace controllers {

class CommandController::Implementation
{
public:
    Implementation(CommandController* _commandController, IDatabaseController* _databaseController, Client* _newClient, ClientSearch* _clientSearch, NavigationController* _navigationController, IWebRequest* _rssWebRequest)
		: commandController(_commandController)
         ,databaseController(_databaseController)
         ,navigationController(_navigationController)
         ,newClient(_newClient)
         ,clientSearch(_clientSearch)
         ,rssWebRequest(_rssWebRequest)
	{
		Command* createClientSaveCommand = new Command( commandController, QChar( 0xf0c7 ), "Save" );
        Command* findClientSearchCommand = new Command( commandController, QChar( 0xf002 ), "Search");
        Command* editClientSaveCommand = new Command( commandController, QChar( 0xf0c7) ,"Save");
        Command* editClientDeleteCommand = new Command( commandController,QChar( 0xf235), "Delete");
        Command* rssRefreshCommand = new Command(commandController, QChar( 0xf021 ),"Refresh");
        QObject::connect( createClientSaveCommand, &Command::executed, commandController, &CommandController::onCreateClientSaveExecuted );
        QObject::connect( findClientSearchCommand, &Command::executed, commandController, &CommandController::onFindClientSearchExecuted );
        QObject::connect( editClientSaveCommand, &Command::executed, commandController, &CommandController::onEditClientSaveExecuted );
        QObject::connect( editClientDeleteCommand, &Command::executed, commandController,&CommandController::onEditClientDeleteExecuted );
        QObject::connect(rssRefreshCommand, &Command::executed, commandController, &CommandController::onRssRefreshExecuted);
        createClientViewContextCommands.append( createClientSaveCommand );
        findClientViewContextCommands.append( findClientSearchCommand );
        editClientViewContextCommands.append( editClientDeleteCommand );
        editClientViewContextCommands.append( editClientSaveCommand );
        rssViewContextCommand.append( rssRefreshCommand);
	}

	CommandController* commandController{nullptr};
    IDatabaseController* databaseController{nullptr};
    NavigationController* navigationController{nullptr};
    Client* newClient{nullptr};
    ClientSearch* clientSearch{nullptr};
    Client* selectedClient{nullptr};
    IWebRequest* rssWebRequest{nullptr};

	QList<Command*> createClientViewContextCommands{};
    QList<Command*> findClientViewContextCommands{};
    QList<Command*> editClientViewContextCommands{};
    QList<Command*> rssViewContextCommand{};
};

CommandController::CommandController(QObject* parent, IDatabaseController* databaseController, Client* newClient, ClientSearch* clientSearch, NavigationController* navigationController, IWebRequest* rssWebRequest)
	: QObject(parent)
{
    implementation.reset(new Implementation(this, databaseController, newClient, clientSearch, navigationController, rssWebRequest));
}

CommandController::~CommandController()
{
}

QQmlListProperty<Command> CommandController::ui_createClientViewContextCommands()
{
	return QQmlListProperty<Command>(this, implementation->createClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_findClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->findClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_editClientViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->editClientViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_rssViewContextCommands()
{
    return  QQmlListProperty<Command>(this, implementation->rssViewContextCommand);
}

void CommandController::onCreateClientSaveExecuted()
{
	qDebug() << "You executed the Save command!";
    implementation->databaseController->createRow(implementation->newClient->key(), implementation->newClient->id(), implementation->newClient->toJson());
    implementation->clientSearch->searchText()->setValue(implementation->newClient->id());
    implementation->clientSearch->search();
    implementation->navigationController->goFindClientView();
    qDebug()<<" New Client Saved";
}

void CommandController::onFindClientSearchExecuted()
{
    qDebug() <<"You executed the Search command";
    implementation->clientSearch->search();
}

void CommandController::onEditClientSaveExecuted()
{
    qDebug() <<"You executed the Edit command";
    implementation->databaseController->updateRow(implementation->selectedClient->key(),implementation->selectedClient->id(), implementation->selectedClient->toJson());
    qDebug() <<"Updated Client Saved";
}

void CommandController::onEditClientDeleteExecuted()
{
    qDebug() <<"You executed the Delete command";
    implementation->databaseController->deleteRow(implementation->selectedClient->key(),implementation->selectedClient->id());
    implementation->selectedClient = nullptr;
    implementation->newClient = nullptr;
    qDebug() <<"Client Deleted";
    implementation->clientSearch->search();
    implementation->navigationController->goDashboardView();
}

void CommandController::setSelectedClient(Client* client)
{
    implementation->selectedClient = client;
}
void CommandController::onRssRefreshExecuted()
{
    qDebug() << "You executed the Rss Refresh command!";
    implementation->rssWebRequest->execute();
}
}}
