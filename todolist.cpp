#include "todolist.h"

ToDoList::ToDoList()
{
}

void ToDoList::ReadFromFile(globeset globe)
{
    QFile   _TaskFile(globe.GetAndPostPos);
    _TaskFile.open(QIODevice::ReadOnly);
     QDomDocument    doc;
     doc.setContent(&_TaskFile);

     QDomElement                     xml_root;
     QDomElement                     xml_Done;
     QDomElement                     xml_Doing;
         QDomElement                     xml_Task;

             QDomElement                     xml_BeginDate;
             QDomElement                     xml_EndDate;
             QDomElement                     xml_TaskName;//在属性中储存TaskID
             QDomElement                     xml_MinuteContinue;

             QDomElement                     xml_KeyWordList;
             QDomElement                     xml_KeyWords;

             QDomElement                     xml_ToDoList;
             QDomElement                     xml_Record;
             QDomElement                     xml_Thing;
             QDomElement                     xml_ThingRem;
             QDomElement                     xml_Date;
             QDomElement                     xml_Time;
             QDomElement                     xml_Minute;

             JustDo_it                       Read_Task;
             QList<QString>                  Read_KeyWord;
             DoneList_Record                 Read_Record;
             QList<DoneList_Record>          Read_ToDoList;



     xml_root       =               doc.firstChildElement("root");
     TaskId_Max     =               xml_root.attribute("TaskId_Max").toInt();
     xml_Done       =               xml_root.firstChildElement("Done");
     xml_Doing      =               xml_root.firstChildElement("Doing");

     xml_Task       =               xml_Done.firstChildElement("Task");
     int            TaskAppendSequence=0;
     while(!xml_Task.isNull())
     {
         Read_Task.clear();
         xml_TaskName=              xml_Task.firstChildElement("TaskName");
         Read_Task.TaskID   =       xml_TaskName.attribute("TaskID").toInt();
         Read_Task.TaskName =       xml_TaskName.text();
         Read_Task.BeginDate=       xml_Task.firstChildElement("BeginDate").text();
         Read_Task.EndDate  =       xml_Task.firstChildElement("EndDate").text();
         Read_Task.MinuteContinue=  xml_Task.firstChildElement("MinuteContinue").attribute("MinuteContinue").toInt();

         xml_KeyWordList    =       xml_Task.firstChildElement("KeyWordList");
         xml_KeyWords       =       xml_KeyWordList.firstChildElement("KeyWords");
         while(!xml_KeyWords.isNull())
         {
             Read_Task.appendKeyWord(xml_KeyWords.text());
             xml_KeyWords   =       xml_KeyWords.nextSiblingElement();
         }

         xml_ToDoList       =       xml_Task.firstChildElement("ToDoList");
         xml_Record         =       xml_ToDoList.firstChildElement("Record");
         while(!xml_Record.isNull())
         {
             Read_Record.Date    =   xml_Record.firstChildElement("Date").text();
             Read_Record.Time    =   xml_Record.firstChildElement("Time").text();
             Read_Record.Thing   =   xml_Record.firstChildElement("Thing").text();
             Read_Record.ThingRem=   xml_Record.firstChildElement("ThingRem").text();
             Read_Record.intDate =   xml_Record.firstChildElement("Date").attribute("intDate").toInt();
             Read_Record.intTime =   xml_Record.firstChildElement("Time").attribute("intTime").toInt();
             Read_Record.Minute  =   xml_Record.firstChildElement("Minute").attribute("Minute").toInt();

             Read_Task.ToDoList.append(Read_Record);
             xml_Record          =   xml_Record.nextSiblingElement();
         }
         TaskList.append(Read_Task);
         MapForRecordID.insert(Read_Task.TaskID,TaskAppendSequence);
         TaskAppendSequence++;
         xml_Task=xml_Task.nextSiblingElement();
     }
}

