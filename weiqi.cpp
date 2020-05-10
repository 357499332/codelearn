#include"头文件.h"     
#define C 1500																		   //窗口长度   
#define D  800                                                                         //窗口高度
#define A 760                                                                          //棋盘尺寸
#define B 40                                                                           //每格尺寸，都是像素单位
#define R 8                                                                            //星位点的半径
#define RQ 18                                                                          //棋子半径

FILE *fp;
int i = 1;                                                                           //0是白棋先行，1是红棋先行，根据步数除以2的余数定
int hei1[200];                                                                        //红棋坐标   
int hei2[200]; 
int bk = 0;
int bai1[200];                                                                         //白棋坐标
int bai2[200];
int wt = 0;
int weizhi[21][21] = {0};                                                              //初始位置都没有棋子，记录为0 
int x, y;                                                                              //纵横十九路
int a, b;
int da_jie[2][2];		 															   //用于记录死子位置，每次复位
int count_wt;                                                                          //形式判断白棋空
int count_bk;
static int B_dead=0;																   //黑子死子数量，每次归1
static int W_dead=0;																   //白子死子数量，每次归1
int buff;                                                                              //网络对战位置数据传输变量
int buffer[200];
char zuobiao[20];
//char *zb;

int Q = 0;
int ch;                                                                                //记录按键
int T = 25;                                                                             //////////////////////////
TCHAR bai[100];
TCHAR hong[100];                                                                        //存储步数字符，显示棋子步数

IMAGE img;

void huitu();																	       //绘制界面
char * shubiao();                                                                      //鼠标动作与结果
int  main();
void luozi();                                                                          //落子声音
void tizi();
void jinshou();
int  jia_yan_b();  
int  jia_yan_w();                                                                      //打劫
void pass();
void huaxian();                                                                        //算法观察
void Eat_more_than_one_w();                                                            //死子大于等于2个(sizi>=1)，则执行此函数
void Eat_more_than_one_b();
void SHA_bk();
void SHA_wt();
void shuaxin_w();                                                                      //要从多个方向遍历刷新，否则会出现自己吃自己现象
void shuaxin_b();
void chizhi_w();
void chizhi_b();
void no_breath();                                                                       //无气的位置
void creat_data();
int  *read_data();
void  save();
void fu_pan();
void xing_shi_panduan();
void xiaqi_wt();
void xiaqi_bk();
int client();
int jieshou();
void go_online_wt();
void go_online_bk();

/********主体函数********主体函数*****************************************************************************************************************************************/

