#ifndef ARR_H_INCLUDED
#define ARR_H_INCLUDED
#define MAXKEY 1024
#include "word.h"
/*�ṹ�嶨��*/
typedef struct Dynarray
{
    int count;          //Ԫ�ظ���
    int capacity;       //��������С
    void **data;        //ָ������ָ������
}Dynarray;
                   //��ϣ������
TkWord* tk_hashtable[MAXKEY];          //���ʹ�ϣ��
Dynarray tktable;                       //���ʱ�

#endif // ARR_H_INCLUDED
