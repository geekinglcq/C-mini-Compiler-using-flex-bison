


#ifndef _UTIL_H_
#define _UTIL_H_

 
void printToken( TokenType, const char*);//定义打印token函数

TreeNode * newNode(NodeKind kind);       //这函数用来申请开辟语法树结点


char * copyString( char * );

void printTree( TreeNode *);//打印语法树

extern FILE* yyout;

#endif