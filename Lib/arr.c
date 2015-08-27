/****************************************************
//本文件实现数组（array）的定义。
//采用动态分配内存的方式。
//relloc函数在每次内存不足的时候倍增一次内存。
//包括初始化、重新分配、追加、查找等功能
//2015.7.13
                    徐嘉埥
*****************************************************/
#include "sys.h"

/*初始化*/
/**********************************************
*parr:数组结构指针
*initsize:初始化长度
**********************************************/
void dynarray_init(Dynarray *parr,int initsize)
{
    if(parr!=0)
    {
        parr->data=(void**)malloc(sizeof(char)*initsize);
        parr->count=0;
        parr->capacity=initsize;
    }
}

/*释放*/
/***************************************************
*parr:数组结构指针
****************************************************/
void dynarray_free(Dynarray *parr)
{
    void **p;
    for(p=parr->data;parr->count;++p,--parr->count)
    {
        if(*p)
            free(*p);
        free(parr->data);
        parr->data=NULL;
    }
}
/*重新分配*/
/***************************************
*parr:数组结构体指针
*size：重新分配的长度
***************************************/
void Dynarray_relloc(Dynarray *parr,int size)
{
       int capacity;
    char * data;
    capacity=parr->capacity;
    while(capacity<size)
        capacity=capacity*2;
    data=realloc(parr->data,capacity);
    if(!data)
        error("数组内存分配错误");
    parr->capacity=capacity;
    parr->data=data;
}

/*追加*/
/****************************************
*parr:数组结构指针
*count：追加数据
****************************************/
void Dynarray_add(Dynarray *parr,int num)
{
     int count;
    count=parr->count+1;
    if(count>parr->capacity)
        {
            Dynarray_relloc(parr,count);
        }
    (parr->data)[count-1]=num;
    parr->count=count;
}

/*查找*/
/******************************************
*parr:数组结构指针
*key：查找关键字
*返回值：所在元素的数组下标//-1为无法查到。
*******************************************/
int Dynarray_find(Dynarray *parr,int key)
{
    int i=0;
    int **p=(int**)parr->data;
    for(i=0;i<parr->count;i++,p++)
        if(key==**p)
        {
            return i;
        }
    return -1;
}
