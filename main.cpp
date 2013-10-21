#include <QCoreApplication>
#include "GTDxml.h"
#include "smsreader.h"
#include "recordname.h"
#include "globe.h"
#include "namewithsortnumreturnrecord.h"
#include "recordgetandpost.h"
#include "todolist.h"
#include "content_check.h"
globeset globe;//待修改成标准模式




int main(void)
{
    globe.read();
    Content_Check a;
    QString       b;
    QFile         c("c:/123.txt");
    c.open(QIODevice::ReadOnly);
    QTextStream   d(&c);
    b = d.readLine();
    qDebug()<<"b="<<b;
    qDebug()<<a.check(globe,b);
    return 0;
}
