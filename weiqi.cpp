#include"ͷ�ļ�.h"     
#define C 1500																		   //���ڳ���   
#define D  800                                                                         //���ڸ߶�
#define A 760                                                                          //���̳ߴ�
#define B 40                                                                           //ÿ��ߴ磬�������ص�λ
#define R 8                                                                            //��λ��İ뾶
#define RQ 18                                                                          //���Ӱ뾶

FILE *fp;
int i = 1;                                                                      //0�ǰ������У�1�Ǻ������У����ݲ�������2��������
int hei1[200];                                                                        //��������   
int hei2[200]; 
int bk = 0;
int bai1[200];                                                                         //��������
int bai2[200];
int wt = 0;
int weizhi[21][21] = {0};                                                              //��ʼλ�ö�û�����ӣ���¼Ϊ0 
int x, y;                                                                              //�ݺ�ʮ��·
int a, b;
int da_jie[2][2];		 															   //���ڼ�¼����λ�ã�ÿ�θ�λ
int count_wt;                                                                          //��ʽ�жϰ����
int count_bk;
static int B_dead=0;																   //��������������ÿ�ι�1
static int W_dead=0;																   //��������������ÿ�ι�1

int ch;                                                                                //��¼����
int T = 25;                                                                             //////////////////////////
TCHAR bai[100];
TCHAR hong[100];                                                                        //�洢�����ַ�����ʾ���Ӳ���
//IMAGE img_go_b, img_go_bk;
IMAGE img;
void huitu();																	       //���ƽ���
void shubiao();                                                                        //��궯������
int  main();
void luozi();                                                                          //��������
void jinshou();
int  jia_yan_b();  
int  jia_yan_w();                                                                      //���
void pass();
void huaxian();                                                                        //�㷨�۲�
void Eat_more_than_one_w();                                                            //���Ӵ��ڵ���2��(sizi>=1)����ִ�д˺���
void Eat_more_than_one_b();
void SHA_bk();
void SHA_wt();
void shuaxin_w();                                                                      //Ҫ�Ӷ���������ˢ�£����������Լ����Լ�����
void shuaxin_b();
void chizhi_w();
void chizhi_b();
void no_breath();                                                                       //������λ��
int  creat_data();
void xing_shi_panduan();
void xiaqi_wt();
void xiaqi_bk();
int Q=0;

/********���庯��********���庯��*****************************************************************************************************************************************/

void weiqi()                                                                            //���������򿪽���
{
    int j=1;
	int p=3;                                                                           //���Ӵ�ӡ��λ������Ϊ�˶�������
	mciSendString(_T("open ./music/BGM.mp3 alias bkmusic"), NULL, 0, NULL);              //�򿪱�������
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);                             //ѭ������
	initgraph(C, D, SHOWCONSOLE);                                                        //����SHOWCONSOLE���Ա�������̨
	HWND hwnd = GetHWnd();                                                               //���ô��ڱ������� 
	SetWindowText(hwnd,_T( "Χ��GO"));
	huitu();                                                                             //��ʼ����ͼ���������巽���ں������
	BeginBatchDraw();                                                                    //Easy-x��ͼ�⺯������ͼ��ʼ
	while (1)                                                                            //ѭ�����嶯��
	{
		//���Գ��������λ��ʵ���Զ����ӹ��ܣ����������������ʽ����a/b��ֵ   
		//Ҫʵ�������ս���ܣ�Ӧ��Ҳ�������λ�����֣�ͨ��socket
		//�Լ�����������������

		shubiao();                                                                     //ִ����궯������,�ᵽ��궯�������ڲ���¼��
		if (Q == 2)            //�����°���
			{
			Sleep(1000);
		    xiaqi_wt();     //���Ҫ�����������������������Ӧ���ڴ˺������ȥ������ѵ�������׿���������ֵ�ж���ѡ�㣬����Է���һ������������������Լ���������λ��ִ�м���//
			}
		if (Q == 1)            //�л�Ϊ�����º���
			{
			Sleep(1000);
			xiaqi_bk();    
			}

		if (i % 2 == 0)                                                                      // ����������ֵ�����ǰ������������   
		{
			chizhi_w();
			Eat_more_than_one_w();
			shuaxin_w();                                                                //����ˢ�£�������궯��ǰ��
			SHA_wt();
			chizhi_b();
			SHA_bk();
		}
		if (i % 2 == 1)                                                                  //��������֮����Ժ�������  
		{
			chizhi_b();
			Eat_more_than_one_b();
			shuaxin_b();
			SHA_bk();
			chizhi_w();
			SHA_wt();
		}

		FlushBatchDraw();
		//Sleep(300);
	/*	if (_kbhit())																   //��ؼ��̣��������������Ϸ
		{
			ch = _getch();
			switch (ch)
			{
			case 32:																   //���ո񣬸���չʾ,��¼���ܿ��ܸ���
			{
				cleardevice;
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
				huitu();
				for (int k = 0; k < i + 5; k++)
				{
	
					setlinecolor(RGB(30, 30, 30));                                         //����������ɫ
					setfillcolor(RGB(30, 30, 30));
					fillcircle(hei1[k], hei2[k], RQ);                                    //������                  
					setbkcolor(BLACK);										   //���ֱ���   
					settextcolor(WHITE);                                                     //������ɫ
					_stprintf_s(hong, _T("%d"), j);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
					if (k >= 10)
						p = 7;
					outtextxy(hei1[k] - p, hei2[k] - 7, hong);                           //д����
					luozi();
	
					setlinecolor(WHITE);												   //����������ɫ
					setfillcolor(WHITE);												   //���������ɫ
					fillcircle(bai1[k], bai2[k], RQ);									   //������
					setbkcolor(WHITE);													   //���ֱ���   
					settextcolor(BLACK);                                                   //������ɫ
					_stprintf_s(bai, _T("%d"), j++);                                       //��������������������������䲻��
					if (k >= 10)
						p =7;
					outtextxy(bai1[k]-p, bai2[k]-7, bai);                                  //д����
					luozi();
					if (j > i-1 )
						{
						 break;
						}
				Sleep(500);
				} 
				FlushBatchDraw();
				//continue;
			}
			case 100:                                                                     
				mciSendString(_T("close  bkmusic"), NULL, 0, NULL);                       //��d�ر�����
				continue;
			case 97:
				mciSendString(_T("open ./music/BGM.mp3 alias bkmusic"), NULL, 0, NULL);  //��a��ʼ����
				mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
				continue;
			case 113:
				closegraph;
				main();
			}
		}*/
		
	}
	EndBatchDraw();																	      //Easy-x��ͼ�⺯������ͼˢ��	
	cleardevice();
	fflush(stdout);	
}
/****************************************************************************************************************************************************************************/

