#include"ͷ�ļ�.h"     
#define C 1500																		   //���ڳ���   
#define D  800                                                                         //���ڸ߶�
#define A 760                                                                          //���̳ߴ�
#define B 40                                                                           //ÿ��ߴ磬�������ص�λ
#define R 8                                                                            //��λ��İ뾶
#define RQ 18                                                                          //���Ӱ뾶
                                                          														  
static int i = 1;                                                                      //0�ǰ������У�1�Ǻ������У����ݲ�������2��������
int hong1[200];                                                                        //��������   
int hong2[200]; 
int bai1[100];                                                                         //��������
int bai2[100];
int addrss[300][2];                                                                   //��¼ÿһ�����꣬��i�滻300��
int weizhi[21][21] = {0};                                                              //��ʼλ�ö�û�����ӣ���¼Ϊ0 
int zong, heng;                                                                        //�ݺ�ʮ��·
int a, b;
int adss[100][2];																	   //���ڼ�¼����λ�ã�ÿ�θ�λ
static int B_dead=0;																   //��������������ÿ�ι�1
static int W_dead=0;																   //��������������ÿ�ι�1
int Sam_B_dead = 0;																	   //�����ܹ���������
int Sam_W_dead = 0;																	   //�����ܹ���������
int ch;                                                                                //��¼����
int T = 0;                                                                            //////////////////////////
TCHAR bai[10];
TCHAR hong[10];                                                                        //�洢�����ַ�����ʾ���Ӳ���
//IMAGE img_go_b, img_go_bk;
IMAGE img;
void huitu();																	       //���ƽ���
void shubiao();                                                                        //��궯������
int  main();
void luozi();                                                                          //��������
void jinshou();
void jia_yan_b();
void jia_yan_w();
void pass();
void huaxian();
void Eat_more_than_one_w();                                                              //���Ӵ��ڵ���2��(sizi>=1)����ִ�д˺���
void Eat_more_than_one_b();
void shuaxin_w();
void chizhi_w();
void shuaxin_b();
void chizhi_b();
void dao_pu();                                                                          //����ĵ��ˣ������һ
void no_breath();                                                                       //������λ��

/********************************************************************************************************************************************************/

void weiqi()                                                                            //���������򿪽���
{
    int j=0;
	int x = 3;                                                                         //���Ӵ�ӡ��λ������Ϊ�˶�������
	//mciSendString(_T("open ./music/BGM2.mp3 alias bkmusic"), NULL, 0, NULL);          //�򿪱�������
	//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);                          //ѭ������
	initgraph(C, D, SHOWCONSOLE);                                                      //����SHOWCONSOLE���Ա�������̨
	HWND hwnd = GetHWnd();                                                             //���ô��ڱ������� 
	SetWindowText(hwnd,_T( "Χ��GO"));
	huitu();                                                                           //��ʼ����ͼ���������巽���ں������
	BeginBatchDraw();                                                                  //Easy-x��ͼ�⺯������ͼ��ʼ
	while (1)                                                                          //ѭ�����嶯��
	{
		no_breath();
		dao_pu();
		jia_yan_b();
		jia_yan_w();
		shubiao();                                                                     //ִ����궯������,�ᵽ��궯�������ڲ���¼��	
		if (i % 2 == 0)
		{
			chizhi_w();
			//chizhi_b();
			Eat_more_than_one_w();
			shuaxin_w();                                                                     //����ˢ�£�������궯��ǰ��
			
			
		}
		if (i % 2 == 1)
		{
			chizhi_b();
			chizhi_w();
			//Eat_more_than_one_b();
			shuaxin_b();

			
		}
		//JIN_SHOU;                                                       //ÿ��ˢ��                                                               
		if (_kbhit())																   //��ؼ��̣��������������Ϸ
		{
			ch = _getch();
			switch (ch)
			{
			case 32:																   //���ո񣬸���չʾ,��¼���ܿ��ܸ���
			{
				cleardevice;
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
				huitu();
				for (int k = 0; k < i+5;k++)
				{
	/***********�ֵ�����***************************************************************************************************************************/
					setlinecolor(RGB(30, 30, 30));                                         //����������ɫ
					setfillcolor(RGB(30, 30, 30));
					fillcircle(hong1[k], hong2[k], RQ);                                    //������                  
					setbkcolor(RGB(30, 30, 30));										   //���ֱ���   
					settextcolor(RED);                                                     //������ɫ
					_stprintf_s(hong, _T("%d"), j);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
					if (k >= 10)
						x = 7;
					outtextxy(hong1[k] - x, hong2[k] - 7, hong);                           //д����
					luozi();
		/***********�ֵ�����***************************************************************************************************************************/
					setlinecolor(WHITE);												   //����������ɫ
					setfillcolor(WHITE);												   //���������ɫ
					fillcircle(bai1[k], bai2[k], RQ);									   //������
					setbkcolor(WHITE);													   //���ֱ���   
					settextcolor(BLACK);                                                   //������ɫ
					_stprintf_s(bai, _T("%d"), j++);                                       //��������������������������䲻��
					if (k >= 10)
						x =7;
					outtextxy(bai1[k]-x, bai2[k]-7, bai);                                  //д����
					luozi();
				if (j > i-1 )
					{
					 break;
					}
				FlushBatchDraw();
				Sleep(1000);
				} 
				//continue;
			}
			case 100:                                                                     
				mciSendString(_T("close  bkmusic"), NULL, 0, NULL);                       //��d�ر�����
				continue;
			case 97:
				mciSendString(_T("open ./music/BGM2.mp3 alias bkmusic"), NULL, 0, NULL);  //��a��ʼ����
				mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
				continue;
			case 113:
				closegraph;
				main();
			}
		}
		
	}
	EndBatchDraw();																	      //Easy-x��ͼ�⺯������ͼˢ��	
	cleardevice();
	fflush(stdout);
	
}

