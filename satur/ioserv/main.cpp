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
    QCoreApplication::setApplicationName("satur");

    QSettings set;
    set.setValue("/db/db","satur");


    QVector<RxModbus*> r;
    QVector<IoDev*> src; // джерела даних.

    {
        RxModbus *t= new RxModbus;
        t->setObjectName("satur1");
        t->loadList(":/text/list1.txt");
        t->setHostName("10.0.1.1");
        t->setPort(502);
        r << t;
        src << t;
    }
{
        RxModbus *t= new RxModbus;
        t->setObjectName("satur2");
        t->loadList(":/text/list2.txt");
        t->setHostName("10.0.1.2");
        t->setPort(502);
        r << t;
        src << t;
 }

    Logging l(src,5000); // писалка історіх
    QStringList tables;
    tables <<  "trend1" << "trend2" ;
    l.setTables(tables);

    IoNetServer s(src); // мережевий інтерфейс


    //Alert al(&r);
    //al.loadList(":/text/Linovitsa/filters/text/alert.txt");
    //QObject::connect(&r,SIGNAL(updateData()),&al,SLOT(checkAlert()));
    //QObject::connect(&al,SIGNAL(newAlert(QString)),&s,SLOT(sendAlert(QString)));

    for(int i=0;i<2;++i)
    {
        QObject::connect(r[i],SIGNAL(Alert(QString)),&s,SLOT(sendAlert(QString)));
        r[i]->start();
    }
//    r[0]->start();

    qDebug() << "Started" ;
    return a.exec();
}

