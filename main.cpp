#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QtXml/QtXml>
#include <QString>



globeset globe;//待修改成标准模式

int main()
{

    QFile       csvRead(globe.SmsPos);
    csvRead.open(QIODevice::ReadOnly);
    QTextStream textRead(&csvRead);
    QString     Reader;
    QString     Year,Month,Day,Hour,Minute;
    QString     CommaHour,CommaMinute;
    QString     Buffer;
    QString     LastRecord,Nextrecord,LastRemember,NextRemember;
    QString     ReadItLatter;//待办记事
    int         DayDate,TimeDate;
    int         LastPos,NextPos;//定义完毕，正式开始

    /*****************************************/
    Reader      = textRead.readAll();
    //qDebug()<<Reader;//Debug;
    LastPos     = Reader.indexOf("sms,submit,");
    while(LastPos != -1)
    {
        LastPos = Reader.indexOf(",,",LastPos);
        LastPos = Reader.indexOf(",,",LastPos+1);
        Year    = Reader.mid(LastPos+2,4);//"sms,submit,,	10086,,2013. 6.25  9:44,109,。？做答案"
        Month   = Reader.mid(LastPos+7,2);
        Day     = Reader.mid(LastPos+10,2);//"  9:44,109,。？做答案""
        Hour    = Reader.mid(LastPos+13,2);
        Minute  = Reader.mid(LastPos+16,2);
        NextPos = Reader.indexOf("sms,",LastPos+19);//一旦有人把sms写进信息体里面怎么办？
        Buffer  = Reader.mid(LastPos+19+4,NextPos-LastPos-23);
        qDebug()<<"Year="+Year;qDebug()<<"Month="+Month;qDebug()<<"Day="+Day;qDebug()<<"Hour="+Hour;qDebug()<<"Minute="+Minute;//Debug
        qDebug()<<"Buffer = "+Buffer;//Debug
        /*buffer处理*/
        LastPos = Reader.indexOf("sms,submit,",NextPos);

    }


    return 0;
}
