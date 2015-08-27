#ifndef ARR_H_INCLUDED
#define ARR_H_INCLUDED
#define MAXKEY 1024
#include "sys.h"
/*�ṹ�嶨��*/
typedef struct Dynarray
{
    int count;          //Ԫ�ظ���
    int capacity;       //��������С
    void **data;        //ָ������ָ������
}Dynarray;

void dynarray_init(Dynarray *parr,int initsize);
void dynarray_free(Dynarray *parr);
void Dynarray_relloc(Dynarray *parr,int size);
void Dynarray_add(Dynarray *parr,int num);
int Dynarray_find(Dynarray *parr,int key);
                   //��ϣ������
TkWord* tk_hashtable[MAXKEY];          //���ʹ�ϣ��
Dynarray tktable;                       //���ʱ�

#endif // ARR_H_INCLUDED
