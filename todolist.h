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

typedef struct
{
   QString Date;
   QString Time;
   int     intDate;//标准时间1970年1月1日
   int     intTime;//标准时间00：00
   int     Minute;
   QString Thing;
   QString ThingRem;

   void    Debugprintf(void)
   {
       qDebug()<<"Date="<<Date;
       qDebug()<<"intDate="<<intDate;
       qDebug()<<"Time="<<Time;
       qDebug()<<"intTime="<<intTime;
       qDebug()<<"Thing="<<Thing;
       qDebug()<<"ThingRem="<<ThingRem;
       qDebug()<<"Minute="<<Minute;
   }
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
    void       clear()
    {
        TaskID  =0;
        TaskName.clear();
        BeginDate.clear();
        EndDate.clear();
        MinuteContinue=0;
        KeyWord.clear();
        ToDoList.clear();
        return;
    }



    int  intBeginDate(void)
    {
        QDate   a,b;
        a=QDate::fromString("2010-01-01","yyyy-MM-dd");
        b=QDate::fromString(BeginDate,"yyyy-MM-dd");
        return  a.daysTo(b);
    }
    int  intEndDate(void)
    {
        QDate   a,b;
        a=QDate::fromString("2010-01-01","yyyy-MM-dd");
        b=QDate::fromString(EndDate,"yyyy-MM-dd");
        return  a.daysTo(b);
    }
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
    void    KeyWordList(QString keyWords);
    void    AddTaskIntoList(QString    TaskName,QString BeginDate,QString EndDate );//添加任务
   /*添加任务相关变量*/
    QList<QString>      KeyWordListBuffer;
    int     TaskId_Max;//已分配的任务ID最大值
   /*添加任务相关变量*/
    QList<JustDo_it>            TaskList;//所有任务均读取至TaskList中，添加的新任务从总任务库中检索
    QMap<int,int>               MapForRecordID;//key为TaskID
    QMultiMap<QString,int>      MuiltMap;//关键字与KeyID
private:
    QList<int>                  Return_value;
};

#endif // TODOLIST_H
