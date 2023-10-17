#ifndef DOWNREPLY_H
#define DOWNREPLY_H

#include <QThread>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDir>
#include <QReadWriteLock>
#include <QDateTime>
class DownReply : public QThread
{
    Q_OBJECT
public:
    void setNowBytes(qint64& num);
    DownReply(QUrl& url,QNetworkReply* reply,QObject* widget = nullptr);
    ~DownReply();
    void setReply(QNetworkReply* reply);
    void setLock(QReadWriteLock* lock);

protected slots:
    void run();
    void do_readyRead();
    void do_finished();
private:
    QNetworkReply* reply;
    QFile file;
    QReadWriteLock* lock;
    qint64 nowRow = 0;
};

#endif // DOWNREPLY_H
