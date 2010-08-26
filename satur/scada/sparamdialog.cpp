#include "sparamdialog.h"
#include "ui_sparamdialog.h"

#include "IoNetClient.h"
#include "iodev.h"

#include <QSettings>

#include <QDebug>


SParamDialog::SParamDialog(IoNetClient &src,QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SParamDialog),
    s(src)
{
    m_ui->setupUi(this);

    foreach(QString tag,s[0]->getTags().keys())
    {
        if(s[0]->isScaleChange(tag))
            tag_name_0 << tag;
    }

    foreach(QString str,tag_name_0)
    {
        m_ui->bx_Teg_0->addItem(s[0]->getText()[str]);
    }
    //qDebug() << tag_name_0;

    foreach(QString tag,s[1]->getTags().keys())
    {
        if(s[1]->isScaleChange(tag))
            tag_name_1 << tag;
    }

    foreach(QString str,tag_name_1)
    {
        m_ui->bx_Teg_1->addItem(s[1]->getText()[str]);
    }
    //qDebug() << tag_name_0;

    m_ui->sb_Zs_0->setKeyboardTracking(false);
    m_ui->sb_Zs_1->setKeyboardTracking(false);
    m_ui->sb_Fs_0->setKeyboardTracking(false);
    m_ui->sb_Fs_1->setKeyboardTracking(false);
    m_ui->sb_f_0->setKeyboardTracking(false);
    m_ui->sb_f_0->setKeyboardTracking(false);

    connect(m_ui->bn_Ok,SIGNAL(clicked()),this,SLOT(myAccept()));
    connect(m_ui->bx_Teg_0,SIGNAL(currentIndexChanged(int)),this,SLOT(selectTeg(int)));
    connect(m_ui->bx_Teg_1,SIGNAL(currentIndexChanged(int)),this,SLOT(selectTeg(int)));

    connect(m_ui->sb_Fs_0,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));
    connect(m_ui->sb_Zs_0,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));
    connect(m_ui->sb_f_0,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));

    connect(m_ui->sb_Fs_1,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));
    connect(m_ui->sb_Zs_1,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));
    connect(m_ui->sb_f_1,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));

    connect(m_ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(selectPage(int)));

    //connect(m_ui->sb_m,SIGNAL(valueChanged(QString)),this,SLOT(slotSet(QString)));

    m_ui->bx_Teg_0->setCurrentIndex(0);

    selectTeg(0);

    QSettings set;
    m_ui->le_ioserv->setText(set.value("/ioserv/hostname","localhost").toString());

    m_ui->le_dbserv->setText(set.value("/db/hostname","localhost").toString());
    m_ui->le_dbname->setText(set.value("/db/dbname","test").toString());
    m_ui->le_username->setText(set.value("/db/username","scada").toString());
    m_ui->le_passwd->setText(set.value("/db/passwd","").toString());


}

SParamDialog::~SParamDialog()
{
    delete m_ui;
}

void SParamDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void SParamDialog::myAccept()
{

    s[0]->sendValue("Save",qint16(-1));
    s[0]->sendValue("Run",qint16(0));
    s[1]->sendValue("Save",qint16(-1));
    s[1]->sendValue("Run",qint16(0));


    QSettings set;
    set.setValue("/ioserv/hostname",m_ui->le_ioserv->text());

    set.setValue("/db/hostname",m_ui->le_dbserv->text());
    set.setValue("/db/dbname",m_ui->le_dbname->text());
    set.setValue("/db/username",m_ui->le_username->text());
    set.setValue("/db/passwd",m_ui->le_passwd->text());


    accept();
}



void SParamDialog::slotSet(QString v )
{
    if(sender()->objectName().right(1).toInt()) // сигнали із таба другого контролера
    {
        if(sender()->objectName().left(sender()->objectName().size()-2)=="sb_Zs")
            s[1]->setScaleZero(tag_name_1[m_ui->bx_Teg_1->currentIndex()],v.toDouble());
        else if(sender()->objectName().left(sender()->objectName().size()-2)=="sb_Fs")
            s[1]->setScaleFull(tag_name_1[m_ui->bx_Teg_1->currentIndex()],v.toDouble());
        else if(sender()->objectName().left(sender()->objectName().size()-2)=="sb_f")
            s[1]->sendValue(QString("Kf_%1").arg(tag_name_1[m_ui->bx_Teg_0->currentIndex()].right(2)),qint16(v.toInt()));
    }
    else // першого контролера
    {
        if(sender()->objectName().left(sender()->objectName().size()-2)=="sb_Zs")
            s[0]->setScaleZero(tag_name_0[m_ui->bx_Teg_0->currentIndex()],v.toDouble());
        else if(sender()->objectName().left(sender()->objectName().size()-2)=="sb_Fs")
            s[0]->setScaleFull(tag_name_0[m_ui->bx_Teg_0->currentIndex()],v.toDouble());
        else if(sender()->objectName().left(sender()->objectName().size()-2)=="sb_f")
            s[0]->sendValue(QString("Kf_%1").arg(tag_name_0[m_ui->bx_Teg_0->currentIndex()].right(2)),qint16(v.toInt()));
    }

}

void SParamDialog::selectTeg(int v)
{
    if(m_ui->tabWidget->currentIndex()==0)
    {
        if(v<m_ui->bx_Teg_0->count())
        {
            m_ui->sb_Zs_0->setValue(s[0]->scaleZero(tag_name_0[v]));
            m_ui->sb_Fs_0->setValue(s[0]->scaleFull(tag_name_0[v]));
            m_ui->sb_f_0->setValue(s[0]->getValue16(QString("Kf_%1").arg(tag_name_0[v].right(2))));
        }
    }
    else if( m_ui->tabWidget->currentIndex()==1)
    {
        if(v<m_ui->bx_Teg_1->count())
        {
            m_ui->sb_Zs_1->setValue(s[1]->scaleZero(tag_name_1[v]));
            m_ui->sb_Fs_1->setValue(s[1]->scaleFull(tag_name_1[v]));
            m_ui->sb_f_1->setValue(s[1]->getValue16(QString("Kf_%1").arg(tag_name_1[v].right(2))));
        }
    }

    //m_ui->sb_m->setValue((double)s.getValue16(QString("m_%1").arg(tag_name[v]))/4000.0*(s.scaleFull(tag_name[v])-s.scaleZero(tag_name[v]))+s.scaleZero(tag_name[v]));
}

void SParamDialog::selectPage(int v)
{
    if(v==0)
    {
        m_ui->bx_Teg_0->setCurrentIndex(0);
    }
    else if(v==1)
    {
        m_ui->bx_Teg_1->setCurrentIndex(0);
    }
    selectTeg(0);
}


