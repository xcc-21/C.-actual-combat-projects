#include"contact.h"

void InitContact(Contact* pc)
{


	pc->sz=0;
	//pc->data=0;----err
	//memset  �ڴ�����
	memset(pc->data,0,sizeof(pc->data));
	
}
void AddContact(Contact* pc)
{
	if(pc->sz==MAX)
	{
	
		printf("ͨѶ¼����,�޷����");
		return ; 
	}
	//����һ���˵���Ϣ
	printf("����������>");
	scanf("%s",pc->data[pc->sz].name);
	printf("����������>");
	scanf("%d",&(pc->data[pc->sz].age));
	printf("�������Ա�>");
	scanf("%s",pc->data[pc->sz].sex);
	printf("������绰>");
	scanf("%s",pc->data[pc->sz].tele);
	printf("�������ַ>");
	scanf("%s",pc->data[pc->sz].addr);
	pc->sz++;
	printf("��ӳɹ�\n");
}
void  PrintContact(const Contact *pc)
{

	int i= 0;
	//��ӡ����
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n","����","����","�Ա�","�绰","��ַ");
	//��ӡ����
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
	return -1;//�Ҳ���
}
void DelContact(Contact *pc)
{	
	int i;
	int pos;
	char name[MAX_NAME]={0};
	if(pc->sz==0)
	{
		printf("ͨѶ¼Ϊ�գ�����ɾ��\n");
		return ;
	}
	printf("������Ҫɾ���˵�����>");
	scanf("%s",name);

	//1.����ɾ������
	//�� û��
	pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("Ҫɾ�����˲�����\n");
		return ;
	}
	//2.ɾ��
	
	for(i=pos;i<pc->sz-1;i++)
	{
		pc->data[i]=pc->data[i+1];

	}
	pc->sz--;
	printf("ɾ���ɹ�\n");
}
void SearchContact(Contact *pc)
{
	char name[MAX_NAME]={0};
	int pos;
	printf("������Ҫ�����˵�����>");
	scanf("%s",name);
	 pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("Ҫ���ҵ��˲�����\n");
		return ;
	}
	else
	{
	//��ӡ����
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n","����","����","�Ա�","�绰","��ַ");
	//��ӡ����
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
	printf("������Ҫ�޸��˵�����>");
	scanf("%s",name);
	 pos=FindByName(pc, name);
	if(pos==-1)
	{
	
		printf("Ҫ�޸ĵ��˲�����\n");
		return ;
	}
	else
	{
	printf("����������>");
	scanf("%s",pc->data[pos].name);
	printf("����������>");
	scanf("%d",&(pc->data[pos].age));
	printf("�������Ա�>");
	scanf("%s",pc->data[pos].sex);
	printf("������绰>");
	scanf("%s",pc->data[pos].tele);
	printf("�������ַ>");
	scanf("%s",pc->data[pos].addr);
	printf("�޸ĳɹ�\n");
	}
}
void Sort_Name(Contact *pc)   //����������������ϵ��
{
	int i = 0;
	int j = 0;
	int flag = 0;
	printf("�����ֽ�������(a-->z)\n");
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