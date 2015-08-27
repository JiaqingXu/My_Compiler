/****************************************************
//���ļ�ʵ�����飨array���Ķ��塣
//���ö�̬�����ڴ�ķ�ʽ��
//relloc������ÿ���ڴ治���ʱ����һ���ڴ档
//������ʼ�������·��䡢׷�ӡ����ҵȹ���
//2015.7.13
                    ��Έ�
*****************************************************/
#include "sys.h"

/*��ʼ��*/
/**********************************************
*parr:����ṹָ��
*initsize:��ʼ������
**********************************************/
void dynarray_init(Dynarray *parr,int initsize)
{
    if(parr!=0)
    {
        parr->data=(void**)malloc(sizeof(char)*initsize);
        parr->count=0;
        parr->capacity=initsize;
    }
}

/*�ͷ�*/
/***************************************************
*parr:����ṹָ��
****************************************************/
void dynarray_free(Dynarray *parr)
{
    void **p;
    for(p=parr->data;parr->count;++p,--parr->count)
    {
        if(*p)
            free(*p);
        free(parr->data);
        parr->data=NULL;
    }
}
/*���·���*/
/***************************************
*parr:����ṹ��ָ��
*size�����·���ĳ���
***************************************/
void Dynarray_relloc(Dynarray *parr,int size)
{
       int capacity;
    char * data;
    capacity=parr->capacity;
    while(capacity<size)
        capacity=capacity*2;
    data=realloc(parr->data,capacity);
    if(!data)
        error("�����ڴ�������");
    parr->capacity=capacity;
    parr->data=data;
}

/*׷��*/
/****************************************
*parr:����ṹָ��
*count��׷������
****************************************/
void Dynarray_add(Dynarray *parr,int num)
{
     int count;
    count=parr->count+1;
    if(count>parr->capacity)
        {
            Dynarray_relloc(parr,count);
        }
    (parr->data)[count-1]=num;
    parr->count=count;
}

/*����*/
/******************************************
*parr:����ṹָ��
*key�����ҹؼ���
*����ֵ������Ԫ�ص������±�//-1Ϊ�޷��鵽��
*******************************************/
int Dynarray_find(Dynarray *parr,int key)
{
    int i=0;
    int **p=(int**)parr->data;
    for(i=0;i<parr->count;i++,p++)
        if(key==**p)
        {
            return i;
        }
    return -1;
}
