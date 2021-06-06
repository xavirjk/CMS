#ifndef IWEBREQUEST_H
#define IWEBREQUEST_H

#include <QUrl>
#include "cm-lib_global.h"
namespace cm {
namespace networking {
class IWebRequest{
public:
    IWebRequest(){}
    ~IWebRequest(){}

    virtual void execute() = 0;
    virtual bool isBusy() const = 0;
    virtual void setUrl(const QUrl& url) = 0;
    virtual QUrl url() const = 0;
};
}}
#endif // IWEBREQUEST_H