void shubiao()                                                                          //���������㷨������������궯��
{

	for (y = 0; y <= 20; y++)                                                 //������ΧһȦ��ֵ������������ӳ������
			{
			weizhi[y][0] = 5;
			}
	for (y = 0; y <= 20; y++)
			{
			weizhi[y][20] = 5;
			}
	for (x = 0; x <= 20; x++)
			{
			weizhi[0][x] = 5;
			}
	for (x = 0; x <= 20; x++)
			{
			weizhi[20][x] = 5;
			}
	
	
	MOUSEMSG m;																	       //���������Ϣ
	while (MouseHit()  )															   //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)				                                   //����������������������Ӧ�����������֣�
		{
			
			a = m.x / B*B;														       //Բ�����꣬����40����40��֤�õ�40�ı���������������
			b = m.y / B*B; 

			if (m.x >800 && m.x < 1100 && m.y > 260 && m.y <600)                         //PASS��ť
			{
				Q = 1;                                            /////////////////////////////////////////
				//i++;
				//pass();
				
					/*	for (x = 1; x < 20; x++)                                          //��ٽ��ִ���,ǰ�ֶԷ������ӣ��ڱ��������ָ���Ӧֵ���´��ܱ���
						{
							for (y = 1; y < 20; y++)
							{
								if ((a >= 40 && a <= 760 && b >= 40 && b <= 760) && (weizhi[x][y] == 4 || weizhi[x][y] == 3)
									&& (weizhi[a / B][b / B] != 3 && weizhi[a / B][b / B] != 4))
									//����������λ�õ�����ӣ���ٽ���λ���л�Ϊ���0��
								{
									weizhi[x][y] = 0;
									//if (weizhi[x][y] == 0)
									//{
										_stprintf_s(bai, _T("%d"), 0);                                     //////																
										outtextxy(x*B , y*B - 7, bai);                                  /////////}
									//}
									//continue;
								}
							}
						}
						//jinshou();
					 */
			}

			if (m.x > 1150 && m.x < 1400 && m.y > 260 && m.y < 320)                         //PASS��ť
			{
				Q = 2;                                            /////////////////////////////////////////
				//i++;
				//pass();
			}

			else if (m.x >1240 && m.x < 1300 && m.y > 40 && m.y <60)                         //����
			{
			   
				xing_shi_panduan();

				TCHAR s14[] = _T("�׷���ʽ     �ڷ���ʽ");
				setbkcolor(RGB(220, 180, 70));
				outtextxy(1000, 430, s14);
				_stprintf_s(hong, _T("%d"), count_wt+ B_dead);
				settextcolor(WHITE);
				outtextxy(1000, 450, hong);
				_stprintf_s(hong, _T("%d"), count_bk + W_dead);
				settextcolor(WHITE);
				outtextxy(1120, 450, hong);
				count_wt = 0;                                                                 //���㣬������ظ�
				count_bk = 0;
	
			}
			
			else if (weizhi[a / B][b / B] == 1 || weizhi[a / B][b / B] == 2 || weizhi[a / B][b / B] == 7 || weizhi[a / B][b / B] == 8)
				
					{
						jinshou();	
						//i--;
						continue;
					}

			else if (m.x > 1300 && m.x < 1340 && m.y > 40 && m.y < 80)                         //�˳���ť                       
			{
				
				i = 1;
				bk = 0;
				wt = 0;
				for (int m = 0; m < 21; m++)
					for (int n = 0; n < 21;n++)
					{
						weizhi[m][n] = { 0 };
					}
				mciSendString(_T("close  bkmusic"), NULL, 0, NULL);                      
				cleardevice();
				//fflush(stdout);
				closegraph();
				main();
				//creat_data();                                                              
				
			}
			else
			{
				if (a >= 40 && a <= 760 && b >= 40 && b <= 760)                             //��¼λ��״̬,��������ʵ�ֽ���
				{
					if (i % 2 == 0 && weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
					{
						da_jie[1][0] = 0;                                                      //��ٵ�λ�ø�λ
					    da_jie[1][1] = 0;
				       //�����ж������������㷨����������2��������ֻ��0��1����Ӧ�������
						bai1[wt] = a;                                                      //���������
						bai2[wt] = b;													   //���������� 
						wt++;
						weizhi[a / 40][b / 40] = 2;                                        //��¼λ�õ�״̬��0Ϊû�����ӣ�1Ϊ�к����ӣ�2Ϊ�а�ɫ����
						
									setlinecolor(WHITE);
									setfillcolor(WHITE);
									fillcircle(a, b, RQ);
									setbkcolor(WHITE);												   //���ֱ���   
									settextcolor(BLACK);                                               //������ɫ
									//_stprintf_s(bai, _T("%d"), i);                                   //�Ѳ������ֱ���ַ�����һ����ʾ�ַ� 
									_stprintf_s(bai, _T("%d"), 2);                                     //////
									//if (i >= 10)
									//	x = 7;
									outtextxy(a - 3, b - 7, bai);                                      //д���岽��

									for (y = 0; y <= 20; y++)                                //������ΧһȦ��ֵ���л�Ϊ���ӷ�
										{
										weizhi[y][0] = 2;
										}
									for (y = 0; y <= 20; y++)
										{
										weizhi[y][20] = 2;
										}
									for (x = 0; x <= 20; x++)
										{
										weizhi[0][x] = 2;
										}
									for (x = 0; x <= 20; x++)
										{
										weizhi[20][x] = 2;
										}

									setlinecolor(WHITE);
									setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
									line(30, 30, 770, 30);
									line(30, 770, 770, 770);
									line(30, 30, 30, 770);
									line(770, 30, 770, 770);

									line(990, 30, 990, 210);
									line(990, 30, 1210, 30);
									line(1210, 30, 1210, 210);
									line(990, 210, 1210, 210);

									
									TCHAR s13[] = _T("��һ�֣�����");
									setbkcolor(RGB(220, 180, 70));
									outtextxy(1000, 400, s13);
									setlinecolor(BLACK);
									setfillcolor(BLACK);
									fillcircle(1120, 410, 10);
									_stprintf_s(hong, _T("%d"), i);
									settextcolor(WHITE);
									outtextxy(1000, 380, hong);  
									
						luozi();
						i++;
						//huaxian();                                                                   /////////////////////////////////////
				
				
				}
					/****�������Ӵ��˼·�ǽ���Χ����һ·�����ݺ�ڶ�ʮ·��ȫ����ֵΪ5�������ʱ��ֱ�ӵ��þ��У��ܱ������Ǵ�0��800��������һ����ά�����ʾ***/
					/****�ĸ�����ʱ��û�д���***************************************************************************************************************/

					else if (i % 2 == 1 &&weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
						                                                                    //�����ж�
					{ 
						da_jie[1][0] = 0;
						da_jie[1][1] = 0;

						hei1[bk] = a;                                                       //���������
						hei2[bk] = b;                                                       //���������� 
						bk++;
						
						weizhi[a / 40][b / 40] = 1;                                        //��¼λ�õ�״̬��1Ϊ�к����ӣ�0Ϊû�����ӣ�2Ϊ�а�ɫ����
					
						setlinecolor(RGB(30, 30, 30));
						setfillcolor(RGB(30, 30, 30));
						fillcircle(a, b, RQ);

															 
						setbkcolor(RGB(30, 30, 30));									   //���ֱ���   
						settextcolor(WHITE);                                               //������ɫ
						//_stprintf_s(hong, _T("%d"), i);                                  //�Ѳ������ֱ���ַ�����һ����ʾ�ַ� 
						_stprintf_s(hong, _T("%d"), 1);
						//if (i >= 10)
						//	x = 7;
						outtextxy(a - 3, b - 7, hong);                         //д���岽��
							for (y = 0; y <= 20; y++)                                      //������ΧһȦ��ֵ���л�Ϊ���ӷ�
								{
									weizhi[y][0] = 1;
								}
							for (y = 0; y <= 20; y++)
								{
									weizhi[y][20] = 1;
								}
							for (x = 0; x <= 20; x++)
								{
									weizhi[0][x] = 1;
								}
							for (x = 0; x <= 20; x++)
								{
									weizhi[20][x] = 1;
								}
								setlinecolor(BLACK);
								setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
								line(30, 30, 770, 30);
								line(30, 770, 770, 770);
								line(30, 30, 30, 770);
								line(770, 30, 770, 770);

								line(990, 30, 990, 210);
								line(990, 30, 1210, 30);
								line(1210, 30, 1210, 210);
								line(990, 210, 1210, 210);
							
								TCHAR s13[] = _T("��һ�֣�����");
								setbkcolor(RGB(220, 180, 70));
								outtextxy(1000, 400, s13);
								setlinecolor(WHITE);
								setfillcolor(WHITE);
								fillcircle(1120, 410, 10);
								_stprintf_s(hong, _T("%d"), i);
								settextcolor(BLACK);
								outtextxy(1000, 380, hong);   
													
						luozi();
						i++;
						//huaxian();   
					}
				}

				FlushBatchDraw();													             //����ǰ��ͼ�Σ�����ˢ������	
				continue;                                    /////////////////////////////////////////////////////
			}	
		}
		/*************************************************************************************************************

		**************************************************************************************************************/
		else if (m.uMsg == WM_RBUTTONDOWN)                                              //����Ҽ����£�����
		{
			Q = 0;                                                                      //�رռ�����Զ�����
			if (i % 2 == 1)
			{
				weizhi[bai1[wt-1 ] / 40][bai2[wt-1 ] / 40] = 0;                           //���ʱ�ǲ��ӱ���i�Ѿ����ӣ�����һ��Ҫ-1;
				getimage(&img, 1020, 60, 40, 40);                                       //���塢�������Ӻ�ò���ʮ��
				putimage(bai1[wt-1 ] - 20, bai2[wt-1 ] - 20, &img);                       //��Ҫȡ�øղ����ӵ�����

				jinshou();
				i--;
				
			}
			else if (i % 2 == 0)
			{
				weizhi[hei1[bk-1 ] / 40][hei2[bk-1 ] / 40] = 0;

				getimage(&img, 1020, 60, 40, 40);                                       //���塢�������Ӻ�ò���ʮ��
				putimage(hei1[bk-1] - 20, hei2[bk-1] - 20, &img);                         //��Ҫȡ�øղ����ӵ�����

				i--;
				jinshou();
			}
			T = T + 5;

			FlushBatchDraw();

		}
	
	     /********************************************************************************************************************
			*���̱�Ե�����߳�ͷ
			*��һ�Ա��취����������λ��һ����ÿ�β�����Χ������
			*������������һ�����ӵ�ʱ���������Ӷ���������һ�룬ɵ���ˣ�����ֻҪ�������������ӵ����򱳾���ɫ����
			*�ٺ����ַ��֣�����һ��������߾����ˣ�����д�����򵥡���׼ȷ
			*����ö�Ӧ��ͼ���Ǿ���
			*�򵥵���������෽��������ɣ��������������صķ����ͺ���
			*��˸��������ı��ʺ���Ҫ������������ĵ㣬������ͨ����������������ǵ������������Ӻܶ಻˵��������δ֪����
		
		**********************************************************************************************************************/
	}
}

void huitu()                                                                           //ͼ�ν������
{
	for (int y = 0; y < D; y++)                                                        //������
	{
		setlinecolor(RGB(220, 180, 70));
		line(0, y, C, y);
	}
	setcolor(RGB(255, 255, 255));													   //����������ɫ
	for (int y = B; y <= A; y += B)													   //���ݺ�ʮ��·����
		line(B, y, A, y);
	for (int x = B; x <= A; x += B)
		line(x, B, x, A);


	int i, j;
	for (i = 4; i < 19; i += 6)
		for (j = 4; j < 19; j += 6)                                                    //�Ÿ���λ�ĵ�λ��
		{
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillcircle(i * B, j * B, R);											   //���Ÿ���λ�ĵ㣬������Ԫ
		}
	for (int y = 40; y <= 200; y += 40)                                                //��һ���ο���
		line(1000, y, 1200, y);
	for (int x = 1000; x <= 1200; x += B)
		line(x, 40, x, 200);
	    setlinecolor(WHITE);                                                           // �����ο���λ��,���ڽ�ͼ
	    setfillcolor(WHITE);
	    fillcircle(1040, 120, R);
		
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
		line(30, 30, 770, 30);
		line(30,770, 770, 770);
		line(30, 30, 30, 770);
		line(770, 30, 770, 770);

		line(990, 30, 990, 210);
		line(990, 30, 1210, 30);
		line(1210, 30, 1210, 210);
		line(990, 210, 1210, 210);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
	
		// (a >1200 && a < 1400 && b > 400 && b <100)
		
		TCHAR s1[] = _T(" ����˵��: C���� + EASY-X ͼ�ν�������Χ����Ϸ��");
		TCHAR s2[] = _T(" (1)���������Ͻ������������ӣ�λ��ż����׼;");
		TCHAR s3[] = _T(" (2)���ڰ׽�������;");
		TCHAR s4[] = _T(" (3)���Ҽ����壬ֹͣ�������� ");
		TCHAR s5[] = _T(" (4)�������ߺ���      �����߰���");
		TCHAR s6[] = _T(" (5)���ʵ�λ�ã������");
		TCHAR s7[] = _T(" (6)����a���ָ����֣�d��ͣ��");
		TCHAR s8[] = _T(" ��ʽ");
		TCHAR s9[] = _T(" �˳�");
		TCHAR s10[] = _T("A        B       C        D       E        F       G        H         I        J        K        L        M       N       O        P        Q       R        S ");
		CHAR s11[] = "1234567891111111111";
		CHAR s12[] = "0123456789";
	
		//CHAR S13[]= "'10''11''12'����";                                                    /////////////////////////
		setbkcolor(RGB(220, 180, 70));													   //���ֱ���   
		//settextcolor(RGB(150, 150, 0));                                            	   //������ɫ
		outtextxy(1000, 220, s1);
		outtextxy(1000, 240, s2);
		outtextxy(1000, 260, s3);
		outtextxy(1000, 280, s4);
		outtextxy(1000, 300, s5);
		outtextxy(1000, 320, s6);
		outtextxy(1000, 340, s7);
		outtextxy(1240, 40, s8);
		outtextxy(1300, 40, s9);
		outtextxy(38, 5, s10);

		for (i = 0; i <= 18;i++)
		{
			outtextxy(5, (i+1)*40-6, s11[i]);
		}
		for (i = 10; i <= 19; i++)
		{
			outtextxy(12, i  * 40 - 6, s12[i-10]);
		}

		FlushBatchDraw();																   //Easy-x��ͼ�⺯�������̸���	

}

void luozi()
{
	mciSendString(_T("close  ggmusic"), NULL, 0, NULL);               // �����������Ȱ�ǰ��һ�ε����ֹر�  
	mciSendString(_T("open ./music/stone111.mp3 alias ggmusic"), NULL, 0, NULL);                                // ������
	mciSendString(_T("play ggmusic"), NULL, 0, NULL);                  // ������һ��
}

void jinshou()
{
	mciSendString(_T("close jjmusic"), NULL, 0, NULL);                 // �����������Ȱ�ǰ��һ�ε����ֹر�  
	mciSendString(_T("open ./music/gotEnemy.mp3 alias jjmusic"), NULL, 0, NULL);                                // ������
	mciSendString(_T("play jjmusic"), NULL, 0, NULL);                  // ������һ��

	mciSendString(_T("close  psmusic"), NULL, 0, NULL);               // �����������Ȱ�ǰ��һ�ε����ֹر�  
	mciSendString(_T("open ./music/pass.mp3 alias psmusic"), NULL, 0, NULL);                                // ������
	mciSendString(_T("play psmusic"), NULL, 0, NULL);                  // ������һ��


}

int jia_yan_b(int x ,int y)
{
	for (int m = 1; m <= 19; m++)
	{
		for (int n = 1; n <= 19; n++)
		{
			
			 if ((weizhi[x][y] == 1)
				&& (weizhi[x - 1][y] == 2 && weizhi[x][y - 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y + 1] == 0)
				|| (weizhi[x][y - 1] == 2 && weizhi[x][y + 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x - 1][y] == 0)
				|| (weizhi[x - 1][y] == 2 && weizhi[x][y + 1] == 2 && weizhi[x][y - 1] == 2 && weizhi[x + 1][y] == 0)
				|| (weizhi[x - 1][y] == 2 && weizhi[x][y + 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y - 1] == 0))
				{
					return 1;
				}

		}
	}
}

int jia_yan_w(int x, int y)
{
	for (int m = 1; m <= 19; m++)
	{
		for (int n = 1; n <= 19; n++)
		{
			if ((weizhi[x][y] == 2)
				&& (weizhi[x - 1][y] == 1 && weizhi[x][y - 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y + 1] == 0)
				|| (weizhi[x][y - 1] == 1 && weizhi[x][y + 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x - 1][y] == 0)
				|| (weizhi[x - 1][y] == 1 && weizhi[x][y + 1] == 1 && weizhi[x][y - 1] == 1 && weizhi[x + 1][y] == 0)
				|| (weizhi[x - 1][y] == 1 && weizhi[x][y + 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y - 1] == 0))
			{
				return 1;
			}

		}
	}
}
	
void no_breath()
{
	for (int x = 1; x <= 19; x++)                                                   //���ֵ��в���
	{
		for (int y = 1; y <= 19; y++)
		{
			if ((weizhi[x][y] == 0) && (weizhi[x - 1][y] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y - 1] == 1 && weizhi[x][y + 1] == 1))
			{
				weizhi[x][y] = 5;
				_stprintf_s(bai, _T("%d"), 5);                                     //////																
				outtextxy(x*B - 3, y*B - 7, bai);
			}
		}
	}

	for (int x = 1; x <= 19; x++)                                                   //���ֵ��в���
	{
		for (int y = 1; y <= 19; y++)
		{
			if ((weizhi[x][y] == 0) && (weizhi[x - 1][y] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y - 1] == 2 && weizhi[x][y + 1] == 2))
			{
				weizhi[x][y] = 6;
				_stprintf_s(bai, _T("%d"), 6);                                     //////																
				outtextxy(x*B - 3, y*B - 7, bai);
			}
		}
	}



}

