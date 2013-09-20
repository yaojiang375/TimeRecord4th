#include "xml.h"

GTDxml::GTDxml()
{

    instruction = doc.createProcessingInstruction("xml","version=\"1.0\" encoding = \"UTF-8\"");
    doc.appendChild(instruction);
    root        = doc.createElement("root");
    ID          =   0;

}

void GTDxml::FileWrite(QString _Date,QString _Time,QString _LastThing,QString _LastRem,QString _NextThing,QString _NextRem,bool  _WrongFlag)
{

    ID++;

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

    _Toint.setNum(ID);
    text    =doc.createTextNode(_Toint);
    id.appendChild(text);
    if(_WrongFlag)
    {
        text=doc.createTextNode("True");
        WrongFlag.appendChild(text);
    }
    else
    {
        text=doc.createTextNode("Flase");
        WrongFlag.appendChild(text);
    }
    text    =doc.createTextNode(_Date);
    Date.appendChild(text);
    text    =doc.createTextNode(_Time);
    Time.appendChild(text);
    text    =doc.createTextNode(_LastThing);
    LastThing.appendChild(text);
    text    =doc.createTextNode(_LastRem);
    LastRem.appendChild(text);
    text    =doc.createTextNode(_NextThing);
    NextThing.appendChild(text);
    text    =doc.createTextNode(_NextRem);
    NextRem.appendChild(text);

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

     doc.appendChild(root);
}

void GTDxml::XmlSave(QString    xmlWrite)
{

    QFile       _xml(xmlWrite);
    _xml.open(QIODevice::WriteOnly);
    QTextStream  out(&_xml);
    doc.appendChild(root);
    doc.save(out,4);
}
