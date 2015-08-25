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
        tp=(TkWord *)mallocz(sizeof(TkWord)+length+1);
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

void * mallocz(int size)
{
    void * ptr;
    ptr = malloc(size);
    if(!ptr && size)
        error("内存分配失败！！！\n");
    memset(ptr,0,size);
    return ptr;
}

void init_lex()
{
    TkWord * tp;
    static TkWord keywords[]={
    {TK_PLUS,       NULL,       "+",           NULL,    NULL},
    {TK_MINUS,      NULL,       "-",            NULL,   NULL},
    {TK_STAR,       NULL,       "*",            NULL,   NULL},
    {TK_DEVIDE,     NULL,        "/",           NULL,   NULL},
    {TK_MOD,        NULL,       "%",            NULL,   NULL},
    {TK_EQ,         NULL,       "==",           NULL,   NULL},
    {TK_NEQ,        NULL,       "!=",           NULL,   NULL},
    {TK_LT,         NULL,        "<",           NULL,   NULL},
    {TK_LEQ,        NULL,        "<=",          NULL,   NULL},
    {TK_GT,         NULL,        ">",           NULL,   NULL},
    {TK_GEQ,        NULL,        ">=",          NULL,   NULL},
    {TK_ASSIGN,     NUL,         "=",           NULL,   NULL},
    {TK_POINTSTO,   NUL          "->",          NULL,   NULL},
    {TK_DOT,        NULL,        ".",          NULL,   NULL},
    {TK_AND,        NULL,        "&",           NULL,   NULL},
    {TK_OPENPA,     NULL,        "(",           NULL,   NULL},
    {TK_CLOSEPA,    NULL;         ")",          NULL,   NULL},
    {TK_OPENBR,     NULL;         "[",         NULL,   NULL},
    {TK_CLOSEBR,    NULL,         "]",          NULL,   NULL},
    {TK_BEGIN,      NULL,         "{",          NULL,   NULL},
    {TK_END,        NULL,         "}",          NULL,   NULL},
    {TK_SEMICOLON,  NULL,         ";",          NULL,   NULL},
    {TK_COMMA,      NULL,          ",",         NULL,   NULL},
    {TK_ELLIPSIS,   NULL,       "...",          NULL,   NULL},
    {TK_EOF,        NULL,     "End_Of_File",    NULL,   NULL},

    /*常量*/
    {TK_CINT,       NULL,     "整型常量",       NULL,   NULL},
    {TK_CCHAR,      NULL,     "字符常量",       NULL,   NULL},
    {TK_CSTR,       NULL,      "字符串常量",    NULL,    NULL},

    /*关键字*/
    {KW_CHAR,       NULL,     "char",           NULL,   NULL},
    {KW_SHORT,      NULL,     "short",          NULL,   NULL},
    {KW_INT,        NULL,     "int",            NULL,   NULL},
    {KW_VOID,       NULL,     "void",           NULL,   NULL},
    {KW_STRUCT,     NULL,     "struct",         NULL,   NULL},
    {KW_IF,         NULL,     "if",             NULL,   NULL},
    {KW_ELSE,       NULL,     "else",           NULL,   NULL},
    {KW_FOR,        NULL,     "for",            NULL,   NULL},
    {KW_CONTINUE,   NULL,     "continue",       NULL,   NULL},
    {KW_BREAK,      NULL,     "break",          NULL,   NULL},
    {KW_RETURN,     NULL,     "return",         NULL,   NULL},
    {KW_SIZEOF,     NULL,     "sizeof",         NULL,   NULL},

    {KW_ALIGN,      NULL,     "__align",        NULL,   NULL},
    {KW_CDECL,      NULL,     "__cdecl",        NULL,   NULL},
    {KW_STDCALL,    NULL,     "__sedcall",      NULL,   NULL},

    {0,             NULL,       NULL,           NULL,   NULL}
    };
    dynarray_init(&tktable,8);
    for(tp=&keywords[0];tp->spelling!=NULL;tp++)
    {
        tkword_direct_insert(tp);
    }
}
