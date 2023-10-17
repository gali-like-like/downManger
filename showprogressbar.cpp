#include "showprogressbar.h"

ShowProgressBar::ShowProgressBar(QObject *parent)
    : QThread{parent}
{

}

void ShowProgressBar::setProgressBar(QProgressBar* progress)
{
    this->progressBar = progress;
}

void ShowProgressBar::run(qint64 now,qint64 total)
{
    this->do_downProgressBar(now,total);
}



void ShowProgressBar::setLock(QReadWriteLock* lock)
{
    this->lock = lock;
}

void ShowProgressBar::do_downProgressBar(qint64 now,qint64 total)
{
    if(this->progressBar == nullptr) {return;}
    else
    {
        qDebug()<<"显示线程 总共KB数 "<<QString::number(total/1024);
        lock->tryLockForRead(200);
        this->progressBar->setValue(now/1024);
        this->progressBar->setTextVisible(true);
        this->progressBar->setFormat("%vKB");
        this->progressBar->setMaximum(total/1024);
    }
}
