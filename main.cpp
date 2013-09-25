#include <QCoreApplication>
#include "GTDxml.h"
#include "smsreader.h"
#include "recordname.h"
#include "globe.h"
#include "namewithsortnumreturnrecord.h"
globeset globe;//待修改成标准模式




int main(void)
{
    globe.read();
    NameWithSortNumReturnRecord t;
    t.ReadDomFromFile(globe);
    t.appendRecord(QString::fromUtf8("学数学"),3,"2011-10-11","11:12",QString::fromUtf8("看书"),QString::fromUtf8("在寝室"),50,0);
    t.appendRecord(QString::fromUtf8("学数学"),3,"2011-10-11","11:12",QString::fromUtf8("看书"),QString::fromUtf8("在寝室"),50,0);
    t.appendRecord(QString::fromUtf8("学数学"),4,"2011-10-11","11:12",QString::fromUtf8("看dianying"),QString::fromUtf8("在寝室"),50,0);
    t.appendRecord(QString::fromUtf8("学数学"),4,"2011-10-11","11:12",QString::fromUtf8("看电影"),QString::fromUtf8("在寝室"),50,0);
    t.SaveDomOnFile(globe);
    return 0;
}
