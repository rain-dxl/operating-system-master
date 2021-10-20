#include<stdio.h>
#include <iostream>
using namespace std;
#define N 5		//��ҵ������

int time=0;		//���ڼ�¼ʱ�����ţ���������ʱ����С��λΪ1
float ATAroundTime; //ƽ����תʱ��
float AWTrunTime;	//ƽ����Ȩ��תʱ��

//��ҵ�ṹ��
typedef struct Process
{
	int ATime;		//����ʱ��arrive
	int DTime;		//ִ��ʱ��do
	int BTime;		//��ʼִ��ʱ��begin
	int OTime;		//ִ�н���ʱ��over
	int TAroundTime; //��תʱ��
	float WTrunTime;	//��Ȩ��תʱ��
	int flag;			//��־��ҵ�Ƿ�ִ���ˣ�0��δִ�У�1�Ѿ�ִ��
	float hrrn;			//��ҵ����Ӧ��
}Process;

//��ҵ��֪��Ϣ��ֵ
int Input(Process *P)
{
	int i;
	for(i=0;i<N;i++)
	{
		printf("����%d��ҵ�ĵ���ʱ��(0-100����):",i+1);
		scanf("%d",&P[i].ATime);

		printf("����%d��ҵ��ִ��ʱ��(0-100����):",i+1);
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
	int i,flag=0;		//flagĬ�ϵ�ǰû����ҵδִ��
	int then=first;
	//printf("\nִ����һ��then_do\n");
	for(i=0;i<N;i++)	//��������Ȩ
	{
		if(P[i].ATime<=time && P[i].flag==0)
		{
			//printf("\n������һ������Ȩ\n");
			P[i].hrrn = (time-P[i].ATime)*1.0/P[i].DTime+1;
			//printf("\n%f\n",P[i].hrrn);
			then=i;
		}
	}
	for(i=0;i<N;i++)	//�ҵ�����Ȩ�����ҵ
	{
		if(P[i].hrrn>P[then].hrrn && P[i].flag==0)
		{
			then=i;
		}
	}
	for(i=0;i<N;i++)	//�жϵ�ǰ�Ƿ�����ҵδִ��
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
		time += P[then].DTime;		//ʱ�����ŵ���һ����ҵִ��֮��
		P[then].OTime=time;		//��һ����ҵִ�����
		P[then].flag=1;			//��־����ҵ��ִ��	
		//printf("\nִ����%d��ҵ\n",then+1);
		//printf("\n����ҵ����ȨΪ%f\n",P[then].hrrn);
		then_do(P, then);
	}

}

//���ҵ�һ��ִ�е���ҵ��Ϊ����ִ�����̵�
void first_do(Process *P)
{
	int i,first=0;
	for(i=0;i<N;i++)
	{
		if(P[i].ATime < P[first].ATime)
			first = i;
	}
	//printf("\n��һ��ִ�е���%d��ҵ\n",first+1);
	
	P[first].BTime = time;
	time += P[first].DTime;		//ʱ�����ŵ���һ����ҵִ��֮��
	//printf("\nʱ������%d\n",time);
	P[first].OTime=time;	//��һ����ҵִ�����
	P[first].flag=1;		//��־����ҵ��ִ��

	then_do(P, first);
}



//������תʱ�䣬��Ȩ��תʱ�䣬ƽ����תʱ�䣬ƽ����Ȩ��תʱ�� ����֪��ʼִ��ʱ�䡢����ִ��ʱ�䣩
int TurnAround(Process *P)
{
	int i;
	float sum_T=0,sum_W=0;
	for(i=0;i<N;i++)
	{
		P[i].TAroundTime = P[i].OTime-P[i].ATime;
		sum_T+=P[i].TAroundTime;
		//printf("\n\n��%d����ҵ����תʱ����%d\n",i+1,P[i].TAroundTime);
		P[i].WTrunTime = P[i].TAroundTime*1.0/P[i].DTime;
		sum_W+=P[i].WTrunTime;
		//printf("��%d����ҵ�Ĵ�Ȩ��תʱ����%.2f\n\n",i+1,P[i].WTrunTime);
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
	cout << "��ҵ\t" << "����ʱ��\t" << "����ʱ��\t" << "��ʼʱ��\t" << "���ʱ��\t" << "��תʱ��\t" << "��Ȩ��תʱ��" << endl;
	for(i=0;i<N;i++)
		cout << i+1<<"\t" << P[i].ATime <<"\t\t"<< P[i].DTime<<"\t\t" << P[i].BTime <<"\t\t"<<P[i].OTime<<"\t\t"<<P[i].TAroundTime<<"\t\t"<<P[i].WTrunTime<<endl;
}

void main(void)
{
	//int i;
	Process P[N];

	Input(P);//��ҵ��Ϣ��ֵ

	//for(i=0;i<N;i++)
	//{
	//	printf("%d\n",P[i].ATime);
	//	printf("%d\n",P[i].DTime);  //�����Ƿ�ɹ���ֵ
	//}

	hrrn_initial(P); //���ó�ʼ����Ȩֵ
	first_do(P);
	TurnAround(P);
	OutPut(P);
}