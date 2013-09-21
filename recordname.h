#ifndef RECORDNAME_H
#define RECORDNAME_H
#include "globe.h"
#include <QString>
#include <QMap>
#include <QtXml>
#include <QFile>
#include <QTextStream>


struct  Record_Name
{
    QString RecordOtherName;
    QString TrueName;
};

class RecordName
{
public:
    RecordName(globeset globe);
    void        ReadRecordNameConnect(globeset globe);
    bool        appendRecordNameConnect(QString    RecordOtherName, QString    TrueName);//成功返回TRUE，已有返回FALSE(FASLE之后应该有一个强制更换的功能)
    QString     RerutnTrueName(QString  RecordOtherName);
    QString     SureChangeNameConnect(QString RecordOtherName,QString   TrueName);
    bool        SaveRecordNameConnect(globeset globe);//这里难道还需要再导入一个全局变量吗？困惑
private:
    QMap<QString,QString> Name;
    QDomDocument doc        ;
};

#endif // RECORDNAME_H
