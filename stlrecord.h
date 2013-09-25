#ifndef STLRECORD_H
#define STLRECORD_H
#include <QString>
class STLRecord
{
public:
    STLRecord();
private:
    struct  _SmsContentBody
    {
        QString LastThing;
        QString LastRem;
    };
    struct  _SmsDate
    {
        QString _Date;
        QString _Time;
    };
    struct  _OtherInfo
    {
        int _ScreenShowWrongFlag;
        int _SortNum;
        
    };
};

#endif // STLRECORD_H
