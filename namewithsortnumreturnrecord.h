#ifndef NAMEWITHSORTNUMRETURNRECORD_H
#define NAMEWITHSORTNUMRETURNRECORD_H
//给出事件名与分类号，返回事件记录
#include <QString>
#include <QFile>
#include <QtextStream>
#include <QMap>
#include <QtXml>
#include <globe.h>

typedef struct
{
    QString Date;
    QString Time;
    QString LastThing;
    QString LastRem;
    int     HandOnbyMinute;//持续时常
    int     ShowFlag;//0表示正常现实且记录，1表示不显示但记录，2表示不显示且不记录
} RecordBody;

typedef struct
{
    int LongestTime;
    int ShortestTime;
    int AverageTime;
    int Count;//该项下的记录总数，使用vector.count获得
    QString LongestDate_Time;//记录关键字，用于对记录进行修改
    QString ShortestDate_Time;
}   Std_Return_Sort;

typedef QVector<RecordBody>      RecordVector   ;

typedef QMap<QString,RecordVector> Name_Sort_Map;

class NameWithSortNumReturnRecord
{
public:
    NameWithSortNumReturnRecord();
    RecordVector ReturnRecord(QString    RecordName,int SortNum);
    bool         appendRecord  (QString    RecordName,int SortNum,QString Date,QString Time,QString LastThing,QString LastRem,int HandOnMinute,int ShowFlag = 0);
    bool         SaveDomOnFile(globeset globe);
    bool         ReadDomFromFile(globeset globe);
private:
    Name_Sort_Map   Nmap;
    RecordVector    Rvector,BufferVector;//常备、临时；
    RecordBody      ReadBody;

};

#endif // NAMEWITHSORTNUMRETURNRECORD_H
