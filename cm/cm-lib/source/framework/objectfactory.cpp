#include "objectfactory.h"

#include <controllers/command-controller.h>
#include <controllers/databasecontroller.h>
#include <controllers/navigation-controller.h>
#include <models/client.h>
#include <models/clientsearch.h>
#include <network/networkaccessmanager.h>
#include <network/webrequest.h>
using namespace cm::models;
using namespace cm::networking;
using namespace cm::controllers;
namespace cm {
namespace framework {
ObjectFactory::ObjectFactory():
    IObjectFactory()
{

}

Client* ObjectFactory::createClient(QObject* parent) const
{
    return new Client(parent);
}

ClientSearch* ObjectFactory::createClientSearch(QObject* parent, IDatabaseController* databaseController) const
{
    return  new ClientSearch(parent, databaseController);
}

INetworkAccessManager* ObjectFactory::createNetworkAccessManager(QObject* parent) const
{
    return new NetworkAccessManager(parent);
}

IWebRequest* ObjectFactory::createWebRequest(QObject* parent, INetworkAccessManager* networkAccessManager, const QUrl& url) const
{
    return new WebRequest(parent,networkAccessManager,url);
}
}}
