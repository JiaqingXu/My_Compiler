#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED
#include "sys.h"

/*��̬�ַ�������*/
typedef struct Dynstring
{
    int count;          //�ַ�������
    int capacity;       //����������
    char * data;        //�ַ���ָ��
}Dynstring;
void dynstring_init(Dynstring *pstr,int initsize);
void dynstring_free(Dynstring * pstr);
void dynstring_reset(Dynstring *pstr);
void dynstring_relloc(Dynstring *pstr,int new_size);
void dynstring_chcat(Dynstring * pstr,int ch);


#endif // STR_H_INCLUDED