void shubiao()                                                                         //���������㷨������������궯��
{
	//loadimage(&img_go_b, _T("./img/go-b.png"));                                      
	//loadimage(&img_go_bk, _T("./img/go-bk.jpg"));
	//int a, b;                                                                          //��������
	//int you_a, you_b;
	
	for (heng = 0; heng <= 20; heng++)                                                 //������ΧһȦ��ֵ������������ӳ������
			{
			weizhi[heng][0] = 5;
			}
	for (heng = 0; heng <= 20; heng++)
			{
			weizhi[heng][20] = 5;
			}
	for (zong = 0; zong <= 20; zong++)
			{
			weizhi[0][zong] = 5;
			}
	for (zong = 0; zong <= 20; zong++)
			{
			weizhi[20][zong] = 5;
			}

	
	int x = 3;
	MOUSEMSG m;																	       //���������Ϣ
	while (MouseHit()  )															   //����������ڼ�⵱ǰ�Ƿ��������Ϣ
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)				                                   //����������������������Ӧ�����������֣�
		{
			a = m.x / B*B;														       //Բ�����꣬����40����40��֤�õ�40�ı���������������
			b = m.y / B*B; 
			for (zong = 1; zong < 20; zong++)                                          //��ٽ��ִ���,ǰ�ֶԷ������ӣ��ڱ��������ָ���Ӧֵ���´��ܱ���
				{
				for (heng = 1; heng < 20; heng++)
					{
						if ((a >= 40 && a <= 760 && b >= 40 && b <= 760) && (weizhi[zong][heng] == 4 || weizhi[zong][heng] == 3)
							&& (weizhi[a / B][b / B] != 3 && weizhi[a / B][b / B] != 4))
							//����������λ�õ�����ӣ���ٽ���λ���л�Ϊ���0��
						{
							weizhi[zong][heng] = 0;
							if (weizhi[zong][heng] == 0)
							{
								_stprintf_s(bai, _T("%d"), 0);                                     //////																
								outtextxy(zong*B - x, heng*B - 7, bai);                          /////////}
							}
							continue;
						}
				     }
			    }
			
			if (m.x >800 && m.x < 1450 && m.y > 400 && m.y <800)                         //PASS��ť
			{
				i++;
				pass();
				for (zong = 1; zong < 20; zong++)                                          //��ٽ��ִ���,ǰ�ֶԷ������ӣ��ڱ��������ָ���Ӧֵ���´��ܱ���
				{
					for (heng = 1; heng < 20; heng++)
					{
						if ((a >= 40 && a <= 760 && b >= 40 && b <= 760) && (weizhi[zong][heng] == 4 || weizhi[zong][heng] == 3)
							&& (weizhi[a / B][b / B] != 3 && weizhi[a / B][b / B] != 4))
							//����������λ�õ�����ӣ���ٽ���λ���л�Ϊ���0��
						{
							weizhi[zong][heng] = 0;
							if (weizhi[zong][heng] == 0)
							{
								_stprintf_s(bai, _T("%d"), 0);                                     //////																
								outtextxy(zong*B - x, heng*B - 7, bai);                          /////////}
							}
							continue;
						}
					}
				}
				//jinshou();
			}
			
			else if (weizhi[a / B][b / B] == 1 || weizhi[a / B][b / B] == 2 || weizhi[a / B][b / B] == 3 || weizhi[a / B][b / B] == 4 )          //�ڽ���λ�õ����Ч
			{
				jinshou();
				//pass();
					if(weizhi[a / B][b / B] == 3)
						{
							weizhi[a / B][b / B] = 3;
						}
					if (weizhi[a / B][b / B] == 4)
						{
							weizhi[a / B][b / B] = 4;
						}
					if (weizhi[a / B][b / B] == 5)
						{
							weizhi[a / B][b / B] = 5;
						}
				//i--;
				continue;
			}

			

			else
			{
				/********׼����������� Dead_Or_Live(int x , int y ,int kong)����ɱ����㺯������������true�����½���,���� false ������ continue***************************

				bool=Dead_Or_Live(int mx , int my);            // return  0 or 1;

				********׼����������� Dead_Or_Live(int mx , int my)����ɱ����㺯������������1�����½���,����0 ������ continue***************************/

				/*	switch (weizhi[a / 40][b / 40])                                           //�������µĿ�ֵ3��4�ж��ܲ����½�ȥ
				{
				case 3:
				{
					sihuo = Dead_Or_Live(a / B, b / B, 3);
					if (sihuo == 1)
					{
						weizhi[a / 40][b / 40] = 0;
						break;
					}
					else
					{
						weizhi[a / 40][b / 40] = 3;
						jinshou();
						continue;
					}
				}
				case 4:
				{
					sihuo = Dead_Or_Live(a / B, b / B, 4);
					if (sihuo == 1)
					{
						weizhi[a / 40][b / 40] = 0;
						break;
					}
					else
					{
						weizhi[a / 40][b / 40] = 4;
						jinshou();
						continue;
					}
				}
				default:
					break;
				}

				*********************************************************************************************************************/

				if (a >= 40 && a <= 760 && b >= 40 && b <= 760)                          //��¼λ��״̬,��������ʵ�ֽ���
				{
					 if (i % 2 == 0 &&  weizhi[a / B][b / B] != 5 && ((weizhi[a / B][b / B] == 0) || (weizhi[a / B][b / B] != 3) || weizhi[a / B][b / B] == 6))
				    //�����ж������������㷨����������2��������ֻ��0��1����Ӧ�������
					//if (i % 2 == 0 && (weizhi[a / B][b / B] == 0))                        //д�ú���������Ͳ��ø��ӵ��߼�������
					{
						weizhi[a / 40][b / 40] = 2;                                        //��¼λ�õ�״̬��0Ϊû�����ӣ�1Ϊ�к����ӣ�2Ϊ�а�ɫ����
						setlinecolor(WHITE);
						setfillcolor(WHITE);
						fillcircle(a, b, RQ);
						//_stprintf_s(bai, _T("%d"), 2);
						//outtextxy(bai1[i] - x, bai2[i] - 7, bai);                          //д���岽��
						//putimage(a - 20, b - 20, &img_go_b, NOTSRCERASE);
						//putimage(a - 20, b - 20, &img_go_bk, SRCINVERT);    // 
						//FlushBatchDraw();  //

						bai1[i] = a;    //                                                 //���������
						bai2[i] = b;	//												   //���������� 

						addrss[i][0] = a / B;
						addrss[i][1] = b / B;

						setbkcolor(WHITE);												   //���ֱ���   
						settextcolor(BLACK);                                               //������ɫ
						//_stprintf_s(bai, _T("%d"), i);                                   //�Ѳ������ֱ���ַ�����һ����ʾ�ַ� 
						_stprintf_s(bai, _T("%d"), 2);                                     //////
						//if (i >= 10)
						//	x = 7;
						outtextxy(bai1[i] - x, bai2[i] - 7, bai);                          //д���岽��

									for (heng = 0; heng <= 20; heng++)                     //������ΧһȦ��ֵ���л�Ϊ���ӷ�
										{
										weizhi[heng][0] = 2;
										}
									for (heng = 0; heng <= 20; heng++)
										{
										weizhi[heng][20] = 2;
										}
									for (zong = 0; zong <= 20; zong++)
										{
										weizhi[0][zong] = 2;
										}
									for (zong = 0; zong <= 20; zong++)
										{
										weizhi[20][zong] = 2;
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

									/*if(weizhi[a/B-1][b/B] != 0 && weizhi[a / B + 1][b / B] != 0 && weizhi[a / B][b / B + 1] != 0 && weizhi[a / B][b / B - 1] != 0)
										for (heng = 0; heng <= 20; heng++)                     //������ΧһȦ��ֵ���л�Ϊ���ӷ�
										{
											weizhi[heng][0] = 1;
										}
										for (heng = 0; heng <= 20; heng++)
										{
											weizhi[heng][20] = 1;
										}
										for (zong = 0; zong <= 20; zong++)
										{
											weizhi[0][zong] = 1;
										}
										for (zong = 0; zong <= 20; zong++)
										{
											weizhi[20][zong] = 1;
										}*/
						luozi();
						TCHAR s13[] = _T("��һ�֣�����");
						setbkcolor(RGB(220, 180, 70));
						outtextxy(1000, 400, s13);
						setlinecolor(BLACK);
						setfillcolor(BLACK);
						fillcircle(1120, 410, 10);
						_stprintf_s(hong, _T("%d"), i);
						settextcolor(WHITE);
						outtextxy(1000, 380, hong);                     
						i++;
						//huaxian();                                                                   /////////////////////////////////////
						setlinecolor(WHITE);
						setfillcolor(WHITE);
						fillcircle(a, b, RQ);
						setbkcolor(WHITE);												   //���ֱ���   
						settextcolor(BLACK);                                               //������ɫ
						_stprintf_s(bai, _T("%d"), 2);
						outtextxy(a - x, b - 7, bai);                                      //д���岽��
						/**********����Ӧ���Ǵ����Ƿ����ӵ�ʱ��*************************************************************************************************
						for (zong = 1; zong < 20; zong++)
						{
							for (heng = 1; heng < 20; heng++)
							{
								if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
								{
									getimage(&img, 1020, 60, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 4;                                      //�Ե�һ���ӣ������Ե����ȸ�ֵΪ4�����λ�ò����������ӣ�
									weizhi[a / 40][b / 40] = 6;                                   //�����µ�����λ����ʱ������Ϊ��Ӧֵ����һ���Զ����
									//_stprintf_s(bai, _T("%d"), 4);           //
									//outtextxy(zong*B - x, heng*B - 7, bai);  //
                                     
									//tizi(a/B ,b/B,2);                                             //���������

											if ((zong ==  4 && heng ==  4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
											{
												getimage(&img, 1020, 100, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
											{
												getimage(&img, 1020, 100, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
											{
												getimage(&img, 1020, 100, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (heng*B == 40&& zong*B!=40&&zong*B!=760)					 //�ϱ�
											{
												getimage(&img, 1020, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}

											else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
											{
												getimage(&img, 1020, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
											{
												getimage(&img, 980, 60, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
											{
												getimage(&img, 1180, 60, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
											{
												getimage(&img, 980, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
											{
												getimage(&img, 1180, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 760 && heng*B == 760)                             //���½�                      
											{
												getimage(&img, 1180, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B == 760)                              //���½�
											{
												getimage(&img, 980, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}

									_stprintf_s(bai, _T("%d"), 4);           //
									outtextxy(zong*B - x, heng*B - 7, bai);  //

								}

								  else if (((weizhi[zong][heng] == 1 ) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 5))
								  {//��
									  getimage(&img, 1020, 20, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] =4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									  //tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 2))
								  {//��
									  getimage(&img, 1020, 180, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									  //tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
								  {//��
									  getimage(&img, 980, 60, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									  //tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
								  {//��
									  getimage(&img, 1180, 60, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									 // tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 5))
								  {//��
									  getimage(&img, 980, 20, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									 // tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 2))
								  {//��
									  getimage(&img, 1180, 180, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									  //tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 2))
								  {//��
									  getimage(&img, 980, 180, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									//  tizi(a/B ,b/B);

								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 5))
								  {//��
									  getimage(&img, 1180, 20, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									 // tizi(a/B ,b/B);

								  }
								// else 
								//  {
								//	  tizi(a / B, b / B, 2);
								//  }
						}
					 }*/
					//i++;
				}
					/****�������Ӵ��˼·�ǽ���Χ����һ·�����ݺ�ڶ�ʮ·��ȫ����ֵΪ5�������ʱ��ֱ�ӵ��þ��У��ܱ������Ǵ�0��800��������һ����ά�����ʾ***/
					/****�ĸ�����ʱ��û�д���***************************************************************************************************************/

					else if (i % 2 == 1 && weizhi[a / B][b / B] != 6 && ((weizhi[a / B][b / B] == 0) || (weizhi[a / B][b / B] != 4) || weizhi[a / B][b / B] == 5))
						                                                                    //�����ж�
					{ 
						weizhi[a / 40][b / 40] = 1;                                        //��¼λ�õ�״̬��1Ϊ�к����ӣ�0Ϊû�����ӣ�2Ϊ�а�ɫ����

						setlinecolor(RGB(30, 30, 30));
						setfillcolor(RGB(30, 30, 30));
						fillcircle(a, b, RQ);

						hong1[i] = a;                                                      //���������
						hong2[i] = b;													   //���������� 

						addrss[i][0] = a / B;
						addrss[i][1] = b / B;

						setbkcolor(RGB(30, 30, 30));									   //���ֱ���   
						settextcolor(WHITE);                                               //������ɫ
						//_stprintf_s(hong, _T("%d"), i);                                  //�Ѳ������ֱ���ַ�����һ����ʾ�ַ� 
						_stprintf_s(hong, _T("%d"), 1);
						//if (i >= 10)
						//	x = 7;
						outtextxy(hong1[i] - x, hong2[i] - 7, hong);                       //д���岽��
							for (heng = 0; heng <= 20; heng++)                             //������ΧһȦ��ֵ���л�Ϊ���ӷ�
								{
									weizhi[heng][0] = 1;
								}
							for (heng = 0; heng <= 20; heng++)
								{
									weizhi[heng][20] = 1;
								}
							for (zong = 0; zong <= 20; zong++)
								{
									weizhi[0][zong] = 1;
								}
							for (zong = 0; zong <= 20; zong++)
								{
									weizhi[20][zong] = 1;
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

								/*if (weizhi[a / B - 1][b / B] != 0 && weizhi[a / B + 1][b / B] != 0 && weizhi[a / B][b / B + 1] != 0 && weizhi[a / B][b / B - 1] != 0)
									for (heng = 0; heng <= 20; heng++)                     //������ΧһȦ��ֵ���л�Ϊ���ӷ�
									{
										weizhi[heng][0] = 2;
									}
									for (heng = 0; heng <= 20; heng++)
									{
										weizhi[heng][20] = 2;
									}
									for (zong = 0; zong <= 20; zong++)
									{
										weizhi[0][zong] = 2;
									}
									for (zong = 0; zong <= 20; zong++)
									{
										weizhi[20][zong] = 2;
									}*/
						luozi();
						TCHAR s13[] = _T("��һ�֣�����");
						setbkcolor(RGB(220, 180, 70));
						outtextxy(1000, 400, s13);
						setlinecolor(WHITE);
						setfillcolor(WHITE);
						fillcircle(1120, 410, 10);
						_stprintf_s(hong, _T("%d"), i);
						settextcolor(BLACK);
						outtextxy(1000, 380, hong);                                             //д���岽��

						i++;

						//huaxian();
						setlinecolor(RGB(30, 30, 30));
						setfillcolor(RGB(30, 30, 30));
						fillcircle(a, b, RQ);
						setbkcolor(RGB(30, 30, 30));									       //���ֱ���   
						settextcolor(WHITE);												   //������ɫ
						_stprintf_s(hong, _T("%d"), 1);
						outtextxy(a - x, b - 7, hong);										   //д���岽��

						/*for (zong = 1; zong < 20; zong++)
						{
							for (heng = 1; heng < 20; heng++)
							{

								if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
								{
									getimage(&img, 1020, 60, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									//_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									//outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //tizi(a/B ,b/B);                                    //���������

									if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
									{
										getimage(&img, 1020, 100, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
									{
										getimage(&img, 1020, 100, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
									{
										getimage(&img, 1020, 100, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //�ϱ�
									{
										getimage(&img, 1020, 20, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}

									else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
									{
										getimage(&img, 1020, 180, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
									{
										getimage(&img, 980, 60, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
									{
										getimage(&img, 1180, 60, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
									{
										getimage(&img, 980, 20, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
									{
										getimage(&img, 1180, 20, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 760 && heng*B == 760)                             //���½�                      
									{
										getimage(&img, 1180, 180, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 40 && heng*B == 760)
									{
										getimage(&img, 980, 180, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}

							_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
							outtextxy(zong*B - x, heng*B - 7, bai);			     //

							}
								/*
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 5))
								{//��
									getimage(&img, 1020, 20, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 // tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 1))
								{//��
									getimage(&img, 1020, 180, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 // tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
								{//��
									getimage(&img, 980, 60, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
								{//��
									getimage(&img, 1180, 60, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 5))
								{//���Ͻ�
									getimage(&img, 980, 20, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 1))
								{//���½�
									getimage(&img, 1180, 180, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 1))
								{//���½�
									getimage(&img, 980, 180, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 5))
								{//���Ͻ�
									getimage(&img, 1180, 20, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 // tizi(a/B ,b/B);
								}

								else  
								{
									tizi(a / B, b / B, 1);
								    for (int k = 0; k <= Bsizi; k++)
									{
									weizhi[addrss[k][0]][addrss[k][1]] = 0;
									getimage(&img, 1020, 60, 40, 40);
									putimage(addrss[k][0] * B - 20, addrss[k][1] * B - 20, &img);
									}
									//���￼�Ǳ߽ǲ���ͼ���
									//Bsizi = 0;
									mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
									mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
									mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																															   // }
								}
								
							}
						}*/

						 // i++;                                                                //��¼����
					}
				}
				else if (m.x > 1300 && m.x < 1340 && m.y > 40 && m.y < 80)                      //�˳���ť                       
				{
						cleardevice();
						fflush(stdout);
						closegraph();
						main();
				}

			
				FlushBatchDraw();													             //����ǰ��ͼ�Σ�����ˢ������	
				continue;                                    /////////////////////////////////////////////////////
			}	
		}
		/*************************************************************************************************************

		**************************************************************************************************************/
		else if (m.uMsg == WM_RBUTTONDOWN)                                              //����Ҽ����£�����
		{
			if (i % 2 == 1)
			{
				weizhi[bai1[i - 1] / 40][bai2[i - 1] / 40] = 0;                         //���ʱ�ǲ��ӱ���i�Ѿ����ӣ�����һ��Ҫ-1;

				getimage(&img, 1020, 60, 40, 40);                                       //���塢�������Ӻ�ò���ʮ��
				putimage(bai1[i - 1] - 20, bai2[i - 1] - 20, &img);                     //��Ҫȡ�øղ����ӵ�����

				jinshou();
				i--;
			}
			else if (i % 2 == 0)
			{
				weizhi[hong1[i - 1] / 40][hong2[i - 1] / 40] = 0;

				getimage(&img, 1020, 60, 40, 40);                                       //���塢�������Ӻ�ò���ʮ��
				putimage(hong1[i - 1] - 20, hong2[i - 1] - 20, &img);                   //��Ҫȡ�øղ����ӵ�����

				i--;
				jinshou();
			}
		}
			/*you_a = m.x / B*B;
			you_b = m.y / B*B;
			/////////////////////////////////////////////////////////////////////////////////
			if (you_a >= 80 && you_a <= 720 && you_b >= 80 && you_b <= 720 && (weizhi[you_a / 40][you_b / 40] != 0))
			{
				getimage(&img, 1020, 60, 40, 40);                                               	//���塢�������Ӻ���ʮ�֣�����������̲��ô���ĵط�����������ô���ܶ�
				putimage(you_a - 20, you_b - 20, &img);
				weizhi[you_a / 40][you_b / 40] = 0;
				if ((you_a == B * 4 && you_b == B * 4) || (you_a == B * 10 && you_b == B * 4) || (you_a == B * 16 && you_b == B * 4))	      //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(you_a - 20, you_b - 20, &img);
				}
				else if ((you_a == B * 4 && you_b == B * 10) || (you_a == B * 10 && you_b == B * 10) || (you_a == B * 16 && you_b == B * 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(you_a - 20, you_b - 20, &img);
				}
				else if ((you_a == B * 4 && you_b == B * 16) || (you_a == B * 10 && you_b == B * 16) || (you_a == B * 16 && you_b == B * 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(you_a - 20, you_b - 20, &img);
				}
				i--;
			
			****************************************************************************************************************
			*���̱�Ե�����߳�ͷ
			*��һ�Ա��취����������λ��һ����ÿ�β�����Χ������
			*������������һ�����ӵ�ʱ���������Ӷ���������һ�룬ɵ���ˣ�����ֻҪ�������������ӵ����򱳾���ɫ����
			*�ٺ����ַ��֣�����һ��������߾����ˣ�����д�����򵥡���׼ȷ
			*����ö�Ӧ��ͼ���Ǿ���
			*�򵥵���������෽��������ɣ��������������صķ����ͺ���
			*��˸��������ı��ʺ���Ҫ������������ĵ㣬������ͨ����������������ǵ������������Ӻܶ಻˵��������δ֪����
			****************************************************************************************************************
											else if (heng*B == 40&& zong*B!=40&&zong*B!=760)					 //�ϱ�
											{
												getimage(&img, 1020, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}

											else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
											{
												getimage(&img, 1020, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
											{
												getimage(&img, 980, 60, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
											{
												getimage(&img, 1180, 60, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
											{
												getimage(&img, 980, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
											{
												getimage(&img, 1180, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 760 && heng*B == 760)                             //���½�                      
											{
												getimage(&img, 1180, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B == 760)                              //���½�
											{
												getimage(&img, 980, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
			//i--;                                                                          //ǰ�沽����Ч
		}*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	
		FlushBatchDraw();
		/* ***********************************************************************************************************
		�߽��ͷ�Ƚ��Ѵ�����������
		else if (m.uMsg == WM_RBUTTONDOWN)
		{
			a = m.x / B*B;
			b = m.y / B*B;
			if (b = 40)
				{
				getimage(&img, 1020, 20, 40, 40);
				putimage(a - 20, b - 20, &img);													  //�˷������ڽ�ȡ��Ӧ��ͼƬ����
				}
		
			if (b = 40)
				{
				getimage(&img, 1020, 20, 40, 40);
				putimage(a - 20, b - 20, &img);
				}
		}
		**********************************************************************************************************************/
	}
}

