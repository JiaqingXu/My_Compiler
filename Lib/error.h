#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED
#include "sys.h"
/***************************************
错误级别
***************************************/
enum e_ErrorLever
{
    Lever_Warning,
    Lever_Error,
};

/***************************************
工作阶段
*****************************************/
enum e_WorkeStage
{
    Stage_Campile,
    Stage_Link,
};
void handle_exception(int stage,int level,char *fmt,va_list ap);
void warning(char *fmt,...);
void error(char * fmt,...);
void expect(char *msg);
char * get_tkstr(int v);
void skip(int c);
void link_error(char * fmt,...);
char * filename;
int line_num;
Dynstring sourcestr;
#endif // ERROR_H_INCLUDED
