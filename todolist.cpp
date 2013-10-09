#include "todolist.h"

ToDoList::ToDoList()
{
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
            Return_value    =   MuiltMap.values(Buf.Thing);
            for(int i = 0;i < Return_value.size();i++)
            {
                (Doing.begin()+MapForRecordID.value(Return_value.at(i)))->appendRecord(Buf);//Qlist的at（）以及value方法返回的之阵位常量指针，无法改变其内容，所以要用begin（）来代替
                (Doing.begin()+MapForRecordID.value(Return_value.at(i)))->AddMinute(Buf.Minute);
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
    QList<JustDo_it>::const_iterator     it_Done=Done.begin();
    QList<QString>::const_iterator       it_Done_KeyWord    = it_Done->KeyWord.begin();
    QList<DoneList_Record>::const_iterator       it_Done_ToDoList   = it_Done->ToDoList.begin();

    while(it_Done!=Done.end())
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

/*Doing*/

    xml_Doing          =   xml_Save.createElement("Doing");
    QList<JustDo_it>::const_iterator     it_Doing=Doing.begin();
    QList<QString>::const_iterator       it_Doing_KeyWord    = it_Doing->KeyWord.begin();
    QList<DoneList_Record>::const_iterator       it_Doing_ToDoList   = it_Doing->ToDoList.begin();

    while(it_Doing!=Doing.end())
    {
    xml_Task          =   xml_Save.createElement("Task");
    xml_Text          =   xml_Save.createTextNode(it_Doing->TaskName);
    xml_TaskName      =   xml_Save.createElement("TaskName");
    xml_TaskName.appendChild(xml_Text);
    xml_TaskName.setAttribute("TaskId",it_Doing->TaskID);
    xml_BeginDate     =   xml_Save.createElement("BeginDate");
    xml_Text          =   xml_Save.createTextNode(it_Doing->BeginDate);
    xml_BeginDate.appendChild(xml_Text);
    xml_EndDate       =   xml_Save.createElement("EndDate");
    xml_Text          =   xml_Save.createTextNode(it_Doing->EndDate);
    xml_EndDate.appendChild(xml_Text);

    xml_MinuteContinue=   xml_Save.createElement("MinuteContinue");
    xml_MinuteContinue.setAttribute("MinuteContinue",it_Doing->MinuteContinue);

    xml_KeyWordList   =   xml_Save.createElement("KeyWorldList");
    while(it_Doing_KeyWord!=it_Doing->KeyWord.end())
    {
        xml_KeyWords  =   xml_Save.createElement("KeyWords");
        xml_Text      =   xml_Save.createTextNode(*it_Doing_KeyWord);
        xml_KeyWordList.appendChild(xml_KeyWords);

        it_Doing_KeyWord++;
    }

    xml_ToDoList      =   xml_Save.createElement("ToDoList");
    while(it_Doing_ToDoList!=it_Doing->ToDoList.end())
    {
        xml_Record    =   xml_Save.createElement("Record");

        xml_Date         =   xml_Save.createElement("Date");
        xml_Text          =   xml_Save.createTextNode(it_Doing_ToDoList->Date);
        xml_Date.appendChild(xml_Text);
        xml_Date.setAttribute("intDate",it_Doing_ToDoList->intDate);
        xml_Time         =   xml_Save.createElement("Time");
        xml_Text         =   xml_Save.createTextNode(it_Doing_ToDoList->Time);
        xml_Time.appendChild(xml_Text);
        xml_Time.setAttribute("intTime",it_Doing_ToDoList->intTime);

        xml_Minute         =   xml_Save.createElement("Minute");
        xml_Minute.setAttribute("Minute",it_Doing_ToDoList->Minute);

        xml_Thing         =   xml_Save.createElement("Thing");
        xml_Text         =   xml_Save.createTextNode(it_Doing_ToDoList->Thing);
        xml_Thing.appendChild(xml_Text);
        xml_ThingRem         =   xml_Save.createElement("ThingRem");
        xml_Text         =   xml_Save.createTextNode(it_Doing_ToDoList->ThingRem);
        xml_ThingRem.appendChild(xml_Text);

        xml_Record.appendChild(xml_Date);
        xml_Record.appendChild(xml_Time);
        xml_Record.appendChild(xml_Minute);
        xml_Record.appendChild(xml_Thing);
        xml_Record.appendChild(xml_ThingRem);

        xml_ToDoList.appendChild(xml_Record);
        it_Doing_ToDoList++;
    }

    xml_Task.appendChild(xml_BeginDate);
    xml_Task.appendChild(xml_EndDate);
    xml_Task.appendChild(xml_TaskName);
    xml_Task.appendChild(xml_MinuteContinue);
    xml_Task.appendChild(xml_KeyWordList);
    xml_Task.appendChild(xml_ToDoList);

    xml_Doing.appendChild(xml_Task);

    }
    xml_root.appendChild(xml_Doing);

/*/Doing结束*/
    xml_Save.appendChild(xml_root);

    xml_Save.save(_Task,4);
}

int ToDoList::AllThingCount()
{
    return Done.count()+Doing.count();
}

int ToDoList::DoingCount()
{
    return Doing.count();
}

int ToDoList::DoneCount()
{
    return Done.count();
}

void ToDoList::KeyWordList(QString keyWords)
{
    KeyWordListBuffer.append(keyWords);
    return ;
}

void ToDoList::AddNeedTodo(QString TaskName, QString BeginDate, QString EndDate)
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