void weiqi()                                                                            //主函数，打开界面
{
    int j=1;
	int p=3;                                                                            //棋子打印左位移量，为了对齐网格
	mciSendString(_T("open ./music/BGM.mp3 alias bkmusic"), NULL, 0, NULL);              //打开背景音乐
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);                             //循环播放
	initgraph(C, D, SHOWCONSOLE);                                                        //加上SHOWCONSOLE可以保留控制台
	HWND hwnd = GetHWnd();                                                               //设置窗口标题文字 
	SetWindowText(hwnd,_T( "围棋GO"));

	//要实现网络对战功能，应该也是在这个位置着手，通过socket以及服务器建立连接
	
	huitu();   
	//client();//初始化绘图函数，具体方法在后面代码
	BeginBatchDraw();                                                                    //Easy-x画图库函数，画图开始
	while (1)                                                                            //循环下棋动作
	{
		//可以尝试在这个位置实现自动落子功能，比如用随机数的形式生成a/b的值   初步实现                                                                  
		if (Q == 2)            //电脑下白棋
			{
			Sleep(100);
		    xiaqi_wt();       //如果要给程序加上智能落子能力，应该在此函数深化下去，包括训练、棋谱库搜索、价值判断与选点，传入对方上一步坐标给函数，函数自己返回落子位置执行即可//
			chizhi_b();
			Eat_more_than_one_b();
			shuaxin_b();
			SHA_bk();
			chizhi_w();
			Eat_more_than_one_w();
			shuaxin_w();
			SHA_wt();
			}
		if (Q == 1)            //切换为电脑下黑棋
			{
			Sleep(100);
			xiaqi_bk();    
			chizhi_w();
			Eat_more_than_one_w();
			shuaxin_w();                                                                  //方向刷新，放在鼠标动作前面
			SHA_wt();
			chizhi_b();
			Eat_more_than_one_b();
			shuaxin_b();
			SHA_bk();

			}
		shubiao();             ////////////////////////////////////////////////////////////////////////////////
		if (i % 2 == 0)                                                                   // 黑棋下完后轮到白棋前搜索白棋死活   还是要研究禁手算法，不入和倒扑棋型
		{
			chizhi_w();
			Eat_more_than_one_w();
			shuaxin_w();                                                                  //方向刷新，放在鼠标动作前面
			SHA_wt();
			chizhi_b();
			Eat_more_than_one_b();
			shuaxin_b();
			SHA_bk();
			
		}
		if (i % 2 == 1)                                                                    //白棋下完之后针对黑棋搜索  
		{
			chizhi_b();
			Eat_more_than_one_b();
			shuaxin_b();
			SHA_bk();
			chizhi_w();
			Eat_more_than_one_w();
			shuaxin_w();                                                                  //方向刷新，放在鼠标动作前面
			SHA_wt();
		}

		//go_online_wt();   //////////////////////////////////////////////////
	   // go_online_bk();   //////////////////////////////////////////////////         //通过客户端函数输出落子坐标
		FlushBatchDraw();
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
				for (int k = 0; k < i + 5; k++)
				{
	
					setlinecolor(RGB(30, 30, 30));                                       //设置线条颜色
					setfillcolor(RGB(30, 30, 30));
					fillcircle(hei1[k], hei2[k], RQ);                                    //画棋子                  
					setbkcolor(BLACK);										              //文字背景   
					settextcolor(WHITE);                                                   //文字颜色
					_stprintf_s(hong, _T("%d"), j);                                        //把步数数字变成字符，下一步显示字符  
					if (k >= 10)
						p = 7;
					outtextxy(hei1[k] - p, hei2[k] - 7, hong);                           //写步数
					luozi();
	
					setlinecolor(WHITE);												   //设置线条颜色
					setfillcolor(WHITE);												   //设置填充颜色
					fillcircle(bai1[k], bai2[k], RQ);									   //画棋子
					setbkcolor(WHITE);													   //文字背景   
					settextcolor(BLACK);                                                   //文字颜色
					_stprintf_s(bai, _T("%d"), j++);                                       //计数必须自增，否则跟步数搭配不了
					if (k >= 10)
						p =7;
					outtextxy(bai1[k]-p, bai2[k]-7, bai);                                  //写步数
					luozi();
					if (j > i-1 )
						{
						 break;
						}
				Sleep(1000);
				} 
				FlushBatchDraw();
			
			}
			case 100:                                                                     
				mciSendString(_T("close  bkmusic"), NULL, 0, NULL);                       //按d关闭音乐
				continue;
			case 97:
				mciSendString(_T("open ./music/BGM.mp3 alias bkmusic"), NULL, 0, NULL);  //按a开始音乐
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
/****************************************************************************************************************************************************************************/