void pass()
{
	mciSendString(_T("close  pssmusic"), NULL, 0, NULL);               // �����������Ȱ�ǰ��һ�ε����ֹر�  
	mciSendString(_T("open ./music/pass.wav alias pssmusic"), NULL, 0, NULL);                                // ������
	mciSendString(_T("play pssmusic"), NULL, 0, NULL);                  // ������һ��
	T = T - 5;
}

void Eat_more_than_one_w()
{    
	int x, y;
	TCHAR s13[] = _T("����ǰ����   �ڷ�����-             �׷�����-               ��������");
	setbkcolor(RGB(220, 180, 70));
	outtextxy(1000, 360, s13);
	_stprintf_s(hong, _T("%d"), W_dead);                                                           //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
	outtextxy(1170, 360, hong);
	_stprintf_s(hong, _T("%d"), B_dead);														   //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
	outtextxy(1320, 360, hong);
	
	for (x = 1; x <= 19; x++)
	{	
		for (y = 1; y <= 19; y++)
		{
			 if((weizhi[x][y] == 2 && weizhi[x - 1][y] != 0 && weizhi[x + 1][y] != 0 && weizhi[x][y - 1] != 0 && weizhi[x][y + 1] != 0))
			

					{
						weizhi[x][y] = 8;
					
						_stprintf_s(hong, _T("%d"), 8);                                                 //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
						outtextxy(x*B-3, y*B-7, hong);                                                  //д����
						Eat_more_than_one_w();                                                          //////////////////��ʼ�ݹ�ѭ��,  ���ڴ��ط��֣���겻���������һֱ����
						
					}
		
		}
	}		
}

