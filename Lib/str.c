/****************************************************
//���ļ�ʵ���ַ����Ķ��塣
//���ö�̬�����ڴ�ķ�ʽ��
//relloc������ÿ���ڴ治���ʱ����һ���ڴ档
//������ʼ�������á����·��䡢׷�ӵȹ���
//2015.7.8
                    ��Έ�
*****************************************************/

#include "str.h"
#include <stdlib.h>
#include <malloc.h>



/*��ʼ��*/
/*************************************************
*pstr:�����ַ����ṹ
*initsize����ʼ���ռ��С
**************************************************/
void dynstring_init(Dynstring *pstr,int initsize)
{
    if(pstr != 0)
    {
        pstr->data = (char *)malloc(sizeof(char)*initsize);
        pstr->count=0;
        pstr->capacity=initsize;
    }
}

/*�ͷſռ�*/
/************************************************************
*pstr���ͷŵ��ַ����ṹ
*************************************************************/
void dynstring_free(Dynstring * pstr)
{
    if(pstr != 0)
    {
        if(pstr->data!=0)
        {
            free(pstr->data);
        }
        pstr->capacity=0;
        pstr->count=0;
    }
}


/*����,Ԥ��8�ֽڳ���*/
/******************************************************
*pstr:���õ��ַ����ṹ
*******************************************************/
void dynstring_reset(Dynstring *pstr)
{
    dynstring_free(pstr);
    dynstring_init(pstr,8);
}


/*���·�������*/
/***************************************************
*pstr:�ַ����ṹ
*new_size���ַ����³���
******************************************************/
void Dynstring_relloc(Dynstring *pstr,int new_size)
{
    int capacity;
    char * data;
    capacity=pstr->capacity;
    while(capacity<new_size)
        capacity=capacity*2;
    data=realloc(pstr->data,capacity);
    if(!data)
        error("�ַ����ڴ�������");
    pstr->capacity=capacity;
    pstr->data=data;

}

/*׷����*/
/*********************************************
*pstr:�ַ����ṹ
*ch:Ҫ׷�ӵ��ַ�
**********************************************/
void dynstring_chcat(Dynstring * pstr,int ch)
{
    int count;
    count=pstr->count+1;
    if(count>pstr->capacity)
        {
            Dynstring_relloc(pstr,count);
        }
    (pstr->data)[count-1]=ch;
    pstr->count=count;
}
