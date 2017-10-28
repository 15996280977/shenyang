#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<time.h> 

#define MAX 2/*车库容量*/ 
#define price 0.05 /*每车每分钟费用*/ 
typedef struct time{ 
          int hour; 
          int min; 
}Time; /*时间结点*/ 
typedef struct node{ 
          char num[10];
		  char size[10];
          Time reach; 
          Time leave; 
}CarNode; /*车辆信息结点*/ 
typedef struct NODE{ 
          CarNode *stack[MAX+1]; 
          int top; 
}SeqStackCar; /*模拟车站*/ 
typedef struct car{ 
          CarNode *data; 
          struct car *next; 
}QueueNode; 
typedef struct Node{ 
          QueueNode *head; 
          QueueNode *rear; 
}LinkQueueCar; /*模拟通道*/
 

void InitStack(SeqStackCar *); /*初始化栈*/ 
int InitQueue(LinkQueueCar *); /*初始化便道*/ 
int Arrival(SeqStackCar *,LinkQueueCar *); /*车辆到达*/ 
void Leave(SeqStackCar *,SeqStackCar *,LinkQueueCar *); /*车辆离开*/ 
void List(SeqStackCar,LinkQueueCar); /*显示存车信息*/
int check(char *ps); 
void WRITE();
void READ();
FILE *fp2;


void main() 
{ 
    SeqStackCar Enter,Temp; 
    LinkQueueCar Wait; 
    int ch; 
	char str[10];
	int b=0;
    int a;
	printf("请输入口令登录：（以#号键结束，输错4次后将关闭）：");
    while((str[b]=getchar())!='#')
	{
		b++;
	}
	str[b]='\0';
        
	if(check(str))
		printf("验证通过！\n");
	else
	{
		printf("验证错误！\n");
	for(a=3;a>0;a--)
	{   
		b=0;
		getchar();

		printf("请输入口令进行登录：（以#号键结束，剩余%d次机会）：",a);
		while((str[b]=getchar())!='#')
	{
		b++;
	}
	str[b]='\0';
    if(check(str))
	{
		printf("验证通过！\n"); 
		break;
	}
	else
	{
		printf("验证错误！\n");
	}
	}
	}
      if(!check(str))
           exit(0);

    system("cls");
    InitStack(&Enter); /*初始化车站*/ 
    InitStack(&Temp); /*初始化让路的临时栈*/ 
    InitQueue(&Wait); /*初始化通道*/ 
    
	while(1) 
	{ 
         printf("******** 1. the car arrive ********\n"); 
         printf("******** 2. the car leave  ********\n"); 
         printf("******** 3. the schedule   ********\n"); 
         printf("******** 4. out            ********\n"); 
         while(1) 
		 { 
              scanf("%d",&ch); 
              if
				  (ch>=1&&ch<=4)break; 
              else 
				  printf("\nplease choose： 1|2|3|4."); 
		 } 
          switch(ch) 
		  { 
               case 1:Arrival(&Enter,&Wait);break; /*车辆到达*/ 
               case 2:Leave(&Enter,&Temp,&Wait);break; /*车辆离开*/ 
               case 3:List(Enter,Wait);break; /*列表打印信息*/ 
               case 4:exit(0); /*退出主程序*/ 
               default: break; 
		  } 
	} 
} 

 
void InitStack(SeqStackCar *s) /*初始化栈*/ 
{ 
    int i; 
    s->top=0; 
    for(i=0;i<=MAX;i++) 
        s->stack[s->top]=NULL; 
}

 
int InitQueue(LinkQueueCar *Q) /*初始化便道*/ 
{ 
    Q->head=(QueueNode *)malloc(sizeof(QueueNode)); 
    if(Q->head!=NULL) 
	{ 
        Q->head->next=NULL; 
        Q->rear=Q->head; 
     return(1); 
	} 
    else return(-1); 
}

 
void PRINT(CarNode *p,int room) /*打印出站车的信息*/ 
{ 
    int A1,A2,B1,B2; 
    struct tm *local;
	long m;
	time(&m);
	local = localtime(&m);
	local->tm_year = local->tm_year + 1900;
	local->tm_mon ++;
    p->leave.hour=local->tm_hour;
	p->leave.min=local->tm_min; 
    printf("\nthe number of the car:"); 
    puts(p->num); 
	printf("the size of car is %s",p->size);
    printf("\nthe time the car arrive: %d:%d",p->reach.hour,p->reach.min); 
    printf("the depart time: %d:%d",p->leave.hour,p->leave.min); 
    A1=p->reach.hour; 
    A2=p->reach.min; 
    B1=p->leave.hour; 
    B2=p->leave.min; 
    printf("\nthe fee: %2.1f元",((B1-A1)*60+(B2-A2))*price); 
free(p); 
}

 
int Arrival(SeqStackCar *Enter,LinkQueueCar *W) /*车辆到达*/ 
{
	char ch;
    CarNode *p; 
    QueueNode *t; 
    struct tm *local;
	long m;
	time(&m);
	local = localtime(&m);
	local->tm_year = local->tm_year + 1900;
	local->tm_mon ++;
    p=(CarNode *)malloc(sizeof(CarNode)); 
    flushall();
	READ();
	if(Enter->top<MAX)/*车场未满，车进车场*/
	{
        fp2=fopen("D:\\test.txt","ab+");
		
    printf("\ninput the number of the car(例:陕A1234):"); 
    gets(p->num); 	fwrite(p,sizeof(p),1,fp2); WRITE();
    fp2=fopen("D:\\test.txt","a+");
	printf("input the size of the car(大|中|小):");
	gets(p->size);	fwrite(p,sizeof(p),1,fp2); WRITE();
    Enter->top++; 
    printf("\n",Enter->top); 
    p->reach.hour=local->tm_hour;
    p->reach.min=local->tm_min; 
    Enter->stack[Enter->top]=p;
	fwrite(p,sizeof(p),1,fp2);
		fclose(fp2);
    return(1); 
     WRITE();
	} 
    else /*车场已满，车进便道*/ 
	{
		printf("车场已满，是否等待（Y|N）:");
		scanf("%c",&ch);
		if(ch='y')
        {
			printf("\n该车须在便道等待!\n");
            t=(QueueNode *)malloc(sizeof(QueueNode)); 
            t->data=p; 
            t->next=NULL; 
            W->rear->next=t; 
            W->rear=t; 
            return(1);
		}
	} 
}

 
void Leave(SeqStackCar *Enter,SeqStackCar *Temp,LinkQueueCar *W) /*车辆离开*/ 
{ 
    int  room; 
    CarNode *p,*t; 
    QueueNode *q; /*判断车场内是否有车*/
    struct tm *local;
	long m;
	time(&m);
	local = localtime(&m);
	local->tm_year = local->tm_year + 1900;
	local->tm_mon ++;
    if(Enter->top>0) /*有车*/ 
	{ 
         while(1) /*输入离开车辆的信息*/ 
		 { 
              printf("\n请输入车在车场的位置/1--%d/：",Enter->top); 
              scanf("%d",&room); 
              if(room>=1&&room<=Enter->top) 
				  break; 
		 } 
         while(Enter->top>room) /*车辆离开*/ 
		 { 
              Temp->top++; 
              Temp->stack[Temp->top]=Enter->stack[Enter->top]; 
              Enter->stack[Enter->top]=NULL; 
              Enter->top--; 
		 } 
         p=Enter->stack[Enter->top]; 
         Enter->stack[Enter->top]=NULL; 
         Enter->top--; 
         while(Temp->top>=1) 
		 { 
              Enter->top++; 
              Enter->stack[Enter->top]=Temp->stack[Temp->top]; 
              Temp->stack[Temp->top]=NULL; 
              Temp->top--; 
		 } 
         PRINT(p,room);/*判断通道上是否有车及车站是否已满*/ 
         if((W->head!=W->rear)&&Enter->top<MAX) /*便道的车辆进入车场*/ 
		 { 
              q=W->head->next; 
              t=q->data; 
              Enter->top++; 
              printf("\n便道的%s号车进入车场第%d位置.",t->num,Enter->top); 
              t->reach.hour=local->tm_hour,t->reach.min=local->tm_min; 
              W->head->next=q->next; 
              if(q==W->rear) 
				  W->rear=W->head; 
              Enter->stack[Enter->top]=t; 
          free(q); 
		 } 
         else printf("\n便道里没有车.\n"); 
	} 
     else printf("\n车场里没有车.\n"); /*没车*/ 
}

 
void List1(SeqStackCar *S) /*列表显示车场信息*/ 
{ 
    int i; 
    if(S->top>0) /*判断车站内是否有车*/ 
	{ 
         printf("\n车场:"); 
         printf("\n 位置 到达时间 车牌号  车型\n"); 
         for(i=1;i<=S->top;i++) 
		 { 
             printf("  %d ",i); 
             printf("   %d:%d ",S->stack[i]->reach.hour,S->stack[i]->reach.min); 
             printf("    %2s  ",S->stack[i]->num); 
			 printf("  %2s ",S->stack[i]->size);
		 } 
	} 
    else printf("\n车场里没有车\n"); 
}

 



