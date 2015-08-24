/****************************************************
//���ļ�ʵ�ֱ������Ĺؼ��ּ��ʷ�����
//ʹ��ö�������г���������������ؼ��ֺͱ�ʶ��
//2015.7.8
                    ��Έ�
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "word.h"
#include "arr.h"
//һЩȫ�ֱ���

/**********************************
�����ϣ��ַ
key����ϣ�ؼ���
MAXKEY����ϣ����
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
�ؼ��ַ��뵥�ʱ�
tp�����뵥�ʱ�Ĺؼ���
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
�ڵ��ʱ��в��ҵ���
p:Ҫ���ҵĵ���
keyno�����ʵĹ�ϣֵ
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
����ʶ���Ȳ��ң��Ҳ�������뵥�ʱ�
p����ʶ��
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
