#ifndef TODOLIST_H
#define TODOLIST_H
#include "globe.h"
#include <QMultiMap>
#include <QMap>
#include <QVector>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QtXml>

typedef struct apc
{
   QString Date;
   QString Time;
   int     intDate;//标准时间1970年1月1日
   int     intTime;//标准时间00：00
   int     Minute;
   QString Thing;
   QString ThingRem;
}  DoneList_Record;

typedef struct enenen
{
    int        TaskID;//任务记录号，用于分配给MultiMap
    QString    TaskName;
    QString    BeginDate;
    QString    EndDate;
    int        MinuteContinue;
    QList<QString>  KeyWord;

    QList<DoneList_Record>  ToDoList;//为用而用！已完成事件


    //method
    void appendRecord(DoneList_Record a)
    {
        ToDoList.append(a);
        return;
    }
    void appendKeyWord(QString a)
    {
        KeyWord.append(a);
        return;
    }
    void AddMinute(int a)
    {
        MinuteContinue +=a;
        return;
    }
    enenen(void)
    {
        TaskID        =   0;
        MinuteContinue  =   0;
        return;
    }


}   JustDo_it;

class ToDoList
{
public:
    ToDoList();
    void    ReadFromFile(globeset globe)  ;
    void    ReadFromAddDBFile(globeset globe);
    void    SaveToFile(globeset globe)    ;
    int     AllThingCount();
    int     DoingCount();//进行中任务计数
    int     DoneCount();//已做完任务计数
    QList<JustDo_it>            Done;
    QList<JustDo_it>            Doing;
    QMap<int,int>               MapForRecordID;
    QMultiMap<QString,int>      MuiltMap;
private:
    QList<int>                  Return_value;
};

#endif // TODOLIST_H
