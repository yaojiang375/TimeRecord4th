#ifndef GLOBE_H
#define GLOBE_H

#endif // GLOBE_H

class globeset
{
public:
    QString SmsPos;
    bool ReadWrong;
    QString RILFlag;
    QString RecFlag;
    QString AddFlag;

    globeset()
    {
        SmsPos      = "c:/1.csv";
        ReadWrong   =FALSE;
        RILFlag     ="！";
        RecFlag     ="。";
        AddFlag     ="，";
    }
};
