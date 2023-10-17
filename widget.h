#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QMessageBox>
#include <QReadWriteLock>
#include "downreply.h"
#include "showprogressbar.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initTableWidget();
    QProgressBar* getProgressBar();
public slots:
    void createThread();
    void delRow();
    void addRow();
    void stopDown();
    void pause();
    void remuse();
//    void insertRow();
private slots:
    void on_checkBox_toggled(bool checked);

    void on_btnRemove_clicked();

private:
    Ui::Widget *ui;
    QNetworkAccessManager* manager;
    QNetworkReply* reply;
    QNetworkRequest quest;
    QReadWriteLock* lock;
    DownReply* threadDown;
    ShowProgressBar* threadShow;
};
#endif // WIDGET_H
