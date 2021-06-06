#include "webrequest.h"
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QNetworkRequest>
namespace cm {
namespace networking {
static const QMap<QNetworkReply::NetworkError, QString> networkErrorMapper =
{
   {QNetworkReply::ConnectionRefusedError, "Remote server Refused Connection"},
   {QNetworkReply::UnknownNetworkError, "Unknown Network Error Occured"}
};
class WebRequest::Implementation {
public:
    Implementation(WebRequest* _webRequest, INetworkAccessManager* _networkAccessManager, const QUrl& _url)
        :webRequest(_webRequest)
        ,netWorkAccessManager(_networkAccessManager)
        ,url(_url)
    {}
    WebRequest* webRequest{nullptr};
    INetworkAccessManager* netWorkAccessManager{nullptr};
    QUrl url{};
    QNetworkReply* reply{nullptr};
public:
    bool isBusy() const{
        return isBusy_ ;
    }
    void setIsBusy(bool value){
        if(value != isBusy_){
            isBusy_ = value;
            emit webRequest->isBusyChanged();
        }
    }
private:
    bool isBusy_ {false};
};
WebRequest::WebRequest(QObject* parent, INetworkAccessManager* networkAccessManager, const QUrl& url)
    :QObject(parent),
      IWebRequest()
{
    implementation.reset(new WebRequest::Implementation(this, networkAccessManager, url));
}
WebRequest::~WebRequest(){}
void WebRequest::execute(){
    if(implementation->isBusy()){
        qDebug() <<"Busy";
        return;
    }
    if(!implementation->netWorkAccessManager->isNetworkAccessible()){
        qDebug() <<"Not Accessible";
        emit error("Network not Accessible");
        return;
    }
    implementation->setIsBusy(true);
    QNetworkRequest request;
    request.setUrl(implementation->url);
    implementation->reply = implementation->netWorkAccessManager->get(request);
    qDebug() <<"Reply "<<implementation->reply;
    if(implementation->reply != nullptr){
        connect(implementation->reply, &QNetworkReply::finished, this, &WebRequest::replyDelegate);
        connect(implementation->reply, &QNetworkReply::sslErrors, this, &WebRequest::sslErrorsDelegate);
    }
}

bool WebRequest::isBusy() const{
    return implementation->isBusy();
}

void WebRequest::setUrl(const QUrl &url){
    if( url != implementation->url)
    {
        implementation->url = url;
        emit urlChanged();
    }
}

QUrl WebRequest::url() const{
    return implementation->url;
}

void WebRequest::replyDelegate()
{
    implementation->setIsBusy(false);
    if(implementation->reply == nullptr)
    {
        emit error("Unexpected Error - Reply object is null");
        return;
    }
    disconnect(implementation->reply, &QNetworkReply::finished, this, &WebRequest::replyDelegate);
    disconnect(implementation->reply, &QNetworkReply::sslErrors, this, &WebRequest::sslErrorsDelegate);

    auto statusCode = implementation->reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray responseBody = implementation ->reply->readAll();
    QJsonDocument jsdoc(QJsonDocument::fromJson(responseBody));
    qDebug() <<"Document "<<jsdoc;
    QJsonArray jsArr = jsdoc.array();
    for (int i = 0; i< jsArr.size();i++){
        QJsonObject obj =jsArr[i].toObject();
        qDebug() <<obj.value("email").toString();
    }
    auto replyStatus = implementation->reply->error();
    implementation->reply->deleteLater();
    if(replyStatus != QNetworkReply::NoError){
        emit error(networkErrorMapper[implementation->reply->error()]);
    }
    emit requestComplete(statusCode, responseBody);
}
void WebRequest::sslErrorsDelegate(const QList<QSslError>& errors)
{
    QString sslError;
    for(const auto& error : errors){
        sslError += error.errorString() + "\n";
    }
    emit error(sslError);
}
}}
