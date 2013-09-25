#include "namewithsortnumreturnrecord.h"

NameWithSortNumReturnRecord::NameWithSortNumReturnRecord()
{
}

RecordVector NameWithSortNumReturnRecord::ReturnRecord(QString RecordName, int SortNum)
{
    QString buf;
    buf.setNum(SortNum);
    RecordName=RecordName +"_+_" +buf;
    return Nmap.value(RecordName);
}

bool NameWithSortNumReturnRecord::appendRecord(QString RecordName, int SortNum, QString Date, QString Time, QString LastThing, QString LastRem, int HandOnMinute, int ShowFlag)
{
    BufferVector.clear();
    ReadBody.Date=Date;
    ReadBody.Time=Time;
    ReadBody.LastThing=LastThing;
    ReadBody.LastRem=LastRem;
    ReadBody.HandOnbyMinute=HandOnMinute;
    ReadBody.ShowFlag=ShowFlag;
    QString buf;
    buf.setNum(SortNum);
    RecordName=RecordName +"_+_" +buf;
    BufferVector  = Nmap.value(RecordName);//没有重复检验。一旦碰见重复添加记录怎么办？
    BufferVector.append(ReadBody);
    qDebug()<<"ReadBody.LastThing="<<ReadBody.LastThing;//Debug
    Nmap.insert(RecordName,BufferVector);
    return TRUE;

}

bool NameWithSortNumReturnRecord::SaveDomOnFile(globeset globe)
{
    QString FromInt;

    QFile _read(globe.NameWithSortNumReturnRecordXmlPOS);
    _read.open(QIODevice::WriteOnly);
    QTextStream _READ(&_read);

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    QDomElement root        ;


    QDomElement Record;//RecordName+RecordSortNum
    QDomElement DomStruct;
    QDomElement Date;
    QDomElement Time;
    QDomElement LastThing;
    QDomElement LastRem;
    QDomElement HandOnMinute;
    QDomElement ShowFlag;

    QDomText    _Text       ;

    QMap<QString,RecordVector>::const_iterator i;
    i=Nmap.begin();
    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding = \"UTF-8\"");
    doc.appendChild(instruction);
    root        = doc.createElement("root");
    while(i != Nmap.end())
    {
        Record  =doc.createElement("Record");
        _Text   =doc.createTextNode(i.key());
        Record.setAttribute("key",i.key());//使用属性保存关键字

        BufferVector=i.value();
        QVector<RecordBody>::Iterator ite;
        ite =  BufferVector.begin();
        while(ite!=BufferVector.end())
        {
        DomStruct=doc.createElement("DomStruct");
        ReadBody.Date=ite->Date;
        qDebug()<<"ite.Date="<<ite->Date;//Debug;
        qDebug()<<"ite.LastThing="<<ite->LastThing;//Debug

        Date     =doc.createElement("Date");
        _Text    =doc.createTextNode(ite->Date);
        Date.appendChild(_Text);
        Time     =doc.createElement("Time");
        _Text    =doc.createTextNode(ite->Time);
        Time.appendChild(_Text);
        LastThing     =doc.createElement("LastThing");
        _Text    =doc.createTextNode(ite->LastThing);
        LastThing.appendChild(_Text);
        LastRem     =doc.createElement("LastRem");
        _Text    =doc.createTextNode(ite->LastRem);
        LastRem.appendChild(_Text);
        HandOnMinute=doc.createElement("HandOnMinute");
        _Text   =doc.createTextNode(FromInt.setNum(ite->HandOnbyMinute));
        HandOnMinute.appendChild(_Text);
        ShowFlag    =doc.createElement("ShowFlag");
        _Text   =doc.createTextNode(FromInt.setNum(ite->ShowFlag));
        ShowFlag.appendChild(_Text);


        DomStruct.appendChild(Date);
        DomStruct.appendChild(Time);
        DomStruct.appendChild(LastThing);
        DomStruct.appendChild(LastRem);
        DomStruct.appendChild(HandOnMinute);
        DomStruct.appendChild(ShowFlag);
        Record.appendChild(DomStruct);
        ite++;
        }
        root.appendChild(Record);
        i++;

    }
    doc.appendChild(root);
    doc.save(_READ,4);
}

bool NameWithSortNumReturnRecord::ReadDomFromFile(globeset globe)
{
    QFile _Xml(globe.NameWithSortNumReturnRecordXmlPOS);
    QDomDocument    doc;
    doc.setContent(&_Xml);
    QString         key;
    RecordVector    value;
    RecordBody      Body;
    QDomNode        DomStruct;

    QDomElement DocElem=doc.documentElement();
    QDomNode    n      =DocElem.firstChild();

    while(!n.isNull())
    {
        qDebug()<<"ReadFileBegin";//debug
        key=n.toElement().attribute("key","NULL");
        qDebug()<<"key="<<key;//debug
        DomStruct=n.firstChild();
        while(!DomStruct.isNull())
        {
            Body.Date=              DomStruct.firstChildElement("Date").text();

            Body.HandOnbyMinute=    DomStruct.firstChildElement("HandOnbyMinute").text().toInt();
            Body.LastRem=           DomStruct.firstChildElement("LastRem").text();
            Body.LastThing=         DomStruct.firstChildElement("LastThing").text();
            qDebug()<<"Body.LastThing="<<Body.LastThing;//Debug
            Body.ShowFlag=          DomStruct.firstChildElement("ShowFlag").text().toInt();
            Body.Time=              DomStruct.firstChildElement("Time").text();
            DomStruct=DomStruct.nextSibling();
            value.append(Body);
        }
        Nmap.insert(key,value);
        n   =n.nextSibling();
    }



    return TRUE;

}
