#ifndef RECORDAUTOSORT_H
#define RECORDAUTOSORT_H
#include<QVector>
#include<QString>
#include <QMap>
#include <QtXml>
struct  SortNum
{
    int Sort;
    int Count;
};

QVector<SortNum> ReturnSortNum   ;



class RecordAutoSort//使用自定义QMap和key，key的格式为QString+   &***&****&     +分类代号
{
public:
    RecordAutoSort();
    void Read();//读取过往记录
    QVector<SortNum>      ReturnMultiSortNum();//返回分类号
    bool    RecordSortSave();
    bool    SortRecordPushBack(QString  RecordName,int  SortNum);

private:
    void    RecordBodyWrite();
    void    RecordBodyRead();
    void    SortRecordWrite();
    void    SortRecordRead();
    void    RecordByNameWrite();
    void    RecordByNameRead();

    QDomDocument doc        ;
    QDomProcessingInstruction instruction;
    QDomElement root        ;
    QDomElement RecordByName;
    QDomElement SortByNum   ;
    int         SBN         ;//SortByNum
    QDomElement Record      ;
    QDomElement Date        ;
    QDomElement Time        ;
    QDomElement Body        ;
    QDomElement LastThing   ;
    QDomElement LastRem     ;
};

#endif // RECORDAUTOSORT_H
