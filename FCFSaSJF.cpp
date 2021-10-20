#include<stdio.h>
#include <iostream>
using namespace std;
#define N 5		//���̵�����

float ATAroundTime; //ƽ����תʱ��
float AWTrunTime;	//ƽ����Ȩ��תʱ��

//���̽ṹ��
typedef struct Process
{
	int ATime;		//����ʱ��arrive
	int DTime;		//ִ��ʱ��do
	int BTime;		//��ʼִ��ʱ��begin
	int OTime;		//ִ�н���ʱ��over
	int TAroundTime; //��תʱ��
	float WTrunTime;	//��Ȩ��תʱ��
	int flag;			//��־�����Ƿ�ִ���ˣ�0��δִ�У�1�Ѿ�ִ�У�����SJF��
}Process;

//������֪��Ϣ��ֵ
int Input(Process &P)
{
	printf("����������̵ĵ���ʱ��(0-100����):");
	scanf("%d",&P.ATime);

	printf("����������̵�ִ��ʱ��(0-100����):");
	scanf("%d",&P.DTime);

	return 1;
}


//����ִ��˳������SJF
int BSort_SJF(Process *P, int *num)
{
	int m,i,j;
	int time=0;
	
	for(i=0;i<N;i++)	
		P[i].flag = 0;		//���н��̶�δִ��

	m=0;		//Ĭ������ִ�н�����1�ţ�P[0]
	for(i=0;i<N-1;i++)		//�ҵ����н��������ȵ���Ľ���
	{
		if(P[i].ATime>P[i+1].ATime)
			m=i+1;
		if(P[i].ATime==P[i].ATime)
		{
			if(P[i].DTime>P[i].DTime)
				m=i+1;
		}
	}
	//printf("\n����ִ��%d!\n",m+1);
	P[m].flag = 1;
	num[0]=m;		//�ҵ��˵�һ��ִ�еĽ���
	time += P[m].DTime;		//ʱ�����ŵ���һ������ִ�н���
	//printf("\nʱ�����ŵ�%d\n",time);


	for(i=0;i<N-1;i++)		//��ʣ�½�������ѡ��
	{
		for(j=0;j<N;j++)		//�ҵ�һ���Ѿ��������һ�δִ�еĽ�����m��ֵ
		{
			if(P[j].ATime<time && P[j].flag==0)		
			{
				m=j;
			}
			break;
		}

		for(j=0;j<N;j++)
		{

			if(P[j].ATime<=time && P[j].flag==0 && P[j].DTime<P[m].DTime)		//�ҵ��Ѿ� ������ �� ��δִ�� �� ִ��ʱ����� �Ľ���
			{
				//printf("\n����һ�������ʽ���\n");
				m=j;
			}
		}
		num[i+1]=m;		//�����źõ�˳����
		//printf("\n��%d���̼���˳��\n",m+1);
		P[m].flag=1;	//ִ�иý���
		time += P[m].DTime;	//ʱ�����ŵ��ý���ִ�����֮��
		//printf("\nʱ�����ŵ�%d\n",time);
	}

	//printf("\nִ��˳��Ϊ��");
	//for(i=0;i<N;i++)
	//	printf("%d ",num[i]+1);

	return 1;
}
//����ִ��˳������FCFS
int BSort_FCFS(Process *P, int *num)
{
	int m,i,j;
	for(i=0;i<N;i++)
		num[i]=i;		//��ʼִ��˳��
	for(i=0;i<N-1;i++)
		for(j=0;j<N-1-i;j++)
			if(P[j].ATime>P[j+1].ATime)
			{
				m=num[j];
				num[j]=num[j+1];
				num[j+1]=m;
			}

	//printf("\n����ִ��˳��Ϊ��");
	//for(i=0;i<N;i++)
	//	printf("%d ",num[i]+1);

	return 1;
}

