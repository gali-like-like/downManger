#include "downreply.h"

DownReply::DownReply(QUrl& url,QNetworkReply* reply,QObject* widget):QThread(widget)
{
//    this->setParent(widget);
    QString strUrl = url.toString();
    QString newUrl = strUrl.sliced(strUrl.lastIndexOf('/')+1);
    qDebug()<<"最后一个路径为 "<<newUrl;
    QString absPath = QDir::currentPath() + "/downFolder/";

    QDir dir(absPath);
    if(!dir.exists())
    {
        dir.mkdir(dir.absolutePath());
    }
    file.setFileName(absPath + "/"+newUrl);
    qDebug()<<"完成路径为 "<<file.fileName();
    this->reply = reply;
}

void DownReply::setReply(QNetworkReply* reply)
{
    this->reply = reply;
}

void DownReply::do_finished()
{
    lock->unlock();
    file.close();
    qDebug()<<"写入完成";
}

void DownReply::setLock(QReadWriteLock* lock)
{
    this->lock = lock;
}

void DownReply::do_readyRead()
{

}

void DownReply::run()
{
    if(!file.isOpen())
    {
        qDebug()<<"进入准备读取";
        if(file.open(QIODevice::WriteOnly | QIODevice::Append))
        {
            qDebug()<<"准备写入文件";
            lock->tryLockForWrite(200);
            while(!reply->atEnd())
            {
                file.write(reply->readLine());
                this->nowRow ++;
            }
            qDebug()<<"写入了"<<nowRow;
            return ;
        }
    }
    qDebug()<<"准备写入文件";
    lock->tryLockForWrite(200);
    file.write(reply->readAll());
}

void DownReply::setNowBytes(qint64& value)
{

}

DownReply::~DownReply()
{
    reply->deleteLater();
    if(file.isOpen())
    {
        file.close();
    }
}
