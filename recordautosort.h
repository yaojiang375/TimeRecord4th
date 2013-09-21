#ifndef RECORDAUTOSORT_H
#define RECORDAUTOSORT_H
#include<QVector>
#include<QString>
#include <QMap>

struct  SortNum
{
    int Sort;
    int Count;
};

QVector<SortNum> ReturnSortNum   ;



class RecordAutoSort
{
public:
    RecordAutoSort();
    void Read();//读取过往记录
    QVector<SortNum>      ReturnMultiSortNum();//返回分类号

private:
    
};

#endif // RECORDAUTOSORT_H
