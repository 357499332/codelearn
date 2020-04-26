#include"头文件.h"     
#define C 1500																		   //窗口长度   
#define D  800                                                                         //窗口高度
#define A 760                                                                          //棋盘尺寸
#define B 40                                                                           //每格尺寸，都是像素单位
#define R 8                                                                            //星位点的半径
#define RQ 18                                                                          //棋子半径
                                                          														  
static int i = 1;                                                                      //0是白棋先行，1是红棋先行，根据步数除以2的余数定
int hong1[200];                                                                        //红棋坐标   
int hong2[200]; 
int bai1[100];                                                                         //白棋坐标
int bai2[100];
int addrss[300][2];                                                                   //记录每一步坐标，用i替换300，
int weizhi[21][21] = {0};                                                              //初始位置都没有棋子，记录为0 
int zong, heng;                                                                        //纵横十九路
int a, b;
int adss[100][2];																	   //用于记录死子位置，每次复位
static int B_dead=0;																   //黑子死子数量，每次归1
static int W_dead=0;																   //白子死子数量，每次归1
int Sam_B_dead = 0;																	   //黑子总共死子数量
int Sam_W_dead = 0;																	   //黑子总共死子数量
int ch;                                                                                //记录按键
int T = 0;                                                                            //////////////////////////
TCHAR bai[10];
TCHAR hong[10];                                                                        //存储步数字符，显示棋子步数
//IMAGE img_go_b, img_go_bk;
IMAGE img;
void huitu();																	       //绘制界面
void shubiao();                                                                        //鼠标动作与结果
int  main();
void luozi();                                                                          //落子声音
void jinshou();
void jia_yan_b();
void jia_yan_w();
void pass();
void huaxian();
void Eat_more_than_one_w();                                                              //死子大于等于2个(sizi>=1)，则执行此函数
void Eat_more_than_one_b();
void shuaxin_w();
void chizhi_w();
void shuaxin_b();
void chizhi_b();
void dao_pu();                                                                          //经典的倒扑，打二还一
void no_breath();                                                                       //无气的位置

/********************************************************************************************************************************************************/

