#ifndef GLOBE_H
#define GLOBE_H
#include <QTextStream>
#include <QFile>

class globeset
{
public:
    QString SmsPos;
    bool    ReadWrong;
    QString RILFlag;
    QString RecFlag;
    QString AddFlag;
    QString ReghtRem;
    QString LeftRem;
    QString MidThing;

    QString iniPos;

    globeset()
    {
        SmsPos      = "c:/1.csv";
        ReadWrong   =FALSE;
        RILFlag     ='！';
        RecFlag     ='。';
        AddFlag     ="，";
        ReghtRem    ="]";
        LeftRem     ="[";
        MidThing    ="？";

        iniPos      ="c:/1.ini";//Qdebug
    }
    void read()
    {
        QFile ini(iniPos);
        qDebug()<<ini.isOpen();//Qdebug;
        QChar key;
        ini.open(QIODevice::ReadOnly);
        QTextStream iniRead(&ini);

        iniRead>>key;
        RecFlag=key;
        iniRead>>MidThing;
        iniRead>>RILFlag;
        return;
    }
};



#endif // GLOBE_H