void huitu()                                                                           //ͼ�ν������
{
	//int c = 150;                                                                     //��ɫֵ
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
	TCHAR s4[] = _T(" (3)���Ҽ�����;");
	TCHAR s5[] = _T(" (4)�����ո�����̣�");
	TCHAR s6[] = _T(" (5)���ʵ�λ�ã������");
	TCHAR s7[] = _T(" (6)����a���ָ����֣�d��ͣ��");
	TCHAR s8[] = _T(" PASS");
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
	//_stprintf_s(bai, "%d", 3);                                                      //  ������ת��Ϊ�ַ���
	//outtextxy(zong*B - 3, heng*B - 7, bai);			                              //

	

	FlushBatchDraw();																   //Easy-x��ͼ�⺯�������̸���	

}

void luozi()
{
	mciSendString(_T("close  gemusic"), NULL, 0, NULL);               // �����������Ȱ�ǰ��һ�ε����ֹر�  
	mciSendString(_T("open ./music/stone.mp3 alias gemusic"), NULL, 0, NULL);                                // ������
	mciSendString(_T("play gemusic"), NULL, 0, NULL);                  // ������һ��
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

void jia_yan_b()                                                                     //������ �����һ������
{
	int x, y;
	for (x = 1; x <= 19; x++)
		{
			for (y = 1; y <= 19; y++) 
			{

				/*if  ( ( weizhi[x][y] == 5 )
					&& (( weizhi[x - 1][y-1] == 2 && weizhi[x + 1][y-1] == 2 && weizhi[x][y-2] == 2 )       //�ϰ�Χ
					|| (  weizhi[x - 1][y-1] == 2 && weizhi[x - 1][y+1] == 2 && weizhi[x-2][y] == 2 )       //���Χ
					|| (  weizhi[x - 1][y+1] == 2 && weizhi[x + 1][y+1] == 2 && weizhi[x][y+2] == 2 )       //�°�Χ
					|| (  weizhi[x + 1][y+1] == 2 && weizhi[x + 1][y-1] == 2 && weizhi[x+2][y] == 2 ))  )   //�Ұ�Χ
					*/
				if ((weizhi[x][y] == 1)
					&& (weizhi[x - 1][y] == 2 && weizhi[x][y - 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y + 1] == 5)           //�������±�
					|| (weizhi[x][y - 1] == 2 && weizhi[x][y + 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x - 1][y] == 5)         //���������
					|| (weizhi[x - 1][y] == 2 && weizhi[x][y + 1] == 2 && weizhi[x][y - 1] == 2 && weizhi[x + 1][y] == 5)     //   �������ұ�
					|| (weizhi[x - 1][y] == 2 && weizhi[x][y + 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y - 1] == 5))   // �������ϱ�
					for (x = 1; x <= 19; x++)
					{
						for (y = 1; y <= 19; y++)
						{
							if (weizhi[x][y] == 5)
							{
								weizhi[x][y] = 10;
								_stprintf_s(bai, _T("%d"), 10);                                     //////																
								outtextxy(x*B - 7, y*B - 7, bai);
								//FlushBatchDraw();
							}
						}
					}
			}
		}	
}

void jia_yan_w()
{
	for (int x = 1; x <= 19; x++)
	{
		for (int y = 1; y <= 19; y++)
		{
			if ((weizhi[x][y] == 2)
				&& (weizhi[x - 1][y] == 1 && weizhi[x][y - 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y + 1] == 6)           //�������±�
				|| (weizhi[x][y - 1] == 1 && weizhi[x][y + 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x - 1][y] == 6)         //���������
				|| (weizhi[x - 1][y] == 1 && weizhi[x][y + 1] == 1 && weizhi[x][y - 1] == 1 && weizhi[x + 1][y] == 6)     //   �������ұ�
				|| (weizhi[x - 1][y] == 1 && weizhi[x][y + 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y - 1] == 6))   // �������ϱ�
				for (x = 1; x <= 19; x++)
				{
					for (y = 1; y <= 19; y++)
					{
						if (weizhi[x][y] == 6)
						{
							weizhi[x][y] = 9;
							_stprintf_s(bai, _T("%d"), 9);                                     //////																
							outtextxy(x*B - 3, y*B - 7, bai);
							//FlushBatchDraw();
						}
					}
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
			if ((weizhi[x][y] == 0||weizhi[x][y] == 10) && (weizhi[x - 1][y] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y - 1] == 1 && weizhi[x][y + 1] == 1))
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
			if ((weizhi[x][y] == 0|| weizhi[x][y] == 9) && (weizhi[x - 1][y] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y - 1] == 2 && weizhi[x][y + 1] == 2))
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
}

void Eat_more_than_one_w()
{    
	//int B_dead = 0;																		       //��������������ÿ�ι�1
	//int W_dead = 0;																		       //��������������ÿ�ι�1
	int x, y;
	int i=0;
	//int SamB_dead = 0;																		   //�����ܹ���������
	//int W_dead = 0;																		   //�����ܹ���������
	TCHAR s13[] = _T("����ǰ����   �ڷ�����-             �׷�����-    ");
	setbkcolor(RGB(220, 180, 70));
	outtextxy(1000, 360, s13);
	_stprintf_s(hong, _T("%d"), W_dead);                                           //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
	outtextxy(1170, 360, hong);
	_stprintf_s(hong, _T("%d"), B_dead);                                           //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
	outtextxy(1320, 360, hong);
	FlushBatchDraw();
	
	for (x = 1; x <= 19; x++)
	{	
		for (y = 1; y <= 19; y++)
		{
			/*else if (weizhi[x][y] == 1 && weizhi[x - 1][y] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y - 1] == 2 && weizhi[x][y + 1] == 2)
			{
			weizhi[x][y] = 2;
			adss[i][0] = x*B;
			adss[i][1] = y*B;
			SamW_dead += i;
			getimage(&img, 1020, 60, 40, 40);                                                     ///////////////////�۲�Ч����;
			putimage(x*B - 20, y*B - 20, &img);                                                   /////////////////////�۲�Ч����;
			}*/
			
				

			 if((weizhi[x][y] == 2 && weizhi[x - 1][y] != 0 && weizhi[x + 1][y] != 0 && weizhi[x][y - 1] != 0 && weizhi[x][y + 1] != 0)
				    &&(weizhi[x - 1][y] == 2 || weizhi[x + 1][y] == 2 || weizhi[x][y - 1] == 2 || weizhi[x][y + 1] == 2)
				    && (weizhi[x - 1][y] != 2 || weizhi[x + 1][y] != 2 || weizhi[x][y - 1] != 2 || weizhi[x][y + 1] != 2))
				{
				weizhi[x][y] = 8;
				adss[i][0] = x*B;
				adss[i][1] = y*B;
				i++;
				//W_dead++;
				//SamW_dead++;
				//getimage(&img, 1020, 60, 40, 40);                                ///////////////////�۲�Ч����;
				//putimage(x*B - 20, y*B - 20, &img);                             /////////////////////�۲�Ч����;
				_stprintf_s(hong, _T("%d"), 8);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
				outtextxy(x*B-3, y*B-7, hong);                                  //д����
				Eat_more_than_one_w();                                            //////////////////��ʼ�ݹ�ѭ��,  ���ڴ��ط��֣���겻���������һֱ����
				}
			
			 else if ((weizhi[x][y] == 2 && weizhi[x - 1][y] != 0 && weizhi[x + 1][y] != 0 && weizhi[x][y - 1] != 0 && weizhi[x][y + 1] != 0)
				 &&
				 (weizhi[x - 1][y] == 8 || weizhi[x + 1][y] == 8 || weizhi[x][y - 1] == 8 || weizhi[x][y + 1] == 8)
				 &&
				 (weizhi[x - 1][y] != 2 || weizhi[x + 1][y] != 2 || weizhi[x][y - 1] != 2 || weizhi[x][y + 1] != 2)
				 &&
				 (weizhi[x - 1][y] != 4 && weizhi[x + 1][y] != 4 && weizhi[x][y - 1] != 4 && weizhi[x][y + 1] != 4))

				 {
				 weizhi[x][y] = 8;
				 adss[i][0] = x*B;
				 adss[i][1] = y*B;
				 //Eat_more_than_one();                                                             //������������
				 //W_dead++;
				 //SamW_dead = SamW_dead + W_dead;
				 exit;
				
			 }

			//W_dead = i;
			//SamW_dead += i;
			else  if( weizhi[x][y] == 2 && (weizhi[x - 1][y] == 0 || weizhi[x + 1][y] == 0 || weizhi[x][y - 1] == 0 || weizhi[x][y + 1] == 0)
			        && (weizhi[x - 1][y] ==8 || weizhi[x + 1][y] == 8 || weizhi[x][y - 1] == 8 || weizhi[x][y + 1] == 8))
				{
					exit;
				}
		}
	}		
}

void Eat_more_than_one_b()
{

}

void chizhi_w()
{
	/*for (zong = a / B - 1, heng = b / B; zong >= 1; zong--)
	{
		if ((weizhi[zong][heng] == 2) && (weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
		{
			getimage(&img, 1020, 60, 40, 40);
			putimage(zong*B - 20, heng*B - 20, &img);
			weizhi[zong][heng] = 3;
			//weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
			//_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
			//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
			if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //�ϱ�
			{
				getimage(&img, 1020, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
			{
				getimage(&img, 1020, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
			{
				getimage(&img, 980, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
			{
				getimage(&img, 1180, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
			{
				getimage(&img, 980, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
			{
				getimage(&img, 1180, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 760)                             //���½�
			{
				getimage(&img, 1180, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 760)
			{
				getimage(&img, 980, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
			mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
			mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																										// }
			_stprintf_s(bai, _T("%d"), 3);                                      //���Լ�¼�ã���ɾ��
			outtextxy(zong*B - 3, heng*B - 7, bai);			                    //

			W_dead++;
		}
	
	}
	for (zong = a / B + 1, heng = b / B; zong <= 19; zong++)
	{
		if ((weizhi[zong][heng] == 2) && (weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
		{
			getimage(&img, 1020, 60, 40, 40);
			putimage(zong*B - 20, heng*B - 20, &img);
			weizhi[zong][heng] = 3;
			//weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
			//_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
			//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
			if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //�ϱ�
			{
				getimage(&img, 1020, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
			{
				getimage(&img, 1020, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
			{
				getimage(&img, 980, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
			{
				getimage(&img, 1180, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
			{
				getimage(&img, 980, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
			{
				getimage(&img, 1180, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 760)                             //���½�
			{
				getimage(&img, 1180, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 760)
			{
				getimage(&img, 980, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
			mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
			mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																										// }
			_stprintf_s(bai, _T("%d"), 3);                                      //���Լ�¼�ã���ɾ��
			outtextxy(zong*B - 3, heng*B - 7, bai);			                    //
			W_dead++;
		}
		
	}

	for (heng = b / B - 1; heng >= 1; heng--)
		for (zong = 1; zong <= 19; zong++)
		{
			if ((weizhi[zong][heng] == 2) && (weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
			{
				getimage(&img, 1020, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
				weizhi[zong][heng] = 3;
				//weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
				//_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //�ϱ�
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //���½�
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																											// }
				_stprintf_s(bai, _T("%d"), 3);                                      //���Լ�¼�ã���ɾ��
				outtextxy(zong*B - 3, heng*B - 7, bai);			                    //

				W_dead++;
			}	
		}

	for (heng = b / B + 1; heng <= 19; heng++)
		for (zong = 1; zong <= 19; zong++)
		{
			if ((weizhi[zong][heng] == 2) && (weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
			{
				getimage(&img, 1020, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
				weizhi[zong][heng] = 3;
				//weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
				//_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //�ϱ�
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //���½�
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																											// }
				_stprintf_s(bai, _T("%d"), 3);                                      //���Լ�¼�ã���ɾ��
				outtextxy(zong*B - 3, heng*B - 7, bai);			                    //

				W_dead++;
			}
			
		}*/

	for (zong = 1; zong <= 19; zong++)
	{
		for (heng = 1; heng <= 19; heng++)
		{
			if ((weizhi[zong][heng] == 2) && (weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
			{
				getimage(&img, 1020, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
				weizhi[zong][heng] = 3;
				//weizhi[a / 40][b / 40] = 7;                          //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
				//_stprintf_s(bai, _T("%d"), 3);                       //���Լ�¼�ã���ɾ��
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //�ϱ�
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //���½�
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																											// }
				_stprintf_s(bai, _T("%d"), 3);                                      //���Լ�¼�ã���ɾ��
				outtextxy(zong*B - 3, heng*B - 7, bai);			                    //
				W_dead++;
			}
			
			
		}
	}
}

void shuaxin_w() 
{
	int x, y;
	for (x = 19; x >= 1; x--)
	{
		for (y = 19; y >= 1; y--)
		{
		
			if ((weizhi[x][y] == 8) && (weizhi[x - 1][y] != 2 && weizhi[x + 1][y] != 2 && weizhi[x][y - 1] != 2 && weizhi[x][y + 1] != 2) 
				&& (weizhi[x - 1][y] != 4 && weizhi[x + 1][y] != 4 && weizhi[x][y - 1] != 4 && weizhi[x][y + 1] != 4))
					{
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
									W_dead++;                                                              //��������
								}
							}
						}
						/*for (int j = 0; j <= i; j++)
						{

						weizhi[adss[j][0] / B][adss[j][1] / B] = 0;
						_stprintf_s(hong, _T("%d"), 7);                                               //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�
						outtextxy(adss[i][0] - 3, adss[i][1] - 7, hong);                              //д����
						getimage(&img, 1020, 60, 40, 40);                                             ///////////////////�۲�Ч����;
						putimage(adss[j][0] - 20, adss[j][1] - 20, &img);                             /////////////////////�۲�Ч����;
						//FlushBatchDraw();
						}

						_stprintf_s(hong, _T("%d"), SamW_dead);                                           //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�
						outtextxy(1150, 360, hong);                                                        //д����       */
						luozi();
						exit;

					}
			else if ((weizhi[x][y] == 8) && (weizhi[x - 1][y] == 2 || weizhi[x + 1][y] == 2 || weizhi[x][y - 1] == 2 || weizhi[x][y + 1] == 2))
						{
						//setlinecolor(WHITE);
						//setfillcolor(WHITE);
						//fillcircle(x, y, RQ);                                                  //������/////////////////////////////////////////

							weizhi[x][y] = 2;
							_stprintf_s(hong, _T("%d"), 2);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
							outtextxy(x*B - 3, y*B - 7, hong);                                      //д����
						}
		}
	}	
}

void shuaxin_b()
{
	    /*
			 if( (weizhi[x][y] == 7) && (weizhi[x - 1][y] == 1 || weizhi[x + 1][y] == 1 || weizhi[x][y - 1] == 1 || weizhi[x][y + 1] == 1))
					{
							//setlinecolor(BLACK);
							//setfillcolor(BLACK);
							//fillcircle(x, y, RQ);                                                  //������/////////////////////////////////////////
							weizhi[x][y] = 1;
							_stprintf_s(hong, _T("%d"), 1);                                        //�Ѳ������ֱ���ַ�����һ����ʾ�ַ�  
							outtextxy(x*B - 3, y*B - 7, hong);                                     //д����
					}
		*/
}

void chizhi_b()
{

	/*for (zong = a / B - 1, heng = b / B; zong >= 1; zong--)
	{
		
	          if (((weizhi[zong][heng] == 1) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
		{
			getimage(&img, 1020, 60, 40, 40);
			putimage(zong*B - 20, heng*B - 20, &img);
			weizhi[zong][heng] = 4;
			//weizhi[a / 40][b / 40] = 7;                                       //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
			//_stprintf_s(bai, _T("%d"), 4);                                   //���Լ�¼�ã���ɾ��
			//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
			if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //�ϱ�
			{
				getimage(&img, 1020, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
			{
				getimage(&img, 1020, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
			{
				getimage(&img, 980, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
			{
				getimage(&img, 1180, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
			{
				getimage(&img, 980, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
			{
				getimage(&img, 1180, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 760)                             //���½�                      
			{
				getimage(&img, 1180, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 760)
			{
				getimage(&img, 980, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
			mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
			mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																										// }
			_stprintf_s(bai, _T("%d"), 4);                                                      //���Լ�¼�ã���ɾ��
			outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //

			B_dead++;
		}
	}
	for (zong = a / B + 1, heng = b / B; zong <= 19; zong++)
	{
		
		      if (((weizhi[zong][heng] == 1) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
		{
			getimage(&img, 1020, 60, 40, 40);
			putimage(zong*B - 20, heng*B - 20, &img);
			weizhi[zong][heng] = 4;
			//weizhi[a / 40][b / 40] = 7;                                       //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
			//_stprintf_s(bai, _T("%d"), 4);                                   //���Լ�¼�ã���ɾ��
			//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
			if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
			{
				getimage(&img, 1020, 100, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //�ϱ�
			{
				getimage(&img, 1020, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
			{
				getimage(&img, 1020, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
			{
				getimage(&img, 980, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
			{
				getimage(&img, 1180, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
			{
				getimage(&img, 980, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
			{
				getimage(&img, 1180, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 760)                             //���½�                      
			{
				getimage(&img, 1180, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 760)
			{
				getimage(&img, 980, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
			mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
			mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																										// }
			_stprintf_s(bai, _T("%d"), 4);                                                      //���Լ�¼�ã���ɾ��
			outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //
			B_dead++;																					//tizi(a/B ,b/B);     //���������
		}
	}

	for (heng = b / B - 1; heng >= 1; heng--)
		for (zong = 1; zong <= 19; zong++)
		{
			
			 if (((weizhi[zong][heng] == 1) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
			{
				getimage(&img, 1020, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
				weizhi[zong][heng] = 4;
				//weizhi[a / 40][b / 40] = 7;                                       //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
				//_stprintf_s(bai, _T("%d"), 4);                                   //���Լ�¼�ã���ɾ��
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			     //�ϱ�
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //���½�                      
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																											// }
				_stprintf_s(bai, _T("%d"), 4);                                                      //���Լ�¼�ã���ɾ��
				outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //
				B_dead++;																					//tizi(a/B ,b/B);     //���������
			}
		}

	for (heng = b / B + 1; heng <= 19; heng++)
		for (zong = 1; zong <= 19; zong++)
		{
			
			 if (((weizhi[zong][heng] == 1) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
			{
				getimage(&img, 1020, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
				weizhi[zong][heng] = 4;
				//weizhi[a / 40][b / 40] = 7;                                       //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
				//_stprintf_s(bai, _T("%d"), 4);                                   //���Լ�¼�ã���ɾ��
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //�ϱ�
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //���½�                      
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																											// }
				_stprintf_s(bai, _T("%d"), 4);                                                      //���Լ�¼�ã���ɾ��
				outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //
				B_dead++;																					//tizi(a/B ,b/B);     //���������
			}
		}     */

	for (zong = 1; zong <= 19; zong++)
	{
		for (heng = 1; heng <= 19; heng++)
		{
			
			if (((weizhi[zong][heng] == 1) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
			{
				getimage(&img, 1020, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
				weizhi[zong][heng] = 4;
				//weizhi[a / 40][b / 40] = 7;                                       //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
				//_stprintf_s(bai, _T("%d"), 4);                                   //���Լ�¼�ã���ɾ��
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //��������λ����Ҫ����ԭ���׵�*
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 10) || (zong == 10 && heng == 10) || (zong == 16 && heng == 10))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if ((zong == 4 && heng == 16) || (zong == 10 && heng == 16) || (zong == 16 && heng == 16))
				{
					getimage(&img, 1020, 100, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //�ϱ�
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //�±�
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //���
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //�ұ�
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //���Ͻ�
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //���Ͻ�
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //���½�                      
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																											// }
				_stprintf_s(bai, _T("%d"), 4);                                                      //���Լ�¼�ã���ɾ��
				outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //
				B_dead++;											                                       //tizi(a/B ,b/B);     //���������
			}

			
		}
	}
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
			/*srand((unsigned)time(NULL));
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
			setcolor(RGB(b,g,r));
			line(B, y * 40, A, y * 40);	*/										   //���ݺ�ʮ��·
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
			}										   //���Ÿ���λ�ĵ㣬������Ԫ
		}
    }
}

void dao_pu()
{
	int x, y;

			for (x = 1; x <= 19; x++)
			{
				for (y = 1; y <= 19; y++)
				{
					if((weizhi[x][y] == 2 && (weizhi[x - 1][y] == 2 || weizhi[x + 1][y] == 2 || weizhi[x][y - 1] == 2 || weizhi[x][y + 1] == 2))
						&&( weizhi[x - 1][y] == 4 || weizhi[x + 1][y] == 4 || weizhi[x][y - 1] == 4 || weizhi[x][y + 1] == 4))
						for (x = 1; x <= 19; x++)
						
							for (y = 1; y <= 19; y++)
							{

								if (weizhi[x][y] == 4)
								{
									weizhi[x][y] = 0;
									_stprintf_s(bai, _T("%d"), 0);                                                      //���Լ�¼�ã���ɾ��
									outtextxy(x*B - 3, y*B - 7, bai);
								}
						
							}
							                                   
			
				}
			}

			for (x = 1; x <= 19; x++)
			{
				for (y = 1; y <= 19; y++)
				{
					if ((weizhi[x][y] == 1 && (weizhi[x - 1][y] == 1 || weizhi[x + 1][y] == 1 || weizhi[x][y - 1] == 1 || weizhi[x][y + 1] == 1))
						&& (weizhi[x - 1][y] == 3 || weizhi[x + 1][y] == 3 || weizhi[x][y - 1] == 3 || weizhi[x][y + 1] == 3))
						for (x = 1; x <= 19; x++)
						{
							for (y = 1; y <= 19; y++)
							{
								if (weizhi[x][y] == 3)
								{
									weizhi[x][y] = 0;
									_stprintf_s(bai, _T("%d"), 0);                                                      //���Լ�¼�ã���ɾ��
									outtextxy(x*B - 3, y*B - 7, bai);
								}

							}
						}

				}
			}
}

	/* if (who == 2)                                                                             //����
	 {
		 for (zong = 1; zong <= 19; zong++)
		 {
			 for (heng = 1; heng <= 19; heng++)
			 {
				 if ((weizhi[zong][heng] == 1) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2)
				 {
					 /*addrss[Bsizi][0] = zong;                                         
					 addrss[Bsizi][1] = heng;
					 Bsizi++;
					 SamB += Bsizi;
					 if (Bsizi == 1) 
					 { 
							 weizhi[addrss[Bsizi][0]][addrss[Bsizi][1]] = 4;
							 getimage(&img, 1020, 60, 40, 40);
							 putimage(addrss[Bsizi][0] * B - 20, addrss[Bsizi][1] * B - 20, &img);
							 weizhi[x][y] = 6;                                    //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
							 //_stprintf_s(bai, _T("%d"), 4);                       //���Լ�¼�ã���ɾ��
							 outtextxy(zong*B - x, heng*B - 7, bai);			     //
							 //���￼�Ǳ߽ǲ���ͼ���
							 Bsizi = 0;
							 mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
							 mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
							 mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
					 }
					 else if(Bsizi>=2)
					 {
					 for (int k = 0; k <= Bsizi; k++)
					 {
						 weizhi[addrss[k][0]][addrss[k][1]] = 0;
						 getimage(&img, 1020, 60, 40, 40);
						 putimage(addrss[k][0] * B - 20, addrss[k][1] * B - 20, &img);
					 }
						 //���￼�Ǳ߽ǲ���ͼ���
						 //Bsizi = 0;
						 mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
						 mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
						 mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
																													 // }
		    			

					 //return 0;
				 }
				 else if (((weizhi[zong][heng] == 1) && weizhi[zong - 1][heng] != 0 && weizhi[zong + 1][heng] != 0 && weizhi[zong][heng + 1] != 0 
				       && weizhi[zong][heng - 1] != 0)&& (weizhi[zong - 1][heng] == 1 || weizhi[zong + 1][heng] == 1 || weizhi[zong][heng + 1] == 1 || weizhi[zong][heng - 1] == 1))
				 {
					 addrss[Bsizi][0] = zong;
					 addrss[Bsizi][1] = heng;
					 Bsizi++;
					 SamB += Bsizi;
					 x = zong;    
					 y = heng;
					 weizhi[x][y] = 2;
					 tizi( x, y,  2);
					//return 0;
				 }
				 else if ((weizhi[zong][heng] == 1) && (weizhi[zong - 1][heng] == 0 || weizhi[zong + 1][heng] == 0 || weizhi[zong][heng + 1] == 0 
				     || weizhi[zong][heng - 1] == 0)
					 || (weizhi[zong - 1][heng] == 3 || weizhi[zong + 1][heng] == 3 || weizhi[zong][heng + 1] == 3 || weizhi[zong][heng - 1] == 3))
				 {
					continue;
				 }
			 }
		 }

	 }
	 

	 else if (who == 1)                                                                                  //����
	 {
		 for (zong = 1; zong <= 19; zong++)
		 {
			 for (heng = 1; heng <= 19; heng++)
			 {
				 if ((weizhi[zong][heng] == 2) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1)
				 {
					 //addrss[Wsizi][0] = zong;
					 //addrss[Wsizi][1] = heng;
					// Wsizi++;
					// SamB += Wsizi;
					/* if (Wsizi == 1)
					 {
							 weizhi[addrss[Wsizi][0]][addrss[Wsizi][1]] = 3;                               ////////////////////////////////////////
							 getimage(&img, 1020, 60, 40, 40);
							 putimage(addrss[Wsizi][0] *B - 20, addrss[Wsizi][1] * B - 20, &img);
							 weizhi[x][y] = 7;																		    //��������˰�һ���ӣ�λ�ñ�ǹ���һ�£���ֹ�������Ի���
							 _stprintf_s(bai, _T("%d"), 3);															    //���Լ�¼�ã���ɾ��
							 outtextxy(zong*B - x, heng*B - 7, bai);			     //
							 Wsizi = 0;
							 mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
							 mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
							 mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
					 }
					 else if (Wsizi >= 2)
					 {
						 for (int k = 0; k <= Wsizi; k++)
						 {
							 weizhi[addrss[k][0]][addrss[k][1]] = 0;                                      ///////////////////////////////////////
							 getimage(&img, 1020, 60, 40, 40);
							 putimage(addrss[k][0] * B - 20, addrss[k][1] * B - 20, &img);
						 }
						    //���￼�Ǳ߽ǲ���ͼ���
							// Wsizi = 0;
							 mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // �����������Ȱ�ǰ��һ�ε����ֹر�  
							 mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // ������
							 mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // ������һ��
					// }
					// return 0;
				 }
					 else if ((((weizhi[zong][heng] == 2)|| (weizhi[zong][heng] == 6)) && weizhi[zong - 1][heng] != 0 && weizhi[zong + 1][heng] != 0 && weizhi[zong][heng + 1] != 0 && weizhi[zong][heng - 1] != 0) && (weizhi[zong - 1][heng] == 2 || weizhi[zong + 1][heng] == 2 || weizhi[zong][heng + 1] == 2 || weizhi[zong][heng - 1] == 2))
					 {
						 addrss[Wsizi][0] = zong;
						 addrss[Wsizi][1] = heng;
						 Wsizi++;
						 SamB += Wsizi;
						 x = zong;
						 y = heng;
						 weizhi[x][y] = 1;
						 tizi( x, y, 1);
						 //return 0;
					 }
					 else if ((weizhi[zong][heng] == 2) && (weizhi[zong - 1][heng] == 0 || weizhi[zong + 1][heng] == 0 || weizhi[zong][heng + 1] == 0 || weizhi[zong][heng - 1] == 0)
						 || (weizhi[zong - 1][heng] == 4 || weizhi[zong + 1][heng] == 4 || weizhi[zong][heng + 1] == 4 || weizhi[zong][heng - 1] == 4))
					 {
						 continue;
					 }
			 }
		 }
	 }*/


/*int  Dead_Or_Live(int x, int y, int kong)                                                  //�ֵ�˭�±����л�Ϊ˭������
{
    //int zong, heng;
	//int addrss[50][2];																	   //���ڼ�¼����λ�ã�ÿ�θ�λ
	//int Bsizi = 0;																		   //��������������ÿ�ι�1
	//int Wsizi = 0;																		   //��������������ÿ�ι�1
	//int SamB = 0;																		   //�����ܹ���������
	//int SamW = 0;																		   //�����ܹ���������
	
	 if (kong == 3)                                                                         //������ͼ�½�ȥ
	{
		weizhi[x][y] = 2;                                                                   //�ȼٶ�������ȥ�����Ҹ�λ�üƶ�Ӧ���ţ������ǰ���
			for (heng = 0; heng <= 20; heng++)                                            //������ΧһȦ��ֵ���л�Ϊ���ӷ�
			{
				weizhi[heng][0] = 2;
			}
			for (heng = 0; heng <= 20; heng++)
			{
				weizhi[heng][20] = 2;
			}
			for (zong = 0; zong <= 20; zong++)
			{
				weizhi[0][zong] = 2;
			}
			for (zong = 0; zong <= 20; zong++)
			{
				weizhi[20][zong] = 2;
			}
		for (zong = y-2; zong <= y+2; zong++)
		{
			for (heng = x-2; heng <=x+2; heng++)
			{
			    
				if( (weizhi[zong][heng] == 1)&& weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2)
				{
					return 1;
				}
				else if (((weizhi[zong][heng] == 1) && weizhi[zong - 1][heng]!= 0 && weizhi[zong + 1][heng]!= 0 && weizhi[zong][heng + 1] != 0 && weizhi[zong][heng - 1] != 0)
					    &&(weizhi[zong - 1][heng] == 1 || weizhi[zong + 1][heng] == 1 || weizhi[zong][heng + 1] == 1 ||  weizhi[zong][heng - 1] == 1 ))
				{
					addrss[Bsizi][0] = zong;
					addrss[Bsizi][1] = heng;
					Bsizi++;
					SamB += Bsizi;
					x = zong;
					y = heng;
					//weizhi[x][y] = 2;
					Dead_Or_Live(x, y, 3);
				}
				else if((weizhi[zong][heng] == 1) && (weizhi[zong - 1][heng] == 0 || weizhi[zong + 1][heng] == 0 || weizhi[zong][heng + 1] == 0 || weizhi[zong][heng - 1] == 0)
					    ||( weizhi[zong - 1][heng] == 3 || weizhi[zong + 1][heng] == 3 || weizhi[zong][heng + 1] == 3 || weizhi[zong][heng - 1] == 3))
				{
					return 0;
				}
				else  if ((weizhi[zong][heng] == 7) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2)
				{
					return 0;
				}
			}
		}

	}

	
	else if ( kong == 4)
	{
		weizhi[x][y] = 1;                                                                         //�ȼٶ�������ȥ�����Ҹ�λ�üƶ�Ӧ���ţ������Ǻ���  
			for (heng = 0; heng <= 20; heng++)                                                    //������ΧһȦ��ֵ���л�Ϊ���ӷ�
			{
				weizhi[heng][0] = 1;
			}
			for (heng = 0; heng <= 20; heng++)
			{
				weizhi[heng][20] = 1;
			}
			for (zong = 0; zong <= 20; zong++)
			{
				weizhi[0][zong] = 1;
			}
			for (zong = 0; zong <= 20; zong++)
			{
				weizhi[20][zong] = 1;
			}

		for (zong = y - 2; zong <= y + 2; zong++)                                             //�����ӵ�λ����Χ24�����ӽ��б���
		{
			for (heng = x - 2; heng <= x + 2; heng++)
			{

				if ((weizhi[zong][heng] == 2) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1)
				{
					return 1;
				}
				else if (((weizhi[zong][heng] == 2) && weizhi[zong - 1][heng] != 0 && weizhi[zong + 1][heng] != 0 && weizhi[zong][heng + 1] != 0 && weizhi[zong][heng - 1] != 0)
					&& (weizhi[zong - 1][heng] == 2 || weizhi[zong + 1][heng] == 2 || weizhi[zong][heng + 1] == 2 || weizhi[zong][heng - 1] == 2))
				{
					addrss[Wsizi][0] = zong;
					addrss[Wsizi][1] = heng;
					Wsizi++;
					SamB += Wsizi;
					x = zong;
					y = heng;
					//weizhi[x][y] = 1;
					Dead_Or_Live(x, y, 4);
				}
				else if ((weizhi[zong][heng] == 2) && (weizhi[zong - 1][heng] == 0 || weizhi[zong + 1][heng] == 0 || weizhi[zong][heng + 1] == 0 || weizhi[zong][heng - 1] == 0)
					|| (weizhi[zong - 1][heng] == 4 || weizhi[zong + 1][heng] == 4 || weizhi[zong][heng + 1] == 4 || weizhi[zong][heng - 1] == 4))
				{
					return 0;
				}
				else  if ((weizhi[zong][heng] == 6) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1)
				{
					return 0;
				}
			}
		}
	}


}
*/