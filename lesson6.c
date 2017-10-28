#include<stdio.h> 
#include<stdlib.h> 
#include<string.h>
#include<time.h> 

#define MAX 2/*��������*/ 
#define price 0.05 /*ÿ��ÿ���ӷ���*/ 
typedef struct time{ 
          int hour; 
          int min; 
}Time; /*ʱ����*/ 
typedef struct node{ 
          char num[10];
		  char size[10];
          Time reach; 
          Time leave; 
}CarNode; /*������Ϣ���*/ 
typedef struct NODE{ 
          CarNode *stack[MAX+1]; 
          int top; 
}SeqStackCar; /*ģ�⳵վ*/ 
typedef struct car{ 
          CarNode *data; 
          struct car *next; 
}QueueNode; 
typedef struct Node{ 
          QueueNode *head; 
          QueueNode *rear; 
}LinkQueueCar; /*ģ��ͨ��*/
 

void InitStack(SeqStackCar *); /*��ʼ��ջ*/ 
int InitQueue(LinkQueueCar *); /*��ʼ�����*/ 
int Arrival(SeqStackCar *,LinkQueueCar *); /*��������*/ 
void Leave(SeqStackCar *,SeqStackCar *,LinkQueueCar *); /*�����뿪*/ 
void List(SeqStackCar,LinkQueueCar); /*��ʾ�泵��Ϣ*/
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
	printf("����������¼������#�ż����������4�κ󽫹رգ���");
    while((str[b]=getchar())!='#')
	{
		b++;
	}
	str[b]='\0';
        
	if(check(str))
		printf("��֤ͨ����\n");
	else
	{
		printf("��֤����\n");
	for(a=3;a>0;a--)
	{   
		b=0;
		getchar();

		printf("�����������е�¼������#�ż�������ʣ��%d�λ��ᣩ��",a);
		while((str[b]=getchar())!='#')
	{
		b++;
	}
	str[b]='\0';
    if(check(str))
	{
		printf("��֤ͨ����\n"); 
		break;
	}
	else
	{
		printf("��֤����\n");
	}
	}
	}
      if(!check(str))
           exit(0);

    system("cls");
    InitStack(&Enter); /*��ʼ����վ*/ 
    InitStack(&Temp); /*��ʼ����·����ʱջ*/ 
    InitQueue(&Wait); /*��ʼ��ͨ��*/ 
    
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
				  printf("\nplease choose�� 1|2|3|4."); 
		 } 
          switch(ch) 
		  { 
               case 1:Arrival(&Enter,&Wait);break; /*��������*/ 
               case 2:Leave(&Enter,&Temp,&Wait);break; /*�����뿪*/ 
               case 3:List(Enter,Wait);break; /*�б��ӡ��Ϣ*/ 
               case 4:exit(0); /*�˳�������*/ 
               default: break; 
		  } 
	} 
} 

 
void InitStack(SeqStackCar *s) /*��ʼ��ջ*/ 
{ 
    int i; 
    s->top=0; 
    for(i=0;i<=MAX;i++) 
        s->stack[s->top]=NULL; 
}

 
int InitQueue(LinkQueueCar *Q) /*��ʼ�����*/ 
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

 
void PRINT(CarNode *p,int room) /*��ӡ��վ������Ϣ*/ 
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
    printf("\nthe fee: %2.1fԪ",((B1-A1)*60+(B2-A2))*price); 
free(p); 
}

 
int Arrival(SeqStackCar *Enter,LinkQueueCar *W) /*��������*/ 
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
	if(Enter->top<MAX)/*����δ������������*/
	{
        fp2=fopen("D:\\test.txt","ab+");
		
    printf("\ninput the number of the car(��:��A1234):"); 
    gets(p->num); 	fwrite(p,sizeof(p),1,fp2); WRITE();
    fp2=fopen("D:\\test.txt","a+");
	printf("input the size of the car(��|��|С):");
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
    else /*�����������������*/ 
	{
		printf("�����������Ƿ�ȴ���Y|N��:");
		scanf("%c",&ch);
		if(ch='y')
        {
			printf("\n�ó����ڱ���ȴ�!\n");
            t=(QueueNode *)malloc(sizeof(QueueNode)); 
            t->data=p; 
            t->next=NULL; 
            W->rear->next=t; 
            W->rear=t; 
            return(1);
		}
	} 
}

 
void Leave(SeqStackCar *Enter,SeqStackCar *Temp,LinkQueueCar *W) /*�����뿪*/ 
{ 
    int  room; 
    CarNode *p,*t; 
    QueueNode *q; /*�жϳ������Ƿ��г�*/
    struct tm *local;
	long m;
	time(&m);
	local = localtime(&m);
	local->tm_year = local->tm_year + 1900;
	local->tm_mon ++;
    if(Enter->top>0) /*�г�*/ 
	{ 
         while(1) /*�����뿪��������Ϣ*/ 
		 { 
              printf("\n�����복�ڳ�����λ��/1--%d/��",Enter->top); 
              scanf("%d",&room); 
              if(room>=1&&room<=Enter->top) 
				  break; 
		 } 
         while(Enter->top>room) /*�����뿪*/ 
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
         PRINT(p,room);/*�ж�ͨ�����Ƿ��г�����վ�Ƿ�����*/ 
         if((W->head!=W->rear)&&Enter->top<MAX) /*����ĳ������복��*/ 
		 { 
              q=W->head->next; 
              t=q->data; 
              Enter->top++; 
              printf("\n�����%s�ų����복����%dλ��.",t->num,Enter->top); 
              t->reach.hour=local->tm_hour,t->reach.min=local->tm_min; 
              W->head->next=q->next; 
              if(q==W->rear) 
				  W->rear=W->head; 
              Enter->stack[Enter->top]=t; 
          free(q); 
		 } 
         else printf("\n�����û�г�.\n"); 
	} 
     else printf("\n������û�г�.\n"); /*û��*/ 
}

 
void List1(SeqStackCar *S) /*�б���ʾ������Ϣ*/ 
{ 
    int i; 
    if(S->top>0) /*�жϳ�վ���Ƿ��г�*/ 
	{ 
         printf("\n����:"); 
         printf("\n λ�� ����ʱ�� ���ƺ�  ����\n"); 
         for(i=1;i<=S->top;i++) 
		 { 
             printf("  %d ",i); 
             printf("   %d:%d ",S->stack[i]->reach.hour,S->stack[i]->reach.min); 
             printf("    %2s  ",S->stack[i]->num); 
			 printf("  %2s ",S->stack[i]->size);
		 } 
	} 
    else printf("\n������û�г�\n"); 
}

 



void List(SeqStackCar S,CarNode W) 
{ 
    int flag,tag; 
    flag=1; 
    while(flag) 
	{ 
         printf("\n��ѡ�� 1|2:"); 
         printf("\n1.����\n2.����\n"); 
         while(1) 
		 { 
             scanf("%d",&tag); 
             if(tag>=1||tag<=2) 
				 break; 
             else 
				 printf("\n��ѡ�� 1|2:"); 
		 } 
          switch(tag) 
		  { 
               case 1:List1(&S);break; /*�б���ʾ������Ϣ*/ 
                
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
		printf("�޷������ļ�!\n");
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
		printf("�޷����ļ�!\n\n");
		getchar();
		return;
	}
	fscanf(fp2,"%d",&n);
	fclose(fp2);
}
