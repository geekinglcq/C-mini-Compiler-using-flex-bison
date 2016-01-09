/* source code courtesy of Frank Thomas Braun */

/* calc3d.c: Generation of the graph of the syntax tree */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "publicvar.h"
//#include "y.tab.h"

int del = 1; /* 图形参数 */
int eps = 3; /* 图形参数 */
#define lmax 200
#define cmax 200

char graph[lmax][cmax];
int graphNumber = 0; /* 图形化矩阵 */
/* interface for drawing (can be replaced by "real" graphic using GD or other) */
void graphInit (void);
void graphFinish();
void graphBox (char *s, int *w, int *h);
void graphDrawBox (char *s, int c, int l);
void graphDrawArrow (int c1, int l1, int c2, int l2);
void graphTest(int l,int c);
void exNode (TreeNode *p, int c, int l, int *ce, int *cm);

/*****************************************************************************/

/* main entry point of the manipulation of the syntax tree */
int ex (TreeNode *p) {
    int rte, rtm,cs;

    graphInit ();

    exNode (p, 0, 0, &rte, &rtm);
    while(p->sibling)
    { cs=rte;
      exNode(p->sibling,cs,0,&rte,&rtm);
      p=p->sibling;
    }
    graphFinish();
    return 0;
}

/*c----cm---ce---->                       绘制叶子结点
 l leaf-info
 */

/*c---------------cm--------------ce----> 绘制非叶子结点
 l            node-info
 *                |
 *    -------------     ...----
 *    |       |               |
 *    v       v               v
 * child1  child2  ...     child-n
 *        che     che             che
 *cs      cs      cs              cs
 *
 */


/* 处理某节点 */
void exNode (TreeNode *p, int c, int l, int *ce, int *cm)/*c 列起点， l 行起点，ce 子节点列终点，che 子节点列中点*/
{

    int w, h;           /* 节点宽度和高度*/
    /*节点的文本 */
	  char *s;
    int cbar;           /* 节点横向的起点 */
    int k;              /* 用于计数儿子&兄弟的数量 */
    int che, chm;       /* 横向终点和子树的中点*/
    int cs;             /* 子树起点  */
    //int ji;
    char word[20];      /* 方便测试 */

    if (!p) return;

    strcpy (word, "???"); /* 测试用 */
    s = word;
    printf("%d ",p->kind);
    switch(p->kind) {
        case ConstK: sprintf (word, "c(%d)", p->attr.val); break;
        case IdK:  sprintf (word, "id(%s)", p->attr.name); break;
        case IfK:   s="if"; break;
        case WhileK:    s="while"; break;
        case AssignK:   s="[=]";break;
        case ReturnK:   s="return";break;
        case CallK:     s="call";  break;
        case VarDeclK:
            switch (p->attr.op) {
              case 262:       s="int";    break;
              case 264:       s="void";   break;
              default:        break;
            }break;
        case FunDeclK:  s="FunDecl";break;
        case OpK:
            switch(p->attr.op){
                case 268:       s = "[=]";     break;
                case 275:       s = "[+]";     break;
                case 276:       s = "[-]";     break;
                case 277:       s = "[*]";     break;
                case 278:       s = "[/]";     break;
                case 273:       s = "[<]";     break;
                case 274:       s = "[>]";     break;
                case 272:        s = "[>=]";    break;
                case 271:        s = "[<=]";    break;
                case 270:        s = "[!=]";    break;
                case 269:        s = "[==]";    break;
                case 279:        s="[(]";        break;
                case 280:        s="[)]";       break;
                case 281:        s="[[]";       break;
                case 282:         s="[]]";      break;
                case 283:         s="[{]";      break;
                case 284:         s="[}]";      break;
                case 286:        s="[,]";       break;
                case 285:       s = "[;]";     break;
                default:         break;
            }
            break;
    }

    /* 构建文本框 */
    graphBox (s, &w, &h);
    cbar = c;
    *ce = c + w;
    *cm = c + w / 2;

    /* 叶子结点 */
    if (!p->child[0]) {
        graphDrawBox (s, cbar, l);
        return;
    }

    /* 有子女的节点 */
    cs = c;

    printf("%s\n",s);
    switch (p->kind)
    {
      case OpK:
        switch (p->attr.op){
          case 269:
          case 270:
          case 271:
          case 272:
          case 273:
          case 274:
          case 275:
          case 276:
          case 277:
          case 278: cs=c;

                    for(k=0;k<3;k++){
                    if(p->child[k]!=NULL){
                        exNode (p->child[k], cs, l+h+eps, &che, &chm);
                        printf("child- %s,%d,%d\n",s,cs,l+h+eps);

                        cs = che;
                    }
                  }
                    /* 节点 总宽度 */
                    if (w < che - c) {
                        cbar += (che - c - w) / 2;
                        *ce = che;
                        *cm = (c + che) / 2;
                    }
                    /* 绘制该节点 */
                    graphDrawBox (s, cbar, l);
                    cs = c;
                    for(k=0;k<3;k++){
                    if(p->child[k]!=NULL){
                        exNode (p->child[k], cs, l+h+eps, &che, &chm);
                        printf("child- %s,%d,%d\n",s,cs,l+h+eps);
                        graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
                        cs = che;
                    }
                  }
                  /*  exNode(p->child[0],cs,l+h+eps,&che,&chm);
                    graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
                    cs = che;
                //    exNode (p->child[2], cs, l+h+eps, &che, &chm);
                    graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
                    cs = che;*/
                    break;
          default: break;
        };break;
      default:
      for(k=0;k<3;k++){
      if(p->child[k]!=NULL)
          {
            exNode(p->child[k],cs,l+h+eps,&che,&chm);
            printf("child+ %s,%d,%d\n",s,cs,l+h+eps);
            cs=che;
            k++;
          }
        }
        for(k=0;k<3;k++)
        {
          if(p->child[k]!=NULL)
          if(p->child[k]->sibling!=NULL)
          {
            exNode(p->child[k]->sibling,cs,l+h+eps,&che,&chm);
            printf("child * %s,%d,%d\n",s,cs,l+h+eps);
            cs=che;
          }
        }
          /* 节点 总宽度 */
          if (w < che - c) {
              cbar += (che - c - w) / 2;
              *ce = che;
              *cm = (c + che) / 2;
          }

          /* 绘制该节点 */
          graphDrawBox (s, cbar, l);

          /*绘制箭头*/
          cs = c;
          for(k=0;k<3;k++){
          if(p->child[k]){
              exNode (p->child[k], cs, l+h+eps, &che, &chm);
              printf("child= %s,%d,%d\n",s,cs,l+h+eps);
              graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
              cs = che;
          }
        }
        for(k=0;k<3;k++)
        {
        if(p->child[k]!=NULL)
        if(p->child[k]->sibling!=NULL)
        {
          exNode(p->child[k]->sibling,cs,l+h+eps,&che,&chm);
          printf("sibling %s,%d,%d\n",s,cs,l+h+eps);
          graphDrawArrow (*cm, l+h, chm, l+h+eps-1);
          printf("%d",k);
          cs=che;
        }
      }
          break;



}
}

