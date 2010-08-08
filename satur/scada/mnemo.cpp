
#include "mnemo.h"
#include "ui_mnemo.h"

#include <IoNetClient.h>

#include "trendchart.h"
#include "panelReg.h"

// унікальні діалогові вікна
#include "dlgpumpctrl.h"
#include "dlgvbctrl.h"
#include <QVBoxLayout>
#include <QPalette>
#include <QTimer>

Mnemo::Mnemo(IoNetClient &src, QWidget *p) : QWidget(p), m_ui(new Ui::mnemo),s(src)
{
    m_ui->setupUi(this);

    connect(&s,SIGNAL(updateDataRaw()),this,SLOT(updateDataRaw())); // при отриманні нових даних, засвітити їх на картинці
    connect(&s,SIGNAL(updateDataScaled()),this,SLOT(updateDataScaled())); // при отриманні нових даних, засвітити їх на картинці

    bnX0
            << m_ui->bb_X0_01
            << m_ui->bb_X0_02
            << m_ui->bb_X0_03
            << m_ui->bb_X0_04
            << m_ui->bb_X0_05
            << m_ui->bb_X0_06
            << m_ui->bb_X0_07
            << m_ui->bb_X0_08
            << m_ui->bb_X0_09
            << m_ui->bb_X0_10

            << m_ui->rb_X0_01
            << m_ui->rb_X0_02
            << m_ui->rb_X0_03
            //<< m_ui->br_X0_04
            << m_ui->rb_X0_05
            << m_ui->rb_X0_06
            << m_ui->rb_X0_07;

    foreach(QPushButton *p,bnX0)
    {
        connect(p,SIGNAL(clicked()),this,SLOT(slotCallReg()));
    }
    connect(m_ui->rb_Y_07,SIGNAL(clicked()),this,SLOT(slotCallPumpCtrl()));

    bnBl
            << m_ui->rb_X_08
            << m_ui->rb_X_09
            << m_ui->rb_X_10
            << m_ui->rb_X_11
            << m_ui->rb_X_12
            << m_ui->rb_X_13 ;

    foreach(QPushButton *p,bnBl)
    {
        connect(p,SIGNAL(clicked()),this,SLOT(slotCallVb()));
    }


    b_lcd
            << m_ui->bd_V_01
            << m_ui->bd_V_02
            << m_ui->bd_V_03
            << m_ui->bd_V_04
            << m_ui->bd_V_05
            << m_ui->bd_V_06
            << m_ui->bd_V_07
            << m_ui->bd_V_08
            << m_ui->bd_V_09
            << m_ui->bd_V_10
            << m_ui->bd_V_11
            << m_ui->bd_V_12
            << m_ui->bd_V_13
            << m_ui->bd_V_14
            << m_ui->bd_V_15
            << m_ui->bd_V_16;
    r_lcd
            << m_ui->rd_V_01
            << m_ui->rd_V_02
            << m_ui->rd_V_03
            << m_ui->rd_V_04
            << m_ui->rd_V_05
            << m_ui->rd_V_06
            << m_ui->rd_V_07
            //<< m_ui->r_V_08
            << m_ui->rd_V_09
            << m_ui->rd_V_10
            << m_ui->rd_V_11
            << m_ui->rd_V_12
            << m_ui->rd_V_13
            << m_ui->rd_V_14
            << m_ui->rd_V_15
            << m_ui->rd_V_16
            << m_ui->rd_V_17
            << m_ui->rd_V_18
            << m_ui->rd_V_19
            << m_ui->rd_V_20
            << m_ui->rd_V_21;

    b_pb
            << m_ui->bp_V_10
            << m_ui->bp_V_11
            << m_ui->bp_V_12
            << m_ui->bp_V_13;
    r_pb
            << m_ui->rp_V_10
            << m_ui->rp_V_11
            << m_ui->rp_V_12
            << m_ui->rp_V_13
            << m_ui->rp_V_14
            << m_ui->rp_V_15
            << m_ui->rp_V_16
            << m_ui->rp_V_21;
    b_X0
            << m_ui->bl_X0_01
            << m_ui->bl_X0_02
            << m_ui->bl_X0_03
            << m_ui->bl_X0_04
            << m_ui->bl_X0_05
            << m_ui->bl_X0_06
            << m_ui->bl_X0_07
            << m_ui->bl_X0_08
            << m_ui->bl_X0_09
            << m_ui->bl_X0_10;
    r_X0
            << m_ui->rl_X0_01
            << m_ui->rl_X0_02
            << m_ui->rl_X0_03
            //<< m_ui->lr_X0_04
            << m_ui->rl_X0_05
            << m_ui->rl_X0_06
            << m_ui->rl_X0_07;

    b_cb
            << m_ui->bc_X_11
            //<< m_ui->b_X_12
            << m_ui->bc_X_13
            << m_ui->bc_X_14
            << m_ui->bc_X_15
            //<< m_ui->b_X_16
            << m_ui->bc_X_17
            << m_ui->bc_X_18
            << m_ui->bc_X_19
            << m_ui->bc_X_20
            << m_ui->bc_X_21
            << m_ui->bc_X_22
            << m_ui->bc_X_23
            << m_ui->bc_X_24
            << m_ui->bc_AM_01
            << m_ui->bc_AM_02
            << m_ui->bc_AM_03
            << m_ui->bc_AM_04
            << m_ui->bc_AM_05
            << m_ui->bc_AM_06
            << m_ui->bc_AM_07
            << m_ui->bc_AM_08
            << m_ui->bc_AM_09
            << m_ui->bc_AM_10;
    r_cb
            << m_ui->rc_Y_01
            << m_ui->rc_Y_02
            << m_ui->rc_Y_03
            << m_ui->rc_Y_04
            << m_ui->rc_Y_05
            << m_ui->rc_Y_06
            << m_ui->rc_AM_01
            << m_ui->rc_AM_02
            << m_ui->rc_AM_03
            //<< m_ui->r_AM_04
            << m_ui->rc_AM_05
            << m_ui->rc_AM_06
            << m_ui->rc_AM_07
            << m_ui->rc_en_p_01
            << m_ui->rc_en_p_02
            << m_ui->rc_en_p_03
            << m_ui->rc_en_p_04
            << m_ui->rc_en_p_05
            << m_ui->rc_en_p_06;

    QVector<QFrame *> f ;
         f  << m_ui->s_Tr_01
            << m_ui->s_Tr_02
            << m_ui->s_Tr_03
            << m_ui->s_Tr_04
            << m_ui->s_Tr_05
            << m_ui->s_Tr_06
            << m_ui->s_Tr_07;

    for(int i=0;i<7;++i)
    {
        TrendChart *t=new TrendChart(this);
        QVBoxLayout *vbl = new QVBoxLayout(f[i]);
        vbl->addWidget(t);
        f[i]->setLayout(vbl);
        trc << t;
    }

    // це сильно константне рішення
    QStringList stl;
    // 1 вапно на дефекацію
    stl << "V_49" <<  "X_06" <<"SP_06" <<  "V_16" << "Spr_06" ;
    trChTags << stl;

    // 2 відкачка з холодного
    stl.clear();
    stl << "V_37" <<	"X_18"	<< "SP_18"<< 	"Spr_18" <<	 "V_28"<<	"SP2_18";
    trChTags << stl;

      // 3 повернення соку 1 сатурації
    stl.clear();
    stl << "V_46" <<	"X_03" << "SP_03" <<	"Spr_03" <<"V_16" <<	"V_48"  ;
    trChTags << stl;

    //4 рН першрї сатурації
    stl.clear();
    stl << "V_53" <<	"X_10"  <<"SP_10"<< "V_37";
    trChTags << stl;

    //5 витрата на деф 2 сат
    stl.clear();
    stl << "V_38" <<	"X_19" << "SP_19" <<  "V_27" <<	"Spr_19" ;
    trChTags << stl;


    //6 рН 2 сатурації
    stl.clear();
    stl << "V_54" <<	"X_11" <<"SP_11"<< "V_38" ;
    trChTags << stl;

    //7 витрата суспензії 2 сат
    stl.clear();
    stl << "V_48" <<	"X_05"  <<"SP_05" ;
    trChTags << stl;


    QTimer *t = new QTimer(this);
    t->setInterval(5000);
    t->start();
    connect(t,SIGNAL(timeout()),this,SLOT(updateTrendChart()));
}

