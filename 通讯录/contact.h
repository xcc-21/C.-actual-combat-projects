#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
//Ϊ�Ժ�ά�� ����Ԥ��������
#define MAX_NAME 20
#define MAX_SEX 20
#define MAX_TELE 12	//����Ϊ11λ������Ϊ��������\0
#define MAX_ADDR 30
#define MAX 1000

//���͵Ķ���
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

	PeoInfo data[MAX];//�����ӽ����˵���Ϣ
	int sz;//��¼���ǵ�ǰͨѶ¼����Ч��Ϣ�ĸ���
}Contact;

//��ʼ��ͨѶ¼
void InitContact(Contact* pc);
//���ͨѶ¼
void AddContact(Contact* pc);
//��ӡ��ϵ����Ϣ
void  PrintContact(const Contact *pc);
//ɾ����ϵ����Ϣ
void DelContact(Contact *pc);
//����
void SearchContact(Contact *pc);
//�޸�
void ModifyContact(Contact* pc);
//����
void Sort_Name(Contact* pc);