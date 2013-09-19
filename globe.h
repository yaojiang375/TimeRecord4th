#ifndef GLOBE_H
#define GLOBE_H
#include <QTextStream>
#include <QFile>
#include <QDateTime>


class globeset
{
public:
    QString SmsPos;
    bool    ReadWrong;
    QString RILFlag;
    QString RecFlag;
    QString AddFlag;
    QString AddEndFlag;
    QString ReghtRem;
    QString LeftRem;
    QString MidThing;
    QDate   STLDate;//标准时间，1970-01-01_00：00
    QString iniPos;

    globeset()
    {
        SmsPos      = "c:/1.csv";
        ReadWrong   =FALSE;
        RILFlag     ="！";
        RecFlag     ="。";
        AddFlag     ="，";
        AddEndFlag  ="！";
        ReghtRem    ="]";
        LeftRem     ="[";
        MidThing    ="？";
        iniPos      ="c:/1.ini";//Qdebug
        STLDate.fromString("1970-01-01","yyyy-MM-dd");
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
        iniRead>>AddFlag;
        iniRead>>AddEndFlag;
        
        return;
    }
    void Show()
    {
        qDebug()<<"SmsPos="     <<SmsPos    <<'\n'
               <<"ReadWrong="   <<ReadWrong <<'\n'
                <<"RILFlag="    <<RILFlag   <<'\n'
                <<"RecFlag="    <<RecFlag   <<'\n'
                <<"AddFlag="    <<AddFlag   <<'\n'
                <<"AddEndFlag=" <<AddEndFlag<<'\n'
                <<"ReghtRem="   <<ReghtRem  <<'\n'
                <<"LeftRem="    <<LeftRem   <<'\n'
                <<"MidThing="   <<MidThing  <<'\n'
                <<"iniPos="     <<iniPos    <<'\n'  ;
             /*   <<"=" << <<'\n'
                <<"=" << <<'\n'
                <<"=" << <<'\n'
                <<"=" << <<'\n'  */
    }
};



#endif // GLOBE_H
