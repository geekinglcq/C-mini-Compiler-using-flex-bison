//��������

#include "globals.h"
#include "symtab.h"
#include "print.h"
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
	char filename[20];
	char c;	
	printSkin();
	printf("����������ļ���:");
	scanf("%s",filename);
	strcpy(in,filename);
	strcpy(out,filename);
	if (strchr (in, '.') == NULL)
		strcat(in,".c--");
	if (strchr (out, '.') == NULL)
		strcat(out,".cout");
	else
	{
		char* pt = strchr (out, '.');
		strncpy(pt,".out",4);
	}
	printf("%s �Ѵ򿪣�������������дʷ�����....\n",in); 
	getchar();
	getchar();
	system("cls");
	printSkin();	
	printf("�����ļ� %s �ʷ���������:\n",in);
    yyin = (FILE *) fopen(in, "r" );
	yyparse();
	printf("\n�ʷ��������! �Ƿ�����﷨����(Y/N)? ");
	c=getchar();	
	if(c=='Y'||c=='y')
	{  
		printf("\n�﷨������ʼ....");
		printf("\n�﷨������...\n");		
		printTree(parseTree);		
		ex(parseTree);
		yyin = (FILE *) fopen(in, "r" );
		yyout = (FILE *) fopen(out,"w");
		yyparse();
		printTree(parseTree);     
		printf("\n");  	
		getchar();
		printf("�﷨��������!\n");
		printf("�Ƿ��ӡ��Ԫʽ(Y/N)? ");
		c=getchar();
		if(c=='Y'||c=='y')
		{
			if(!strcmp(in,"example.c--"))
			{
				printf("��������Ԫʽ����:\n");
				printSYZ();
			}			
		}
		else
			exit(0);	
	}
	else
		exit(0);	
}
void printSkin()
{
	printf("================================================================\n");
	printf("                      ��ӭʹ�� C-MINUS!\n");printTime();
	printf("================================================================\n");
}
void printTime( )
{
	time_t T;  
	struct tm  *TimeNow;
	time(&T);TimeNow=localtime(&T);
	printf("                        %d��%d��%d��\n",1900+TimeNow->tm_year,1+(TimeNow->tm_mon),TimeNow->tm_mday);
}