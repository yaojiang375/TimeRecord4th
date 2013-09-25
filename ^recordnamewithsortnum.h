#ifndef RECORDNAMEWITHSORTNUM_H
#define RECORDNAMEWITHSORTNUM_H
#include <QString>
#include <QMap>
#include <QtXml>
#include <QVector>
typedef struct
{
    QString Date;
    QString Time;
    QString LastThing;
    QString LastRem;
    int     HandOnbyMinute;//持续时常
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

typedef QVector<RecordBody>      NameVector   ;
typedef QMap<QString,NameVector> Name_Sort_Map;

class RecordNameWithSortNum
{
public:
    RecordNameWithSortNum();
    void ReadFromFile();
    void WritetoFile ();
    void appendRecord(RecordBody Read,int SortNum);
    Std_Return_Sort     ReturnSortNum(RecordBody   NeedReturn);
private:
    RecordBody               RecordBuffer ;
    NameVector               RecordVector ;

};

#endif // RECORDNAMEWITHSORTNUM_H
