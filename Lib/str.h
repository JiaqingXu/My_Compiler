#ifndef STR_H_INCLUDED
#define STR_H_INCLUDED
#include "sys.h"

/*动态字符串定义*/
typedef struct Dynstring
{
    int count;          //字符串长度
    int capacity;       //缓冲区长度
    char * data;        //字符串指针
}Dynstring;
void dynstring_init(Dynstring *pstr,int initsize);
void dynstring_free(Dynstring * pstr);
void dynstring_reset(Dynstring *pstr);
void dynstring_relloc(Dynstring *pstr,int new_size);
void dynstring_chcat(Dynstring * pstr,int ch);


#endif // STR_H_INCLUDED