void ToDoList::ReadFromAddDBFile(globeset globe)
{
    QFile   _fanzhengkeyishuibianqi(globe.GetAndPostPos);
    _fanzhengkeyishuibianqi.open(QIODevice::ReadOnly);

    QDomDocument    doc;
    doc.setContent(&_fanzhengkeyishuibianqi);
    QDomElement                     root;
    QDomNode                        Record;
    QDomElement                     Date;
    QDomElement                     Time;
    QDomElement                     Minute;
    QDomElement                     Thing;
    QDomElement                     ThingRem;
    root            =doc.firstChildElement("Other_root");
    Record          =root.firstChildElement("Other_Record");
    DoneList_Record                 Buf;

    int                             currentdate=globe.STLDate.daysTo(QDate::currentDate());//当前时间
    Buf.intDate =   Record.firstChildElement("Other_Date").attribute("intDate").toInt();//任务开始时间

    //先读取记录开始时间，以设定进行中任务关键字列表

    QList<JustDo_it>::iterator      eachListItem=TaskList.begin();
    QList<QString>::iterator        eachListItem_KeyWord;
    while (eachListItem!=TaskList.end())
    {
        if((eachListItem->intBeginDate()<Buf.intDate))
        {
            eachListItem_KeyWord=eachListItem->KeyWord.begin();
            while(eachListItem_KeyWord!=eachListItem->KeyWord.end())
            {
                MuiltMap.insert(*eachListItem_KeyWord,eachListItem->TaskID);
                eachListItem_KeyWord++;
            }
        }
        eachListItem++;
    }






    while(!Record.isNull())
    {
        Buf.Date    =   Record.firstChildElement("Other_Date").text();
        Buf.Time    =   Record.firstChildElement("Other_Time").text();
        Buf.Minute  =   Record.firstChildElement("Other_Minute").attribute("Minute").toInt();
        Buf.Thing   =   Record.firstChildElement("Other_Thing").text();
        Buf.ThingRem=   Record.firstChildElement("Other_ThingRem").text();
        Buf.intDate =   Record.firstChildElement("Other_Date").attribute("intDate").toInt();
        Buf.intTime =   Record.firstChildElement("Other_Time").attribute("intTime").toInt();
        Buf.Debugprintf();
        if(MuiltMap.contains(Buf.Thing))
        {
            Return_value    =   MuiltMap.values(Buf.Thing);//需要修改
            for(int i = 0;i < Return_value.size();i++)
            {
                if(Buf.intDate()<(TaskList.begin()+MapForRecordID.value(Return_value.at(i)))->intEndDate())
                {
                    (TaskList.begin()+MapForRecordID.value(Return_value.at(i)))->appendRecord(Buf);//Qlist的at（）以及value方法返回的之阵位常量指针，无法改变其内容，所以要用begin（）来代替
                    (TaskList.begin()+MapForRecordID.value(Return_value.at(i)))->AddMinute(Buf.Minute);
                }
            }
        }
        else
        {}//跳过
        Record  =   Record.nextSibling();
    }
    return;
}

