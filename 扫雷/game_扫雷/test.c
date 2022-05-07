
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
	//不应该存储[9][9]，因为我们排查雷都以9*9的格式，而如果在四个角落的话，
	//就会受限，会越界；那时就要设置四个角落排查信息为3格子，比较麻烦。
	//为防止访问越界，所以我们给他扩充两行两列，一律9*9排查，所以得11*11格式(辅助作用)

	char mine[ROWS][COLS]={0};//存放布置好的雷的信息
	char show[ROWS][COLS]={0};//存放排查除的雷的信息
	//初始化棋盘
	InitBoard(mine,ROWS,COLS,'0');//‘0’
	InitBoard(show,ROWS,COLS,'*');//‘*’

	//打印棋盘
	
	DisplayBoard(show,ROW,COL);

	//布置雷
	SetMine(mine,ROW,COL);
	//DisplayBoard(mine,ROW,COL);

	//排查雷
	FindMine(mine,show,ROW,COL);

}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));

	do
	{
	menu();
	printf("请选择：>");
	scanf("%d",&input);
	switch(input)
	{
	
	case 1:
		game();//扫雷游戏

		break;
	case 0:
		printf("退出游戏\n");
		break;
	default :
		printf("选择错误,重新选择! \n");
		break;
	}

	}while(input);

	return 0;
}