char *shubiao()                                                                          //行棋主体算法函数，处理鼠标动作
{
	int n = 3;
	for (y = 0; y <= 20; y++)                                                 //棋盘外围一圈赋值，计算边线落子吃子情况
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
		
	MOUSEMSG m;																	       //定义鼠标消息
	while (MouseHit()  )															   //这个函数用于检测当前是否有鼠标消息
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)				                                   //鼠标点击动作，解决禁手问题应该在这里着手，
		{
			
			a = m.x / B*B;														       //圆心坐标，除以40乘以40保证得到40的倍数，消除浮点数
			b = m.y / B*B; 
			

			if (m.x >800 && m.x < 1100 && m.y > 260 && m.y <600)                         //黑棋自动走棋
			{
				Q = 1;                                            /////////////////////////////////////////
				//i++;
				pass();				
					/*	for (x = 1; x < 20; x++)                                          //打劫禁手处理,前手对方的落子，在本次下完后恢复对应值，下次能被吃
						{
							for (y = 1; y < 20; y++)
							{
								if ((a >= 40 && a <= 760 && b >= 40 && b <= 760) && (weizhi[x][y] == 4 || weizhi[x][y] == 3)
									&& (weizhi[a / B][b / B] != 3 && weizhi[a / B][b / B] != 4))
									//在棋盘其他位置点击落子，打劫禁手位置切换为标记0，
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

			if (m.x > 1150 && m.x < 1400 && m.y > 260 && m.y < 320)                       //白棋自动走棋
			{
				Q = 2;                                            /////////////////////////////////////////
				//i++;
				pass();
			}

			else if (m.x >1240 && m.x < 1300 && m.y > 40 && m.y <60)                         //形势判断
			{
			   
				xing_shi_panduan();

				TCHAR s14[] = _T("白方形式     黑方形式");
				setbkcolor(RGB(220, 180, 70));
				outtextxy(1000, 430, s14);
				_stprintf_s(hong, _T("%d"), count_wt+ B_dead);
				settextcolor(WHITE);
				outtextxy(1000, 450, hong);
				_stprintf_s(hong, _T("%d"), count_bk + W_dead);
				settextcolor(WHITE);
				outtextxy(1120, 450, hong);
				count_wt = 0;                                                                 //归零，否则会重复
				count_bk = 0;
	
			}
			
			else if (weizhi[a / B][b / B] == 1 || weizhi[a / B][b / B] == 2 || weizhi[a / B][b / B] == 7 || weizhi[a / B][b / B] == 8)
				
					{
						jinshou();	
						//i--;
						continue;
					}

			else if (m.x > 1300 && m.x < 1340 && m.y > 40 && m.y < 80)                         //退出按钮                       
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
				////////////////////////////////////////////////////////////////////测试记录棋谱
				cleardevice();
				//fflush(stdout);
				closegraph();
				main();
				//creat_data();                                                              
				
			}

			else if (m.x > 1350 && m.x < 1400 && m.y > 40 && m.y < 80)                    //复盘按钮                       
			{

					fu_pan();
	
			}
			else if (m.x > 1400 && m.x < 1450 && m.y > 40 && m.y < 80)                    //保存棋谱                       
			{

			    	save();

			}
			else
			{
				if (a >= 40 && a <= 760 && b >= 40 && b <= 760)                             //记录位置状态,有棋子则实现禁手
				{
					if (i % 2 == 0 && weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
					{
						da_jie[1][0] = 0;                                                  //打劫的位置复位
					    da_jie[1][1] = 0;
				       //白棋行动，轮流下棋算法，步数除以2的余数，只有0或1，对应两个玩家
						bai1[wt] = a;                                                      //白棋横坐标
						bai2[wt] = b;													   //白棋纵坐标 
						wt++;
						weizhi[a / 40][b / 40] = 2;                                        //记录位置的状态，0为没有棋子，1为有红棋子，2为有白色棋子
						buff = (a * 10000 + b + 2);                                        //这个数据的格式决定了棋谱的记录和读取可能性  白棋尾数加2
						buffer[i] = buff;
						itoa(buff,zuobiao,10);                       /////整数转字符串
						creat_data();                                                      //每次循环记录步数信息
						
									setlinecolor(WHITE);
									setfillcolor(WHITE);
									fillcircle(a, b, RQ);
									setbkcolor(WHITE);												   //文字背景   
									settextcolor(BLACK);                                               //文字颜色
									_stprintf_s(bai, _T("%d"), i);                                   //把步数数字变成字符，下一步显示字符 
									//_stprintf_s(bai, _T("%d"), 2);                                     //////
									if (i >= 10)
										n = 7;
									outtextxy(a - n, b - 7, bai);                                      //写白棋步数

									for (y = 0; y <= 20; y++)                                //棋盘外围一圈赋值，切换为落子方
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

									
									TCHAR s13[] = _T("下一手：黑棋");
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
					/****边线提子大概思路是将外围扩大一路，即纵横第二十路，全部赋值为5，计算的时候直接调用就行，总表数据是从0到800，单独用一个二维数组表示***/
					/****四个角暂时还没有处理***************************************************************************************************************/

					else if (i % 2 == 1 &&weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
						                                                                    //黑棋行动
					{ 
						da_jie[1][0] = 0;
						da_jie[1][1] = 0;
						hei1[bk] = a;                                                       //黑棋横坐标
						hei2[bk] = b;                                                       //黑棋纵坐标 
						bk++;
						weizhi[a / 40][b / 40] = 1;                                        //记录位置的状态，1为有黑棋子，0为没有棋子，2为有白色棋子
					
						buff = (a * 10000 + b  + 1);                                          //这个数据的格式决定了棋谱的记录和读取可能性  黑棋尾数加1
						buffer[i] = buff;
						itoa(buff, zuobiao, 10);                     //////////////////整数转字符串
						creat_data();                                                             //每次循环记录步数信息

						setlinecolor(RGB(30, 30, 30));
						setfillcolor(RGB(30, 30, 30));
						fillcircle(a, b, RQ);

															 
						setbkcolor(RGB(30, 30, 30));									   //文字背景   
						settextcolor(WHITE);                                               //文字颜色
						_stprintf_s(hong, _T("%d"), i);                                  //把步数数字变成字符，下一步显示字符 
						//_stprintf_s(hong, _T("%d"), 1);
						if (i >= 10)
							n = 7;
						outtextxy(a - n, b - 7, hong);                         //写黑棋步数
							for (y = 0; y <= 20; y++)                                      //棋盘外围一圈赋值，切换为落子方
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
							
								TCHAR s13[] = _T("下一手：白棋");
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

				FlushBatchDraw();													             //保持前面图形，增加刷新内容	
				continue;                                    /////////////////////////////////////////////////////
			}	
		}
		/*************************************************************************************************************

		**************************************************************************************************************/
		else if (m.uMsg == WM_RBUTTONDOWN)                                              //鼠标右键按下，悔棋
		{
			Q = 0;                                                                      //关闭计算机自动落子
			if (i % 2 == 1)
			{
				weizhi[bai1[wt-1 ] / 40][bai2[wt-1 ] / 40] = 0;                         //点击时记步子变量i已经增加，故上一步要-1;
				getimage(&img, 1020, 60, 40, 40);                                       //悔棋、消除棋子后得补上十字
				putimage(bai1[wt-1 ] - 20, bai2[wt-1 ] - 20, &img);                     //需要取得刚才棋子的坐标

				jinshou();
				i--;	
			}
			else if (i % 2 == 0)
			{
				weizhi[hei1[bk-1 ] / 40][hei2[bk-1 ] / 40] = 0;

				getimage(&img, 1020, 60, 40, 40);                                       //悔棋、消除棋子后得补上十字
				putimage(hei1[bk-1] - 20, hei2[bk-1] - 20, &img);                       //需要取得刚才棋子的坐标

				i--;
				jinshou();
			}
			T = T + 5;
			FlushBatchDraw();
		}
	     /********************************************************************************************************************
			*棋盘边缘老是线出头
			*试一试笨办法，跟补画星位点一样，每次补画外围背景。
			*后来发现消除一个棋子的时候其他棋子都被消除了一半，傻眼了，发现只要补画被消除棋子的区域背景颜色即可
			*再后来又发现，补画一条多出的线就行了，而且写法更简单、更准确
			*最后用对应截图覆盖就行
			*简单的事情有许多方法可以完成，但是最终用朴素的方法就好了
			*因此搞清楚问题的本质很重要，集中在问题的点，而不是通过其他方法把问题盖掉，计算量增加很多不说，还引起未知错误
		**********************************************************************************************************************/
	}
	//zb = zuobiao;
	return  zuobiao;
}

