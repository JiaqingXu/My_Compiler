/****************************************************
//本文件实现编译器的关键字及词法分析
//使用枚举类型列出运算符、常量、关键字和标识符
//2015.7.8
                    徐嘉埥
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "word.h"
#include "arr.h"
//一些全局变量

/**********************************
计算哈希地址
key：哈希关键字
MAXKEY：哈希表长度
**********************************/
int elf_hash(char*key)
{
    int h=0,g;
    while(*key)
    {
        h=(h<<4)+*key++;
        g=h&0xf000000;
        if(g)
            h^=g>>24;
        h&=~g;
    }
    return h&MAXKEY;
}

/***************************************************
关键字放入单词表
tp：放入单词表的关键字
***************************************************/
TkWord * tkword_direct_insert(TkWord * tp)
{
    int keyno;
    Dynarray_add(&tktable,tp);
    keyno = elf_hash(tp->spelling);
    tp->next=tk_hashtable[keyno];
    tk_hashtable[keyno]=tp;
    return tp;
}
/***********************************************
在单词表中查找单词
p:要查找的单词
keyno：单词的哈希值
**************************************************/
TkWord * tkword_find(char *p,int keyno)
{
    TkWord *tp=NULL,*tp1;
    for(tp1=tk_hashtable[keyno];tp1;tp1=tp1->next)
    {
        if(!strcmp(p,tp1->spelling))
        {
             token = tp->tkcode;
            tp=tp1;
        }
    }
    return tp;
}

/***************************************
将标识符先查找，找不到则插入单词表
p：标识符
*****************************************/
TkWord *tkword_insert(char *p)
{
    TkWord *tp;
    int keyno;
    char *s;
    char *end;
    int length;
    keyno = elf_hash(p);
    tp = tkword_find(p,keyno);
    if(tp==NULL)
    {
        length = strlen(p);
        tp=(TkWord *)malloc(sizeof(TkWord)+length+1);
        tp->next=tk_hashtable[keyno];
        tk_hashtable[keyno] = tp;
        Dynarray_add(&tktable,tp);
        tp->tkcode=tktable.count-1;
        s=(char*)tp+sizeof(TkWord);
        tp->spelling=(char *)s;
        for(end=p+length;p<end;)
        {
            * s++=*p++;
        }
        *s = (char)'\0';
    }
    return tp;
}
