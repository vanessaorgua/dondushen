#ifndef __MNEMO_H__
#define __MNEMO_H__

#include <QWidget>
#include <QVector>

class TrendChart;
class IoNetClient;
class QCheckBox;
class QLineEdit;
class QLCDNumber;
class QCheckBox;
class QProgressBar;
class QPushButton;

class TrendChart;

namespace Ui {
    class mnemo;
}

class Mnemo: public QWidget
{
    Q_OBJECT
public:
    Mnemo(IoNetClient &src, QWidget *p=NULL);
    ~Mnemo();

public slots:
    void updateDataRaw(); // слот обновляє дані на мнемосхемі
    void updateDataScaled(); // слот обновляє дані на мнемосхемі
    void updateTrendChart(); // поновлення графіків
    void slotCallReg();
    void slotCallPumpCtrl();
    void slotCallVb();
private:
    Ui::mnemo *m_ui;
    IoNetClient &s;


    // індикатори
    QVector<QLCDNumber*> b_lcd,r_lcd;
    QVector<QProgressBar*> b_pb,r_pb;
    QVector<QCheckBox*> b_cb,r_cb;
    QVector<QLineEdit*> b_X0,r_X0;

    QVector<TrendChart*> trc;

    QVector<QPushButton*> bnX0;

    QVector<QPushButton*> bnBl;

    QVector<QStringList> trChTags;
};

#endif
