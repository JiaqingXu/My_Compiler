/**************************************
*本文本实现编译器的错误处理。
*错误等级分为Error和Warning
*标出错误类型为C（编译错误），L（链接错误）
*提示错误行号。
2015.8.22
            徐嘉埥
***************************************/
#include <stdarg.h>
#include "error.h"
#include <string.h>
#include "sys.h"


/*异常处理*/
/************************************
stage：异常阶段
level：错误级别
fmt：参数输出格式
ap：可变参数列表
****************************************/
void handle_exception(int stage,int level,char *fmt,va_list ap)
{
    char buf[1024];
    vsprintf(buf,fmt,ap);
    if (stage == Stage_Campile)
    {
        if(level == Lever_Warning)
        {
            printf("%s的第%d行：编译警告：%s！\n",filename,line_num,buf);
        }
        else if(level == Lever_Error)
        {
            printf("%s的第%d行：编译错误：%s！！！！！\n",filename,line_num,buf);
            exit(-1);
        }
    }
    else
    {
        printf("链接错误：%s[摊手]\n",buf);
        exit(-1);
    }
}
/*编译警告*/
/*******************************
fmt:参数输出格式。
ap：可变参数列表。
***********************************/
void warning(char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    handle_exception(Stage_Campile,Lever_Warning,fmt,ap);
    va_end(ap);
}
/*编译错误*/
/************************************
fmt:参数输出格式
ap：可变参数列表
*************************************/
void error(char * fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    handle_exception(Stage_Campile,Lever_Error,fmt,ap);
    va_end(ap);
}
/*语法成分缺失*/
/*************************************
msg:缺少语法成分名称
***************************************/
void expect(char *msg)
{
    error("缺少%s",msg);
}

/*获取源码字符串*/
/***************************************
v:单词编号
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
/*word缺失*/
/**************************************
c:缺少的word
***************************************/
void skip(int c)
{
    if(token != c)
    {
        error("缺少%s",get_tkstr(c));
        get_token();
    }
}
/*链接错误*/
/*************************************************
fmt:参数输出格式
ap：可变参数列表
***********************************/
void link_error(char * fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    handle_exception(Stage_Link,Lever_Error,fmt,ap);
    va_end(ap);
}

