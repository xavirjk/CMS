#include "master-controller.h"
#include <network/networkaccessmanager.h>
#include <network/webrequest.h>

using namespace cm::models;
using namespace cm::networking;
namespace cm {
namespace controllers {

class MasterController::Implementation
{
public:
	Implementation(MasterController* _masterController)
		: masterController(_masterController)
	{
		navigationController = new NavigationController(masterController);
        databaseController = new DatabaseController(masterController);
		newClient = new Client(masterController);
        networkAccessManager = new NetworkAccessManager(masterController);
        clientSearch = new ClientSearch(masterController,databaseController);
        rssWebRequest = new WebRequest(masterController, networkAccessManager,QUrl("http://localhost:3000/userData"));
        commandController = new CommandController(masterController,databaseController,newClient,clientSearch,navigationController,rssWebRequest);

        QObject::connect(rssWebRequest, &WebRequest::requestComplete, masterController ,&MasterController::onRssReplyReceived);
    }

	MasterController* masterController{nullptr};
	CommandController* commandController{nullptr};
	NavigationController* navigationController{nullptr};
    DatabaseController* databaseController{nullptr};
    ClientSearch* clientSearch{nullptr};
	Client* newClient{nullptr};
    NetworkAccessManager* networkAccessManager{nullptr};
    WebRequest* rssWebRequest{nullptr};
	QString welcomeMessage = "Welcome to the Client Management system!";
};

MasterController::MasterController(QObject* parent)
	: QObject(parent)
{
	implementation.reset(new Implementation(this));
}

MasterController::~MasterController()
{
}

void MasterController::selectClient(Client *client)
{
    implementation->navigationController->goEditClientView(client);
}

void MasterController::onRssReplyReceived(int statusCode, QByteArray body)
{
    qDebug() <<"Received Rss Request Status Code "<<statusCode<<":";
    qDebug() <<body;
    qDebug() <<"***********************************************************";
}

CommandController* MasterController::commandController()
{
	return implementation->commandController;
}

NavigationController* MasterController::navigationController()
{
	return implementation->navigationController;
}

DatabaseController* MasterController::databaseController()
{
    return implementation->databaseController;
}

Client* MasterController::newClient()
{
    qDebug()<<"Fron new Client "<<implementation->newClient;
	return implementation->newClient;
}

ClientSearch* MasterController::clientSearch()
{
    return implementation->clientSearch;
}
const QString& MasterController::welcomeMessage() const
{
	return implementation->welcomeMessage;
}

}}