void Eat_more_than_one_b()                           
{
	int x, y;
	TCHAR s13[] = _T("����ǰ����   �ڷ�����-             �׷�����-    ");
	setbkcolor(RGB(220, 180, 70));
	outtextxy(1000, 360, s13);
	_stprintf_s(hong, _T("%d"), W_dead);                                                           //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
	outtextxy(1170, 360, hong);
	_stprintf_s(hong, _T("%d"), B_dead);														   //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
	outtextxy(1320, 360, hong);
	for (x = 1; x <= 19; x++)
	{	
		for (y = 1; y <= 19; y++)
		{
			 if(weizhi[x][y] == 1 && (weizhi[x - 1][y] != 0 && weizhi[x + 1][y] != 0 && weizhi[x][y - 1] != 0 && weizhi[x][y + 1] != 0))
				
				{
					weizhi[x][y] = 7;
			
					_stprintf_s(hong, _T("%d"), 7);                                                 //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
					outtextxy(x*B-3, y*B-7, hong);                                                  //д����
					Eat_more_than_one_b();                                        //////////////////��ʼ�ݹ�ѭ��,  ���ڴ��ط��֣���겻���������һֱ����
				}
			
		}
	}		
}

void chizhi_w()
{
	for (x = 1; x <= 19; x++)
	{
		for (y = 1; y <= 19; y++)
		{
			if ((weizhi[x][y] == 2) && (weizhi[x - 1][y] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y + 1] == 1 && weizhi[x][y - 1] == 1))
			{
				getimage(&img, 1020, 60, 40, 40);
				putimage(x*B - 20, y*B - 20, &img);
				weizhi[x][y] = 0;
			
				//weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
				//_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
				//outtextxy(x*B - 3, y*B - 7, bai);			     //
				if ((x == 4 && y == 4) || (x == 10 && y == 4) || (x == 16 && y == 4))	                 //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if ((x == 4 && y == 10) || (x == 10 && y == 10) || (x == 16 && y == 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if ((x == 4 && y == 16) || (x == 10 && y == 16) || (x == 16 && y == 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (y*B == 40 && x*B != 40 && x*B != 760)			    //�ϱ�
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (y*B == 760 && x*B != 40 && x*B != 760)			 //�±�
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B != 40 && y*B != 760)				 //���
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B != 40 && y*B != 760)              //�ұ�
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B == 40)                               //���Ͻ�
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 760 && y*B == 40)                              //���Ͻ�
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 760 && y*B == 760)                             //���½�
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																											// }
				_stprintf_s(bai, _T("%d"), 0);                                      //���Լ�¼�ã���ɾ��
				outtextxy(x*B - 3, y*B - 7, bai);			                        //
				da_jie[1][0] = x;
				da_jie[1][1] = y;
				
				W_dead++;
			}
		}
	}
	//FlushBatchDraw();
	if (jia_yan_w(a / B, b / B))
	{
		da_jie[1][0] = 0;
		da_jie[1][1] = 0;
	}
}

