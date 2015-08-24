#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED


/*动态字符串定义*/
typedef struct Dynstring
{
    int count;          //字符串长度
    int capacity;       //缓冲区长度
    char * data;        //字符串指针
}Dynstring;

#endif // STR_H_INCLUDED
