#ifndef SHOWPROGRESSBAR_H
#define SHOWPROGRESSBAR_H

#include <QThread>
#include <QProgressBar>
#include <QReadWriteLock>
#include <QDebug>
class ShowProgressBar : public QThread
{
    Q_OBJECT
public:
    explicit ShowProgressBar(QObject *parent = nullptr);
    void setProgressBar(QProgressBar* progress);
    void setLock(QReadWriteLock* lock);
public slots:
    void run(qint64 now,qint64 total);
    void do_downProgressBar(qint64 now,qint64 total);
private:
    QProgressBar* progressBar;
    QReadWriteLock* lock;
};

#endif // SHOWPROGRESSBAR_H
