#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define EASY_COUNT 10
#define ROW 9
#define COL 9

//Ϊʹ�÷��㣬�������ָ�ʽ��ʹ�ã����ʻ���9*9

#define ROWS ROW+2
#define COLS COL+2

//��ʼ������
void InitBoard(char board[ROWS][COLS],int rows,int cols,char set);

//��ӡ����
void DisplayBoard(char board[ROWS][COLS],int row,int col );

//������
void SetMine(char mine[ROWS][COLS],int row,int col);

//�Ų���
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col);