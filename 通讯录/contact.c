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