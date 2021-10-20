#include<stdio.h>
#include <iostream>
using namespace std;
#define N 5		//作业的数量

int time=0;		//用于记录时间流逝，本代码中时间最小单位为1
float ATAroundTime; //平均周转时间
float AWTrunTime;	//平均带权周转时间

//作业结构体
typedef struct Process
{
	int ATime;		//到达时刻arrive
	int DTime;		//执行时间do
	int BTime;		//开始执行时刻begin
	int OTime;		//执行结束时刻over
	int TAroundTime; //周转时间
	float WTrunTime;	//带权周转时间
	int flag;			//标志作业是否执行了，0还未执行，1已经执行
	float hrrn;			//作业的响应比
}Process;

//作业已知信息赋值
int Input(Process *P)
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("输入%d作业的到达时间(0-100整数):",i+1);
		scanf("%d",&P[i].ATime);

		printf("输入%d作业的执行时间(0-100整数):",i+1);
		scanf("%d",&P[i].DTime);
		P[i].flag=0;
	}

	return 1;
}

int hrrn_initial(Process *P)
{
	int i;
	for(i=0;i<N;i++)
	{
		P[i].hrrn = 0;
	}
	return 1;
}

void then_do(Process *P, int first)
{
	int i,flag=0;		//flag默认当前没有作业未执行
	int then=first;
	//printf("\n执行了一次then_do\n");
	for(i=0;i<N;i++)	//计算优先权
	{
		if(P[i].ATime<=time && P[i].flag==0)
		{
			//printf("\n计算了一次优先权\n");
			P[i].hrrn = (time-P[i].ATime)*1.0/P[i].DTime+1;
			//printf("\n%f\n",P[i].hrrn);
			then=i;
		}
	}
	for(i=0;i<N;i++)	//找到优先权最高作业
	{
		if(P[i].hrrn>P[then].hrrn && P[i].flag==0)
		{
			then=i;
		}
	}
	for(i=0;i<N;i++)	//判断当前是否还有作业未执行
	{
		if(P[i].flag == 0)
			flag=1;
	}
	if(then==first)
	{
		if(flag==1)
		{
			time += 1;
			then_do(P, then);
		}

	}

	else
	{
		P[then].BTime = time;
		time += P[then].DTime;		//时间流逝到第一个作业执行之后
		P[then].OTime=time;		//第一个作业执行完毕
		P[then].flag=1;			//标志该作业已执行	
		//printf("\n执行了%d作业\n",then+1);
		//printf("\n该作业优先权为%f\n",P[then].hrrn);
		then_do(P, then);
	}

}

//查找第一个执行的作业，为后续执行做铺垫
void first_do(Process *P)
{
	int i,first=0;
	for(i=0;i<N;i++)
	{
		if(P[i].ATime < P[first].ATime)
			first = i;
	}
	//printf("\n第一个执行的是%d作业\n",first+1);
	
	P[first].BTime = time;
	time += P[first].DTime;		//时间流逝到第一个作业执行之后
	//printf("\n时间流逝%d\n",time);
	P[first].OTime=time;	//第一个作业执行完毕
	P[first].flag=1;		//标志该作业已执行

	then_do(P, first);
}



//计算周转时间，带权周转时间，平均周转时间，平均带权周转时间 （已知开始执行时间、结束执行时间）
int TurnAround(Process *P)
{
	int i;
	float sum_T=0,sum_W=0;
	for(i=0;i<N;i++)
	{
		P[i].TAroundTime = P[i].OTime-P[i].ATime;
		sum_T+=P[i].TAroundTime;
		//printf("\n\n第%d个作业的周转时间是%d\n",i+1,P[i].TAroundTime);
		P[i].WTrunTime = P[i].TAroundTime*1.0/P[i].DTime;
		sum_W+=P[i].WTrunTime;
		//printf("第%d个作业的带权周转时间是%.2f\n\n",i+1,P[i].WTrunTime);
	}

	ATAroundTime = sum_T/N;	//平均周转时间
	AWTrunTime = sum_W/N;	//平均带权周转时间
	printf("\n平均周转时间为%.2f\n",ATAroundTime);
	printf("\n平均带权周转时间为%.2f\n",AWTrunTime);
	return 1;
}

void OutPut(Process *P)
{
	int i=0;
	cout << "作业\t" << "到达时间\t" << "运行时间\t" << "开始时间\t" << "完成时间\t" << "周转时间\t" << "带权周转时间" << endl;
	for(i=0;i<N;i++)
		cout << i+1<<"\t" << P[i].ATime <<"\t\t"<< P[i].DTime<<"\t\t" << P[i].BTime <<"\t\t"<<P[i].OTime<<"\t\t"<<P[i].TAroundTime<<"\t\t"<<P[i].WTrunTime<<endl;
}

void main(void)
{
	//int i;
	Process P[N];

	Input(P);//作业信息赋值

	//for(i=0;i<N;i++)
	//{
	//	printf("%d\n",P[i].ATime);
	//	printf("%d\n",P[i].DTime);  //测试是否成功赋值
	//}

	hrrn_initial(P); //设置初始优先权值
	first_do(P);
	TurnAround(P);
	OutPut(P);
}