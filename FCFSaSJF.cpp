#include<stdio.h>
#include <iostream>
using namespace std;
#define N 5		//进程的数量

float ATAroundTime; //平均周转时间
float AWTrunTime;	//平均带权周转时间

//进程结构体
typedef struct Process
{
	int ATime;		//到达时刻arrive
	int DTime;		//执行时间do
	int BTime;		//开始执行时刻begin
	int OTime;		//执行结束时刻over
	int TAroundTime; //周转时间
	float WTrunTime;	//带权周转时间
	int flag;			//标志进程是否执行了，0还未执行，1已经执行，用在SJF中
}Process;

//进程已知信息赋值
int Input(Process &P)
{
	printf("输入这个进程的到达时间(0-100整数):");
	scanf("%d",&P.ATime);

	printf("输入这个进程的执行时间(0-100整数):");
	scanf("%d",&P.DTime);

	return 1;
}


//进程执行顺序排序SJF
int BSort_SJF(Process *P, int *num)
{
	int m,i,j;
	int time=0;
	
	for(i=0;i<N;i++)	
		P[i].flag = 0;		//所有进程都未执行

	m=0;		//默认最先执行进程是1号，P[0]
	for(i=0;i<N-1;i++)		//找到所有进程中最先到达的进程
	{
		if(P[i].ATime>P[i+1].ATime)
			m=i+1;
		if(P[i].ATime==P[i].ATime)
		{
			if(P[i].DTime>P[i].DTime)
				m=i+1;
		}
	}
	//printf("\n最先执行%d!\n",m+1);
	P[m].flag = 1;
	num[0]=m;		//找到了第一个执行的进程
	time += P[m].DTime;		//时间流逝到第一个进程执行结束
	//printf("\n时间流逝到%d\n",time);


	for(i=0;i<N-1;i++)		//在剩下进程中做选择
	{
		for(j=0;j<N;j++)		//找到一个已经到达了且还未执行的进程做m初值
		{
			if(P[j].ATime<time && P[j].flag==0)		
			{
				m=j;
			}
			break;
		}

		for(j=0;j<N;j++)
		{

			if(P[j].ATime<=time && P[j].flag==0 && P[j].DTime<P[m].DTime)		//找到已经 到达了 且 还未执行 且 执行时间更短 的进程
			{
				//printf("\n发现一个更合适进程\n");
				m=j;
			}
		}
		num[i+1]=m;		//加入排好的顺序中
		//printf("\n将%d进程加入顺序\n",m+1);
		P[m].flag=1;	//执行该进程
		time += P[m].DTime;	//时间流逝到该进程执行完毕之后
		//printf("\n时间流逝到%d\n",time);
	}

	//printf("\n执行顺序为：");
	//for(i=0;i<N;i++)
	//	printf("%d ",num[i]+1);

	return 1;
}
//进程执行顺序排序FCFS
int BSort_FCFS(Process *P, int *num)
{
	int m,i,j;
	for(i=0;i<N;i++)
		num[i]=i;		//初始执行顺序
	for(i=0;i<N-1;i++)
		for(j=0;j<N-1-i;j++)
			if(P[j].ATime>P[j+1].ATime)
			{
				m=num[j];
				num[j]=num[j+1];
				num[j+1]=m;
			}

	//printf("\n进程执行顺序为：");
	//for(i=0;i<N;i++)
	//	printf("%d ",num[i]+1);

	return 1;
}

//进程信息计算,开始执行和结束执行的时间
int BeginOver(Process *P, int *num)
{
	int i,time=0;
	for(i=0;i<N;i++)
	{
		if(time>=P[num[i]].ATime)		//如果进程到达时间比预测执行时间time早，代码在规定时间time执行
		{
			P[num[i]].BTime=time;
			//printf("\n%d时刻第%d个进程开始执行！",time,num[i]+1);
		}
		else							//否则进程刚来就直接执行,处理机空闲等待进程到来
		{
			P[num[i]].BTime=P[num[i]].ATime;
			time=P[num[i]].ATime;
			//printf("\n%d时刻第%d个进程开始执行！",time,num[i]+1);

		}
		time=time+P[num[i]].DTime;		//时间流逝到进程执行完毕
		P[num[i]].OTime=time;
		//printf(",%d时刻第%d个进程执行完毕！\n",time,num[i]+1);
	}
	return 1;
}

//计算周转时间，带权周转时间，平均周转时间，平均带权周转时间
int TurnAround(Process *P)
{
	int i;
	float sum_T=0,sum_W=0;
	for(i=0;i<N;i++)
	{
		P[i].TAroundTime = P[i].OTime-P[i].ATime;
		sum_T+=P[i].TAroundTime;
		//printf("\n\n第%d个进程的周转时间是%d\n",i+1,P[i].TAroundTime);
		P[i].WTrunTime = P[i].TAroundTime*1.0/P[i].DTime;
		sum_W+=P[i].WTrunTime;
		//printf("第%d个进程的带权周转时间是%.2f\n\n",i+1,P[i].WTrunTime);
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
	cout << "进程\t" << "到达时间\t" << "运行时间\t" << "开始时间\t" << "完成时间\t" << "周转时间\t" << "带权周转时间" << endl;
	for(i=0;i<N;i++)
		cout << i+1<<"\t" << P[i].ATime <<"\t\t"<< P[i].DTime<<"\t\t" << P[i].BTime <<"\t\t"<<P[i].OTime<<"\t\t"<<P[i].TAroundTime<<"\t\t"<<P[i].WTrunTime<<endl;
}

void main(void)
{
	int i;
	int num_F[N];		//记录FCFS进程执行顺序
	int num_S[N];		//记录SJF进程执行顺序
	Process P_F[N];
	Process P_S[N];

	//进程信息赋值
	for(i=0;i<N;i++)
	{
		printf("\n--以下输入第%d个进程信息--\n",i+1);
		Input(P_F[i]);
		P_S[i].ATime=P_F[i].ATime;
		P_S[i].DTime=P_F[i].DTime;
	}

	//printf("%d",P[0].ATime);
	//printf("%d",P[0].DTime);  //测试是否成功赋值

	//FCFS
	BSort_FCFS(P_F,num_F);		//根据FCFS执行顺序排序
	BeginOver(P_F,num_F);			//计算进程开始结束时间
	TurnAround(P_F);				//计算周转时间，带权周转时间，平均周转时间，平均带权周转时间
	OutPut(P_F);					//输出

	//SJF
	BSort_SJF(P_S,num_S);			//根据SJF执行顺序排序
	BeginOver(P_S,num_S);			//计算进程开始结束时间
	TurnAround(P_S);				//计算周期时间，带权周期时间，平均周转时间，平均带权周转时间
	OutPut(P_S);					//输出
}