Mnemo::~Mnemo()
{
    delete m_ui;
}


void Mnemo::updateDataRaw()
{
    foreach(QProgressBar *p,b_pb)
    {
        p->setValue(s[0]->getValueFloat(p->objectName().right(p->objectName().size()-3)));
    }

    foreach(QProgressBar *p,r_pb)
    {
        p->setValue(s[1]->getValueFloat(p->objectName().right(p->objectName().size()-3)));
    }

    foreach(QCheckBox *p,b_cb)
    {
        p->setChecked(s[0]->getValue16(p->objectName().right(p->objectName().size()-3)));
    }

    foreach(QCheckBox *p,r_cb)
    {
        p->setChecked(s[1]->getValue16(p->objectName().right(p->objectName().size()-3)));
    }


    QPalette pal_w,pal_y;
    pal_w.setColor(QPalette::Base,Qt::white);
    pal_y.setColor(QPalette::Base,Qt::yellow);

    foreach(QLineEdit *p,b_X0)
    {
        p->setPalette(s[0]->getValue16(p->objectName().right(p->objectName().size()-3))?pal_w:pal_y);
    }

    foreach(QLineEdit *p,r_X0)
    {
        p->setPalette(s[1]->getValue16(p->objectName().right(p->objectName().size()-3))?pal_w:pal_y);
    }

    foreach(QPushButton* p,bnBl)
    {
        p->setIcon(QIcon(QPixmap(s[0]->getValue16(p->objectName().right(p->objectName().size()-3))
                ?":/pict/lib/valve_green_20x32.png":":/pict/lib/valve_off_20x32.png")));
    }

    m_ui->bb_X0_08->setIcon(QIcon(QPixmap(s[0]->getValue16("X_12")
                ?":/pict/pump_r_g_25x29.png":":/pict/pump_r_r_25x29.png")));

    m_ui->bb_X0_10->setIcon(QIcon(QPixmap(s[0]->getValue16("X_16")
                ?":/pict/pump_r_g_25x29.png":":/pict/pump_r_r_25x29.png")));

    m_ui->rb_Y_07->setIcon(QIcon(QPixmap(s[0]->getValue16("X_14")
                ?":/pict/pump_l_g_25x29.png":":/pict/pump_l_r_25x29.png")));


}

