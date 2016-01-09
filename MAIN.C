//锟斤拷锟斤拷锟斤拷锟斤拷

#include "publicvar.h"
#include "symboltab.h"

extern FILE * yyin;
extern FILE * yyout;
extern void yyparse();
extern void printTree(TreeNode *);
void printTime();
void printSkin();
char in[20];
char out[20];
main()
{
	char filename[20] = "a.txt";
	char c;
	printSkin();
	//printf("输入文件名吧:");
	//lexerf("%s",filename);
	strcpy(in,filename);
	strcpy(out,filename);
	if (strchr (in, '.') == NULL)
		strcat(in,".cmn");
	if (strchr (out, '.') == NULL)
		strcat(out,".cout");
	else
	{
		char* pt = strchr (out, '.');
		strncpy(pt,".out",4);
	}
    yyin = (FILE *) fopen(in, "r" );
	if(yyin == NULL){
		printf("啊哦，有点错哦%s :\n", in);
		system("pause");
		return 0;
	}
	printf("%s 文件打开了呢，继续吧？",in);
	getchar();
	getchar();
	system("cls");
	printSkin();
	printf("这个代码，→%s 的词法就是这样的:\n",in);
	yyparse();
	printf("\n输入Y就继续语法分析了呢(Y/N)? ");
	c=getchar();
	if(c=='Y'||c=='y')
	{
		printf("\n那么语法分析开始了哦");
		printf("\n这就是语法树\n");
		printTree(parseTree);
		
		ex(parseTree);
		yyin = (FILE *) fopen(in, "r" );
		yyout = (FILE *) fopen(out,"w");
		yyparse();
		printTree(parseTree);
		printf("\n");
		getchar();
		printf("语法结束了\n");
		printf("要不要看看四元式呢？(Y/N)? ");
		c=getchar();
		if(c=='Y'||c=='y')
		{
			printFour(parseTree);
		}
		else
			exit(0);
	}
	else
		exit(0);
}
void printSkin()
{
	printf("=======================( ??ω?)ノ??===================================\n");
	printf("                      C-mini\n");
	printf("================================================================\n");
}