void chizhi_b()
{

	for (x = 1; x <= 19; x++)
	{
		for (y = 1; y <= 19; y++)
		{

			if (((weizhi[x][y] == 1) && weizhi[x - 1][y] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y + 1] == 2 && weizhi[x][y - 1] == 2))
			{
				getimage(&img, 1020, 60, 40, 40);
				putimage(x*B - 20, y*B - 20, &img);
				weizhi[x][y] = 0;

				if ((x == 4 && y == 4) || (x == 10 && y == 4) || (x == 16 && y == 4))	                 //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if ((x == 4 && y == 10) || (x == 10 && y == 10) || (x == 16 && y == 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if ((x == 4 && y == 16) || (x == 10 && y == 16) || (x == 16 && y == 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (y*B == 40 && x*B != 40 && x*B != 760)					 //�ϱ�
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (y*B == 760 && x*B != 40 && x*B != 760)			 //�±�
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B != 40 && y*B != 760)				 //���
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B != 40 && y*B != 760)              //�ұ�
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B == 40)                               //���Ͻ�
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 760 && y*B == 40)                              //���Ͻ�
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 760 && y*B == 760)                             //���½�                      
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																											// }
				_stprintf_s(bai, _T("%d"), 0);                                                      //���Լ�¼�ã���ɾ��
				outtextxy(x*B - 3, y*B - 7, bai);			                                       //
				da_jie[1][0] = x;
				da_jie[1][1] = y;
				B_dead++;											                                       //tizi(a/B ,b/B);     //���������
			}

			//FlushBatchDraw();
		}
	}
	if (jia_yan_b(a / B, b / B))
	{
		da_jie[1][0] = 0;
		da_jie[1][1] = 0;
	}
}

