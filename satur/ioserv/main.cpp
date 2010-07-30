#include <QCoreApplication>
#include <QSettings>
#include <QDebug>


#include "iodev.h"
#include "RxModbus.h"
#include "logging.h"
#include "IoNetServer.h"
#include "alert.h"


//#include "display.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Rabitsa");
    QCoreApplication::setApplicationName("aparat");

    QSettings set;
    set.setValue("/db/db","aparat");


    QVector<RxModbus*> r;
    QVector<IoDev*> src; // джерела даних.

    for(int i=0;i<3;++i)
    {
        RxModbus *t= new RxModbus;
        t->setObjectName(QString("ap_%1").arg(i+1));
        t->loadList(":/text/list.txt");
        t->setHostName(QString("192.168.0.%1").arg(i+70));
        qDebug() << QString("192.168.0.%1").arg(i+70);
        t->setPort(502);
        r << t;
        src << t;
    }

        RxModbus *t= new RxModbus;
        t->setObjectName("common");
        t->loadList(":/text/list2.txt");
        t->setHostName("192.168.0.73");
        t->setPort(502);
        r << t;
        src << t;


    Logging l(src,10010); // писалка історіх
    QStringList tables;
    tables << "ap_1" << "ap_2" << "ap_3" << "trend" ;
    l.setTables(tables);

    IoNetServer s(src); // мережевий інтерфейс


    //Alert al(&r);
    //al.loadList(":/text/Linovitsa/filters/text/alert.txt");
    //QObject::connect(&r,SIGNAL(updateData()),&al,SLOT(checkAlert()));
    //QObject::connect(&al,SIGNAL(newAlert(QString)),&s,SLOT(sendAlert(QString)));

    for(int i=0;i<4;++i)
    {
        QObject::connect(r[i],SIGNAL(Alert(QString)),&s,SLOT(sendAlert(QString)));
        r[i]->start();
    }
//    r[0]->start();

    qDebug() << "Started" ;
    return a.exec();
}

