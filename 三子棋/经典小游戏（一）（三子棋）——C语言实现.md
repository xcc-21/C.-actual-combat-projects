@[toc]
# 预览
## 实现的效果图VS现实图
​​![在这里插入图片描述](https://img-blog.csdnimg.cn/c98edb6472d0463cb11534517f708fb3.png#pic_center)![在这里插入图片描述](https://img-blog.csdnimg.cn/76f3f423c4704adb8e164aa379465f94.png#pic_center)​​
# 设计原理
**1.打印菜单**

```c
void menu();
```


**2设置棋盘格式**

```c
char board[ROW][COL]={0};
```

**3.初始化棋盘**

```c
InitBoard(board,ROW,COL);
```
**4.打印棋盘**

```c
DisplayBoard(board,ROW,COL);
```
**5.下棋**

 1. 玩家下棋

```c
	PlayerMove(board,ROW,COL);
```

 2. 电脑下棋
 


```c
	ComputerMove(board,ROW,COL);
```
**6.判断输赢**

```c
ret=IsWin(board,ROW,COL);
```

#  函数声明

> 作用：声明函数

```c
#define ROW 3    //行
#define COL 3    //列

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//声明
void InitBoard(char board[ROW][COL],int row,int col);
void DisplayBoard(char board[ROW][COL],int row,int col);
void PlayerMove(char board[ROW][COL],int row,int col);
void ComputerMove(char board[ROW][COL],int row,int col);


//告诉我们四种状态
//玩家赢  '*'
//电脑赢  '#'
//平局  'Q'
//继续  'C'
char IsWin(char board[ROW][COL],int row,int col);
```

## main()主函数代码

> 作用：调用test函数

```c
int main()
{
	test();

	return 0;
}
```

## test()函数代码块

> 作用：检查菜单栏是否进行下一步操作![在这里插入图片描述](https://img-blog.csdnimg.cn/b5ac03ae0b4d491899a6988bf55b2812.png#pic_center)


```c
void test()
{
	int input = 0;
     
    //循环游戏的开始与结束，至少执行一次
	do
	{
	
		menu();//调用menu函数,打印菜单栏信息
        game();
		printf("请选择：>");
		scanf("%d",&input);

        //根据用户所输入的数字触发下面的开关		
		switch(input)
		{
		
		case 1:
			printf("三子棋\n");//这里先测试是否会执行成功
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default :
			printf("选择错误，请重新选择!\n");
			break;
		}
	}
	while(input);//直到输入的结果为假，循环才会结束
}
```

## mine()实现菜单函数代码块

```c
void menu()
{

	printf("******************************\n");
	printf("*****  1.paly     0.exit  ****\n");
	printf("******************************\n");

}
```

 展示效果：

![在这里插入图片描述](https://img-blog.csdnimg.cn/b5ac03ae0b4d491899a6988bf55b2812.png#pic_center)


## game()函数代码块

```c
void game()
{

	char ret = 0;
	//数组-存放走出的棋盘信息
	char board[ROW][COL]={0};
	//初始化棋盘
	InitBoard(board,ROW,COL);
	//打印棋盘
	DisplayBoard(board,ROW,COL);
	//下棋
	while(1)
	{
	
		//玩家下棋
		PlayerMove(board,ROW,COL);
		DisplayBoard(board,ROW,COL);
		//判断玩家是否赢
		ret=IsWin(board,ROW,COL);
		if(ret!='C')
		{
		
			break;
		}
		//电脑下棋
		ComputerMove(board,ROW,COL);
		DisplayBoard(board,ROW,COL);
		//判断电脑是否赢
		ret=IsWin(board,ROW,COL);
		if(ret!='C')
		{
		
			break;
		}
	}
		if(ret=='*')
		{
		
			printf("玩家赢\n");
		}
		else if(ret=='#')
		{
		
			printf("电脑赢\n");
		}
		else
			printf("平局\n");

}
```

# 游戏具体实现函数

```c
#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void InitBoard(char board[ROW][COL],int row,int col)
{
	int i = 0;
	int j = 0;
	for(i=0; i<row;i++)
	{
	
		for(j=0; j<col; j++)
			board[i][j]=' ';
	}

}
//void DisplayBoard(char board[ROW][COL],int row,int col)
//{
//
//	int i = 0;
//	for(i=0; i<row; i++)
//	{
//	
//		//1.打印一行的数据
//		printf(" %c | %c | %c \n",board[i][0],board[i][1],board[i][2]);
//		//2.打印分割行
//		if(i<row-1)
//		printf("---|---|---\n");
//	}
//}

//优化后：
void DisplayBoard(char board[ROW][COL],int row,int col)
{

	int i = 0;
	for(i=0; i<row; i++)
	{
		//1.打印一行的数据
		int j = 0;
		for(j = 0;j<col;j++)
		{
		
			printf(" %c ",board[i][j]);
			if(j < col - 1)//最后的列内容不打印|
				printf("|");
		}
		printf("\n");
		//2.打印分割行//最后的行不打印---|---|----
		if(i < row - 1)
		{
			for(j=0;j<col;j++) 
			{
				printf("---");
				if(j<col-1)
				printf("|");
			}
			printf("\n");
		}

	}
}
void PlayerMove(char board[ROW][COL],int row,int col)
{
	int x = 0;
	int y = 0;
	printf("玩家走：>\n");
	while(1)
	{
		printf("请输入要下的坐标:>");
		scanf("%d%d",&x,&y);
		//判断x,y坐标的合法性
		if(x>=1 && x<=row && y>=1 && y<=col)
		{
	
			if(board[x-1][y-1]==' ')
			{
		
				board[x-1][y-1]='*';
				break;
			}
			else
			{
		
				printf("该坐标被占用\n");
			}

		}
		else
		printf("坐标非法，请重新输!\n");
	}
}
void ComputerMove(char board[ROW][COL],int row,int col)
{
	int x = 0;
	int y = 0;
	printf("电脑走:>\n");
	

	while(1)
	{
	
		x = rand()%row;
		y = rand()%col;
		if(board[x][y]==' ')
		{
	
		board[x][y]='#';
		break;
		}
	}

}
//返回1，表示棋盘满了
//返回，表示棋盘没满
int IsFull(char board[ROW][COL],int row,int col)
{

	int i = 0;
	int j = 0;
	for(i = 0;i<row;i++)
	{
	
		for(j=0;j<col;j++)
		{
		
			if(board[i][j]==' ')
			{
			
				return 0;//没满
			}
		}
	}
	return 1;//满了
}
char IsWin(char board[ROW][COL],int row,int col)
{
	int i = 0;
	//横三列
	for(i=0;i<row;i++)
	{
	
		if(board[i][0]==board[i][1]&&board[i][1]==board[i][2]&&board[i][1]!=' ')
			return board[i][1];
	}
	//竖三列
	for(i=0;i<col;i++)
	{
	
		if(board[0][i]==board[1][i]&&board[1][i]==board[2][i]&&board[1][i]!=' ')
			return board[1][i];
	}
	//两个对角线
	if(board[0][0]==board[1][1]&&board[1][1]==board[2][2]&&board[1][1]!=' ')
		return board[1][1];
	if(board[2][0]==board[1][1]&&board[1][1]==board[0][2]&&board[1][1]!=' ')
		return board[1][1];
	//判断是否平局
	if(1==IsFull(board,ROW,COL))
	{
	
		return 'Q';
	}
	return 'C';
}
```

# 完整源代码

```cpp
#include<stdio.h>
#include"game.h"
#define ROW 3
#define COL 3
#include<stdlib.h>
#include<time.h>
//声明
void InitBoard(char board[ROW][COL],int row,int col);
void DisplayBoard(char board[ROW][COL],int row,int col);
void PlayerMove(char board[ROW][COL],int row,int col);
void ComputerMove(char board[ROW][COL],int row,int col);


//告诉我们四种状态
//玩家赢  '*'
//电脑赢  '#'
//平局  'Q'
//继续  'C'
char IsWin(char board[ROW][COL],int row,int col);

void menu()
{

	printf("******************************\n");
	printf("*****  1.paly     0.exit  ****\n");
	printf("******************************\n");

}
void game()
{

	char ret = 0;
	//数组-存放走出的棋盘信息
	char board[ROW][COL]={0};
	//初始化棋盘
	InitBoard(board,ROW,COL);
	//打印棋盘
	DisplayBoard(board,ROW,COL);
	//下棋
	while(1)
	{
	
		//玩家下棋
		PlayerMove(board,ROW,COL);
		DisplayBoard(board,ROW,COL);
		//判断玩家是否赢
		ret=IsWin(board,ROW,COL);
		if(ret!='C')
		{
		
			break;
		}
		//电脑下棋
		ComputerMove(board,ROW,COL);
		DisplayBoard(board,ROW,COL);
		//判断电脑是否赢
		ret=IsWin(board,ROW,COL);
		if(ret!='C')
		{
		
			break;
		}
	}
		if(ret=='*')
		{
		
			printf("玩家赢\n");
		}
		else if(ret=='#')
		{
		
			printf("电脑赢\n");
		}
		else
			printf("平局\n");

}


void test()
{
	int input = 0;
	//srand((unsigned int)time(NULL));
	do
	{
	
		menu();
		printf("请选择：>");
		scanf("%d",&input);
		
		switch(input)
		{
		
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default :
			printf("选择错误，请重新选择!\n");
			break;
		}
	}
	while(input);
}
int main()
{
	test();

	return 0;
}

#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void InitBoard(char board[ROW][COL],int row,int col)
{
	int i = 0;
	int j = 0;
	for(i=0; i<row;i++)
	{
	
		for(j=0; j<col; j++)
			board[i][j]=' ';
	}

}
//void DisplayBoard(char board[ROW][COL],int row,int col)
//{
//
//	int i = 0;
//	for(i=0; i<row; i++)
//	{
//	
//		//1.打印一行的数据
//		printf(" %c | %c | %c \n",board[i][0],board[i][1],board[i][2]);
//		//2.打印分割行
//		if(i<row-1)
//		printf("---|---|---\n");
//	}
//}

//优化后：
void DisplayBoard(char board[ROW][COL],int row,int col)
{

	int i = 0;
	for(i=0; i<row; i++)
	{
		//1.打印一行的数据
		int j = 0;
		for(j = 0;j<col;j++)
		{
		
			printf(" %c ",board[i][j]);
			if(j < col - 1)//最后的列内容不打印|
				printf("|");
		}
		printf("\n");
		//2.打印分割行//最后的行不打印---|---|----
		if(i < row - 1)
		{
			for(j=0;j<col;j++) 
			{
				printf("---");
				if(j<col-1)
				printf("|");
			}
			printf("\n");
		}

	}
}
void PlayerMove(char board[ROW][COL],int row,int col)
{
	int x = 0;
	int y = 0;
	printf("玩家走：>\n");
	while(1)
	{
		printf("请输入要下的坐标:>");
		scanf("%d%d",&x,&y);
		//判断x,y坐标的合法性
		if(x>=1 && x<=row && y>=1 && y<=col)
		{
	
			if(board[x-1][y-1]==' ')
			{
		
				board[x-1][y-1]='*';
				break;
			}
			else
			{
		
				printf("该坐标被占用\n");
			}

		}
		else
		printf("坐标非法，请重新输!\n");
	}
}
void ComputerMove(char board[ROW][COL],int row,int col)
{
	int x = 0;
	int y = 0;
	printf("电脑走:>\n");
	

	while(1)
	{
	
		x = rand()%row;
		y = rand()%col;
		if(board[x][y]==' ')
		{
	
		board[x][y]='#';
		break;
		}
	}

}
//返回1，表示棋盘满了
//返回，表示棋盘没满
int IsFull(char board[ROW][COL],int row,int col)
{

	int i = 0;
	int j = 0;
	for(i = 0;i<row;i++)
	{
	
		for(j=0;j<col;j++)
		{
		
			if(board[i][j]==' ')
			{
			
				return 0;//没满
			}
		}
	}
	return 1;//满了
}
char IsWin(char board[ROW][COL],int row,int col)
{
	int i = 0;
	//横三列
	for(i=0;i<row;i++)
	{
	
		if(board[i][0]==board[i][1]&&board[i][1]==board[i][2]&&board[i][1]!=' ')
			return board[i][1];
	}
	//竖三列
	for(i=0;i<col;i++)
	{
	
		if(board[0][i]==board[1][i]&&board[1][i]==board[2][i]&&board[1][i]!=' ')
			return board[1][i];
	}
	//两个对角线
	if(board[0][0]==board[1][1]&&board[1][1]==board[2][2]&&board[1][1]!=' ')
		return board[1][1];
	if(board[2][0]==board[1][1]&&board[1][1]==board[0][2]&&board[1][1]!=' ')
		return board[1][1];
	//判断是否平局
	if(1==IsFull(board,ROW,COL))
	{
	
		return 'Q';
	}
	return 'C';
}

​
```


