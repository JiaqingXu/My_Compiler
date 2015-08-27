#ifndef ARR_H_INCLUDED
#define ARR_H_INCLUDED
#define MAXKEY 1024
#include "sys.h"
/*结构体定义*/
typedef struct Dynarray
{
    int count;          //元素个数
    int capacity;       //缓冲区大小
    void **data;        //指向数据指针数组
}Dynarray;

void dynarray_init(Dynarray *parr,int initsize);
void dynarray_free(Dynarray *parr);
void Dynarray_relloc(Dynarray *parr,int size);
void Dynarray_add(Dynarray *parr,int num);
int Dynarray_find(Dynarray *parr,int key);
                   //哈希表容量
TkWord* tk_hashtable[MAXKEY];          //单词哈希表
Dynarray tktable;                       //单词表

#endif // ARR_H_INCLUDED
