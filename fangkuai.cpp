#include "ͷ�ļ�.h"
#define  W  100  
#define  H  30

void move();
void start(); 
void show_me();
void creat_food();
int main();
int head_x;
int head_y;
int old_x;
int old_y;
int snake[W][H] = { 0 };
int c;
unsigned int cnt=0;
int der;
int L = 5;
int Speed = 300;
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);              //����ϵͳAPI�ӿں��������ڸ���������ɫ
	return 0;
}
void gotoxy(int x, int y)                                                     //���õ���ϵͳAPI�ӿں������������ù������
{
	COORD pos;
	pos.X = x;  															  //������
	pos.Y = y;  															  //������
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void  fangkuai()
{
	system("cls");
	start();

	while (1)
	{	
		show_me();
		move();
		if (_kbhit())
			c = _getch();
		{
			if (der!=2 && c == 'a') 
				{
				der = 1;
				}
			else if (der !=1 && c == 'd')
				{
				der = 2;
				}
			else if (der != 4 && c == 'w')
				{
				der = 3;
				}
			else if (der != 3 && c == 's')
				{
				der = 4;
				}			
		}	
	
	}	
}

void start()
{
	for (int x = 0; x <= 100;x+=2)
	{	

		snake[x][0] = -1;
		snake[x][30]= -1;
	}
	for (int y = 0; y <= 30;y++)
	{
	
		snake[0][y]  = -1;
		snake[100][y]= -1;
	}
	for (int x = 2; x < 100; x += 2)
	{
		for (int y = 1; y < 30; y++)
		{
			snake[x][y] = 0;
		}
	}
	for (int x = 0; x <= 100; x += 2)
	{
		for (int y = 0; y <= 30; y++)
		{
			if (snake[x][y] == -1)
			{
				color(6);
				gotoxy(x, y);
				printf("��");
			}

		}
	}


	snake[W / 2][H / 2] = 1;

	for (int i = 1; i <= L; i++)
	{
		snake[W / 2 - 2 * i][H / 2] = i+1;
	}

	der = 2;
	creat_food();

	
}

void move()
{
	int x;
	int y;

	for (x = 2; x < 100; x += 2)                           //�߽粻�ܲ������
	{
		for (y = 1; y < 30; y++)
		{
			if (snake[x][y] > 0)
			{
				snake[x][y]++;
			}
		}
	}

	for (x = 2; x < 100; x += 2)
	{
		for (y = 1; y < 30; y++)
		{
			if (snake[x][y] == 2)
			{
				old_x = x;
				old_y = y;
			}
		}
	}

	if (der == 1)
	{
		head_x = old_x - 2;
		head_y = old_y;	
	}
	if (der == 2)
	{
		head_x = old_x + 2;
		head_y = old_y;	
	}
	if (der == 3)
	{
		head_x = old_x;
		head_y = old_y - 1;	
	}
	if (der == 4)
	{
		head_x = old_x;
		head_y = old_y + 1;
	}

	if (snake[head_x][head_y] == -2)
	{
		
		creat_food();
		L++;
		cnt++;
		Speed -= 5;
		
	}
	
	if(snake[head_x][head_y]>0||snake[head_x][head_y] == -1)
	{
		gotoxy(50, 15);
		printf("ʧ��");
		Sleep(3000);
		system("cls");
		main();
	}
	else 
		snake[head_x][head_y] = 1;
}

void show_me()
{	
	for (int x = 0; x <= 100; x += 2)
	{
		for (int y = 0; y <= 30; y++)
		{
			 if (snake[x][y] > 1)
				{
				color(10);                       //����  ��ɫ
				gotoxy(x, y);
				printf("��");
				}
			 if (snake[x][y] == 1)
				{
				color(12);                        //��ͷ ��ɫ
				gotoxy(x, y);
				printf("��");
				}
			 if (snake[x][y] > L+1)
				{
				 snake[x][y] = 0;
				 gotoxy(x, y);
				 printf(" ");
				}
			 if (snake[x][y] == -2)               //ʳ��
			 {
				 color(10);
				 gotoxy(x, y);
				 printf("��");
			 }

		}	
	}
	fflush(stdout);
	printf("�÷֣�%hu", cnt+1);
	printf("\n");
	Sleep(Speed);
}

void creat_food()
{
	int food_x, food_y;
	srand((unsigned)time(NULL));
	food_x = rand() % 48 * 2+2;
	food_y = rand() % 29+1;
	snake[food_x][food_y] = -2;
}