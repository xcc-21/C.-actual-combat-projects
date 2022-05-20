
@[toc]
# 前言

哈喽，大家好![在这里插入图片描述](https://img-blog.csdnimg.cn/e013f6a931e843c5b68c0c45b99a6508.png)


今天来给大家分享一个通讯录的实现，包含了指针，数组，结构体，文章有点长，完整通讯录代码在文章末尾处，希望大家能耐心看完并且有所收获哦

# 效果预览
![在这里插入图片描述](https://img-blog.csdnimg.cn/a1f9f7d4869e4db4bb72b3ccd644e9af.png)


# 一、通讯录的要求实现功能

> test.c	测试通讯录的模块
> contact.h   类型定义 和 函数声明
> contact.c 函数的实现
>
> 通讯录
> //1.通讯录中能够存放1000个人的信息
> //每个人的信息
> //名字+年龄+性别+电话+地址
> //2.增加人的信息
> //3.删除指定人的信息
> //4.修改指定人的信息
> //5.查找指定人的信息
> //6.排序通讯录的信息

## 1.需要用到的操作

 *提供功能*：
1.增加联系人

2.删除联系人

3.修改联系人

4.查找联系人

5.排序联系人

6.打印联系人

**思路分析**:

首先我们可以分三个模块来解决这个问题，代码的整体风格呢还是和之前写的三子棋与扫雷一样，还是建了3个文件，还是先在contact.c文件里放各个函数的实现，然后在头文件contact.h中放这些函数的声明，这样在test.c文件中就可以直接引用contact.h，用contact.c中的函数啦，这样能保证主函数逻辑清晰，简洁利落，简单易懂。

- 第一个模块我们需要一个头文件（contact.h），这个头文件里可以包含一些相应信息，当实现文件和测试文件包含自己定义的头文件时便可以获得一些相关的信息。所以头文件里应该包括一个结构体，这个结构体里应包含姓名，性别，年龄，电话，住址。同时还可以定义一个结构体，这个结构体里包含通讯录，同时通讯录里人员的计数变量，以及当前容量，将通讯录的地址传到别的地方便可以实现对它遍历或者其他操作。
- 第二个模块便是我们的测试函数(test.c)，测试函数便可以实现我们的菜单打印，同时由我们接收不同的值便可以实现不同的操作，就是相应的方法的实现，这里很明显可以通过一个switch语句来进行控制。
- 第三个模块便是我们的方法实现的函数(contact.c)，将模块2里定义的类型为通讯录的地址传到各个方法里，这样便可以实现对通讯录的操作。

## 2.页面菜单

> 菜单能够实现和用户的交互。
>
> 那么作为一个通讯录怎么能没有菜单选项呢？
>
> 我们第一步先来设计一个菜单选项
>
> 代码如下：

```c
void menu()
{

	//打印通讯录菜单
	//0.退出菜单
	//1.添加联系人信息
	//2.删除指定名字的联系人信息
	//3.修改联系人的信息
	//4.查找好友的信息
	//5.展示通讯录联系人信息
	//6.对通讯录指定信息进行排序

	printf("*************************************************\n");
	printf("**********  	——欢迎来到通讯录菜单——    ********\n");
	printf("**********         0.退出菜单           ********\n");
	printf("**********      1.添加联系人信息        *********\n");
	printf("*********       2.删除联系人信息        *********\n");
	printf("*********       3.查找联系人信息        *********\n");
	printf("*********       4.修改联系人信息        *********\n");
	printf("*********       5.排序联系人信息        *********\n");
    printf("*********       6.打印联系人信息        *********\n");
	printf("*************************************************\n");
}
```



## 3.通讯录的主体框架实现

> 这里主要用的是do-while语句和switch语句来将各个函数串联起来，形成一个较为完整的工程。因为操作的对象是通讯录里面的信息，所以定义了一个通讯录类型的变量con。看这段代码应该不难发现基本上每一个函数的参数都是con。里面的涉及到的每一个函数我都会在下面一一讲解的。

```c
//为程序可读性，我们使用枚举
enum Option{

	EXIT,		//对应0
	ADD,		//1
	DEL,		//2
	SEARCH,
	MODIFY,
	SORT,
	PRINT

};
int main()
{
	int input = 0 ;

	//创建通讯录
	Contact con;//通讯录
	//初始化通讯录
	InitContact(&con);
	do{
		menu();
		printf("请选择>");
		scanf("%d",&input);

		switch(input)
		{

			//增加人的信息
		case ADD:
			//增加人的信息
			AddContact(&con);
			break;

			//删除
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SORT:
            Sort_Name(&con);
			break;
		case PRINT:
			PrintContact(&con);
			break;
		case EXIT:
			printf("退出程序\n");
			break;
		default:
			
			printf("选择错误,重新选择\n");
			break;
		}

	}while(input);//只要input小于0为假就退出
	return 0;
}

```

我们用枚举类型将功能一一列举出来，同时每一个枚举成员也代表着对应的数字，我们在switch ...case 语句中也不用 case 1，case 2来记录每一功能对应的数字了，直接以case ADD，case DEL表示，更加直接了当。

------



## 4.通讯录初始化及个人信息的表示

> 因为通讯录最初是没有联系人的任何信息的，所以我们需要将它的实际有效信息数量置为0，然后申请一个PeoInfo大小的空间来存放信息，最初也是将data也就是联系人的各种信息置为空。再接着就是为设置此通讯录的容量。如果空间申请失败，则打印错误信息，方便后期的检查与维护。
>
> 但是如果不是第一次使用这个程序，则之前记录下来的联系人信息就会在启动该程序时自动加载进来，方便查看和修改。因此我利用文件知识写了一个加载信息的函数LoadContact()（别急
>
> 后面也会讲它的具体实现），在初始化时进行加载。

```c
void InitContact(Contact* pc)
{


	pc->sz=0;
	//pc->data=0;----err
	//memset  内存设置
	memset(pc->data,0,sizeof(pc->data));
	
}
```

------



## 二、功能函数的具体实现

## 1.增加联系人的信息

> AddContact()这个函数是用做增添联系人的，调用这个函数就代表要在通讯录里面增加联系人信息，但是每当增添联系人信息时，都需要对通讯录的容量进行一个判断，如果通讯录满了，我就要给它进行增容，因此在AddContact()函数里面的最开始我调用了自己写的一个函数，其功能是判断通讯录是否曾容，是的话就增容，不是的话就暂时不增容，增容成功和判断为不增容都返回1，增容失败则返回0。判断通讯录的容量充足或增容成功之后才可对通讯录进行联系人的添加。
>
> 其实添加联系人很简单，就是对通讯录结构体里面的联系人类型data进行赋值，每次增添一个联系人之后通讯录pc的实际有效信息人数sz就要加一。

```c
void AddContact(Contact* pc)
{
	if(pc->sz==MAX)
	{
	
		printf("通讯录已满,无法添加");
		return ; 
	}
	//增加一个人的信息
	printf("请输入名字>");
	scanf("%s",pc->data[pc->sz].name);
	printf("请输入年龄>");
	scanf("%d",&(pc->data[pc->sz].age));
	printf("请输入性别>");
	scanf("%s",pc->data[pc->sz].sex);
	printf("请输入电话>");
	scanf("%s",pc->data[pc->sz].tele);
	printf("请输入地址>");
	scanf("%s",pc->data[pc->sz].addr);
	pc->sz++;
	printf("添加成功\n");
}
```

## 2.删除联系人的信息

> 删除联系人其实就是对被删除的联系人进行覆盖，将要删除的联系人后面的联系人信息依次往前移，而删除联系人之前我们需要先找到该联系人对应的数组下标，就需要调用FindPeoInfo()函数，然后再将此元素的下一个元素及后面元素依次向前移进行覆盖。覆盖完成之后，再将通讯录的实际有效信息人数sz减一。

```c
void DelContact(Contact *pc)
{	
	int i;
	int pos;
	char name[MAX_NAME]={0};
	if(pc->sz==0)
	{
		printf("通讯录为空，无需删除\n");
		return ;
	}
	printf("请输入要删除人的名字>");
	scanf("%s",name);

	//1.查找删除的人
	//有 没有
	pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要删除的人不存在\n");
		return ;
	}
	//2.删除
	
	for(i=pos;i<pc->sz-1;i++)
	{
		pc->data[i]=pc->data[i+1];

	}
	pc->sz--;
	printf("删除成功\n");
}
```

------



## 3.查找联系人的信息

> 联系人的信息都存放在联系人类型的数组里，查找联系人其实就相当于对数组的一个遍历，当输入要查找的联系人姓名时，就会对此数组进行遍历。找到就返回数组下标，找不到就返回-1。

```c
void SearchContact(Contact *pc)
{
	char name[MAX_NAME]={0};
	int pos;
	printf("请输入要查找人的名字>");
	scanf("%s",name);
	 pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要查找的人不存在\n");
		return ;
	}
	else
	{
	//打印标题
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n","名字","年龄","性别","电话","地址");
	//打印数据
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",pc->data[pos].name,
													pc->data[pos].age,
													pc->data[pos].sex,
													pc->data[pos].tele,
													pc->data[pos].addr);
	}
}
```

------



## 4.修改联系人的信息

> 修改联系人就是将原来赋值的联系人类型data数组中的元素再次赋值，达到更改的一个效果。同样的，在进行修改之前仍然要先调用FindPeoInfo()来查找要修改的联系人。

```c
void ModifyContact(Contact* pc)
{

	char name[MAX_NAME]={0};
	int pos;
	printf("请输入要修改人的名字>");
	scanf("%s",name);
	 pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要修改的人不存在\n");
		return ;
	}
	else
	{
	printf("请输入名字>");
	scanf("%s",pc->data[pos].name);
	printf("请输入年龄>");
	scanf("%d",&(pc->data[pos].age));
	printf("请输入性别>");
	scanf("%s",pc->data[pos].sex);
	printf("请输入电话>");
	scanf("%s",pc->data[pos].tele);
	printf("请输入地址>");
	scanf("%s",pc->data[pos].addr);
	printf("修改成功\n");
	}
}
static int FindByName(Contact *pc,char name[])//static 让它成为静态函数，不让其它源文件访问
{

	int i = 0;
	for(i=0;i<pc->sz;i++)
	{
		if(strcmp(pc->data[i].name,name)==0)
		{
		
			return i;
		}
		

	}
	return -1;//找不到
}
```

------

## 5.排序联系人的信息

> 这个也很简单，就是调用qsort()函数对结构体类型中的那字符串name进行排序。就不过多赘述啦，直接看代码~

```c
void Sort_Name(Contact *pc)   //以名字排序所有联系人
{
	int i = 0;
	int j = 0;
	int flag = 0;
	printf("以名字进行排序(a-->z)\n");
	while(1)
	{
		flag = 0;
		for (j = 0; j < pc->sz - 1; j++)
		{
			if (strcmp(pc->data[j].name, pc->data[j + 1].name)>0)
			{
				PeoInfo tmp =  pc->data[j];
				pc->data[j] = pc->data[j + 1];
				pc->data[j + 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}
```

------



## 6.展示通讯录联系人信息

> 这个函数的实现就是先判断通讯录的实际有效信息人数是否为0，如果为0的话，说明通讯录里面没有人，如果不为0，则对联系人类型的data数组进行遍历，一一打印。

```c
void  PrintContact(const Contact *pc)
{

	int i= 0;
	//打印标题
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n","名字","年龄","性别","电话","地址");
	//打印数据
	for(i=0;i<pc->sz;i++)
	{
	
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",pc->data[i].name,
													pc->data[i].age,
													pc->data[i].sex,
													pc->data[i].tele,
													pc->data[i].addr);
	}
}
```



# 三、整体代码展示



## 1.test.c 通讯录主体框架测试文件

\

```c
#include "contact.h"
void menu()
{
	//打印通讯录菜单
	//0.退出菜单
	//1.添加联系人信息
	//2.删除指定名字的联系人信息
	//3.修改联系人的信息
	//4.查找好友的信息
	//5.展示通讯录联系人信息
	//6.对通讯录指定信息进行排序

	printf("*************************************************\n");
	printf("**********  	——欢迎来到通讯录菜单——    ********\n");
	printf("**********         0.退出菜单           ********\n");
	printf("**********      1.添加联系人信息        *********\n");
	printf("*********       2.删除联系人信息        *********\n");
	printf("*********       3.查找联系人信息        *********\n");
	printf("*********       4.修改联系人信息        *********\n");
	printf("*********       5.排序联系人信息        *********\n");
    printf("*********       6.打印联系人信息        *********\n");
	printf("*************************************************\n");
}
//将菜单的功能一一列举出来，以枚举的类型呈现
enum Option{

	EXIT,		//对应0
	ADD,		//1
	DEL,		//2
	SEARCH,
	MODIFY,
	SORT,
	PRINT

};
int main()
{
	int input = 0 ;

	//创建通讯录
	Contact con;//通讯录
	//初始化通讯录
	InitContact(&con);
	do{
		menu();
		printf("请选择>");
		scanf("%d",&input);

		switch(input)
		{

			//增加人的信息
		case ADD:
			//增加人的信息
			AddContact(&con);
			break;

			//删除
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SORT:
			Sort_Name(&con);
			break;
		case PRINT:
			PrintContact(&con);
			break;
		case EXIT:
			printf("退出程序\n");
			break;
		default:
			
			printf("选择错误,重新选择\n");
			break;
		}

	}while(input);//只要input小于0为假就退出
	return 0;
}
```

## 2.contact.c 通讯录函数文件

```c
#include"contact.h"

void InitContact(Contact* pc)
{


	pc->sz=0;
	//pc->data=0;----err
	//memset  内存设置
	memset(pc->data,0,sizeof(pc->data));
	
}
void AddContact(Contact* pc)
{
	if(pc->sz==MAX)
	{
	
		printf("通讯录已满,无法添加");
		return ; 
	}
	//增加一个人的信息
	printf("请输入名字>");
	scanf("%s",pc->data[pc->sz].name);
	printf("请输入年龄>");
	scanf("%d",&(pc->data[pc->sz].age));
	printf("请输入性别>");
	scanf("%s",pc->data[pc->sz].sex);
	printf("请输入电话>");
	scanf("%s",pc->data[pc->sz].tele);
	printf("请输入地址>");
	scanf("%s",pc->data[pc->sz].addr);
	pc->sz++;
	printf("添加成功\n");
}
void  PrintContact(const Contact *pc)
{

	int i= 0;
	//打印标题
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n","名字","年龄","性别","电话","地址");
	//打印数据
	for(i=0;i<pc->sz;i++)
	{
	
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",pc->data[i].name,
													pc->data[i].age,
													pc->data[i].sex,
													pc->data[i].tele,
													pc->data[i].addr);
	}
}
static int FindByName(Contact *pc,char name[])
{

	int i = 0;
	for(i=0;i<pc->sz;i++)
	{
		if(strcmp(pc->data[i].name,name)==0)
		{
		
			return i;
		}
		

	}
	return -1;//找不到
}
void DelContact(Contact *pc)
{	
	int i;
	int pos;
	char name[MAX_NAME]={0};
	if(pc->sz==0)
	{
		printf("通讯录为空，无需删除\n");
		return ;
	}
	printf("请输入要删除人的名字>");
	scanf("%s",name);

	//1.查找删除的人
	//有 没有
	pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要删除的人不存在\n");
		return ;
	}
	//2.删除
	
	for(i=pos;i<pc->sz-1;i++)
	{
		pc->data[i]=pc->data[i+1];

	}
	pc->sz--;
	printf("删除成功\n");
}
void SearchContact(Contact *pc)
{
	char name[MAX_NAME]={0};
	int pos;
	printf("请输入要查找人的名字>");
	scanf("%s",name);
	 pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要查找的人不存在\n");
		return ;
	}
	else
	{
	//打印标题
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n","名字","年龄","性别","电话","地址");
	//打印数据
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",pc->data[pos].name,
													pc->data[pos].age,
													pc->data[pos].sex,
													pc->data[pos].tele,
													pc->data[pos].addr);
	}
}
void ModifyContact(Contact* pc)
{

	char name[MAX_NAME]={0};
	int pos;
	printf("请输入要修改人的名字>");
	scanf("%s",name);
	 pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要修改的人不存在\n");
		return ;
	}
	else
	{
	printf("请输入名字>");
	scanf("%s",pc->data[pos].name);
	printf("请输入年龄>");
	scanf("%d",&(pc->data[pos].age));
	printf("请输入性别>");
	scanf("%s",pc->data[pos].sex);
	printf("请输入电话>");
	scanf("%s",pc->data[pos].tele);
	printf("请输入地址>");
	scanf("%s",pc->data[pos].addr);
	printf("修改成功\n");
	}
}
void Sort_Name(Contact *pc)   //以名字排序所有联系人
{
	int i = 0;
	int j = 0;
	int flag = 0;
	printf("以名字进行排序(a-->z)\n");
	while(1)
	{
		flag = 0;
		for (j = 0; j < pc->sz - 1; j++)
		{
			if (strcmp(pc->data[j].name, pc->data[j + 1].name)>0)
			{
				PeoInfo tmp =  pc->data[j];
				pc->data[j] = pc->data[j + 1];
				pc->data[j + 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}
```

## 3.contact.h 宏定义及函数声明文件

```c
#include<stdio.h>
#include<string.h>
//为以后维护 设置预处理命令
#define MAX_NAME 20
#define MAX_SEX 20
#define MAX_TELE 12	//号码为11位，留以为作结束符\0
#define MAX_ADDR 30
#define MAX 1000

//类型的定义
typedef struct PeoInfo
{

	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}PeoInfo;

typedef struct Contact
{

	PeoInfo data[MAX];//存放添加进来人的信息
	int sz;//记录的是当前通讯录中有效信息的个数
}Contact;

//初始化通讯录
void InitContact(Contact* pc);
//添加通讯录
void AddContact(Contact* pc);
//打印联系人信息
void  PrintContact(const Contact *pc);
//删除联系人信息
void DelContact(Contact *pc);
//查找
void SearchContact(Contact *pc);
//修改
void ModifyContact(Contact* pc);
//排序
void Sort_Name(Contact* pc);
```

## 四、一键打包

```c
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#define MAX_NAME 20
#define MAX_SEX 20
#define MAX_TELE 12	
#define MAX_ADDR 30
#define MAX 1000

typedef struct PeoInfo
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}PeoInfo;
typedef struct Contact
{
	PeoInfo data[MAX];
	int sz;
}Contact;
void InitContact(Contact* pc);
//添加通讯录
void AddContact(Contact* pc);
//打印联系人信息
void  PrintContact(const Contact *pc);
//删除联系人信息
void DelContact(Contact *pc);
//查找
void SearchContact(Contact *pc);
//修改
void ModifyContact(Contact* pc);
//排序
void Sort_Name(Contact* pc);

void InitContact(Contact* pc)
{


	pc->sz=0;
	//pc->data=0;----err
	//memset  内存设置
	memset(pc->data,0,sizeof(pc->data));
	
}
void AddContact(Contact* pc)
{
	if(pc->sz==MAX)
	{
	
		printf("通讯录已满,无法添加");
		return ; 
	}
	//增加一个人的信息
	printf("请输入名字>");
	scanf("%s",pc->data[pc->sz].name);
	printf("请输入年龄>");
	scanf("%d",&(pc->data[pc->sz].age));
	printf("请输入性别>");
	scanf("%s",pc->data[pc->sz].sex);
	printf("请输入电话>");
	scanf("%s",pc->data[pc->sz].tele);
	printf("请输入地址>");
	scanf("%s",pc->data[pc->sz].addr);
	pc->sz++;
	printf("添加成功\n");
}
void  PrintContact(const Contact *pc)
{

	int i= 0;
	//打印标题
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n","名字","年龄","性别","电话","地址");
	//打印数据
	for(i=0;i<pc->sz;i++)
	{
	
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",pc->data[i].name,
													pc->data[i].age,
													pc->data[i].sex,
													pc->data[i].tele,
													pc->data[i].addr);
	}
}
static int FindByName(Contact *pc,char name[])
{

	int i = 0;
	for(i=0;i<pc->sz;i++)
	{
		if(strcmp(pc->data[i].name,name)==0)
		{
		
			return i;
		}
		

	}
	return -1;//找不到
}
void DelContact(Contact *pc)
{	
	int i;
	int pos;
	char name[MAX_NAME]={0};
	if(pc->sz==0)
	{
		printf("通讯录为空，无需删除\n");
		return ;
	}
	printf("请输入要删除人的名字>");
	scanf("%s",name);

	//1.查找删除的人
	//有 没有
	pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要删除的人不存在\n");
		return ;
	}
	//2.删除
	
	for(i=pos;i<pc->sz-1;i++)
	{
		pc->data[i]=pc->data[i+1];

	}
	pc->sz--;
	printf("删除成功\n");
}
void SearchContact(Contact *pc)
{
	char name[MAX_NAME]={0};
	int pos;
	printf("请输入要查找人的名字>");
	scanf("%s",name);
	 pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要查找的人不存在\n");
		return ;
	}
	else
	{
	//打印标题
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n","名字","年龄","性别","电话","地址");
	//打印数据
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",pc->data[pos].name,
													pc->data[pos].age,
													pc->data[pos].sex,
													pc->data[pos].tele,
													pc->data[pos].addr);
	}
}
void ModifyContact(Contact* pc)
{

	char name[MAX_NAME]={0};
	int pos;
	printf("请输入要修改人的名字>");
	scanf("%s",name);
	 pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("要修改的人不存在\n");
		return ;
	}
	else
	{
	printf("请输入名字>");
	scanf("%s",pc->data[pos].name);
	printf("请输入年龄>");
	scanf("%d",&(pc->data[pos].age));
	printf("请输入性别>");
	scanf("%s",pc->data[pos].sex);
	printf("请输入电话>");
	scanf("%s",pc->data[pos].tele);
	printf("请输入地址>");
	scanf("%s",pc->data[pos].addr);
	printf("修改成功\n");
	}
}
void Sort_Name(Contact *pc)   //以名字排序所有联系人
{
	int i = 0;
	int j = 0;
	int flag = 0;
	printf("以名字进行排序(a-->z)\n");
	while(1)
	{
		flag = 0;
		for (j = 0; j < pc->sz - 1; j++)
		{
			if (strcmp(pc->data[j].name, pc->data[j + 1].name)>0)
			{
				PeoInfo tmp =  pc->data[j];
				pc->data[j] = pc->data[j + 1];
				pc->data[j + 1] = tmp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}
void menu()
{

	printf("*************************************************\n");
	printf("**********  ——欢迎来到通讯录菜单——  *********\n");
	printf("**********	0.退出菜单		********\n");
	printf("**********      1.添加联系人信息        *********\n");
	printf("*********       2.删除联系人信息        *********\n");
	printf("*********       3.查找联系人信息        *********\n");
	printf("*********       4.修改联系人信息        *********\n");
	printf("*********	5.排序联系人信息	*********\n");
	printf("*********       6.展示联系人信息        *********\n");
	printf("*************************************************\n");
}
//为程序可读性，我们使用枚举
enum Option{

	EXIT,		//对应0
	ADD,		//1
	DEL,		//2
	SEARCH,
	MODIFY,
	SORT,
	PRINT

};
int main()
{
	int input = 0 ;

	//创建通讯录
	Contact con;//通讯录
	//初始化通讯录
	InitContact(&con);
	do{
		menu();
		printf("请选择>");
		scanf("%d",&input);

		switch(input)
		{

			//增加人的信息
		case ADD:
			//增加人的信息
			AddContact(&con);
			break;

			//删除
		case DEL:
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SORT:
			Sort_Name(&con);
			break;
		case PRINT:
			PrintContact(&con);
			break;
		case EXIT:
			printf("退出程序\n");
			break;
		default:
			
			printf("选择错误,重新选择\n");
			break;
		}

	}while(input);//只要input小于0为假就退出
	return 0;
}

```

# 小结

  

>由于我们写的通讯录是有一定空间的，我们定义的通讯录空间是一定的，所以仍然存在限制和缺点。还可使用动态内存分配，清空通讯录信息，保存通讯录文件等。

分享就到这里啦，怎么样，是不是很简单呢，有疑问或者看不懂的同学可以问我哦，如果发现哪里写的有问题或者可以改进的也可以提出来，评论区或私聊都可以，我是很希望收到大家的建议的哟



