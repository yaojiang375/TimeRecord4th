#include "recordname.h"



RecordName::RecordName(globeset globe)
{
    ReadRecordNameConnect(globe);

}

void RecordName::ReadRecordNameConnect(globeset globe)
{
    QFile _read(globe.NameConnecrXmlPos);
    _read.open(QIODevice::ReadOnly);
    doc.setContent(&_read);
    QDomElement DocElem=doc.documentElement();
    QDomNode    n      =DocElem.firstChild();

    while(!n.isNull())
    {

        if(n.isElement())
        {
            qDebug()<<"n.toElement().text()="+(n.firstChildElement("OtherName").text());
            Name.insert(n.firstChildElement("OtherName").text(),n.lastChildElement("TrueName").text());
            qDebug()<<"MapValue="+Name.value(n.firstChildElement("OtherName").text());
            qDebug()<<"n.lastChildElement.text()"+n.lastChildElement("TrueName").text();
        }
        n   =n.nextSibling();
    }
    return;
}

bool RecordName::appendRecordNameConnect(QString RecordOtherName, QString TrueName)
{
    if(Name.contains(RecordOtherName))
    {
        return  FALSE;    
    }
    else
    {
        Name.insert(RecordOtherName,TrueName);
        return  TRUE;
    }
    
}

QString RecordName::RerutnTrueName(QString RecordOtherName)
{
    return Name.value(RecordOtherName);
}

QString RecordName::SureChangeNameConnect(QString RecordOtherName, QString TrueName)
{
    Name.insert(RecordOtherName,TrueName);
    return  RecordOtherName;
}

bool RecordName::SaveRecordNameConnect(globeset globe)
{
    QFile _read(globe.NameConnecrXmlPos);
    _read.open(QIODevice::WriteOnly);
    QTextStream _READ(&_read);

    doc.clear();
    QDomProcessingInstruction instruction;
    QDomElement root        ;
    QDomElement Record      ;
    QDomElement OtherName   ;
    QDomElement TrueName    ;
    QDomText    _Text       ;

    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding = \"UTF-8\"");
    doc.appendChild(instruction);
    root        = doc.createElement("root");

    while(!Name.empty())
    {
        Record      = doc.createElement("Record");
        OtherName   = doc.createElement("OtherName");
        TrueName    = doc.createElement("TrueName");
        _Text   =doc.createTextNode(Name.begin().key());
        OtherName.appendChild(_Text);
        _Text   =doc.createTextNode(Name.begin().value());
        TrueName.appendChild(_Text) ;
        Record.appendChild(OtherName);
        Record.appendChild(TrueName) ;
        root.appendChild(Record);
        Name.remove(Name.begin().key());//可以进一步优化
    }
    doc.appendChild(root);
    doc.save(_READ,4);
    return true;
}