void Mnemo::updateDataScaled() // слот обновляє дані на мнемосхемі
{
    foreach(QLCDNumber *p,b_lcd)
    {
        p->display(s[0]->getValueScaled(p->objectName().right(p->objectName().size()-3)));
    }

    foreach(QLCDNumber *p,r_lcd)
    {
        p->display(s[1]->getValueScaled(p->objectName().right(p->objectName().size()-3)));
    }

    foreach(QLineEdit *p,b_X0)
    {
        p->setText(QString("%1").arg(s[0]->getValueScaled(p->objectName().right(p->objectName().size()-3)),3,'f',0));
    }

    foreach(QLineEdit *p,r_X0)
    {
        p->setText(QString("%1").arg(s[1]->getValueScaled(p->objectName().right(p->objectName().size()-3)),3,'f',0));
    }

    foreach(QLineEdit *p,r_X0)
    {
        p->setText(QString("%1").arg(s[1]->getValueScaled(p->objectName().right(p->objectName().size()-3)),3,'f',0));
    }

}

void Mnemo::updateTrendChart() // поновлення графіків
{
/*
    QVector<double> v;
    int i=0;
    foreach(QStringList str,trChTags)
    {
        //qDebug() << str;
        v.clear();
        foreach(QString t,str)
        {
            v << s[0]->getValueFloat(t);
        }
        trc[i++]->addPoint(v);

    }
*/
}


void Mnemo::slotCallReg()
{
    if(sender()->objectName().left(1)=="bb")
    {
        RpanelReg p(*s[0],sender()->objectName().right(2).toInt()-1,this,":/text/reg_1.txt");
        p.exec();
    }
    else
    {
        RpanelReg p(*s[1],sender()->objectName().right(2).toInt()-1,this,":/text/reg_2.txt");
        p.exec();
    }

}

void Mnemo::slotCallPumpCtrl()
{
    QStringList v;
    if(sender()->objectName()=="s_cI_14")
    {
        v << "V_21"
                << "I_14"
                << "R_M_14"
                << "Am_M_14"
                << "V_21_min"
                << "V_21_max";
    }
    else
    {
        v << "V_25"
                << "I_17"
                << "R_M_17"
                << "Am_M_17"
                << "V_25_min"
                << "V_25_max";

    }

    dlgPumpCtrl p(*s[0],v,this);
    p.exec();
}


void Mnemo::slotCallVb()
{
    dlgVbCtrl p(*s[0],sender()->objectName().right(2).toInt(),this);
    p.exec();
}

