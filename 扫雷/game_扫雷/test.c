
#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void menu()
{

	printf("***********************\n");
	printf("******  1.play  ********\n");
	printf("******  0.exit   *******\n");
	printf("***********************\n");
}

void game()
{
	//��Ӧ�ô洢[9][9]����Ϊ�����Ų��׶���9*9�ĸ�ʽ����������ĸ�����Ļ���
	//�ͻ����ޣ���Խ�磻��ʱ��Ҫ�����ĸ������Ų���ϢΪ3���ӣ��Ƚ��鷳��
	//Ϊ��ֹ����Խ�磬�������Ǹ��������������У�һ��9*9�Ų飬���Ե�11*11��ʽ(��������)

	char mine[ROWS][COLS]={0};//��Ų��úõ��׵���Ϣ
	char show[ROWS][COLS]={0};//����Ų�����׵���Ϣ
	//��ʼ������
	InitBoard(mine,ROWS,COLS,'0');//��0��
	InitBoard(show,ROWS,COLS,'*');//��*��

	//��ӡ����
	
	DisplayBoard(show,ROW,COL);

	//������
	SetMine(mine,ROW,COL);
	//DisplayBoard(mine,ROW,COL);

	//�Ų���
	FindMine(mine,show,ROW,COL);

}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));

	do
	{
	menu();
	printf("��ѡ��>");
	scanf("%d",&input);
	switch(input)
	{
	
	case 1:
		game();//ɨ����Ϸ

		break;
	case 0:
		printf("�˳���Ϸ\n");
		break;
	default :
		printf("ѡ�����,����ѡ��! \n");
		break;
	}

	}while(input);

	return 0;
}