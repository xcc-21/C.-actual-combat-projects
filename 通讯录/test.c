#include "contact.h"
//test.c	����ͨѶ¼��ģ��
//contact.h   ���Ͷ��� �� ��������
//contact.c ������ʵ��

//ͨѶ¼
//1.ͨѶ¼���ܹ����1000���˵���Ϣ
//ÿ���˵���Ϣ
//����+����+�Ա�+�绰+��ַ
//2.�����˵���Ϣ
//3.ɾ��ָ���˵���Ϣ
//4.�޸�ָ���˵���Ϣ
//5.����ָ���˵���Ϣ
//6.����ͨѶ¼����Ϣ
//


void menu()
{

	printf("*************************************************\n");
	printf("**********  ������ӭ����ͨѶ¼�˵�����  *********\n");
	printf("**********	0.�˳��˵�		********\n");
	printf("**********      1.�����ϵ����Ϣ        *********\n");
	printf("*********       2.ɾ����ϵ����Ϣ        *********\n");
	printf("*********       3.������ϵ����Ϣ        *********\n");
	printf("*********       4.�޸���ϵ����Ϣ        *********\n");
	printf("*********	5.������ϵ����Ϣ	*********\n");
	printf("*********       6.չʾ��ϵ����Ϣ        *********\n");
	printf("*************************************************\n");
}
//Ϊ����ɶ��ԣ�����ʹ��ö��
enum Option{

	EXIT,		//��Ӧ0
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

	//����ͨѶ¼
	Contact con;//ͨѶ¼
	//��ʼ��ͨѶ¼
	InitContact(&con);
	do{
		menu();
		printf("��ѡ��>");
		scanf("%d",&input);

		switch(input)
		{

			//�����˵���Ϣ
		case ADD:
			//�����˵���Ϣ
			AddContact(&con);
			break;

			//ɾ��
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
			printf("�˳�����\n");
			break;
		default:
			
			printf("ѡ�����,����ѡ��\n");
			break;
		}

	}while(input);//ֻҪinputС��0Ϊ�پ��˳�
	return 0;
}