void weiqi()                                                                            //主函数，打开界面
{
    int j=0;
	int x = 3;                                                                         //棋子打印左位移量，为了对齐网格
	//mciSendString(_T("open ./music/BGM2.mp3 alias bkmusic"), NULL, 0, NULL);          //打开背景音乐
	//mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);                          //循环播放
	initgraph(C, D, SHOWCONSOLE);                                                      //加上SHOWCONSOLE可以保留控制台
	HWND hwnd = GetHWnd();                                                             //设置窗口标题文字 
	SetWindowText(hwnd,_T( "围棋GO"));
	huitu();                                                                           //初始化绘图函数，具体方法在后面代码
	BeginBatchDraw();                                                                  //Easy-x画图库函数，画图开始
	while (1)                                                                          //循环下棋动作
	{
		no_breath();
		dao_pu();
		jia_yan_b();
		jia_yan_w();
		shubiao();                                                                     //执行鼠标动作函数,搬到鼠标动作函数内部记录了	
		if (i % 2 == 0)
		{
			chizhi_w();
			//chizhi_b();
			Eat_more_than_one_w();
			shuaxin_w();                                                                     //方向刷新，放在鼠标动作前面
			
			
		}
		if (i % 2 == 1)
		{
			chizhi_b();
			chizhi_w();
			//Eat_more_than_one_b();
			shuaxin_b();

			
		}
		//JIN_SHOU;                                                       //每次刷新                                                               
		if (_kbhit())																   //监控键盘，点击键盘重新游戏
		{
			ch = _getch();
			switch (ch)
			{
			case 32:																   //按空格，复盘展示,用录像功能可能更好
			{
				cleardevice;
				setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);
				huitu();
				for (int k = 0; k < i+5;k++)
				{
	/***********轮到红棋***************************************************************************************************************************/
					setlinecolor(RGB(30, 30, 30));                                         //设置线条颜色
					setfillcolor(RGB(30, 30, 30));
					fillcircle(hong1[k], hong2[k], RQ);                                    //画棋子                  
					setbkcolor(RGB(30, 30, 30));										   //文字背景   
					settextcolor(RED);                                                     //文字颜色
					_stprintf_s(hong, _T("%d"), j);                                        //把步数数字变成字符，下一步显示字符  
					if (k >= 10)
						x = 7;
					outtextxy(hong1[k] - x, hong2[k] - 7, hong);                           //写步数
					luozi();
		/***********轮到白棋***************************************************************************************************************************/
					setlinecolor(WHITE);												   //设置线条颜色
					setfillcolor(WHITE);												   //设置填充颜色
					fillcircle(bai1[k], bai2[k], RQ);									   //画棋子
					setbkcolor(WHITE);													   //文字背景   
					settextcolor(BLACK);                                                   //文字颜色
					_stprintf_s(bai, _T("%d"), j++);                                       //计数必须自增，否则跟步数搭配不了
					if (k >= 10)
						x =7;
					outtextxy(bai1[k]-x, bai2[k]-7, bai);                                  //写步数
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
				mciSendString(_T("close  bkmusic"), NULL, 0, NULL);                       //按d关闭音乐
				continue;
			case 97:
				mciSendString(_T("open ./music/BGM2.mp3 alias bkmusic"), NULL, 0, NULL);  //按a开始音乐
				mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
				continue;
			case 113:
				closegraph;
				main();
			}
		}
		
	}
	EndBatchDraw();																	      //Easy-x画图库函数，画图刷新	
	cleardevice();
	fflush(stdout);
	
}

void shubiao()                                                                         //行棋主体算法函数，处理鼠标动作
{
	//loadimage(&img_go_b, _T("./img/go-b.png"));                                      
	//loadimage(&img_go_bk, _T("./img/go-bk.jpg"));
	//int a, b;                                                                          //遍历步数
	//int you_a, you_b;
	
	for (heng = 0; heng <= 20; heng++)                                                 //棋盘外围一圈赋值，计算边线落子吃子情况
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
	MOUSEMSG m;																	       //定义鼠标消息
	while (MouseHit()  )															   //这个函数用于检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)				                                   //鼠标点击动作，解决禁手问题应该在这里着手，
		{
			a = m.x / B*B;														       //圆心坐标，除以40乘以40保证得到40的倍数，消除浮点数
			b = m.y / B*B; 
			for (zong = 1; zong < 20; zong++)                                          //打劫禁手处理,前手对方的落子，在本次下完后恢复对应值，下次能被吃
				{
				for (heng = 1; heng < 20; heng++)
					{
						if ((a >= 40 && a <= 760 && b >= 40 && b <= 760) && (weizhi[zong][heng] == 4 || weizhi[zong][heng] == 3)
							&& (weizhi[a / B][b / B] != 3 && weizhi[a / B][b / B] != 4))
							//在棋盘其他位置点击落子，打劫禁手位置切换为标记0，
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
			
			if (m.x >800 && m.x < 1450 && m.y > 400 && m.y <800)                         //PASS按钮
			{
				i++;
				pass();
				for (zong = 1; zong < 20; zong++)                                          //打劫禁手处理,前手对方的落子，在本次下完后恢复对应值，下次能被吃
				{
					for (heng = 1; heng < 20; heng++)
					{
						if ((a >= 40 && a <= 760 && b >= 40 && b <= 760) && (weizhi[zong][heng] == 4 || weizhi[zong][heng] == 3)
							&& (weizhi[a / B][b / B] != 3 && weizhi[a / B][b / B] != 4))
							//在棋盘其他位置点击落子，打劫禁手位置切换为标记0，
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
			
			else if (weizhi[a / B][b / B] == 1 || weizhi[a / B][b / B] == 2 || weizhi[a / B][b / B] == 3 || weizhi[a / B][b / B] == 4 )          //在禁手位置点击无效
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
				/********准备在这里添加 Dead_Or_Live(int x , int y ,int kong)死活杀棋计算函数，函数返回true就往下进行,返回 false 就重新 continue***************************

				bool=Dead_Or_Live(int mx , int my);            // return  0 or 1;

				********准备在这里添加 Dead_Or_Live(int mx , int my)死活杀棋计算函数，函数返回1就往下进行,返回0 就重新 continue***************************/

				/*	switch (weizhi[a / 40][b / 40])                                           //根据所下的空值3或4判断能不能下进去
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

				if (a >= 40 && a <= 760 && b >= 40 && b <= 760)                          //记录位置状态,有棋子则实现禁手
				{
					 if (i % 2 == 0 &&  weizhi[a / B][b / B] != 5 && ((weizhi[a / B][b / B] == 0) || (weizhi[a / B][b / B] != 3) || weizhi[a / B][b / B] == 6))
				    //白棋行动，轮流下棋算法，步数除以2的余数，只有0或1，对应两个玩家
					//if (i % 2 == 0 && (weizhi[a / B][b / B] == 0))                        //写好函数后这里就不用复杂的逻辑计算了
					{
						weizhi[a / 40][b / 40] = 2;                                        //记录位置的状态，0为没有棋子，1为有红棋子，2为有白色棋子
						setlinecolor(WHITE);
						setfillcolor(WHITE);
						fillcircle(a, b, RQ);
						//_stprintf_s(bai, _T("%d"), 2);
						//outtextxy(bai1[i] - x, bai2[i] - 7, bai);                          //写白棋步数
						//putimage(a - 20, b - 20, &img_go_b, NOTSRCERASE);
						//putimage(a - 20, b - 20, &img_go_bk, SRCINVERT);    // 
						//FlushBatchDraw();  //

						bai1[i] = a;    //                                                 //白棋横坐标
						bai2[i] = b;	//												   //白棋纵坐标 

						addrss[i][0] = a / B;
						addrss[i][1] = b / B;

						setbkcolor(WHITE);												   //文字背景   
						settextcolor(BLACK);                                               //文字颜色
						//_stprintf_s(bai, _T("%d"), i);                                   //把步数数字变成字符，下一步显示字符 
						_stprintf_s(bai, _T("%d"), 2);                                     //////
						//if (i >= 10)
						//	x = 7;
						outtextxy(bai1[i] - x, bai2[i] - 7, bai);                          //写白棋步数

									for (heng = 0; heng <= 20; heng++)                     //棋盘外围一圈赋值，切换为落子方
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
										for (heng = 0; heng <= 20; heng++)                     //棋盘外围一圈赋值，切换为落子方
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
						TCHAR s13[] = _T("下一手：黑棋");
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
						setbkcolor(WHITE);												   //文字背景   
						settextcolor(BLACK);                                               //文字颜色
						_stprintf_s(bai, _T("%d"), 2);
						outtextxy(a - x, b - 7, bai);                                      //写白棋步数
						/**********这里应该是触发是否提子的时候*************************************************************************************************
						for (zong = 1; zong < 20; zong++)
						{
							for (heng = 1; heng < 20; heng++)
							{
								if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
								{
									getimage(&img, 1020, 60, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 4;                                      //吃掉一个子，将被吃的子先赋值为4，这个位置不能马上落子，
									weizhi[a / 40][b / 40] = 6;                                   //刚落下的棋子位置暂时不设置为对应值，等一手自动变更
									//_stprintf_s(bai, _T("%d"), 4);           //
									//outtextxy(zong*B - x, heng*B - 7, bai);  //
                                     
									//tizi(a/B ,b/B,2);                                             //提掉黑死子

											if ((zong ==  4 && heng ==  4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
											else if (heng*B == 40&& zong*B!=40&&zong*B!=760)					 //上边
											{
												getimage(&img, 1020, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}

											else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
											{
												getimage(&img, 1020, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
											{
												getimage(&img, 980, 60, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
											{
												getimage(&img, 1180, 60, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B == 40)                               //左上角
											{
												getimage(&img, 980, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 760 && heng*B == 40)                              //右上角
											{
												getimage(&img, 1180, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 760 && heng*B == 760)                             //右下角                      
											{
												getimage(&img, 1180, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B == 760)                              //左下角
											{
												getimage(&img, 980, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}

									_stprintf_s(bai, _T("%d"), 4);           //
									outtextxy(zong*B - x, heng*B - 7, bai);  //

								}

								  else if (((weizhi[zong][heng] == 1 ) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 5))
								  {//上
									  getimage(&img, 1020, 20, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] =4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									  //tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 2))
								  {//下
									  getimage(&img, 1020, 180, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									  //tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
								  {//左
									  getimage(&img, 980, 60, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									  //tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 2))
								  {//右
									  getimage(&img, 1180, 60, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									 // tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 5))
								  {//角
									  getimage(&img, 980, 20, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									 // tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 2))
								  {//角
									  getimage(&img, 1180, 180, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									  //tizi(a/B ,b/B);
								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 2 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 2))
								  {//角
									  getimage(&img, 980, 180, 40, 40);
									  putimage(zong*B - 20, heng*B - 20, &img);
									  weizhi[zong][heng] = 4;;
									  weizhi[a / 40][b / 40] = 6;
									  _stprintf_s(bai, _T("%d"), 4);         //
									  outtextxy(zong*B - x, heng*B - 7, bai);//
									//  tizi(a/B ,b/B);

								  }
								  else if (((weizhi[zong][heng] == 1 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 2 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 2 && weizhi[zong][heng - 1] == 5))
								  {//角
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
					/****边线提子大概思路是将外围扩大一路，即纵横第二十路，全部赋值为5，计算的时候直接调用就行，总表数据是从0到800，单独用一个二维数组表示***/
					/****四个角暂时还没有处理***************************************************************************************************************/

					else if (i % 2 == 1 && weizhi[a / B][b / B] != 6 && ((weizhi[a / B][b / B] == 0) || (weizhi[a / B][b / B] != 4) || weizhi[a / B][b / B] == 5))
						                                                                    //黑棋行动
					{ 
						weizhi[a / 40][b / 40] = 1;                                        //记录位置的状态，1为有黑棋子，0为没有棋子，2为有白色棋子

						setlinecolor(RGB(30, 30, 30));
						setfillcolor(RGB(30, 30, 30));
						fillcircle(a, b, RQ);

						hong1[i] = a;                                                      //黑棋横坐标
						hong2[i] = b;													   //黑棋纵坐标 

						addrss[i][0] = a / B;
						addrss[i][1] = b / B;

						setbkcolor(RGB(30, 30, 30));									   //文字背景   
						settextcolor(WHITE);                                               //文字颜色
						//_stprintf_s(hong, _T("%d"), i);                                  //把步数数字变成字符，下一步显示字符 
						_stprintf_s(hong, _T("%d"), 1);
						//if (i >= 10)
						//	x = 7;
						outtextxy(hong1[i] - x, hong2[i] - 7, hong);                       //写黑棋步数
							for (heng = 0; heng <= 20; heng++)                             //棋盘外围一圈赋值，切换为落子方
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
									for (heng = 0; heng <= 20; heng++)                     //棋盘外围一圈赋值，切换为落子方
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
						TCHAR s13[] = _T("下一手：白棋");
						setbkcolor(RGB(220, 180, 70));
						outtextxy(1000, 400, s13);
						setlinecolor(WHITE);
						setfillcolor(WHITE);
						fillcircle(1120, 410, 10);
						_stprintf_s(hong, _T("%d"), i);
						settextcolor(BLACK);
						outtextxy(1000, 380, hong);                                             //写黑棋步数

						i++;

						//huaxian();
						setlinecolor(RGB(30, 30, 30));
						setfillcolor(RGB(30, 30, 30));
						fillcircle(a, b, RQ);
						setbkcolor(RGB(30, 30, 30));									       //文字背景   
						settextcolor(WHITE);												   //文字颜色
						_stprintf_s(hong, _T("%d"), 1);
						outtextxy(a - x, b - 7, hong);										   //写黑棋步数

						/*for (zong = 1; zong < 20; zong++)
						{
							for (heng = 1; heng < 20; heng++)
							{

								if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
								{
									getimage(&img, 1020, 60, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									//_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
									//outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //tizi(a/B ,b/B);                                    //提掉白死子

									if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
									else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //上边
									{
										getimage(&img, 1020, 20, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}

									else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
									{
										getimage(&img, 1020, 180, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
									{
										getimage(&img, 980, 60, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
									{
										getimage(&img, 1180, 60, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 40 && heng*B == 40)                               //左上角
									{
										getimage(&img, 980, 20, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 760 && heng*B == 40)                              //右上角
									{
										getimage(&img, 1180, 20, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 760 && heng*B == 760)                             //右下角                      
									{
										getimage(&img, 1180, 180, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}
									else if (zong*B == 40 && heng*B == 760)
									{
										getimage(&img, 980, 180, 40, 40);
										putimage(zong*B - 20, heng*B - 20, &img);
									}

							_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
							outtextxy(zong*B - x, heng*B - 7, bai);			     //

							}
								/*
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 5))
								{//上
									getimage(&img, 1020, 20, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 // tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 1))
								{//下
									getimage(&img, 1020, 180, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 // tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
								{//左
									getimage(&img, 980, 60, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 1))
								{//右
									getimage(&img, 1180, 60, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 5))
								{//左上角
									getimage(&img, 980, 20, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 1))
								{//右下角
									getimage(&img, 1180, 180, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 5 && weizhi[zong + 1][heng] == 1 && weizhi[zong][heng + 1] == 5 && weizhi[zong][heng - 1] == 1))
								{//左下角
									getimage(&img, 980, 180, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
									outtextxy(zong*B - x, heng*B - 7, bai);			     //
																						 //  tizi(a/B ,b/B);

								}
								else if (((weizhi[zong][heng] == 2 || weizhi[zong][heng] == 0) && weizhi[zong - 1][heng] == 1 && weizhi[zong + 1][heng] == 5 && weizhi[zong][heng + 1] == 1 && weizhi[zong][heng - 1] == 5))
								{//右上角
									getimage(&img, 1180, 20, 40, 40);
									putimage(zong*B - 20, heng*B - 20, &img);
									weizhi[zong][heng] = 3;
									weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
									cnt++;
									_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
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
									//这里考虑边角补绘图情况
									//Bsizi = 0;
									mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
									mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
									mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																															   // }
								}
								
							}
						}*/

						 // i++;                                                                //记录步数
					}
				}
				else if (m.x > 1300 && m.x < 1340 && m.y > 40 && m.y < 80)                      //退出按钮                       
				{
						cleardevice();
						fflush(stdout);
						closegraph();
						main();
				}

			
				FlushBatchDraw();													             //保持前面图形，增加刷新内容	
				continue;                                    /////////////////////////////////////////////////////
			}	
		}
		/*************************************************************************************************************

		**************************************************************************************************************/
		else if (m.uMsg == WM_RBUTTONDOWN)                                              //鼠标右键按下，悔棋
		{
			if (i % 2 == 1)
			{
				weizhi[bai1[i - 1] / 40][bai2[i - 1] / 40] = 0;                         //点击时记步子变量i已经增加，故上一步要-1;

				getimage(&img, 1020, 60, 40, 40);                                       //悔棋、消除棋子后得补上十字
				putimage(bai1[i - 1] - 20, bai2[i - 1] - 20, &img);                     //需要取得刚才棋子的坐标

				jinshou();
				i--;
			}
			else if (i % 2 == 0)
			{
				weizhi[hong1[i - 1] / 40][hong2[i - 1] / 40] = 0;

				getimage(&img, 1020, 60, 40, 40);                                       //悔棋、消除棋子后得补上十字
				putimage(hong1[i - 1] - 20, hong2[i - 1] - 20, &img);                   //需要取得刚才棋子的坐标

				i--;
				jinshou();
			}
		}
			/*you_a = m.x / B*B;
			you_b = m.y / B*B;
			/////////////////////////////////////////////////////////////////////////////////
			if (you_a >= 80 && you_a <= 720 && you_b >= 80 && you_b <= 720 && (weizhi[you_a / 40][you_b / 40] != 0))
			{
				getimage(&img, 1020, 60, 40, 40);                                               	//悔棋、消除棋子后补上十字，这是面向过程不好处理的地方，面向对象会好处理很多
				putimage(you_a - 20, you_b - 20, &img);
				weizhi[you_a / 40][you_b / 40] = 0;
				if ((you_a == B * 4 && you_b == B * 4) || (you_a == B * 10 && you_b == B * 4) || (you_a == B * 16 && you_b == B * 4))	      //假如在星位，需要补画原来白点*
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
			*棋盘边缘老是线出头
			*试一试笨办法，跟补画星位点一样，每次补画外围背景。
			*后来发现消除一个棋子的时候其他棋子都被消除了一半，傻眼了，发现只要补画被消除棋子的区域背景颜色即可
			*再后来又发现，补画一条多出的线就行了，而且写法更简单、更准确
			*最后用对应截图覆盖就行
			*简单的事情有许多方法可以完成，但是最终用朴素的方法就好了
			*因此搞清楚问题的本质很重要，集中在问题的点，而不是通过其他方法把问题盖掉，计算量增加很多不说，还引起未知错误
			****************************************************************************************************************
											else if (heng*B == 40&& zong*B!=40&&zong*B!=760)					 //上边
											{
												getimage(&img, 1020, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}

											else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
											{
												getimage(&img, 1020, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
											{
												getimage(&img, 980, 60, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
											{
												getimage(&img, 1180, 60, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B == 40)                               //左上角
											{
												getimage(&img, 980, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 760 && heng*B == 40)                              //右上角
											{
												getimage(&img, 1180, 20, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 760 && heng*B == 760)                             //右下角                      
											{
												getimage(&img, 1180, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
											else if (zong*B == 40 && heng*B == 760)                              //左下角
											{
												getimage(&img, 980, 180, 40, 40);
												putimage(zong*B - 20, heng*B - 20, &img);
											}
			//i--;                                                                          //前面步数无效
		}*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	
		FlushBatchDraw();
		/* ***********************************************************************************************************
		边界出头比较难处理，这样不行
		else if (m.uMsg == WM_RBUTTONDOWN)
		{
			a = m.x / B*B;
			b = m.y / B*B;
			if (b = 40)
				{
				getimage(&img, 1020, 20, 40, 40);
				putimage(a - 20, b - 20, &img);													  //此方法意在截取对应的图片补充
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

void huitu()                                                                           //图形界面绘制
{
	//int c = 150;                                                                     //颜色值
	for (int y = 0; y < D; y++)                                                        //画背景
	{
		setlinecolor(RGB(220, 180, 70));
		line(0, y, C, y);
	}
	setcolor(RGB(255, 255, 255));													   //设置线条颜色
	for (int y = B; y <= A; y += B)													   //画纵横十九路棋盘
		line(B, y, A, y);
	for (int x = B; x <= A; x += B)
		line(x, B, x, A);


	int i, j;
	for (i = 4; i < 19; i += 6)
		for (j = 4; j < 19; j += 6)                                                    //九个星位的点位置
		{
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillcircle(i * B, j * B, R);											   //画九个星位的点，包括天元
		}
	for (int y = 40; y <= 200; y += 40)                                                //画一个参考框
		line(1000, y, 1200, y);
	for (int x = 1000; x <= 1200; x += B)
		line(x, 40, x, 200);
	    setlinecolor(WHITE);                                                           // 画个参考星位点,用于截图
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
		
	TCHAR s1[] = _T(" 功能说明: C语言 + EASY-X 图形界面做的围棋游戏：");
	TCHAR s2[] = _T(" (1)、在棋盘上交叉点点击鼠标落子，位置偶尔不准;");
	TCHAR s3[] = _T(" (2)、黑白交替落子;");
	TCHAR s4[] = _T(" (3)、右键悔棋;");
	TCHAR s5[] = _T(" (4)、按空格键复盘；");
	TCHAR s6[] = _T(" (5)、彩蛋位置：变电所");
	TCHAR s7[] = _T(" (6)、按a键恢复音乐，d暂停；");
	TCHAR s8[] = _T(" PASS");
	TCHAR s9[] = _T(" 退出");
	TCHAR s10[] = _T("A        B       C        D       E        F       G        H         I        J        K        L        M       N       O        P        Q       R        S ");
	CHAR s11[] = "1234567891111111111";
	CHAR s12[] = "0123456789";
	
	//CHAR S13[]= "'10''11''12'……";                                                    /////////////////////////
	setbkcolor(RGB(220, 180, 70));													   //文字背景   
	//settextcolor(RGB(150, 150, 0));                                            	   //文字颜色
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
	//_stprintf_s(bai, "%d", 3);                                                      //  把数字转换为字符，
	//outtextxy(zong*B - 3, heng*B - 7, bai);			                              //

	

	FlushBatchDraw();																   //Easy-x画图库函数，过程更新	

}

void luozi()
{
	mciSendString(_T("close  gemusic"), NULL, 0, NULL);               // 落子声音，先把前面一次的音乐关闭  
	mciSendString(_T("open ./music/stone.mp3 alias gemusic"), NULL, 0, NULL);                                // 打开音乐
	mciSendString(_T("play gemusic"), NULL, 0, NULL);                  // 仅播放一次
}

void jinshou()
{
	mciSendString(_T("close jjmusic"), NULL, 0, NULL);                 // 落子声音，先把前面一次的音乐关闭  
	mciSendString(_T("open ./music/gotEnemy.mp3 alias jjmusic"), NULL, 0, NULL);                                // 打开音乐
	mciSendString(_T("play jjmusic"), NULL, 0, NULL);                  // 仅播放一次

	mciSendString(_T("close  psmusic"), NULL, 0, NULL);               // 落子声音，先把前面一次的音乐关闭  
	mciSendString(_T("open ./music/pass.mp3 alias psmusic"), NULL, 0, NULL);                                // 打开音乐
	mciSendString(_T("play psmusic"), NULL, 0, NULL);                  // 仅播放一次


}

void jia_yan_b()                                                                     //跟倒扑 打二还一很相似
{
	int x, y;
	for (x = 1; x <= 19; x++)
		{
			for (y = 1; y <= 19; y++) 
			{

				/*if  ( ( weizhi[x][y] == 5 )
					&& (( weizhi[x - 1][y-1] == 2 && weizhi[x + 1][y-1] == 2 && weizhi[x][y-2] == 2 )       //上包围
					|| (  weizhi[x - 1][y-1] == 2 && weizhi[x - 1][y+1] == 2 && weizhi[x-2][y] == 2 )       //左包围
					|| (  weizhi[x - 1][y+1] == 2 && weizhi[x + 1][y+1] == 2 && weizhi[x][y+2] == 2 )       //下包围
					|| (  weizhi[x + 1][y+1] == 2 && weizhi[x + 1][y-1] == 2 && weizhi[x+2][y] == 2 ))  )   //右包围
					*/
				if ((weizhi[x][y] == 1)
					&& (weizhi[x - 1][y] == 2 && weizhi[x][y - 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y + 1] == 5)           //假眼在下边
					|| (weizhi[x][y - 1] == 2 && weizhi[x][y + 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x - 1][y] == 5)         //假眼在左边
					|| (weizhi[x - 1][y] == 2 && weizhi[x][y + 1] == 2 && weizhi[x][y - 1] == 2 && weizhi[x + 1][y] == 5)     //   假眼在右边
					|| (weizhi[x - 1][y] == 2 && weizhi[x][y + 1] == 2 && weizhi[x + 1][y] == 2 && weizhi[x][y - 1] == 5))   // 假眼在上边
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
				&& (weizhi[x - 1][y] == 1 && weizhi[x][y - 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y + 1] == 6)           //假眼在下边
				|| (weizhi[x][y - 1] == 1 && weizhi[x][y + 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x - 1][y] == 6)         //假眼在左边
				|| (weizhi[x - 1][y] == 1 && weizhi[x][y + 1] == 1 && weizhi[x][y - 1] == 1 && weizhi[x + 1][y] == 6)     //   假眼在右边
				|| (weizhi[x - 1][y] == 1 && weizhi[x][y + 1] == 1 && weizhi[x + 1][y] == 1 && weizhi[x][y - 1] == 6))   // 假眼在上边
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
	for (int x = 1; x <= 19; x++)                                                   //禁手单列测试
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

	for (int x = 1; x <= 19; x++)                                                   //禁手单列测试
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
	mciSendString(_T("close  pssmusic"), NULL, 0, NULL);               // 落子声音，先把前面一次的音乐关闭  
	mciSendString(_T("open ./music/pass.wav alias pssmusic"), NULL, 0, NULL);                                // 打开音乐
	mciSendString(_T("play pssmusic"), NULL, 0, NULL);                  // 仅播放一次
}

void Eat_more_than_one_w()
{    
	//int B_dead = 0;																		       //黑子死子数量，每次归1
	//int W_dead = 0;																		       //白子死子数量，每次归1
	int x, y;
	int i=0;
	//int SamB_dead = 0;																		   //黑子总共死子数量
	//int W_dead = 0;																		   //黑子总共死子数量
	TCHAR s13[] = _T("↓当前步数   黑方提子-             白方提子-    ");
	setbkcolor(RGB(220, 180, 70));
	outtextxy(1000, 360, s13);
	_stprintf_s(hong, _T("%d"), W_dead);                                           //把步数数字变成字符，下一步显示字符  
	outtextxy(1170, 360, hong);
	_stprintf_s(hong, _T("%d"), B_dead);                                           //把步数数字变成字符，下一步显示字符  
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
			getimage(&img, 1020, 60, 40, 40);                                                     ///////////////////观察效果用途
			putimage(x*B - 20, y*B - 20, &img);                                                   /////////////////////观察效果用途
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
				//getimage(&img, 1020, 60, 40, 40);                                ///////////////////观察效果用途
				//putimage(x*B - 20, y*B - 20, &img);                             /////////////////////观察效果用途
				_stprintf_s(hong, _T("%d"), 8);                                        //把步数数字变成字符，下一步显示字符  
				outtextxy(x*B-3, y*B-7, hong);                                  //写步数
				Eat_more_than_one_w();                                            //////////////////开始递归循环,  对内存监控发现，鼠标不点击，数据一直在跑
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
				 //Eat_more_than_one();                                                             //还得再搜索啊
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
			//weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
			//_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
			//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
			if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
			else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //上边
			{
				getimage(&img, 1020, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
			{
				getimage(&img, 1020, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
			{
				getimage(&img, 980, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
			{
				getimage(&img, 1180, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 40)                               //左上角
			{
				getimage(&img, 980, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 40)                              //右上角
			{
				getimage(&img, 1180, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 760)                             //右下角
			{
				getimage(&img, 1180, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 760)
			{
				getimage(&img, 980, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
			mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
			mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																										// }
			_stprintf_s(bai, _T("%d"), 3);                                      //测试记录用，待删除
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
			//weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
			//_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
			//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
			if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
			else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //上边
			{
				getimage(&img, 1020, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
			{
				getimage(&img, 1020, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
			{
				getimage(&img, 980, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
			{
				getimage(&img, 1180, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 40)                               //左上角
			{
				getimage(&img, 980, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 40)                              //右上角
			{
				getimage(&img, 1180, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 760)                             //右下角
			{
				getimage(&img, 1180, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 760)
			{
				getimage(&img, 980, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
			mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
			mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																										// }
			_stprintf_s(bai, _T("%d"), 3);                                      //测试记录用，待删除
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
				//weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
				//_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //上边
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //左上角
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //右上角
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //右下角
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																											// }
				_stprintf_s(bai, _T("%d"), 3);                                      //测试记录用，待删除
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
				//weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
				//_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //上边
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //左上角
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //右上角
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //右下角
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																											// }
				_stprintf_s(bai, _T("%d"), 3);                                      //测试记录用，待删除
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
				//weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
				//_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			    //上边
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //左上角
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //右上角
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //右下角
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																											// }
				_stprintf_s(bai, _T("%d"), 3);                                      //测试记录用，待删除
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
									getimage(&img, 1020, 60, 40, 40);                                      ///////////////////观察效果用途
									putimage(x*B - 20, y*B - 20, &img);                                    //画白棋/////////////////////////////////////////
									weizhi[x][y] = 0;
									_stprintf_s(hong, _T("%d"), 0);                                        //把步数数字变成字符，下一步显示字符  
									outtextxy(x*B - 3, y*B - 7, hong);                                     //写步数
									W_dead++;                                                              //提子数量
								}
							}
						}
						/*for (int j = 0; j <= i; j++)
						{

						weizhi[adss[j][0] / B][adss[j][1] / B] = 0;
						_stprintf_s(hong, _T("%d"), 7);                                               //把步数数字变成字符，下一步显示字符
						outtextxy(adss[i][0] - 3, adss[i][1] - 7, hong);                              //写步数
						getimage(&img, 1020, 60, 40, 40);                                             ///////////////////观察效果用途
						putimage(adss[j][0] - 20, adss[j][1] - 20, &img);                             /////////////////////观察效果用途
						//FlushBatchDraw();
						}

						_stprintf_s(hong, _T("%d"), SamW_dead);                                           //把步数数字变成字符，下一步显示字符
						outtextxy(1150, 360, hong);                                                        //写步数       */
						luozi();
						exit;

					}
			else if ((weizhi[x][y] == 8) && (weizhi[x - 1][y] == 2 || weizhi[x + 1][y] == 2 || weizhi[x][y - 1] == 2 || weizhi[x][y + 1] == 2))
						{
						//setlinecolor(WHITE);
						//setfillcolor(WHITE);
						//fillcircle(x, y, RQ);                                                  //画白棋/////////////////////////////////////////

							weizhi[x][y] = 2;
							_stprintf_s(hong, _T("%d"), 2);                                        //把步数数字变成字符，下一步显示字符  
							outtextxy(x*B - 3, y*B - 7, hong);                                      //写步数
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
							//fillcircle(x, y, RQ);                                                  //画白棋/////////////////////////////////////////
							weizhi[x][y] = 1;
							_stprintf_s(hong, _T("%d"), 1);                                        //把步数数字变成字符，下一步显示字符  
							outtextxy(x*B - 3, y*B - 7, hong);                                     //写步数
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
			//weizhi[a / 40][b / 40] = 7;                                       //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
			//_stprintf_s(bai, _T("%d"), 4);                                   //测试记录用，待删除
			//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
			if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
			else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //上边
			{
				getimage(&img, 1020, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
			{
				getimage(&img, 1020, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
			{
				getimage(&img, 980, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
			{
				getimage(&img, 1180, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 40)                               //左上角
			{
				getimage(&img, 980, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 40)                              //右上角
			{
				getimage(&img, 1180, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 760)                             //右下角                      
			{
				getimage(&img, 1180, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 760)
			{
				getimage(&img, 980, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
			mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
			mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																										// }
			_stprintf_s(bai, _T("%d"), 4);                                                      //测试记录用，待删除
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
			//weizhi[a / 40][b / 40] = 7;                                       //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
			//_stprintf_s(bai, _T("%d"), 4);                                   //测试记录用，待删除
			//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
			if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
			else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //上边
			{
				getimage(&img, 1020, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
			{
				getimage(&img, 1020, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
			{
				getimage(&img, 980, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
			{
				getimage(&img, 1180, 60, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 40)                               //左上角
			{
				getimage(&img, 980, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 40)                              //右上角
			{
				getimage(&img, 1180, 20, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 760 && heng*B == 760)                             //右下角                      
			{
				getimage(&img, 1180, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			else if (zong*B == 40 && heng*B == 760)
			{
				getimage(&img, 980, 180, 40, 40);
				putimage(zong*B - 20, heng*B - 20, &img);
			}
			mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
			mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
			mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																										// }
			_stprintf_s(bai, _T("%d"), 4);                                                      //测试记录用，待删除
			outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //
			B_dead++;																					//tizi(a/B ,b/B);     //提掉白死子
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
				//weizhi[a / 40][b / 40] = 7;                                       //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
				//_stprintf_s(bai, _T("%d"), 4);                                   //测试记录用，待删除
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)			     //上边
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //左上角
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //右上角
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //右下角                      
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																											// }
				_stprintf_s(bai, _T("%d"), 4);                                                      //测试记录用，待删除
				outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //
				B_dead++;																					//tizi(a/B ,b/B);     //提掉白死子
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
				//weizhi[a / 40][b / 40] = 7;                                       //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
				//_stprintf_s(bai, _T("%d"), 4);                                   //测试记录用，待删除
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //上边
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //左上角
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //右上角
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //右下角                      
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																											// }
				_stprintf_s(bai, _T("%d"), 4);                                                      //测试记录用，待删除
				outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //
				B_dead++;																					//tizi(a/B ,b/B);     //提掉白死子
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
				//weizhi[a / 40][b / 40] = 7;                                       //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
				//_stprintf_s(bai, _T("%d"), 4);                                   //测试记录用，待删除
				//outtextxy(zong*B - 3, heng*B - 7, bai);			     //
				if ((zong == 4 && heng == 4) || (zong == 10 && heng == 4) || (zong == 16 && heng == 4))	                 //假如在星位，需要补画原来白点*
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
				else if (heng*B == 40 && zong*B != 40 && zong*B != 760)					 //上边
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (heng*B == 760 && zong*B != 40 && zong*B != 760)			 //下边
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)				 //左边
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B != 40 && heng*B != 760)              //右边
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 40)                               //左上角
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 40)                              //右上角
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 760 && heng*B == 760)                             //右下角                      
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				else if (zong*B == 40 && heng*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(zong*B - 20, heng*B - 20, &img);
				}
				mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
				mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
				mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
																											// }
				_stprintf_s(bai, _T("%d"), 4);                                                      //测试记录用，待删除
				outtextxy(zong*B - 3, heng*B - 7, bai);			                                    //
				B_dead++;											                                       //tizi(a/B ,b/B);     //提掉白死子
			}

			
		}
	}
}

void huaxian()
{
	int x, y;
	int r, g, b;
	
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 1);

	for (x = 1; x <= 19; x++)                                                      //慢速度划线
	{
		for (y = 1; y <= 19; y++)
		{
			srand((unsigned)time(NULL));
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
			setcolor(RGB(r, g, b));
			line(x * 40, B, x * 40, A);											   //设置线条颜色
			FlushBatchDraw();
			/*srand((unsigned)time(NULL));
			r = rand() % 255;
			g = rand() % 255;
			b = rand() % 255;
			setcolor(RGB(b,g,r));
			line(B, y * 40, A, y * 40);	*/										   //画纵横十九路
			circle(x*B, y*B, 3);
			Sleep(T);
			FlushBatchDraw();
		}
	}

	for (x = 1; x <= 19; x++)                                                      //恢复白棋盘
	{
		for (y = 1; y <= 19; y++)
		{
			setcolor(RGB(255, 255, 255));											 //设置线条颜色											 
			line(B, y * 40, A, y * 40);
			line(x * 40, B, x * 40, A);

			setlinecolor(RGB(220, 180, 70));
			circle(x*B, y*B, 3);
		}
	}

	for (x = 4; x < 19; x += 6)
	{
		for (y = 4; y < 19; y += 6)                                                    //九个星位的点位置
		{
			if (weizhi[x][y] == 0) 
			{
			setlinecolor(WHITE);
			setfillcolor(WHITE);
			fillcircle(x * B, y * B, R);
			}										   //画九个星位的点，包括天元
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
									_stprintf_s(bai, _T("%d"), 0);                                                      //测试记录用，待删除
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
									_stprintf_s(bai, _T("%d"), 0);                                                      //测试记录用，待删除
									outtextxy(x*B - 3, y*B - 7, bai);
								}

							}
						}

				}
			}
}

	/* if (who == 2)                                                                             //白棋
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
							 weizhi[x][y] = 6;                                    //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
							 //_stprintf_s(bai, _T("%d"), 4);                       //测试记录用，待删除
							 outtextxy(zong*B - x, heng*B - 7, bai);			     //
							 //这里考虑边角补绘图情况
							 Bsizi = 0;
							 mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
							 mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
							 mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
					 }
					 else if(Bsizi>=2)
					 {
					 for (int k = 0; k <= Bsizi; k++)
					 {
						 weizhi[addrss[k][0]][addrss[k][1]] = 0;
						 getimage(&img, 1020, 60, 40, 40);
						 putimage(addrss[k][0] * B - 20, addrss[k][1] * B - 20, &img);
					 }
						 //这里考虑边角补绘图情况
						 //Bsizi = 0;
						 mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
						 mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
						 mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
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
	 

	 else if (who == 1)                                                                                  //黑棋
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
							 weizhi[x][y] = 7;																		    //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
							 _stprintf_s(bai, _T("%d"), 3);															    //测试记录用，待删除
							 outtextxy(zong*B - x, heng*B - 7, bai);			     //
							 Wsizi = 0;
							 mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
							 mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
							 mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
					 }
					 else if (Wsizi >= 2)
					 {
						 for (int k = 0; k <= Wsizi; k++)
						 {
							 weizhi[addrss[k][0]][addrss[k][1]] = 0;                                      ///////////////////////////////////////
							 getimage(&img, 1020, 60, 40, 40);
							 putimage(addrss[k][0] * B - 20, addrss[k][1] * B - 20, &img);
						 }
						    //这里考虑边角补绘图情况
							// Wsizi = 0;
							 mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
							 mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
							 mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
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


/*int  Dead_Or_Live(int x, int y, int kong)                                                  //轮到谁下边线切换为谁的属性
{
    //int zong, heng;
	//int addrss[50][2];																	   //用于记录死子位置，每次复位
	//int Bsizi = 0;																		   //黑子死子数量，每次归1
	//int Wsizi = 0;																		   //白子死子数量，每次归1
	//int SamB = 0;																		   //黑子总共死子数量
	//int SamW = 0;																		   //黑子总共死子数量
	
	 if (kong == 3)                                                                         //白棋试图下进去
	{
		weizhi[x][y] = 2;                                                                   //先假定落子下去，并且给位置计对应符号，这里是白棋
			for (heng = 0; heng <= 20; heng++)                                            //棋盘外围一圈赋值，切换为落子方
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
		weizhi[x][y] = 1;                                                                         //先假定落子下去，并且给位置计对应符号，这里是黑棋  
			for (heng = 0; heng <= 20; heng++)                                                    //棋盘外围一圈赋值，切换为落子方
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

		for (zong = y - 2; zong <= y + 2; zong++)                                             //对落子的位子周围24个棋子进行遍历
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