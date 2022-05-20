#include "contact.h"
//test.c	测试通讯录的模块
//contact.h   类型定义 和 函数声明
//contact.c 函数的实现

//通讯录
//1.通讯录中能够存放1000个人的信息
//每个人的信息
//名字+年龄+性别+电话+地址
//2.增加人的信息
//3.删除指定人的信息
//4.修改指定人的信息
//5.查找指定人的信息
//6.排序通讯录的信息
//


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
