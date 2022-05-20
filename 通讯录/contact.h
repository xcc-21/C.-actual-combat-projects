#define _CRT_SECURE_NO_WARNINGS 1
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