void shuaxin_w()
{

	int x, y;
	for (x = 19; x >= 1; x--)
	{
		for (y = 19; y >= 1; y--)
		{
			if ((weizhi[x][y] == 8) && (weizhi[x - 1][y] == 2 || weizhi[x + 1][y] == 2 || weizhi[x][y - 1] == 2 || weizhi[x][y + 1] == 2))
			{
				for (x = 1; x <= 19; x++)
				{
					for (y = 1; y <= 19; y++)
					{
						if (weizhi[x][y] == 8)
						{
							
							weizhi[x][y] = 2;
							_stprintf_s(hong, _T("%d"), 2);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
							outtextxy(x*B - 3, y*B - 7, hong);                                     //д����
						}
					}
				}
			}

			
		}
	}
		
	FlushBatchDraw();
		
}

void shuaxin_b()   
{
	int x, y;
	for (x = 19; x >= 1; x--)
	{
		for (y = 19; y >= 1; y--)
		{
			if ((weizhi[x][y] == 7) && (weizhi[x - 1][y] == 1 || weizhi[x + 1][y] == 1 || weizhi[x][y - 1] == 1 || weizhi[x][y + 1] == 1))
			{
				for (x = 1; x <= 19; x++)
				{
					for (y = 1; y <= 19; y++)
					{
						if (weizhi[x][y] == 7)
						{
							
							weizhi[x][y] = 1;
							_stprintf_s(hong, _T("%d"), 1);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
							outtextxy(x*B - 3, y*B - 7, hong);                                     //д����
							                                                                       //��������
						}
					}
				}

			}

		
			
		}
	}

	FlushBatchDraw();
	
}

void huaxian()
{
	int x, y;
	int r, g, b;
	
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	for (x = 1; x <= 19; x++)                                                      //���ٶȻ���
	{
		for (y = 1; y <= 19; y++)
		{
			srand((unsigned)time(NULL));
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
			setcolor(RGB(r, g, b));
			line(x * 40, B, x * 40, A);											   //����������ɫ
			FlushBatchDraw();
		
			circle(x*B, y*B, 3);
			Sleep(T);
			FlushBatchDraw();
		}
	}

	for (x = 1; x <= 19; x++)                                                      //�ָ�������
	{
		for (y = 1; y <= 19; y++)
		{
			setcolor(RGB(255, 255, 255));											 //����������ɫ											 
			line(B, y * 40, A, y * 40);
			line(x * 40, B, x * 40, A);

			setlinecolor(RGB(220, 180, 70));
			circle(x*B, y*B, 3);
		}
	}

	for (x = 4; x < 19; x += 6)
	{
		for (y = 4; y < 19; y += 6)                                                    //�Ÿ���λ�ĵ�λ��
		{
			if (weizhi[x][y] == 0) 
			{
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillcircle(x * B, y * B, R);
			}										                                  //���Ÿ���λ�ĵ㣬������Ԫ
		}
    }
}