/* 画图接口 */

//测试是否超出图画

void graphTest (int l, int c)
{   int ok;
    ok = 1;
    if (l < 0) ok = 0;
    if (l >= 200) ok = 0;
    if (c < 0) ok = 0;
    if (c >= 200) ok = 0;
    if (ok) return;
    printf ("\n+++error: l=%d, c=%d not in drawing rectangle 0, 0 ... %d, %d",
        l, c, 200, 200);
    //exit(1);
}

void graphInit (void) {
    int i, j;
    for (i = 0; i < 200; i++) {
        for (j = 0; j < 200; j++) {
            graph[i][j] = ' ';
        }
    }
}

void graphFinish() {
    int i, j;
    for (i = 0; i < lmax; i++) {
        for (j = cmax-1; j > 0 && graph[i][j] == ' '; j--);
        graph[i][cmax-1] = 0;
        if (j < cmax-1) graph[i][j+1] = 0;
        if (graph[i][j] == ' ') graph[i][j] = 0;
    }
    for (i = lmax-1; i > 0 && graph[i][0] == 0; i--);
    printf ("\n\nGraph \n");
    for (j = 0; j <= i; j++) printf ("\n%s", graph[j]);
    printf("\n");
}

void graphBox (char *s, int *w, int *h) {
    *w = strlen (s) + del;
    *h = 1;
}

void graphDrawBox (char *s, int c, int l) {
    int i;
  //  printf(",.,%s,%d,%d\n",s,c,l);
    graphTest (l, c+strlen(s)-1+del);
    for (i = 0; i < strlen (s); i++) {
        graph[l][c+i+del] = s[i];
      }
}
void graphDrawArrow (int c1, int l1, int c2, int l2) {
    int m;
    graphTest (l1, c1);
    graphTest (l2, c2);
    m = (l1 + l2) / 2;
    while (l1 != m) { graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--; }
    while (c1 != c2) { graph[l1][c1] = '-'; if (c1 < c2) c1++; else c1--; }
    while (l1 != l2) { graph[l1][c1] = '|'; if (l1 < l2) l1++; else l1--; }
    graph[l1][c1] = '|';
}