void ToDoList::SaveToFile(globeset globe)
{
    QFile   _TaskFile(globe.GetAndPostPos);
    _TaskFile.open(QIODevice::ReadWrite);
    QTextStream    _Task(&_TaskFile);

    QDomDocument                    xml_Save;
    QDomProcessingInstruction       xml_InsTruction;

    QDomElement                     xml_root;


            QDomElement                     xml_Done;
            QDomElement                     xml_Doing;
                QDomElement                     xml_Task;

                    QDomElement                     xml_BeginDate;
                    QDomElement                     xml_EndDate;
                    QDomElement                     xml_TaskName;//在属性中储存TaskID
                    QDomElement                     xml_MinuteContinue;

                    QDomElement                     xml_KeyWordList;
                    QDomElement                     xml_KeyWords;

                    QDomElement                     xml_ToDoList;
                    QDomElement                     xml_Record;
                    QDomElement                     xml_Thing;
                    QDomElement                     xml_ThingRem;
                    QDomElement                     xml_Date;
                    QDomElement                     xml_Time;
                    QDomElement                     xml_Minute;

                    QDomText                        xml_Text;

    xml_InsTruction     =   xml_Save.createProcessingInstruction("xml","version=\"1.0\" encoding = \"UTF-8\"");
    xml_Save.appendChild(xml_InsTruction);
    xml_root            =   xml_Save.createElement("root");
    xml_root.setAttribute("TaskId_Max",TaskId_Max);


    xml_Done          =   xml_Save.createElement("Done");
    QList<JustDo_it>::const_iterator     it_Done=TaskList.begin();
    QList<QString>::const_iterator       it_Done_KeyWord    = it_Done->KeyWord.begin();
    QList<DoneList_Record>::const_iterator       it_Done_ToDoList   = it_Done->ToDoList.begin();

    while(it_Done!=TaskList.end())
    {
    xml_Task          =   xml_Save.createElement("Task");
    xml_Text          =   xml_Save.createTextNode(it_Done->TaskName);
    xml_TaskName      =   xml_Save.createElement("TaskName");
    xml_TaskName.appendChild(xml_Text);
    xml_TaskName.setAttribute("TaskId",it_Done->TaskID);
    xml_BeginDate     =   xml_Save.createElement("BeginDate");
    xml_Text          =   xml_Save.createTextNode(it_Done->BeginDate);
    xml_BeginDate.appendChild(xml_Text);
    xml_EndDate       =   xml_Save.createElement("EndDate");
    xml_Text          =   xml_Save.createTextNode(it_Done->EndDate);
    xml_EndDate.appendChild(xml_Text);
    /*
    xml_Text          =   xml_Save.createTextNode(it_Done);
    xml.appendChild(xml_Text);
    xml_Text          =   xml_Save.createTextNode(it_Done);
    xml.appendChild(xml_Text);
    */
    xml_MinuteContinue=   xml_Save.createElement("MinuteContinue");
    xml_MinuteContinue.setAttribute("MinuteContinue",it_Done->MinuteContinue);

    xml_KeyWordList   =   xml_Save.createElement("KeyWorldList");
    while(it_Done_KeyWord!=it_Done->KeyWord.end())
    {
        xml_KeyWords  =   xml_Save.createElement("KeyWords");
        xml_Text      =   xml_Save.createTextNode(*it_Done_KeyWord);
        xml_KeyWordList.appendChild(xml_KeyWords);

        it_Done_KeyWord++;
    }

    xml_ToDoList      =   xml_Save.createElement("ToDoList");
    while(it_Done_ToDoList!=it_Done->ToDoList.end())
    {
        xml_Record    =   xml_Save.createElement("Record");

        xml_Date         =   xml_Save.createElement("Date");
        xml_Text          =   xml_Save.createTextNode(it_Done_ToDoList->Date);
        xml_Date.appendChild(xml_Text);
        xml_Date.setAttribute("intDate",it_Done_ToDoList->intDate);
        xml_Time         =   xml_Save.createElement("Time");
        xml_Text         =   xml_Save.createTextNode(it_Done_ToDoList->Time);
        xml_Time.appendChild(xml_Text);
        xml_Time.setAttribute("intTime",it_Done_ToDoList->intTime);

        xml_Minute         =   xml_Save.createElement("Minute");
        xml_Minute.setAttribute("Minute",it_Done_ToDoList->Minute);

        xml_Thing         =   xml_Save.createElement("Thing");
        xml_Text         =   xml_Save.createTextNode(it_Done_ToDoList->Thing);
        xml_Thing.appendChild(xml_Text);
        xml_ThingRem         =   xml_Save.createElement("ThingRem");
        xml_Text         =   xml_Save.createTextNode(it_Done_ToDoList->ThingRem);
        xml_ThingRem.appendChild(xml_Text);

        xml_Record.appendChild(xml_Date);
        xml_Record.appendChild(xml_Time);
        xml_Record.appendChild(xml_Minute);
        xml_Record.appendChild(xml_Thing);
        xml_Record.appendChild(xml_ThingRem);

        xml_ToDoList.appendChild(xml_Record);
        it_Done_ToDoList++;
    }

    xml_Task.appendChild(xml_BeginDate);
    xml_Task.appendChild(xml_EndDate);
    xml_Task.appendChild(xml_TaskName);
    xml_Task.appendChild(xml_MinuteContinue);
    xml_Task.appendChild(xml_KeyWordList);
    xml_Task.appendChild(xml_ToDoList);

    xml_Done.appendChild(xml_Task);

    }
    xml_root.appendChild(xml_Done);


    xml_Save.appendChild(xml_root);

    xml_Save.save(_Task,4);
}

int ToDoList::AllThingCount()
{
    return TaskList.count();
}




void ToDoList::KeyWordList(QString keyWords)
{
    KeyWordListBuffer.append(keyWords);
    return ;
}

void ToDoList::AddTaskIntoList(QString TaskName, QString BeginDate, QString EndDate)
{
    JustDo_it   a;
    a.TaskID    = TaskId_Max+1;
    TaskId_Max++;
    a.BeginDate =BeginDate;
    a.EndDate   =EndDate;
    a.KeyWord   =KeyWordListBuffer;
    KeyWordListBuffer.clear();
    a.MinuteContinue=0;
    Doing.append(a);
    return;
}
