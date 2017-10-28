#include<stdio.h>
#include<stdlib.h>
#include"file.h"
#include<student.h>
void printhead()
{
    printf("%8s%10s%8s%6s%8s%6s%6s\n","学号"，"姓名"，"性别"，"数学"，"英语"，"计算机"，"总分"，"名次");
}

void menu()
{
     printf("******** 1.显示基本信息 ********\n");
     printf("******** 2.基本信息管理 ********\n");
	 printf("******** 3.学生成绩管理 ********\n");
	 printf("******** 4.考试成绩统计 ********\n");
	 printf("******** 5.根据条件查询 ********\n");
	 printf("******** 6.推出         ********\n");
}

void menubase()
{
    printf("%%%%%%%% 1.插入学生记录 %%%%%%%%%\n");
	printf("%%%%%%%% 2.删除学生记录 %%%%%%%%%\n");
	printf("%%%%%%%% 3.修改学生记录 %%%%%%%%%\n");
	printf("%%%%%%%% 0.返回上层菜单 %%%%%%%%%\n");
}

void menuscore()
{
    printf("@@@@@@@@ 1.计算学生总分 @@@@@@@@");
	printf("@@@@@@@@ 2.根据总分排名 @@@@@@@@");
	printf("@@@@@@@@ 0.返回上层菜单 @@@@@@@@");
}

void menucount()
{
    printf("&&&&&&&& 1.求课程最高分 &&&&&&&&");
	printf("&&&&&&&& 2.求课程最低分 &&&&&&&&");
	printf("&&&&&&&& 3.求课程平均分	&&&&&&&&");
	printf("&&&&&&&& 0.返回上层菜单 &&&&&&&&");
}

void menusearch()
{
    printf("######## 1.按学号查询   ########");
	printf("######## 2.按姓名查询   ########");
	printf("######## 3.按名次查询   ########");
	printf("######## 0.返回上层菜单 ########");
}

int basemanage(student stu[],int n)
{
    int choice,t,find[NUM];
	student s;
	do
	{
	    menubase();
		printf("choose one operation you want to do:\n");
		scanf("%d",&choice);
		switch(choice)
		{
		   case 1:readstu(&s,1);
		       n=insertstu(stu,n,s);
		       break;
		   case 2:printf("input the number deleted\n");
		       scanf("%ld",&s.num);
			   n=deletestu(stu,n,s);
			   break;
		    case 3:printf("input the number modified\n");
			    scanf("%ld",&s.num);
				t=searchstu(stu,n,s,1,find);
				if(t)
				{
				    readstu(&s,1);
					stu[find[0]]=s;				
				}
				else
				    printf("this student is not ni,can not be modified.\n");
				break;
			case 0:break;		
		}	
	}while(choice);
	return n;
}

void socremanage(student stu[],int n)
{
    int choice;
	do
	{
	    menuscore();
		printf("choose one operation you wnat to do:\n");
		scanf("%d",&choice);
		switch(choice)
		{
		    case 1:calcutotal(stu,n);
			    break;
			case 2:calcurank(stu,n);
			    break;
			case 0:break;		
		}	
	}while(choice);
}

void printmarkcourse(char *s,double m[3][3],int k)
{
    int i;
	printf(s)
	for(i=0;i<3;i++)
	printf("%10.2lf",m[i][k]);
	printf(\n"");
}

void countmanage(student stu[],int n)
{
    int choice;
	double mark[3][3];
	do
	{
	    menucount();
		calcumark(mark,stu,n);
		printf("choose one operation you want to do:\n");
		scanf("%d",&choice);
		switch(choice)
		{
		    case 1:printmarkcourse("三门课的最高分分别是：\n",mark,0);
			    braek;
			case 2:printmarkcourse("三门课的最低分分别是：\n",mark,0);
			    braek;
			case 1:printmarkcourse("三门课的平均分分别是：\n",mark,0);
			    braek;
		    case 0:break;
		}	
	}while(choie);
}

void searchmanage(student stu[],int n)
{
    int i,choice,findnum,f[NUM];
	student s;
	do
	{
	    menusearch();
		printf("choose one operation you want to do:\n");
		scanf("%d",&choice);
		switch(choice)
		{
		    case 1:printf("input a student\'s num will be searched:\n");
			    scanf("%s",&s.num);
				break;
			case 2:printf("input a student\'s name will be searched:\n");
			    scanf("%s",&s.name);
				break;
			case 3:printf("input a rank will be searched:\n");
			    scanf("%s",&s.rank);
				break;
			case 0:break;		
		}
		if(choice>=1&&choice<=3)
		{
		    findnum=searchstu(stu,n,s,choice,f);
			if(findnum)
			{
			    printhead();
				for(i=0;i<findnum;i++)
				    printstu(&stu[f[i]],1)			
			}
			eles
			printf("this record dose not exit!\n");		
		}	
	}while(choice);
}

int runmain(student stu[],int n,int choice)
{
    switch(choice)
	{
	    case 1:printhead();
		     sortstu(stu,n,1);
			 printstu(stu,n);
			 break;
		case 2:n=basemanage(stu,n);
		    break;
		case 3:scoremanage(stu,n);
		    break;
		case 4:countmanage(stu,n);
		    break;
		case 5:searchmanage(stu,n);
		    break;
		case 0:break;	
	}
	return n;
}

int main()
{
    student stu[NUM];
	int choice,n;
	n=readfile;
	if(!n)
	{
	    n=creatfile(stu);
	}
	do
	{
	    menu();
		printf("please input your choice:");
		scanf("%d",&choice);
		if(choice>=0&&choice<=5)
		    n=runmain(stu,n,choice);
		else
		printf("error input,please input your choice again!\n");	
	}while(choice);
	sortstu(stu,n,1);
	savefile(stu,n);
	return 0;
}

