int  creat_data()
{
	//char str[100] = { "hello world!" };
	//fopen_s(&fp, "./data/qipu.txt", " a+");

			
	return 0;
}

void SHA_bk()
{
	int x, y;
		for (x = 1; x <= 19; x++)
		{
			for (y = 1; y <= 19; y++)
			{
				if (weizhi[x][y] == 7)
				{
					getimage(&img, 1020, 60, 40, 40);                                      ///////////////////�۲�Ч����;
					putimage(x*B - 20, y*B - 20, &img);                                    //������/////////////////////////////////////////
					weizhi[x][y] = 0;
					_stprintf_s(hong, _T("%d"), 0);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�
					outtextxy(x*B - 3, y*B - 7, hong);                                     //д����
					W_dead++;   
					luozi();//��������
				}
			}
		}
	
		FlushBatchDraw();
	
}

void SHA_wt()
{
	int x, y;	
		for (x = 1; x <= 19; x++)
		{
			for (y = 1; y <= 19; y++)
			{
				if (weizhi[x][y] == 8)
				{
					getimage(&img, 1020, 60, 40, 40);                                      ///////////////////�۲�Ч����;
					putimage(x*B - 20, y*B - 20, &img);                                    //������/////////////////////////////////////////
					weizhi[x][y] = 0;
					_stprintf_s(hong, _T("%d"), 0);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�
					outtextxy(x*B - 3, y*B - 7, hong);                                     //д����
					W_dead++;  
					luozi();//��������
				}
			}
		}
		

		FlushBatchDraw();

}

void xing_shi_panduan()
{
	int x, y;

	for (x = 1; x <= 19; x++)
	{
		for (y = 1; y <= 19; y++)
		{
			if (weizhi[x][y] == 2 && x<5 && y<5)

				{
					for (int m = 1; m <= x; m++) 
					{
						for (int n = 1; n <= y; n++)
						{
							setcolor(WHITE);
							circle(m*B, n*B, 3);
							count_wt++;
						}
					}
			
				}

			else if (weizhi[x][y] == 2 && x>15 && y<5)

			{
				for (int m = x; m <= 19; m++)
				{
					for (int n = 1; n <= y; n++)
					{
						setcolor(WHITE);
						circle(m*B, n*B, 3);
						count_wt++;
					}
				}

			}

			else if (weizhi[x][y] == 2 && x<5 && y>15)

			{
				for (int m = 1; m <= x; m++)
				{
					for (int n = y; n <= 19; n++)
					{
						setcolor(WHITE);
						circle(m*B, n*B, 3);
						count_wt++;
					}
				}

			}

			else if (weizhi[x][y] == 2 && x>15 && y>15)

			{
				for (int m = x; m <= 19; m++)
				{
					for (int n = y; n <= 19; n++)
					{
						setcolor(WHITE);
						circle(m*B, n*B, 3);
						count_wt++;
					}
				}
			}
		}
	}
	FlushBatchDraw();
}

