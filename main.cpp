#include <QCoreApplication>
#include "GTDxml.h"
#include "smsreader.h"
#include "recordname.h"
#include "globe.h"
#include "namewithsortnumreturnrecord.h"
#include "recordgetandpost.h"
#include "todolist.h"

globeset globe;//待修改成标准模式




int main(void)
{
    globe.read();
    ToDoList    b;
    b.ReadFromAddDBFile(globe);
    b.SaveToFile(globe);
    return 0;
}
