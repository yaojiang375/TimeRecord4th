#include <QCoreApplication>
#include "GTDxml.h"
#include "smsreader.h"
#include "recordname.h"
#include "globe.h"
globeset globe;//待修改成标准模式




int main(void)
{
    globe.read();
    SmsReader   _Reader(globe);
    _Reader.Read(globe);
    RecordName  tryit(globe);

    tryit.appendRecordNameConnect("test","789");
    tryit.SaveRecordNameConnect(globe);
    return 0;
}
