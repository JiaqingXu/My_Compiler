/****************************************************
//本文件实现编译器的关键字及词法分析
//使用枚举类型列出运算符、常量、关键字和标识符
//2015.7.8
                    徐嘉埥
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "sys.h"
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
/*********************************
*********************************/

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

void got_token()
{
    preprocess();
    switch(ch);
    {
        case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':
        case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':
        case 'm':case 'n':case 'o':case 'p':case 'q':case 'r':
        case 's':case 't':case 'u':case 'v':case 'w':case 'x':
        case 'y':case 'z':
        case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':
        case 'G':case 'H':case 'I':case 'J':case 'K':case 'L':
        case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':
        case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':
        case 'Y':case 'Z':
        case '_':
        {
            TkWord * tp;
            parse_identifier();
            tp=tkword_direct_insert(tkstr.data);
            token = tp->tkcode;
            break;
        }
        case '0':case '1':case '2':case '3':case '4':
        case '5':case '6':case '7':case '8':case '9':
        {
            parse_num();
            token=TK_CINT;
            break;
        }
        case'+':
        {
            getch();
            token = TK_PLUS;
            break;
        }
        case'-':
        {
            getch();
            if(ch=='>')
            {
                token = TK_POINTSTO;
                getch();
            }
            else
                token = TK_MINUS;
            break;
        }
        case'/':
        {
            getch();
            token = TK_DEVIDE;
            break;
        }
        case'%':
        {
            getch();
            token = TK_MOD;
            break;
        }
        case'=':
        {
            getch();
            if(ch == '=')
            {
                token = TK_EQ;
                getch();
            }
            else
                token = TK_ASSIGN;
            break;
        }
        case'!':
        {
            getch();
            if(ch == '=')
            {
                token = TK_NEQ;
                getch();
            }
            else
                error("不支持!")
            break;
        }
        case'<':
        {
            getch();
            if(ch == '=')
            {
                token = TK_LEQ;
                getch();
            }
            else
                token = TK_LT;
            break;
        }
        case'>':
        {
            getch();
            if(ch == '=')
            {
                token = TK_GEQ;
                getch();
            }
            else
                token = TK_GT;
            break;
        }
        case'.':
        {
            getch();
            if(ch == '.')
            {
                getch();
                if(ch != '.')
                    error("省略号错了！！！")；
                else
                token = TK_ELLIPSIS;
                getch();
            }
            else
                token = TK_DOT;
            break;
        }
        case'&':
        {
            getch();
            token = TK_AND;
            break;
        }
        case';':
        {
            getch();
            token = TK_SEMICOLON;
            break;
        }
        case']':
        {
            getch();
            token = TK_CLOSEBR;
            break;
        }
        case'}':
        {
            getch();
            token = TK_END;
            break;
        }
        case')':
        {
            getch();
            token = TK_CLOSEPA;
            break;
        }
        case'[':
        {
            getch();
            token = TK_OPENBR;
            break;
        }
        case'{':
        {
            getch();
            token = TK_BEGIN;
            break;
        }
        case'(':
        {
            getch();
            token = TK_OPENPA;
            break;
        }
        case',':
        {
            getch();
            token = TK_COMMA;
            break;
        }
        case'*':
        {
            getch();
            token = TK_STAR;
            break;
        }
        case'\'':
        {
            parse_string(ch);
            token = TK_CCHAR;
            tkvalue= *(char *)tkstr.data;
            break;
        }
        case'\"':
        {
            parse_string(ch);
            token = TK_CSTR;
            break;
        }
        case EOF:
            token = TK_EOF;
            break;
        default :
            error("不认识的字符：\\x%02x",ch);
            getch();
            break;
    }
}

void getch()
{
    ch = getc(fin);

}

//忽略错误
void preprocess()
{
    while(1)
    {
        if(ch == ' '||ch == '\t' || ch == '\r')
            skip_white_space();
        else if(ch == '/')
        {
            getch();
            if(ch == '*')
            {
                parse_comment();
            }
            else
            {
                ungetc(ch,fin);
                ch = '/';
                break;
            }
        }
        else
            break;
    }
}

//解析注释
void parse_comment()
{
    getch();
    do
    {
        do{
            if(ch == '\n'||ch == '*'||ch == CH_EOF)
                break;
            else
                getch();
        }while(1)
        if(ch=='\n')
        {
            line_num++;
            getch();
        }
        else if (ch == '*')
        {
            getch();
            if (ch == '/')
            {
                getch();
                return ;
            }
        }
        else
        {
            error("缺少注释结束符")；
            return;
        }
    }while(1)
}
//跳过空白
void skip_white_space()
{
    while(ch==' '||ch == '\t'||ch == '\r')
    {
        if(ch == '\r')
        {
            getch();
            if (ch != '\n')
                return ;
            line_num++;
        }
        printf("%c",ch);
        getch();
        return ;
    }
}

//解析字母或下划线
int is_nodigit(char c)
{
    return ((c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_');
}
//解析数字
int is_digit(char c)
{
    return (c>='0'&&c<='9');
}
//解析标识符
void parse_identfier()
{
    dynstring_reset(&tkstr);
    dynstring_chcat(&tkstr,ch);
    getch();
    while(is_nodigit(ch)||is_digit(ch))
    {
        dynstring_chcat(&tkstr,ch);
        getch();
    }
    dynstring_chcat(&tkstr,'\0');
}
//解析整数
void parse_num()
{
    dynstring_reset(&tkstr);
    dynstring_reset(&sourcestr);
    do{
    dynstring_chcat(&tkstr,ch);
    dynstring_chcat(&sourcestr,ch);
    getch();
    }while(is_digit(ch));
    if(ch=='.')
    {
        do{
        dynstring_chcat(&tkstr,ch);
        dynstring_chcat(&sourcestr,ch);
        getch();
        }while(is_digit(ch));
    }
    dynstring_chcat(&tkstr,'\0');
    dynstring_chcat(&sourcestr,'\0');
    tkvalue = atoi(tastr.data);
}
//解析字符串
/**************************************
sep:字符串边界，‘或者“
**************************************/
void parse_string(char sep)
{
    char c;
    dynstring_reset(&tkser);
    dynstring_reset(&sourcestr);
    dynstring_chcat(&sourcestr,sep);
    getch();
    while(1)
    {
        if(ch == sep)
            break;
        else if(ch == '\\')
        {
            dynstring_chcat(&sourcestr,sep);
            getch();
            switch(ch)
            {

            }
        }
    }
}

