#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED


/*��̬�ַ�������*/
typedef struct Dynstring
{
    int count;          //�ַ�������
    int capacity;       //����������
    char * data;        //�ַ���ָ��
}Dynstring;

#endif // STR_H_INCLUDED
