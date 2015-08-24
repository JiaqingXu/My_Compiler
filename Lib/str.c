/****************************************************
//本文件实现字符串的定义。
//采用动态分配内存的方式。
//relloc函数在每次内存不足的时候倍增一次内存。
//包括初始化、重置、重新分配、追加等功能
//2015.7.8
                    徐嘉埥
*****************************************************/

#include "str.h"
#include <stdlib.h>
#include <malloc.h>



/*初始化*/
/*************************************************
*pstr:定义字符串结构
*initsize：初始化空间大小
**************************************************/
void dynstring_init(Dynstring *pstr,int initsize)
{
    if(pstr != 0)
    {
        pstr->data = (char *)malloc(sizeof(char)*initsize);
        pstr->count=0;
        pstr->capacity=initsize;
    }
}

/*释放空间*/
/************************************************************
*pstr：释放的字符串结构
*************************************************************/
void dynstring_free(Dynstring * pstr)
{
    if(pstr != 0)
    {
        if(pstr->data!=0)
        {
            free(pstr->data);
        }
        pstr->capacity=0;
        pstr->count=0;
    }
}


/*重置,预设8字节长度*/
/******************************************************
*pstr:重置的字符串结构
*******************************************************/
void dynstring_reset(Dynstring *pstr)
{
    dynstring_free(pstr);
    dynstring_init(pstr,8);
}


/*重新分配容量*/
/***************************************************
*pstr:字符串结构
*new_size：字符串新长度
******************************************************/
void Dynstring_relloc(Dynstring *pstr,int new_size)
{
    int capacity;
    char * data;
    capacity=pstr->capacity;
    while(capacity<new_size)
        capacity=capacity*2;
    data=realloc(pstr->data,capacity);
    if(!data)
        error("字符串内存分配错误");
    pstr->capacity=capacity;
    pstr->data=data;

}

/*追加字*/
/*********************************************
*pstr:字符串结构
*ch:要追加的字符
**********************************************/
void dynstring_chcat(Dynstring * pstr,int ch)
{
    int count;
    count=pstr->count+1;
    if(count>pstr->capacity)
        {
            Dynstring_relloc(pstr,count);
        }
    (pstr->data)[count-1]=ch;
    pstr->count=count;
}
