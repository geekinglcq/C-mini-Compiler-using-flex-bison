
#include "globals.h"
#include "util.h"

/*�ú���������ӡtoken����parse�����е���scan���̣�������token
 */
void printToken( TokenType token, const char* tokenString)
{
  switch (token)
  {
  case IF:
  case ELSE:
  case WHILE:
  case RETURN:
      fprintf(yyout,"Reserved word: %s\n",tokenString);
      break;
  case INT:
	  fprintf(yyout,"int\n");
	  break;
  case VOID:
	  fprintf(yyout,"void\n");
	  break;
  case ASSIGN:
	  fprintf(yyout,"=\n");
	  break;
  case LT:
	  fprintf(yyout,"<\n");
	  break;
  case GT:
	  fprintf(yyout,">\n");
	  break;
  case EQ:
	  fprintf(yyout,"==\n");
	  break;
  case LTEQ:
	  fprintf(yyout,"<=\n");
	  break;
  case GTEQ:
	  fprintf(yyout,">=\n");
	  break;
  case LPAREN:
	  fprintf(yyout,"(\n");
	  break;
  case RPAREN:
	  fprintf(yyout,")\n");
	  break;
  case LBRACK:
	  fprintf(yyout,"[\n");
	  break;
  case RBRACK:
	  fprintf(yyout,"]\n");
	  break;
  case LCURL:
	  fprintf(yyout,"{\n");
	  break;
  case RCURL:
	  fprintf(yyout,"}\n");
	  break;
  case SEMI:
	  fprintf(yyout,";\n");
	  break;
  case COMMA:
	  fprintf(yyout,",\n");
	  break;
  case PLUS:
	  fprintf(yyout,"+\n");
	  break;
  case MINUS:
	  fprintf(yyout,"-\n");
	  break;
  case TIMES:
	  fprintf(yyout,"*\n");
	  break;
  case OVER:
	  fprintf(yyout,"/\n");
	  break;
  case ENDFILE: fprintf(yyout,"EOF\n");
	  break;
  case NUM:
      fprintf(yyout," NUM, val= %s\n",tokenString);
      break;
  case ID:
	  fprintf(yyout," ID, name= %s\n",tokenString);
      break;
  case ERROR:
	  fprintf(yyout,"ERROR: %s\n",tokenString);
      break;
  default:
      fprintf(yyout,"Unknown token: %d\n",token);
  }
}

/*�����﷨���½���
 */

TreeNode * newNode(NodeKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
  {
    fprintf(yyout,"Out of memory error at line %d\n",lineno);
  }
  else
  {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->kind = kind;
    t->lineno = lineno;
  }
  return t;
}

/*
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(yyout,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}


static indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{
	int i;
	for (i=0;i<indentno;i++)
		fprintf(yyout," ");
}
/* ��ӡ�﷨�� */
void printTree( TreeNode * tree)
{
  int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    switch (tree->kind) {
        case IfK:
          fprintf(yyout,"If\n");
          break;
        case WhileK:
          fprintf(yyout,"While\n");
          break;
        case AssignK:
          fprintf(yyout,"Assign to: \n",tree->attr.name);
          break;
        case ReturnK:
          fprintf(yyout,"Return: \n",tree->attr.name);
          break;
        case CallK:
          fprintf(yyout,"Call: \n",tree->attr.name);
          break;
        case VarDeclK:
          fprintf(yyout,"Var Decl: ");
	        printToken(tree->attr.op,'\0');
          break;
        case FunDeclK:
          fprintf(yyout,"Fun Decl: ");
	        printToken(tree->attr.op,'\0');
          break;
        case OpK:
          fprintf(yyout,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(yyout,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(yyout,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(yyout,"Unknown ExpNode kind\n");
          break;
    }
  for (i=0;i<MAXCHILDREN;i++)
    printTree(tree->child[i]);
  tree = tree->sibling;
  }
  UNINDENT;
}
//��Ԫ�鹹��;
/*void printTree( TreeNode * tree)
{
  int i,count,n;
  n=0;
  count=-1;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    switch (tree->kind) {
        case IfK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}
			SYZ[count].type2=0;
			strcpy(SYZ[count].operation,"zht");
			strcpy(SYZ[count].op2,"\0");
			SYZ[count].result_no=n+2;
			n++;
			fprintf(yyout,"If\n");
			break;
        case WhileK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}
			SYZ[count].type2=0;
			strcpy(SYZ[count].op2,"\0");
			strcpy(SYZ[count].operation,"zht");
			SYZ[count].result_no=n+2;
          fprintf(yyout,"While\n");
          break;
        case AssignK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==VarDeclK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}
			SYZ[count].result_no=count;
			fprintf(yyout,"Assign to: \n",tree->attr.name);
			break;
        case ReturnK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}
			SYZ[count].result_no=count;
          fprintf(yyout,"Return: \n",tree->attr.name);
          break;
        case CallK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}
			SYZ[count].result_no=count;
          fprintf(yyout,"Call: \n",tree->attr.name);
          break;
        case VarDeclK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}
			SYZ[count].result_no=count;
          fprintf(yyout,"Var Decl: ");
		  printToken(tree->attr.op,'\0');
          break;
        case FunDeclK:	count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}

			SYZ[count].result_no=count;
          fprintf(yyout,"Fun Decl: ");
		  printToken(tree->attr.op,'\0');
          break;
        case OpK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}

			SYZ[count].result_no=count;
          fprintf(yyout,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}

			SYZ[count].result_no=count;
          fprintf(yyout,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
			count++;
			if(tree->child[0])
			{
				if(tree->child[0]->kind==IdK||tree->child[0]->kind==CallK)
				{
					SYZ[count].type1=0;
					strcpy(SYZ[count].op1,tree->child[0]->attr.name);
				}
				else
				{
					SYZ[count].type1=1;
					SYZ[count].o1=tree->child[0]->attr.val;
				}
			}

			SYZ[count].result_no=count;
          fprintf(yyout,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(yyout,"Unknown ExpNode kind\n");
          break;
    }
  for (i=0;i<MAXCHILDREN;i++)
    printTree(tree->child[i]);
  tree = tree->sibling;
  }
  N=count;
  UNINDENT;
}*/
printCode()
{
	int count;
	for(count=0;count<N;count++)
	{
		printf("(%s",SYZ[count].operation);
		if(SYZ[count].type1==0)
			printf("%s",SYZ[count].op1);
		else
			printf("%d",SYZ[count].o1);
		if(SYZ[count].type2==0)
			printf("%s",SYZ[count].op2);
		else
			printf("%d",SYZ[count].o2);
		printf("T%d)\n",SYZ[count].result_no);
	}
	N=0;
}
