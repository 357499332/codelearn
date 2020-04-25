/**************** (C) COPYRIGHT 2020  QIAN_GANG ***************************************************************************
*
* File Name          : MAIN.CPP
* Author             : QIAN_GANG
* Version            : V1.00
* Date               : 2020/04/13
* 1+1=10
* 计算机的世界里本身是没有0和1这个概念的，一切都是电荷作用，电荷形成电压，电压分为有和无，用有和无来等价于1和0，因此从源头上来说；
* 编程语言最开始都是脉冲电流形成的等效机器语言；
* 后来用形成汇编语言，用于记录机器电路里面的命令；
* 但是历史总是累进式发展的，各国家民族不可能总是要从0开始不断的重新发现各种理论和发明各种工具，比如汉字，祖先已经发明好了，你有什么理由和多大的能力再发明语言？
* 就已知的历史来说，人类是一个命运共同体，合则兴，分则亡；
* 计算机组成原理——DOS命令——汇编语言——C语言——代码书写规范——数据结构——编译原理——操作系统——计算机网络——数据库原理——正则表达式——面向对象——架构；
* 线性代数、离散数学；
* 多用小脑和手，少用眼睛和嘴，会更快学好编程；
* 眼过千遍不如手过一遍！
* 书看千行不如手敲一行！
* 手敲千行不如单步Debug一行！
* 单步Debug千行单步Release一行；
* 单步Release千行不如单步反汇编一行！
* 不要迷信书、考题、老师、回帖；要迷信CPU、编译器、调试器、运行结果；
* 任何理论、权威、传说、真理、标准、解释、想象、知识……都比不上摆在眼前的事实；
*
* 1、2020.04.14修改
*     版本: V2.0
*	  修改了:
*    (1)、大合并，将所有源文件合并到一个工程，通过初始控制台选择进入任何子程序;
*   （2)、还没有实现子程序的返回功能;																			   **mark一下** 基本实现，后续优化
* 2、2020.04.16修改
*     版本: V2.1
*	  修改了:
*    (1) 、增加了第五项，各种计算功能;
*   （2）、解决了围棋部分返回时边线出界bug，就是把鼠标位置获取算法细化一下，四条边，四个角单独处理，增加点工作量；
*   （3）、解决了交替下棋步数错乱的问题，将记录步数的变量i作为全局变量,变化统计放到鼠标点击的函数里去，左键下棋就是i++,但是如果点击了右键必须要减一次i--;
*	 (4) 、关闭图形界面回到主界面问题也得到解决，查询库文档，用  closegraph()关闭界面函数即可；
*	（5）、加入复盘功能，就是在下每一步的时候，用数组来记录每一步的坐标，总共四个数组分别记录红黑纵横坐标。
* 3、2020.04.18修改
*     版本: V2.2
*	  修改了:
*	（1）、在复盘时往棋子上显示步数，有个很奇怪的BUG，界面（0，0）坐标处总是反复交替出现红黑棋子；
*	（2）、增加落子声音；
*   （3）、建立了文件的整体架构，为将来功能扩张做充分的准备；
*    (4) 、下一步重点解决悔棋、吃子、禁手和打劫！问题，禁手和打劫！
* 4、2020.04.19修改
*     版本: V2.3
*	  修改了:
*	（1）、解决棋子重复问题，禁手的一部分；
*	（2）、增加吃子声音；
*   （3）、播放落子声音单独用一个函数复用；
*    (4) 、解决单个吃子问题 
*    (5) 、增加悔棋/后退功能按钮,边界线条暂时没处理了
*   （6）、增加退出按钮
*   （7）、初步实现打劫禁手设置
* 5、2020.04.21修改
*     版本: V2.4
*    (1) 、解决禁手问题,边界问题和禁手问题花了很多脑子，最后找到了比较巧妙有趣的方法克服；                                            
*   （2）、解决吃多个子、即死活算法
*    (3) 、打劫禁手算法解决用缓一步禁手就行，即当前着手位置不能与刚死的位置一样
*   （4）、解决征子算法
* 6、2020.04.23修改  
*   （1）、优化边界算法，与补画边框算法，更加简单好理解
*   （2）、解决吃子BUG，吃子的遍历循环放到鼠标动作函数外面与huitu()函数并列，全部遍历棋盘，问题简单化
*   （3）、改右键为悔棋，按钮为PASS一手
*   （4）、背景音乐修改
**************************************************************************************************************************/
#include"头文件.h"
#define _CRT_SECURE_NO_WARNINGS
void daji();
void bjmusic();
void geussnum();
void suxue();
void weiqi();
char c = 0;
int main()
{
	void(*p)();                                           //函数指针
	p = weiqi;
	system("title 程序学习+围棋");                         //更改标题
	system("color f4");							          //设置屏幕为白底红字
	system("mode con cols=120 lines=50");            	  //设置窗口大小为120×50
	printf("输入1：听音乐\n输入2：猜数游戏\n输入3：测试围棋\n输入4：打飞机(空格键射击）\n输入5：数学计算\n");
	while (1)
	{
			c = _getch();
			switch (c)
			{
			case '1' :
				bjmusic();                                //播放音乐
				break;
			case '2' :
				geussnum();                               //猜数游戏
				break;
			case '3':
				(*p)();
				//weiqi;
				break;
			case '4':
				daji();
				break;
			case'5':
				suxue();
				break;
			}
	}
}