void List(SeqStackCar S,CarNode W) 
{ 
    int flag,tag; 
    flag=1; 
    while(flag) 
	{ 
         printf("\n请选择 1|2:"); 
         printf("\n1.车场\n2.返回\n"); 
         while(1) 
		 { 
             scanf("%d",&tag); 
             if(tag>=1||tag<=2) 
				 break; 
             else 
				 printf("\n请选择 1|2:"); 
		 } 
          switch(tag) 
		  { 
               case 1:List1(&S);break; /*列表显示车场信息*/ 
                
               case 2:flag=0;break; 
               default: break; 
		  } 
	} 
}
int check(char *ps)
{
	char password[10]="123456\0";
	int b=0;
	int flag=1;
	for(;*ps!='\0'&&flag;ps++)
	{
		if(*ps!=password[b])
			flag=0;
		else
			b++;
	}
	if(b!=6)
		flag=0;
	return flag;
}

void WRITE()
{   
	int n=0;
	FILE *fp2;
	if((fp2=fopen("D:\\test.txt","w"))==NULL)
	{
		printf("无法创建文件!\n");
		getchar();
		return;  
	} 
	fprintf(fp2,"%d",n);
	fclose(fp2);
} 

void READ()
{
	int n=0;
	if((fp2=fopen("D:\\test.txt","rb"))==NULL)
	{
		printf("无法打开文件!\n\n");
		getchar();
		return;
	}
	fscanf(fp2,"%d",&n);
	fclose(fp2);
}
