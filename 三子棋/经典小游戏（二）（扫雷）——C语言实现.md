@[toc]
# 扫雷游戏效果对比总览
![在这里插入图片描述](https://img-blog.csdnimg.cn/b0960ab4883040c9bafff1f7a31ae7f2.png#pic_center)
![在这里插入图片描述](https://img-blog.csdnimg.cn/b2136e949e5e47d6b75dbd262b356f2e.png#pic_center)

# 实现的操作：

 1. 显示周围的雷数量
 2. 随机布雷
 3. 第一次下子，不炸死
 4. 坐标周围没雷，可以实现展开
 5. 游戏结束后展示给玩家
 

# 玩家须知：

 1. 数字n代表有n个雷
 2. 雷的总数量设置为10

![在这里插入图片描述](https://img-blog.csdnimg.cn/fc1021fd89724800b0b2ecb15bfe1616.png#pic_center)


# 游戏准备

> 我们使用坐标的方式进行排雷，一次坐标查看一个格子，总共有81个格子，分别为9行9列；9行9列？听着好耳熟，对啦，就是我们学过的二维数组；既然是数组，那坐标（0，0）不就是第一行的第一列吗？真聪明！不过这是聪明的程序员使用的方式，而外行认为第一行第一列那就是（1，1）呀；所以，我们在打印棋盘的时候要多打两行；不应该存储[9][9]，因为我们排查雷都以9*9的格式，而如果在四个角落的话，就会受限，会越界；那时就要设置四个角落排查信息为3格子，比较麻烦。
    为防止访问越界，所以我们给他扩充两行两列，一律9*9排查，所以得11*11格式(辅助作用)

## 1.棋盘格式

> 这里解释为什么定义ROWS，COLS，ROW，COL这四个宏。
mine数组中，除了雷是用1表示，其他的元素都是用0表示，计算雷数时，把周围八个元素的值相加，得到的数刚好就是雷数。但是我们对边界上的元素进行排雷时，会出先数组的越界访问，产生意想不到的结果，这当然不是我们想要的。所以，对数组增加两行与两列（假设二维数组是9 * 9的，增加后变为11 * 11），对11 * 11的数组初始化，但我们使用的是9 * 9 的数组，在计算雷数时就不会出现错误了

```c
#define EASY_COUNT 10//雷的总数量
#define ROW 9	//行
#define COL 9	//列

//为使用方便，这里区分格式的使用，本质还是9*9

#define ROWS ROW+2
#define COLS COL+2
char mine[ROWS][COLS]={0};//存放布置好的雷的信息
char show[ROWS][COLS]={0};//存放排查除的雷的信息
```

## 2.初始化棋盘

> 我们打印设计者棋盘要用数组real_mine,打印玩家棋盘要用数组show_mine,两个数组在开始必须要初始化，在设计者棋盘中字符0代表不是雷，字符1代表雷，先初始化两个数组
代码如下
```c

//初始化棋盘
InitBoard(mine,ROWS,COLS,'0');//‘0’
InitBoard(show,ROWS,COLS,'*');//‘*’
```

```c
void InitBoard(char board[ROWS][COLS],int rows,int cols,char set)
{

	int i = 0;
	int j = 0;
	for(i=0;i<rows;i++)
	
	{
		for(j=0;j<cols;j++)
		{
		
			board[i][j]=set;
		}
	}
}
```



## 3.打印棋盘

> 


```c
DisplayBoard(show,ROW,COL);//打印棋盘
```

```c
//打印棋盘
void DisplayBoard(char board[ROWS][COLS],int row,int col )
{
	int i = 0;
	int j = 0;
	printf("-------------扫雷游戏----------------\n");
	//打印列号
	for(i=0;i<=col;i++)
	{
	
		printf("%d ",i);
	}
	printf("\n");
	for(i=1;i<=row;i++)
	{
	
		printf("%d ",i);
		for(j=1;j<=col;j++)
		{
		
			printf("%c ",board[i][j]);
		}
		printf("\n");
	}
	printf("-------------扫雷游戏----------------\n");
}
```


4.随机布置雷（会用rand生成随机）

```c
//布置雷
	SetMine(mine,ROW,COL);
```

```c
void SetMine(char mine[ROWS][COLS],int row,int col)
{

	//布置雷
	int count = 10;
	while(count)
	{
		//生产随机的下标
		
		int x = rand()%row+1;
		int y= rand()%col+1;
		
		if(mine[x][y]=='0')
		{
		
			mine[x][y]='1';
			count--;
		}
	
		
	}
}
```

## 5.排查雷

> 接着就到了玩家进行排雷了，通过玩家输入坐标，程序把对应的数组元素赋值成周围一圈的雷数，要是踩到雷了，提示玩家玩得太菜 游戏结束。但这又有一个细节，我们创建的数组是字符数组，放置的是字符，把字符相加得到的是对应的ASCII码值。所以我们把相加后的值减去八个字符0的ASCII码值，得到的就是雷数了。我写了一个get_mine_num函数来计算雷数。

```c
//排查雷
	FindMine(mine,show,ROW,COL);
```

```c
//排查雷
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col)
{
	//1.输入排查坐标
	//2.检查坐标是不是雷
		//（1）是雷  - 很遗憾炸死了，游戏结束
		// （2）不是雷  - 统计坐标周围有几个雷 - 存储排查雷的信息到show数组，游戏继续

	int x = 0;
	int y = 0;
	int win = 0;
	while(win<row*col-EASY_COUNT)
	{
	
		printf("请输入要排查的坐标：>");
		scanf("%d %d",&x,&y);//x-(1-9),y-(1-9)

		//判断坐标合法性
		if(x>=1&&x<=row&&y>=1&&y<=col)
		{
			if(mine[x][y]=='1')
			{
				printf("很遗憾 ，你被炸死了\n");
				DisplayBoard(mine,row,col);
				break;
			}
			else
			{
			
				//不是雷的话，统计x，y坐标周围有几个雷
				int  count = get_mine_count(mine,x,y);
				show[x][y]=count+'0';
				//显示排查出的信息
				DisplayBoard(show,row,col);
				win++;
			}

		}
		else
			printf("坐标不合法，请重新输入!");

	}
	if(win==row*col-EASY_COUNT)
	{
	
		printf("排雷成功！\n");
		DisplayBoard(show,row,col);
	}
}
```

## 6.统计雷数量
![在这里插入图片描述](https://img-blog.csdnimg.cn/90ef0c327f3645f0adf624967e2f2dab.png#pic_center)


```c
//统计雷
static int get_mine_count(char mine[ROWS][COLS],int x,int y)
{
	return  mine[x-1][y]+
		mine[x-1][y-1]+
		mine[x][y-1]+
		mine[x+1][y-1]+
		mine[x+1][y]+
		mine[x+1][y+1]+
		mine[x][y+1]+
		mine[x-1][y+1]-8*'0';
}
```

>至此所有的代码我们就完成了，接着是所有文件代码的整体展示


# 完整代码

```c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define EASY_COUNT 10//雷的总数量
#define ROW 9	//行
#define COL 9	//列

//为使用方便，这里区分格式的使用，本质还是9*9

#define ROWS ROW+2
#define COLS COL+2

//初始化棋盘
void InitBoard(char board[ROWS][COLS],int rows,int cols,char set);

//打印棋盘
void DisplayBoard(char board[ROWS][COLS],int row,int col );

//布置雷
void SetMine(char mine[ROWS][COLS],int row,int col);

//排查雷
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col);

void menu()
{

	printf("***********************\n");
	printf("******  1.play  ********\n");
	printf("******  0.exit   *******\n");
	printf("***********************\n");
}

void game()
{
	/*不应该存储[9][9]，因为我们排查雷都以9*9的格式，而如果在四个角落的话，
	就会受限，会越界；那时就要设置四个角落排查信息为3格子，比较麻烦。
	为防止访问越界，所以我们给他扩充两行两列，一律9*9排查，所以得11*11格式(辅助作用)*/

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

void InitBoard(char board[ROWS][COLS],int rows,int cols,char set)
{

	int i = 0;
	int j = 0;
	for(i=0;i<rows;i++)
	
	{
		for(j=0;j<cols;j++)
		{
		
			board[i][j]=set;
		}
	}
}

//打印棋盘
void DisplayBoard(char board[ROWS][COLS],int row,int col )
{
	int i = 0;
	int j = 0;
	printf("-------------扫雷游戏----------------\n");
	//打印列号
	for(i=0;i<=col;i++)
	{
	
		printf("%d ",i);
	}
	printf("\n");
	for(i=1;i<=row;i++)
	{
	
		printf("%d ",i);
		for(j=1;j<=col;j++)
		{
		
			printf("%c ",board[i][j]);
		}
		printf("\n");
	}
	printf("-------------扫雷游戏----------------\n");
}

void SetMine(char mine[ROWS][COLS],int row,int col)
{

	//布置雷
	int count = 10;
	while(count)
	{
		//生产随机的下标
		
		int x = rand()%row+1;
		int y= rand()%col+1;
		
		if(mine[x][y]=='0')
		{
		
			mine[x][y]='1';
			count--;
		}
	
		
	}
}
//统计雷
static int get_mine_count(char mine[ROWS][COLS],int x,int y)
{
	return  mine[x-1][y]+
		mine[x-1][y-1]+
		mine[x][y-1]+
		mine[x+1][y-1]+
		mine[x+1][y]+
		mine[x+1][y+1]+
		mine[x][y+1]+
		mine[x-1][y+1]-8*'0';
}

//排查雷
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col)
{
	//1.输入排查坐标
	//2.检查坐标是不是雷
		//（1）是雷  - 很遗憾炸死了，游戏结束
		// （2）不是雷  - 统计坐标周围有几个雷 - 存储排查雷的信息到show数组，游戏继续

	int x = 0;
	int y = 0;
	int win = 0;
	while(win<row*col-EASY_COUNT)
	{
	
		printf("请输入要排查的坐标：>");
		scanf("%d %d",&x,&y);//x-(1-9),y-(1-9)

		//判断坐标合法性
		if(x>=1&&x<=row&&y>=1&&y<=col)
		{
			if(mine[x][y]=='1')
			{
				printf("很遗憾 ，你被炸死了\n");
				DisplayBoard(mine,row,col);
				break;
			}
			else
			{
			
				//不是雷的话，统计x，y坐标周围有几个雷
				int  count = get_mine_count(mine,x,y);
				show[x][y]=count+'0';
				//显示排查出的信息
				DisplayBoard(show,row,col);
				win++;
			}

		}
		else
			printf("坐标不合法，请重新输入!");

	}
	if(win==row*col-EASY_COUNT)
	{
	
		printf("排雷成功！\n");
		DisplayBoard(show,row,col);
	}
}

​
```

