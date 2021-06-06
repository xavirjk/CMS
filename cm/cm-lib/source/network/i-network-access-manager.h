#ifndef INETWORKACCESSMANAGER_H
#define INETWORKACCESSMANAGER_H
#include <QNetworkRequest>
#include <QNetworkReply>
#include "cm-lib_global.h"
namespace cm {
namespace networking {
class  INetworkAccessManager{
public:
    INetworkAccessManager(){};
    virtual ~INetworkAccessManager(){}

    virtual QNetworkReply* get(const QNetworkRequest& request) = 0;
    virtual bool isNetworkAccessible() const = 0;
};


}}
#endif // INETWORKACCESSMANAGER_H
