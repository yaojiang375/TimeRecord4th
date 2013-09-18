#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QtXml/QtXml>
#include <QString>
#include <globe.h>
#include <QDateTime>

globeset globe;//待修改成标准模式

void ContentDeal(QString &Content,QString &LastRecord,QString &NextRecord,QString &LastRemember,QString &NextRemember,globeset globe)
{
    QString     Buffer;
    Buffer  =Content.mid(0,Content.indexOf(globe.MidThing));
    if(Buffer.indexOf(globe.LeftRem)!=-1&&Buffer.indexOf(globe.ReghtRem)!=-1)//若左右标记同时存在，则认为中间内容为备注内容。
    {
        LastRemember = Buffer.mid(Buffer.indexOf(globe.LeftRem)+1,Buffer.indexOf(globe.ReghtRem)-Buffer.indexOf(globe.LeftRem)-1);
        Buffer.remove(Buffer.indexOf(globe.LeftRem),Buffer.indexOf(globe.ReghtRem)-Buffer.indexOf(globe.LeftRem)+1);
    }
    LastRecord = Buffer;
    Buffer  =Content.mid(Content.indexOf(globe.MidThing)+1,-1);
    if(Buffer.indexOf(globe.LeftRem)!=-1&&Buffer.indexOf(globe.ReghtRem)!=-1)//若左右标记同时存在，则认为中间内容为备注内容。
    {
        NextRemember = Buffer.mid(Buffer.indexOf(globe.LeftRem)+1,Buffer.indexOf(globe.ReghtRem)-Buffer.indexOf(globe.LeftRem)-1);
        Buffer.remove(Buffer.indexOf(globe.LeftRem),Buffer.indexOf(globe.ReghtRem)-Buffer.indexOf(globe.LeftRem)+1);
    }
    NextRecord = Buffer;
    return;
}


int main()
{
    globe.read();

    QFile       csvRead(globe.SmsPos);
    qDebug()<<"csv:"<<csvRead.isOpen();//qdebug
    QFile       xmlWrite("c:/try.xml");
    xmlWrite.open(QIODevice::WriteOnly);
    csvRead.open(QIODevice::ReadOnly);
    QTextStream textRead(&csvRead);

    QDate       _DateTime;
    QTime       _Time;

    QString     Reader;
    QString     CommaHour,CommaMinute;
    QString     Buffer;
    QString          LastRecord,     NextRecord,     LastRemember,     NextRemember,CommaContent,
                CommaLastRecord,CommaNextRecord,CommaLastRemember,CommaNextRemember;
    QString     ReadItLatter;//待办记事
    int         DayDate,TimeDate;
    int         LastPos,NextPos;//

    /*******************xml试验***************************/
    int         RecordId=0;//xml文件中的事件记录序号
    QDomDocument    doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding = \"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root        = doc.createElement("root");

    QDomElement Record      = doc.createElement("Record");
    QDomElement id          = doc.createElement("id");
    QDomElement WrongFlag   = doc.createElement("WrongFlag");
    QDomElement Date        = doc.createElement("Date");
    QDomElement year        = doc.createElement("Year");
    QDomElement month       = doc.createElement("Month");
    QDomElement day         = doc.createElement("Day");
    QDomElement Time        = doc.createElement("Time");
    QDomElement hour        = doc.createElement("Hour");
    QDomElement minute      = doc.createElement("Minute");
    QDomElement Body        = doc.createElement("Body");
    QDomElement LastThing   = doc.createElement("LastThing");
    QDomElement LastRem     = doc.createElement("LastThingRemember");
    QDomElement NextThing   = doc.createElement("NextThing");
    QDomElement NextRem     = doc.createElement("NextThingRemember");
    QDomText    text;



    QTextStream  out(&xmlWrite);

    /*********************定义完毕，正式开始********************/
    Reader      = textRead.readAll();
    //qDebug()<<Reader;//Debug;
    LastPos     = Reader.indexOf("sms,submit,");
    while(LastPos != -1)
    {
        LastPos = Reader.indexOf(",,",LastPos);
        LastPos = Reader.indexOf(",,",LastPos+1);
        _DateTime.setYMD(Reader.mid(LastPos+2,4).toInt(),Reader.mid(LastPos+7,2).toInt(),Reader.mid(LastPos+10,2).toInt());//"sms,submit,,	10086,,2013. 6.25  9:44,109,。？做答案"
        _Time.setHMS(Reader.mid(LastPos+13,2).toInt(),Reader.mid(LastPos+16,2).toInt(),0,0);

        NextPos = Reader.indexOf("sms,",LastPos+19);//一旦有人把sms写进信息体里面怎么办？
        Buffer  = Reader.mid(LastPos+19+4,NextPos-LastPos-23);
        qDebug()<<"Date= "+_DateTime.toString("yyyy-MM-dd");
        qDebug()<<"Buffer = "+Buffer;//Debug
        /******************************************************/

        if(Buffer[0]==globe.RecFlag[0])//globe待改成指针模式
        {
            Buffer.remove(0,1);
            if(Buffer[0]==globe.AddFlag[0])
            {
                Buffer.remove(0,1);

                if(Buffer.indexOf(globe.AddEndFlag)!=-1)
                {
                    text    =doc.createTextNode("FALSE");
                    WrongFlag.appendChild(text);

                }
                else
                {
                    text    =doc.createTextNode("TRUE");
                    WrongFlag.appendChild(text);//当出现错误时只需要跳过该记录即可
                }
            }
            else
            {
                text    =doc.createTextNode("FALSE");
                WrongFlag.appendChild(text);
            }
                
                ContentDeal(Buffer,LastRecord,NextRecord,LastRemember,NextRemember,globe);

                Record      = doc.createElement("Record");
                id          = doc.createElement("id");
                WrongFlag   = doc.createElement("WrongFlag");
                Date        = doc.createElement("Date");
                Time        = doc.createElement("Time");
                Body        = doc.createElement("Body");
                LastThing   = doc.createElement("LastThing");
                LastRem     = doc.createElement("LastThingRemember");
                NextThing   = doc.createElement("NextThing");
                NextRem     = doc.createElement("NextThingRemember");

                RecordId++;
                QString _Toint;
                _Toint.setNum(RecordId);
                text    =doc.createTextNode(_Toint);
                id.appendChild(text);
                text    =doc.createTextNode(_DateTime.toString("yyyy-MM-dd"));
                Date.appendChild(text);
                text    =doc.createTextNode(_Time.toString("hh:mm"));
                Time.appendChild(text);
                text    =doc.createTextNode(LastRecord);
                LastThing.appendChild(text);
                text    =doc.createTextNode(LastRemember);
                LastRem.appendChild(text);
                text    =doc.createTextNode(NextRecord);
                NextThing.appendChild(text);
                text    =doc.createTextNode(NextRemember);
                NextRem.appendChild(text);



                Date.appendChild(year);
                Date.appendChild(month);
                Date.appendChild(day);
                Time.appendChild(hour);
                Time.appendChild(minute);
                Body.appendChild(LastThing);
                Body.appendChild(LastRem);
                Body.appendChild(NextThing);
                Body.appendChild(NextRem);

                Record.appendChild(id);
                Record.appendChild(WrongFlag);
                Record.appendChild(Date);
                Record.appendChild(Time);
                Record.appendChild(Body);

                root.appendChild(Record);
            
        }


        /******************************************************/

        LastPos = Reader.indexOf("sms,submit,",NextPos);

    }
    doc.appendChild(root);
    doc.save(out,4);


    return 0;
}
