#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED
#include "sys.h"
enum e_TokenCode//���ʱ���
{
    /*�����*/
    TK_PLUS,            //+
    TK_MINUS,           //-
    TK_STAR,            //*
    TK_DEVIDE,          //'/'
    TK_MOD,             //%
    TK_EQ,              //==
    TK_NEQ,             //"!="
    TK_LT,              //<
    TK_LEQ,             //<=
    TK_GT,              //>
    TK_GEQ,             //>=
    TK_ASSIGN,          //=
    TK_POINTSTO,        //->
    TK_DOT,             //.
    TK_AND,             //&
    TK_OPENPA,          //(
    TK_CLOSEPA,         //)
    TK_OPENBR,          //[
    TK_CLOSEBR,         //]
    TK_BEGIN,           //{
    TK_END,             //}
    TK_SEMICOLON,       //;
    TK_COMMA,           //,
    TK_ELLIPSIS,        //...
    TK_EOF,             //EOF

    /*����*/
    TK_CINT,            //����
    TK_CCHAR,           //�ַ�
    TK_CSTR,            //�ַ���

    /*�ؼ���*/
    KW_CHAR,            //char
    KW_SHORT,           //short
    KW_INT,             //int
    KW_VOID,            //void
    KW_STRUCT,          //struct
    KW_IF,              //if
    KW_ELSE,            //else
    KW_FOR,             //for
    KW_CONTINUE,        //continue
    KW_BREAK,           //break
    KW_RETURN,          //return
    KW_SIZEOF,          //sizeof

    KW_ALIGN,           //__align
    KW_CDECL,           //__cdecl
    KW_STDCALL,         //__sedcall

    /*��ʶ��*/
    TK_IDENT

};
typedef struct TkWord
{
    int tkcode;                             //���ʱ���
    struct TkWord * next;                   //ָ���ϣ��ͻ��ͬ���
    char * spelling;                        //�����ַ���
    struct Symbol *sym_struct;              //ֻ�뵥������ʾ�Ľṹ����
    struct Symbol *sym_identifier;          //ֻ�뵥������ʾ�ı�ʶ��
}TkWord;
int elf_hash(char*key);
TkWord * tkword_direct_insert(TkWord * tp);
TkWord * tkword_find(char *p,int keyno);
TkWord *tkword_insert(char *p);
void * mallocz(int size);
void init_lex();
void got_token();
void getch();
int token;
#endif
