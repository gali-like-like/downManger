#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->setLayout(ui->horizontalLayout_2);
    initTableWidget();
    manager = new QNetworkAccessManager(this);
    lock = new QReadWriteLock();
}

void Widget::initTableWidget()
{
    for(qint8 row = 0;row<10;row++)
    {
        for(qint8 col = 0;col<8;col++)
        {
            if(col == 0)
            {
                QTableWidgetItem* item = ui->tableWidget->item(row,col);
                if(item == nullptr)
                {
                    QTableWidgetItem* item = new QTableWidgetItem();
                    item->setCheckState(Qt::Unchecked);
                    ui->tableWidget->setItem(row,col,item);
                }
            }
            if(col == 1)
            {
                QLabel* labelTask = new QLabel("任务"+QString::number(row),this);
                ui->tableWidget->setCellWidget(row,col,labelTask);
            }
            else if(col == 2)
            {
                QLineEdit* lineEditUrl = new QLineEdit(this);
                lineEditUrl->setText("https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/online_installers/qt-unified-linux-x64-online.run");
                ui->tableWidget->setCellWidget(row,col,lineEditUrl);
            }
            else if(col == 3)
            {
                QProgressBar* progressBar = new QProgressBar(this);
                ui->tableWidget->setCellWidget(row,col,progressBar);
            }
            else if(col == 4)
            {
                QPushButton* btnDown = new QPushButton("下载",this);
                ui->tableWidget->setCellWidget(row,col,btnDown);
                connect(btnDown,&QPushButton::clicked,this,&Widget::createThread);
            }
            else if(col == 5)
            {
                QPushButton* btnPause = new QPushButton("暂停",this);
                ui->tableWidget->setCellWidget(row,col,btnPause);
                connect(btnPause,&QPushButton::clicked,this,&Widget::pause);
            }
            else if(col == 6)
            {
                QPushButton* btnStop = new QPushButton("停止",this);
                ui->tableWidget->setCellWidget(row,col,btnStop);
                connect(btnStop,&QPushButton::clicked,this,&Widget::stopDown);
            }
            else if(col == 7)
            {
                QPushButton* btnResume = new QPushButton("继续",this);
                ui->tableWidget->setCellWidget(row,col,btnResume);
                connect(btnResume,&QPushButton::clicked,this,&Widget::remuse);
            }
        }
    }
}



void Widget::remuse()
{
    if(reply == nullptr)
    {
        return;
    }
    else
    {
        QProgressBar* progress = this->getProgressBar();
        qint64 skipBytes = progress->value();
        this->createThread();
        threadDown->setNowBytes(skipBytes);
    }
}

void Widget::pause()
{
    if(reply == nullptr)
    {
        return;
    }
    else
    {
        reply->abort();
    }
}

void Widget::stopDown()
{
    if(reply == nullptr)
    {
        return;
    }
    else
    {
        reply->abort();
        reply->close();
    }
}

QProgressBar* Widget::getProgressBar()
{
    int row = ui->tableWidget->currentRow();
    QWidget* widget = ui->tableWidget->cellWidget(row,3);
    QProgressBar* progress = qobject_cast<QProgressBar*>(widget);
    return progress;
}

void Widget::createThread()
{
    int row = ui->tableWidget->currentRow();
    QWidget* widget = ui->tableWidget->cellWidget(row,2);
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(widget);
    QString strUrl = lineEdit->text();
    if(strUrl.isEmpty())
    {
        QMessageBox::information(this,"提示","请输入网址",QMessageBox::Ok);
        return;
    }
    QUrl url = QUrl::fromUserInput(strUrl);
    if(!url.isValid())
    {
        QMessageBox::information(this,"提示","提示网址无效");
        return;
    }
//    qDebug()<<"文件名:"<<url.fileName();
//    if(url.fileName().isEmpty())
//    {
//        QMessageBox::information(this,"提示","网址没有文件名");
//        return;
//    }
    quest.setUrl(url);
    reply = manager->get(quest);
    threadDown = new DownReply(url,reply,this);
    threadShow = new ShowProgressBar(this);
    QProgressBar* progress = this->getProgressBar();
    threadShow->setProgressBar(progress);
    threadDown->setLock(this->lock);
    threadShow->setLock(this->lock);
    connect(reply,SIGNAL(readyRead()),threadDown,SLOT(start()));
    connect(reply,SIGNAL(finished()),threadDown,SLOT(do_finished()));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),threadShow,SLOT(run(qint64,qint64)));
    /*https://doc.qt.io/qt-5/classes.html*/

}

Widget::~Widget()
{
    delete ui;
}

void Widget::delRow()
{
    int row = ui->tableWidget->currentRow();
    if(row >= 0)
    {
        for(qint8 i = 1;i<7;i++)
        {
            ui->tableWidget->removeCellWidget(row,i);
        }
        ui->tableWidget->removeRow(row);
    }
}

void Widget::addRow()
{
    qint8 rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount-1);
//    for(qint8 row = 0;row<rowCount;row++)
//    {
//        ui->tableWidget
//    }
}

void Widget::on_checkBox_toggled(bool checked)
{
    for(qint8 i = 0;i<10;i++)
    {
        if(!checked)
        {
            ui->tableWidget->item(i,0)->setCheckState(Qt::Checked);
        }
        else
        {
            ui->tableWidget->item(i,0)->setCheckState(Qt::Unchecked);
        }
    }
}


void Widget::on_btnRemove_clicked()
{
    this->delRow();
}