void xiaqi_wt()
{
	 srand((unsigned)time(NULL));
	 a = (rand() % 20) * B;
	 b = (rand() % 20) * B;

	if (a >= 40 && a <= 760 && b >= 40 && b <= 760)                             //��¼λ��״̬,��������ʵ�ֽ���
	{
				if (i % 2 == 0 && weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
				{
					da_jie[1][0] = 0;                                                      //��ٵ�λ�ø�λ
					da_jie[1][1] = 0;
					//�����ж������������㷨����������2��������ֻ��0��1����Ӧ�������
					bai1[wt] = a;                                                      //���������
					bai2[wt] = b;													   //���������� 
					wt++;
					weizhi[a / 40][b / 40] = 2;                                        //��¼λ�õ�״̬��0Ϊû�����ӣ�1Ϊ�к����ӣ�2Ϊ�а�ɫ����

					setlinecolor(WHITE);
					setfillcolor(WHITE);
					fillcircle(a, b, RQ);
					setbkcolor(WHITE);												   //���ֱ���   
					settextcolor(BLACK);                                               //������ɫ
																					   //_stprintf_s(bai, _T("%d"), i);                                   //�Ѳ������ֱ���ַ�����һ����ʾ�ַ� 
					_stprintf_s(bai, _T("%d"), 2);                                     //////
																					   //if (i >= 10)
																					   //	x = 7;
					outtextxy(a - 3, b - 7, bai);                                      //д���岽��

					for (y = 0; y <= 20; y++)                                //������ΧһȦ��ֵ���л�Ϊ���ӷ�
					{
						weizhi[y][0] = 2;
					}
					for (y = 0; y <= 20; y++)
					{
						weizhi[y][20] = 2;
					}
					for (x = 0; x <= 20; x++)
					{
						weizhi[0][x] = 2;
					}
					for (x = 0; x <= 20; x++)
					{
						weizhi[20][x] = 2;
					}

					setlinecolor(WHITE);
					setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
					line(30, 30, 770, 30);
					line(30, 770, 770, 770);
					line(30, 30, 30, 770);
					line(770, 30, 770, 770);

					line(990, 30, 990, 210);
					line(990, 30, 1210, 30);
					line(1210, 30, 1210, 210);
					line(990, 210, 1210, 210);


					TCHAR s13[] = _T("��һ�֣�����");
					setbkcolor(RGB(220, 180, 70));
					outtextxy(1000, 400, s13);
					setlinecolor(BLACK);
					setfillcolor(BLACK);
					fillcircle(1120, 410, 10);
					_stprintf_s(hong, _T("%d"), i);
					settextcolor(WHITE);
					outtextxy(1000, 380, hong);

					luozi();
					i++;
					//huaxian();                                                                   /////////////////////////////////////


				}

		/****�������Ӵ��˼·�ǽ���Χ����һ·�����ݺ�ڶ�ʮ·��ȫ����ֵΪ5�������ʱ��ֱ�ӵ��þ��У��ܱ������Ǵ�0��800��������һ����ά�����ʾ***/
		/****�ĸ�����ʱ��û�д���***************************************************************************************************************/
		/*if(Q==0)
		{
			/*else if (i % 2 == 1 && weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
			//�����ж�
			{
				da_jie[1][0] = 0;
				da_jie[1][1] = 0;

				hei1[bk] = a;                                                       //���������
				hei2[bk] = b;                                                       //���������� 
				bk++;

				weizhi[a / 40][b / 40] = 1;                                        //��¼λ�õ�״̬��1Ϊ�к����ӣ�0Ϊû�����ӣ�2Ϊ�а�ɫ����

				setlinecolor(RGB(30, 30, 30));
				setfillcolor(RGB(30, 30, 30));
				fillcircle(a, b, RQ);


				setbkcolor(RGB(30, 30, 30));									   //���ֱ���   
				settextcolor(WHITE);                                               //������ɫ
																				   //_stprintf_s(hong, _T("%d"), i);                                  //�Ѳ������ֱ���ַ�����һ����ʾ�ַ� 
				_stprintf_s(hong, _T("%d"), 1);
				//if (i >= 10)
				//	x = 7;
				outtextxy(a - 3, b - 7, hong);                         //д���岽��
				for (y = 0; y <= 20; y++)                                      //������ΧһȦ��ֵ���л�Ϊ���ӷ�
				{
					weizhi[y][0] = 1;
				}
				for (y = 0; y <= 20; y++)
				{
					weizhi[y][20] = 1;
				}
				for (x = 0; x <= 20; x++)
				{
					weizhi[0][x] = 1;
				}
				for (x = 0; x <= 20; x++)
				{
					weizhi[20][x] = 1;
				}
				setlinecolor(BLACK);
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
				line(30, 30, 770, 30);
				line(30, 770, 770, 770);
				line(30, 30, 30, 770);
				line(770, 30, 770, 770);

				line(990, 30, 990, 210);
				line(990, 30, 1210, 30);
				line(1210, 30, 1210, 210);
				line(990, 210, 1210, 210);

				TCHAR s13[] = _T("��һ�֣�����");
				setbkcolor(RGB(220, 180, 70));
				outtextxy(1000, 400, s13);
				setlinecolor(WHITE);
				setfillcolor(WHITE);
				fillcircle(1120, 410, 10);
				_stprintf_s(hong, _T("%d"), i);
				settextcolor(BLACK);
				outtextxy(1000, 380, hong);

				luozi();
				i++;
				//huaxian();   
			}
		}*/
		
	}

	FlushBatchDraw();													             //����ǰ��ͼ�Σ�����ˢ������	
                                  /////////////////////////////////////////////////////
}

void xiaqi_bk()
{
	srand((unsigned)time(NULL));
	a = (rand() % 20) * B;
	b = (rand() % 20) * B;

	if (a >= 40 && a <= 760 && b >= 40 && b <= 760)                             //��¼λ��״̬,��������ʵ�ֽ���
	{
		if (i % 2 == 1 && weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
		//�����ж�
		{
		da_jie[1][0] = 0;
		da_jie[1][1] = 0;

		hei1[bk] = a;                                                       //���������
		hei2[bk] = b;                                                       //����������
		bk++;

		weizhi[a / 40][b / 40] = 1;                                        //��¼λ�õ�״̬��1Ϊ�к����ӣ�0Ϊû�����ӣ�2Ϊ�а�ɫ����

		setlinecolor(RGB(30, 30, 30));
		setfillcolor(RGB(30, 30, 30));
		fillcircle(a, b, RQ);


		setbkcolor(RGB(30, 30, 30));									   //���ֱ���
		settextcolor(WHITE);                                               //������ɫ
		//_stprintf_s(hong, _T("%d"), i);                                  //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�
		_stprintf_s(hong, _T("%d"), 1);
		//if (i >= 10)
		//	x = 7;
		outtextxy(a - 3, b - 7, hong);                         //д���岽��
		for (y = 0; y <= 20; y++)                                      //������ΧһȦ��ֵ���л�Ϊ���ӷ�
		{
		weizhi[y][0] = 1;
		}
		for (y = 0; y <= 20; y++)
		{
		weizhi[y][20] = 1;
		}
		for (x = 0; x <= 20; x++)
		{
		weizhi[0][x] = 1;
		}
		for (x = 0; x <= 20; x++)
		{
		weizhi[20][x] = 1;
		}
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 3);
		line(30, 30, 770, 30);
		line(30, 770, 770, 770);
		line(30, 30, 30, 770);
		line(770, 30, 770, 770);

		line(990, 30, 990, 210);
		line(990, 30, 1210, 30);
		line(1210, 30, 1210, 210);
		line(990, 210, 1210, 210);

		TCHAR s13[] = _T("��һ�֣�����");
		setbkcolor(RGB(220, 180, 70));
		outtextxy(1000, 400, s13);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(1120, 410, 10);
		_stprintf_s(hong, _T("%d"), i);
		settextcolor(BLACK);
		outtextxy(1000, 380, hong);

		luozi();
		i++;
		//huaxian();
		}
	

	}

	FlushBatchDraw();													             //����ǰ��ͼ�Σ�����ˢ������	
																					 /////////////////////////////////////////////////////
}
