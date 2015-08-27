/**************************************
*���ı�ʵ�ֱ������Ĵ�����
*����ȼ���ΪError��Warning
*�����������ΪC��������󣩣�L�����Ӵ���
*��ʾ�����кš�
2015.8.22
            ��Έ�
***************************************/
#include <stdarg.h>
#include "error.h"
#include <string.h>
#include "sys.h"


/*�쳣����*/
/************************************
stage���쳣�׶�
level�����󼶱�
fmt�����������ʽ
ap���ɱ�����б�
****************************************/
void handle_exception(int stage,int level,char *fmt,va_list ap)
{
    char buf[1024];
    vsprintf(buf,fmt,ap);
    if (stage == Stage_Campile)
    {
        if(level == Lever_Warning)
        {
            printf("%s�ĵ�%d�У����뾯�棺%s��\n",filename,line_num,buf);
        }
        else if(level == Lever_Error)
        {
            printf("%s�ĵ�%d�У��������%s����������\n",filename,line_num,buf);
            exit(-1);
        }
    }
    else
    {
        printf("���Ӵ���%s[̯��]\n",buf);
        exit(-1);
    }
}
/*���뾯��*/
/*******************************
fmt:���������ʽ��
ap���ɱ�����б�
***********************************/
void warning(char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    handle_exception(Stage_Campile,Lever_Warning,fmt,ap);
    va_end(ap);
}
/*�������*/
/************************************
fmt:���������ʽ
ap���ɱ�����б�
*************************************/
void error(char * fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    handle_exception(Stage_Campile,Lever_Error,fmt,ap);
    va_end(ap);
}
/*�﷨�ɷ�ȱʧ*/
/*************************************
msg:ȱ���﷨�ɷ�����
***************************************/
void expect(char *msg)
{
    error("ȱ��%s",msg);
}

/*��ȡԴ���ַ���*/
/***************************************
v:���ʱ��
*****************************************/
char * get_tkstr(int v)
{
    if(v>tktable.count)
        return NULL;
    else if(v>=TK_CINT && v<=TK_CSTR)
        return sourcestr.data;
    else
        return ((TkWord*)tktable.data[v])->spelling;
}
/*wordȱʧ*/
/**************************************
c:ȱ�ٵ�word
***************************************/
void skip(int c)
{
    if(token != c)
    {
        error("ȱ��%s",get_tkstr(c));
        get_token();
    }
}
/*���Ӵ���*/
/*************************************************
fmt:���������ʽ
ap���ɱ�����б�
***********************************/
void link_error(char * fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    handle_exception(Stage_Link,Lever_Error,fmt,ap);
    va_end(ap);
}