void huitu()                                                                           //图形界面绘制
{
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
		TCHAR s4[] = _T(" (3)、右键悔棋，停止电脑走棋 ");
		TCHAR s5[] = _T(" (4)、电脑走黑棋      电脑走白棋");
		TCHAR s6[] = _T(" (5)、彩蛋位置：变电所");
		TCHAR s7[] = _T(" (6)、按a键恢复音乐，d暂停；");
		TCHAR s8[] = _T(" 形式");
		TCHAR s9[] = _T(" 退出      复盘      保存");
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
		settextcolor(RGB(150, 150, 0));
		outtextxy(1000, 300, s5);
		FlushBatchDraw();																   //Easy-x画图库函数，过程更新	

}

void luozi()
{
	mciSendString(_T("close  lzmusic"), NULL, 0, NULL);               // 落子声音，先把前面一次的音乐关闭  
	mciSendString(_T("open ./music/stone1111.mp3 alias lzmusic"), NULL, 0, NULL);                                // 打开音乐
	mciSendString(_T("play lzmusic"), NULL, 0, NULL);                  // 仅播放一次
}

void tizi()
{
	mciSendString(_T("close  tzmusic"), NULL, 0, NULL);                                         // 提子声音，先把前面一次的音乐关闭  
	mciSendString(_T("open ./music/tizi.mp3 alias tzmusic"), NULL, 0, NULL);                    // 打开音乐
	mciSendString(_T("play tzmusic"), NULL, 0, NULL);                                           // 仅播放一次
	
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

int jia_yan_b(int x ,int y)
{
	for (int m = 1; m <= 19; m++)
	{
		for (int n = 1; n <= 19; n++)
		{
			if (weizhi[x][y] == 1 && (weizhi[x - 1][y] == 1 || weizhi[x][y - 1] == 1 || weizhi[x + 1][y] == 1 || weizhi[x][y + 1] == 1))
			{
				return 1;
			}
			else
				return 0;
		}
	}
}

int jia_yan_w(int x, int y)
{
	for (int m = 1; m <= 19; m++)
	{
		for (int n = 1; n <= 19; n++)
		{
			if (weizhi[x][y] == 2&& (weizhi[x - 1][y] == 2 || weizhi[x][y - 1] == 2 || weizhi[x + 1][y] == 2 || weizhi[x][y + 1] == 2))	
			{
				return 1;
			}
			else
				return 0;
		}
	}
}
	
void no_breath()
{
	for (int x = 1; x <= 19; x++)                                                   //禁手单列测试
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

	for (int x = 1; x <= 19; x++)                                                   //禁手单列测试
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
	mciSendString(_T("close  pssmusic"), NULL, 0, NULL);               // 落子声音，先把前面一次的音乐关闭  
	mciSendString(_T("open ./music/pass.wav alias pssmusic"), NULL, 0, NULL);                                // 打开音乐
	mciSendString(_T("play pssmusic"), NULL, 0, NULL);                  // 仅播放一次
	T = T - 5;
}

void Eat_more_than_one_w()
{    
	int x, y;
	TCHAR s13[] = _T("↓当前步数   黑方提子-             白方提子-               计算量：");
	setbkcolor(RGB(220, 180, 70));
	outtextxy(1000, 360, s13);
	_stprintf_s(hong, _T("%d"), W_dead);                                                           //把步数数字变成字符，下一步显示字符  
	outtextxy(1170, 360, hong);
	_stprintf_s(hong, _T("%d"), B_dead);														   //把步数数字变成字符，下一步显示字符  
	outtextxy(1320, 360, hong);
	
	for (x = 1; x <= 19; x++)
	{	
		for (y = 1; y <= 19; y++)
		{
			 if((weizhi[x][y] == 2 && weizhi[x - 1][y] != 0 && weizhi[x + 1][y] != 0 && weizhi[x][y - 1] != 0 && weizhi[x][y + 1] != 0))
			

					{
						weizhi[x][y] = 8;
					
						_stprintf_s(hong, _T("%d"), 8);                                                 //把步数数字变成字符，下一步显示字符  
						outtextxy(x*B-3, y*B-7, hong);                                                  //写步数
						Eat_more_than_one_w();                                                          //////////////////开始递归循环,  对内存监控发现，鼠标不点击，数据一直在跑
						
					}
		
		}
	}		
}

void Eat_more_than_one_b()                           
{
	int x, y;
	TCHAR s13[] = _T("↓当前步数   黑方提子-             白方提子-    ");
	setbkcolor(RGB(220, 180, 70));
	outtextxy(1000, 360, s13);
	_stprintf_s(hong, _T("%d"), W_dead);                                                           //把步数数字变成字符，下一步显示字符  
	outtextxy(1170, 360, hong);
	_stprintf_s(hong, _T("%d"), B_dead);														   //把步数数字变成字符，下一步显示字符  
	outtextxy(1320, 360, hong);
	for (x = 1; x <= 19; x++)
	{	
		for (y = 1; y <= 19; y++)
		{
			 if(weizhi[x][y] == 1 && (weizhi[x - 1][y] != 0 && weizhi[x + 1][y] != 0 && weizhi[x][y - 1] != 0 && weizhi[x][y + 1] != 0))
				
				{
					weizhi[x][y] = 7;
			
					_stprintf_s(hong, _T("%d"), 7);                                                 //把步数数字变成字符，下一步显示字符  
					outtextxy(x*B-3, y*B-7, hong);                                                  //写步数
					Eat_more_than_one_b();                                        //////////////////开始递归循环,  对内存监控发现，鼠标不点击，数据一直在跑
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
				tizi();
				//weizhi[a / 40][b / 40] = 7;                          //黑如果吃了白一颗子，位置标记过渡一下，防止白立即吃回来
				//_stprintf_s(bai, _T("%d"), 3);                       //测试记录用，待删除
				//outtextxy(x*B - 3, y*B - 7, bai);			     //
				if ((x == 4 && y == 4) || (x == 10 && y == 4) || (x == 16 && y == 4))	                 //假如在星位，需要补画原来白点*
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
				else if (y*B == 40 && x*B != 40 && x*B != 760)			    //上边
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (y*B == 760 && x*B != 40 && x*B != 760)			 //下边
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B != 40 && y*B != 760)				 //左边
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B != 40 && y*B != 760)              //右边
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B == 40)                               //左上角
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 760 && y*B == 40)                              //右上角
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 760 && y*B == 760)                             //右下角
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
			
																											// }
				_stprintf_s(bai, _T("%d"), 0);                                      //测试记录用，待删除
				outtextxy(x*B - 3, y*B - 7, bai);			                        //
				da_jie[1][0] = x;
				da_jie[1][1] = y;
				
				W_dead++;
			}
		}
	}
	
	FlushBatchDraw();
	if (jia_yan_w(a / B, b / B)==1)
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
				tizi();
				if ((x == 4 && y == 4) || (x == 10 && y == 4) || (x == 16 && y == 4))	                 //假如在星位，需要补画原来白点*
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
				else if (y*B == 40 && x*B != 40 && x*B != 760)					 //上边
				{
					getimage(&img, 1020, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (y*B == 760 && x*B != 40 && x*B != 760)			 //下边
				{
					getimage(&img, 1020, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B != 40 && y*B != 760)				 //左边
				{
					getimage(&img, 980, 60, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B != 40 && y*B != 760)              //右边
				{
					getimage(&img, 1180, 60, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B == 40)                               //左上角
				{
					getimage(&img, 980, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 760 && y*B == 40)                              //右上角
				{
					getimage(&img, 1180, 20, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 760 && y*B == 760)                             //右下角                      
				{
					getimage(&img, 1180, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				else if (x*B == 40 && y*B == 760)
				{
					getimage(&img, 980, 180, 40, 40);
					putimage(x*B - 20, y*B - 20, &img);
				}
				
																											// }
				_stprintf_s(bai, _T("%d"), 0);                                                      //测试记录用，待删除
				outtextxy(x*B - 3, y*B - 7, bai);			                                       //
				da_jie[1][0] = x;
				da_jie[1][1] = y;
				B_dead++;											                                       //tizi(a/B ,b/B);     //提掉白死子
			}

			
		}
		
		FlushBatchDraw();
	}
	if (jia_yan_b(a / B, b / B)==1)
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
							_stprintf_s(hong, _T("%d"), 2);                                        //把步数数字变成字符，下一步显示字符  
							outtextxy(x*B - 3, y*B - 7, hong);                                     //写步数
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
							_stprintf_s(hong, _T("%d"), 1);                                        //把步数数字变成字符，下一步显示字符  
							outtextxy(x*B - 3, y*B - 7, hong);                                     //写步数
							                                                                       //提子数量
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
			}										                                  //画九个星位的点，包括天元
		}
    }
}

void  creat_data()
{
	
	fopen_s(&fp, "./data/qipu.txt", "a+");
	fprintf(fp,"%d\n",buff);
	fclose(fp);
	
}

int *read_data()
{
	int i;
	int k = 1;
	int count = 0;  //统计文件中字符个数
	int sum_row;  //统计文件中字符个数
	int ch = 0;
	FILE *fp;  //文件指针
	int a_in[200] = { 0 };  //保存文件内容的数组
	int b_in[200] = { 0 };  //保存文件内容的数组
	fopen_s(&fp, "./data/qipu.txt", "r");   //打开文件，只读									
	if (fp == NULL)
	{
		printf("File cannot open! ");
		return 0;
	}
	while (!feof(fp))   //读文件，直到文件末尾
	{
		ch = fgetc(fp);  //将文件内容附给flag
		if (ch == '\n')  //如果为\n表示到行尾，便进行计数
			count++;
	}
	sum_row = count + 1; //加上文件最后一行，即为文件总的行数
	rewind(fp);              //如果用rewind函数，可以把阅读指针退回到文件开头，这样就可以不用重新打开文件fp1；
	for (i = 1; i<sum_row; i++)  //控制文件行数
	{
		fscanf_s(fp, "%d", &a_in[i]);  //将文件其中一行内容保存到数组中
		b_in[k] = a_in[i];  //将读到的每一行的数据都保存到b_in数组中
		k++;                //行数加一
	}
	b_in[0] = sum_row;       //第一个数用了记录步数
	fclose(fp);
	return   b_in;          //返回数组指针
	
}

void save()
{
	fopen_s(&fp, "./data/qipu.txt", "w+");

	for (int m = 1; m <= i;m++)
	{
		fprintf(fp, "%d\n", buffer[m]);
	}
	fclose(fp);


}

void fu_pan()
{
	int *p;																		  //记录读棋谱返回的数组首地址
	int bs;																		  //记录棋谱的步数
	int fu_bk_x[100];                                                      
	int fu_bk_y[100];
	int fu_wt_x[100];
	int fu_wt_y[100];
	for (int m = 0; m < 21; m++)
		for (int n = 0; n < 21; n++)
		{
			weizhi[m][n] = { 0 };
		}
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 0.5);

		huitu();
		p = read_data();														 //读棋谱文件

	for (int m = 0; m < *p; m++)
	{
		printf("%d\n", *(p + m));												  //成功读到保存的数据   
	}
		bs = *(p+0);														      //步数必须得导出来,即数组第一个值
	for (bk = 1; bk <= bs /2; bk++)         
	{
		fu_bk_x[bk] = *(p + 2 * bk - 1) / 10000;
		fu_bk_y[bk] = *(p + 2 * bk - 1) % 1000;

		fu_wt_x[bk] = *(p + 2 * bk) / 10000;
		fu_wt_y[bk] = *(p + 2 * bk) % 1000;
	}
	
	for (int m = 1; m <= bs /2; m++)
	{
		setlinecolor(RGB(30, 30, 30));                                           //设置线条颜色
		setfillcolor(RGB(30, 30, 30));
		fillcircle(fu_bk_x[m], fu_bk_y[m], RQ);                                  //画棋子    
		setbkcolor(BLACK);														 //文字背景   
		settextcolor(WHITE);													 //文字颜色
		_stprintf_s(bai, _T("%d"), 1);											 //把步数数字变成字符，下一步显示字符 
		outtextxy(fu_bk_x[m] - 3, fu_bk_y[m] - 7, bai);                                //写白棋步数
		luozi();
		FlushBatchDraw();                                                       //永远的刷新，否则就是等待很久，然后一次刷新
		Sleep(1000);

		setlinecolor(WHITE);                                                     //设置线条颜色
		setfillcolor(WHITE);
		fillcircle(fu_wt_x[m], fu_wt_y[m], RQ);								     //画棋子    
		setbkcolor(WHITE);														 //文字背景   
		settextcolor(BLACK);
		_stprintf_s(bai, _T("%d"), 2);											 //把步数数字变成字符，下一步显示字符 
		outtextxy(fu_wt_x[m] - 3, fu_wt_y[m] - 7, bai);											 //写白棋步数
		luozi();
		
		FlushBatchDraw();                                                       //永远的刷新，否则就是等待很久，然后一次刷新
		Sleep(1000);
	}
	
	
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
					getimage(&img, 1020, 60, 40, 40);                                      ///////////////////观察效果用途
					putimage(x*B - 20, y*B - 20, &img);                                    //画白棋/////////////////////////////////////////
					weizhi[x][y] = 0;
					_stprintf_s(hong, _T("%d"), 0);                                        //把步数数字变成字符，下一步显示字符
					outtextxy(x*B - 3, y*B - 7, hong);                                     //写步数
					B_dead++;   //提子数量
					tizi();
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
					getimage(&img, 1020, 60, 40, 40);                                      ///////////////////观察效果用途
					putimage(x*B - 20, y*B - 20, &img);                                    //画白棋/////////////////////////////////////////
					weizhi[x][y] = 0;
					_stprintf_s(hong, _T("%d"), 0);                                        //把步数数字变成字符，下一步显示字符
					outtextxy(x*B - 3, y*B - 7, hong);                                     //写步数
					W_dead++;  //提子数量
					tizi();
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
	 int	m = 3;
	// buff = jieshou();
	//上面这个只是随机产生下棋的位置，后面的工作有两大类，一类是实现网络对战，那么需要建立网络连接，接受对方数据同时传输自己数据出去
	// a = read_data() / 10000;
	// b = read_data() % 10000 - 2;
	 srand((unsigned)time(NULL));
	 a = (rand() % 20) * B;
	 b = (rand() % 20) * B;

	if (a >= 40 && a <= 760 && b >= 40 && b <= 760)                                        //记录位置状态,有棋子则实现禁手
	{
				if (i % 2 == 0 && weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
				{
					da_jie[1][0] = 0;                                                      //打劫的位置复位
					da_jie[1][1] = 0;
					//白棋行动，轮流下棋算法，步数除以2的余数，只有0或1，对应两个玩家
					bai1[wt] = a;                                                      //白棋横坐标
					bai2[wt] = b;													   //白棋纵坐标 
					wt++;
					weizhi[a / 40][b / 40] = 2;                                        //记录位置的状态，0为没有棋子，1为有红棋子，2为有白色棋子
					creat_data();
					setlinecolor(WHITE);
					setfillcolor(WHITE);
					fillcircle(a, b, RQ);
					setbkcolor(WHITE);												   //文字背景   
					settextcolor(BLACK);                                               //文字颜色
																					   //_stprintf_s(bai, _T("%d"), i);                                   //把步数数字变成字符，下一步显示字符 
					_stprintf_s(bai, _T("%d"), i);                                     //////
					if (i >= 10)
					m = 7;
					outtextxy(a - m, b - 7, bai);                                      //写白棋步数

					for (y = 0; y <= 20; y++)                                //棋盘外围一圈赋值，切换为落子方
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


					TCHAR s13[] = _T("下一手：黑棋");
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

		/****边线提子大概思路是将外围扩大一路，即纵横第二十路，全部赋值为5，计算的时候直接调用就行，总表数据是从0到800，单独用一个二维数组表示***/
		/****四个角暂时还没有处理***************************************************************************************************************/
		
		
	}

	FlushBatchDraw();													             //保持前面图形，增加刷新内容	
                                  /////////////////////////////////////////////////////
}

void xiaqi_bk()
{
	int	m = 3;
	//buff = jieshou();
	//上面这个只是随机产生下棋的位置，后面的工作有两大类，一类是实现网络对战，那么需要建立网络连接，接受对方数据同时传输自己数据出去
	//buff = (a / B * 100 + b / B);
	// a = buff/100*B;
	// b = buff%100*B;
	srand((unsigned)time(NULL));
	a = (rand() % 20) * B;
	b = (rand() % 20) * B;
	

	if (a >= 40 && a <= 760 && b >= 40 && b <= 760)                        //记录位置状态,有棋子则实现禁手
	{
		if (i % 2 == 1 && weizhi[a / B][b / B] == 0 && a != da_jie[1][0] * 40 && b != da_jie[1][1] * 40)
		//黑棋行动
		{
				da_jie[1][0] = 0;
				da_jie[1][1] = 0;

				hei1[bk] = a;                                                       //黑棋横坐标
				hei2[bk] = b;                                                       //黑棋纵坐标
				bk++;
				weizhi[a / 40][b / 40] = 1;                                        //记录位置的状态，1为有黑棋子，0为没有棋子，2为有白色棋子
				creat_data();
				setlinecolor(RGB(30, 30, 30));
				setfillcolor(RGB(30, 30, 30));
				fillcircle(a, b, RQ);

				setbkcolor(RGB(30, 30, 30));									   //文字背景
				settextcolor(WHITE);                                               //文字颜色
				_stprintf_s(hong, _T("%d"), i);                                  //把步数数字变成字符，下一步显示字符
				//_stprintf_s(hong, _T("%d"), 1);
				if (i >= 10)
				 m = 7;
				outtextxy(a - m, b - 7, hong);                         //写黑棋步数
				for (y = 0; y <= 20; y++)                                      //棋盘外围一圈赋值，切换为落子方
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

				TCHAR s13[] = _T("下一手：白棋");
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

	FlushBatchDraw();													             //保持前面图形，增加刷新内容	
																					 /////////////////////////////////////////////////////
}

void go_online_wt()
{
	int a, b;
	int m = 3;
	
		a = jieshou() / 10000;
		b = jieshou() % 1000 -2;
	
	da_jie[1][0] = 0;                                                      //打劫的位置复位
	da_jie[1][1] = 0;
	//白棋行动，轮流下棋算法，步数除以2的余数，只有0或1，对应两个玩家
	bai1[wt] = a;                                                      //白棋横坐标
	bai2[wt] = b;													   //白棋纵坐标 
	wt++;
	weizhi[a / 40][b / 40] = 2;                                        //记录位置的状态，0为没有棋子，1为有红棋子，2为有白色棋子

	setlinecolor(WHITE);
	setfillcolor(WHITE);
	fillcircle(a, b, RQ);
	setbkcolor(WHITE);												   //文字背景   
	settextcolor(BLACK);                                               //文字颜色
   //_stprintf_s(bai, _T("%d"), i);                                   //把步数数字变成字符，下一步显示字符 
	_stprintf_s(bai, _T("%d"), i);                                     //////
	if (i >= 10)
		m = 7;
	outtextxy(a - m, b - 7, bai);                                      //写白棋步数

	for (y = 0; y <= 20; y++)                                //棋盘外围一圈赋值，切换为落子方
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


	TCHAR s13[] = _T("下一手：黑棋");
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
}

void go_online_bk()
{
	int m = 3;
	int a, b;
		a = jieshou() / 10000;
		b = jieshou() % 1000 - 1;
	
	
	da_jie[1][0] = 0;
	da_jie[1][1] = 0;

	hei1[bk] = a;                                                       //黑棋横坐标
	hei2[bk] = b;                                                       //黑棋纵坐标
	bk++;
	weizhi[a / 40][b / 40] = 1;                                        //记录位置的状态，1为有黑棋子，0为没有棋子，2为有白色棋子

	setlinecolor(RGB(30, 30, 30));
	setfillcolor(RGB(30, 30, 30));
	fillcircle(a, b, RQ);

	setbkcolor(RGB(30, 30, 30));									   //文字背景
	settextcolor(WHITE);                                               //文字颜色
	_stprintf_s(hong, _T("%d"), i);                                  //把步数数字变成字符，下一步显示字符
																	 //_stprintf_s(hong, _T("%d"), 1);
	if (i >= 10)
		m = 7;
	outtextxy(a - m, b - 7, hong);                         //写黑棋步数
	for (y = 0; y <= 20; y++)                                      //棋盘外围一圈赋值，切换为落子方
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

	TCHAR s13[] = _T("下一手：白棋");
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