//������Ϣ����,��ʼִ�кͽ���ִ�е�ʱ��
int BeginOver(Process *P, int *num)
{
	int i,time=0;
	for(i=0;i<N;i++)
	{
		if(time>=P[num[i]].ATime)		//������̵���ʱ���Ԥ��ִ��ʱ��time�磬�����ڹ涨ʱ��timeִ��
		{
			P[num[i]].BTime=time;
			//printf("\n%dʱ�̵�%d�����̿�ʼִ�У�",time,num[i]+1);
		}
		else							//������̸�����ֱ��ִ��,��������еȴ����̵���
		{
			P[num[i]].BTime=P[num[i]].ATime;
			time=P[num[i]].ATime;
			//printf("\n%dʱ�̵�%d�����̿�ʼִ�У�",time,num[i]+1);

		}
		time=time+P[num[i]].DTime;		//ʱ�����ŵ�����ִ�����
		P[num[i]].OTime=time;
		//printf(",%dʱ�̵�%d������ִ����ϣ�\n",time,num[i]+1);
	}
	return 1;
}

//������תʱ�䣬��Ȩ��תʱ�䣬ƽ����תʱ�䣬ƽ����Ȩ��תʱ��
int TurnAround(Process *P)
{
	int i;
	float sum_T=0,sum_W=0;
	for(i=0;i<N;i++)
	{
		P[i].TAroundTime = P[i].OTime-P[i].ATime;
		sum_T+=P[i].TAroundTime;
		//printf("\n\n��%d�����̵���תʱ����%d\n",i+1,P[i].TAroundTime);
		P[i].WTrunTime = P[i].TAroundTime*1.0/P[i].DTime;
		sum_W+=P[i].WTrunTime;
		//printf("��%d�����̵Ĵ�Ȩ��תʱ����%.2f\n\n",i+1,P[i].WTrunTime);
	}

	ATAroundTime = sum_T/N;	//ƽ����תʱ��
	AWTrunTime = sum_W/N;	//ƽ����Ȩ��תʱ��
	printf("\nƽ����תʱ��Ϊ%.2f\n",ATAroundTime);
	printf("\nƽ����Ȩ��תʱ��Ϊ%.2f\n",AWTrunTime);
	return 1;
}

void OutPut(Process *P)
{
	int i=0;
	cout << "����\t" << "����ʱ��\t" << "����ʱ��\t" << "��ʼʱ��\t" << "���ʱ��\t" << "��תʱ��\t" << "��Ȩ��תʱ��" << endl;
	for(i=0;i<N;i++)
		cout << i+1<<"\t" << P[i].ATime <<"\t\t"<< P[i].DTime<<"\t\t" << P[i].BTime <<"\t\t"<<P[i].OTime<<"\t\t"<<P[i].TAroundTime<<"\t\t"<<P[i].WTrunTime<<endl;
}

void main(void)
{
	int i;
	int num_F[N];		//��¼FCFS����ִ��˳��
	int num_S[N];		//��¼SJF����ִ��˳��
	Process P_F[N];
	Process P_S[N];

	//������Ϣ��ֵ
	for(i=0;i<N;i++)
	{
		printf("\n--���������%d��������Ϣ--\n",i+1);
		Input(P_F[i]);
		P_S[i].ATime=P_F[i].ATime;
		P_S[i].DTime=P_F[i].DTime;
	}

	//printf("%d",P[0].ATime);
	//printf("%d",P[0].DTime);  //�����Ƿ�ɹ���ֵ

	//FCFS
	BSort_FCFS(P_F,num_F);		//����FCFSִ��˳������
	BeginOver(P_F,num_F);			//������̿�ʼ����ʱ��
	TurnAround(P_F);				//������תʱ�䣬��Ȩ��תʱ�䣬ƽ����תʱ�䣬ƽ����Ȩ��תʱ��
	OutPut(P_F);					//���

	//SJF
	BSort_SJF(P_S,num_S);			//����SJFִ��˳������
	BeginOver(P_S,num_S);			//������̿�ʼ����ʱ��
	TurnAround(P_S);				//��������ʱ�䣬��Ȩ����ʱ�䣬ƽ����תʱ�䣬ƽ����Ȩ��תʱ��
	OutPut(P_S);					//���
}