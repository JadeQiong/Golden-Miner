#include"CGamePlay.h"
#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include"CDraw.h"
#include"CEndPage.h"
#include<Windows.h>

/*
	IplImage *back_ground_image, *car, *person;
	IplImage *gold[10],*hook[10],*m_gold[10];
	CvPoint p_car, p_person;
	CvPoint start_hook, end_hook, p_gold[10];
	int time, level, score, goal_score;
	bool dir=0, get=0;
	void IniPlayPage();
	void ShowPlayPage();
	void Hook();
	void judge();
	void LoadObjects();
	void ReleasePlayPage();
	CGamePlay();
	virtual ~CGamePlay();
*/

CGamePlay::CGamePlay()
{
	;
}

CGamePlay::~CGamePlay() 
{
	;
}


void CGamePlay::IniPlayPage(int lev) 
{
	LoadObjects();
	SetGoal(lev);
	IniNumbers();
	ArrangePosition();
}

void CGamePlay::Hook() 
{
	//
	CDraw draw;
	IplImage *background = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\play_background.jpg", 1);
	while (1) 
	{

		cvCopy(play_background_image, background);
		//画钩子的绳索
		if (dir) 
		{
			end_hook.x += increase;
			//绳索原点（417，75） 钩子轨迹是以原点为圆心的圆（下半圆）
			end_hook.y = y0 + sqrt(10000-(end_hook.x-x0)*(end_hook.x-x0));
			cvLine(background, end_hook, start_hook,CvScalar(20,60,0),2,8,0);
		}
		else 
		{
			end_hook.x -= increase;
			end_hook.y = y0 + sqrt(10000-(end_hook.x-x0)*(end_hook.x-x0));
			cvLine(background, end_hook, start_hook, CvScalar(20,60,0),2,8,0);
		}

		//越界处理
		if (end_hook.x > x0 + 93) dir = 0;
		if (end_hook.x < x0 - 93) dir = 1;

		if (dir_cloud==0)
		{
			p_cloud.x -= 1;
			draw.ShowCloud(background, cloud, p_cloud.x, p_cloud.y);
		}
		else
		{
			p_cloud.x += 1;
			draw.ShowCloud(background, cloud, p_cloud.x, p_cloud.y);
		}

		if (p_cloud.x >= 550 ) dir_cloud = 0;
		if (p_cloud.x <= 130) dir_cloud = 1;

		for (int i = 0;i <CalLim();i++) 
			if (object[i]) 
				draw.DrawGold(background, m_gold[i], p_gold[i].x, p_gold[i].y);

		DrawHook();
		draw.DrawHook(background, hook[id_hook],hook_now.x,hook_now.y);

		draw.DrawObjects(background, car, start_hook.x-25, start_hook.y-10);
		draw.DrawObjects(background, person, p_person.x, p_person.y);

		//显示分数&时间
		draw.ShowScore(background, score, goal_score);
		draw.ShowLevel(background, level);
		finish= clock();
		int tmp = double(finish - start) / CLOCKS_PER_SEC;
		draw.ShowTimeLeft(background,time_limit- tmp);
		if(tmp>=time_limit) break;
		//if (time - time_add++/ 68 == 0) break;

		cvNamedWindow("GoldMiner", 1);
		cvMoveWindow("GoldMiner", 200, 70);
		cvShowImage("GoldMiner",background);

		if (::GetAsyncKeyState(VK_ESCAPE) && 0x8000)  exit(0);
		//int k = cvvWaitKey(5);
		//::GetAsyncKeyState(VK_DOWN) && 0x8000 
		/*if (mark) {
			mark = 0;
			continue;
		}*/
		if (::GetAsyncKeyState(VK_DOWN) && 0x8000) {
			//记录按下挖矿时候的位置 
			mark = 1;
			CvPoint temp = end_hook;
			cvCopy(play_background_image, background);
			judge(background);
			//如果挖到，从头开始
			if (get)
				end_hook = cvPoint(377, 118);
			//如果未挖到，从记录的位置开始
			else {
				end_hook = temp;
				mark = 1;
			}
		}
		else{
			if(level == 1)
				cvWaitKey(13);
			if (level == 2)
				cvWaitKey(8);
			if (level == 3)
				cvWaitKey(5);
		}
	}
}

void CGamePlay::judge(IplImage* pic)
{
	CDraw draw;
	get = 0;
	IplImage *background;
	background = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\play_background.jpg", 1);
	//while(x)与while(x>0)不一样... debug两天
	// 如果让绳索边缘碰到图是边缘 再画钩子 会报错（内存泄漏
	while (end_hook.x < background->width - 40  && end_hook.x > 40
		&& end_hook.y < background->height - 40 &&end_hook.y> y0) 
	{
		cvCopy(pic, background);
		if (dir_cloud == 0)
		{
			p_cloud.x -= 1;
			draw.ShowCloud(background, cloud, p_cloud.x, p_cloud.y);
		}
		else
		{
			p_cloud.x += 1;
			draw.ShowCloud(background, cloud, p_cloud.x, p_cloud.y);
		}

		if (p_cloud.x >= 550) dir_cloud = 0;
		if (p_cloud.x <= 130) dir_cloud = 1;

		for (int i = 0;i < CalLim();i++) 
		{
			if (object[i]) 
			{
				draw.DrawGold(background, m_gold[i], p_gold[i].x, p_gold[i].y);
			}
		}
		//给纵坐标一个微小增量 画直线
		//相似三角
		end_hook.y += 2;
		//如果在左边 往左延伸
		if (end_hook.x < x0) 
		{
			end_hook.x -= 2 * (x0 - end_hook.x) / (1.0*(end_hook.y - y0 - 2));
		}
		//右边 同理
		if (end_hook.x > x0) 
		{
			end_hook.x += 2 * (end_hook.x - x0) / (1.0*(end_hook.y - y0 - 2));
		}
		//if(get&&flag_show)

		//往下延申
		if(!get)
		cvLine(background, end_hook, start_hook, CvScalar(20, 20, 0), 2, 8, 0);
		if(get)
			cvLine(background, end_hook, start_hook, CvScalar(20, 40, 0), 2, 8, 0);
		//找钩子 画钩子
		DrawHook();
		draw.DrawHook(background, hook[id_hook], hook_now.x, hook_now.y);

		draw.DrawObjects(background, car, start_hook.x - 25, start_hook.y - 10);
		draw.DrawObjects(background, person, p_person.x, p_person.y);

			//draw.DrawObjects(background, hook[0], end_hook.x, end_hook.y);
			//显示时间 得分 目标得分

		draw.ShowLevel(background, level);
		draw.ShowScore(background, score, goal_score);
		finish = clock();
		int tmp = double(finish - start) / CLOCKS_PER_SEC;

		draw.ShowTimeLeft(background, time_limit - tmp);
		//if (time - time_add++ / 68 == 0) break;
		if (tmp >= time_limit) break;

		cvNamedWindow("GoldMiner", 1);
		cvMoveWindow("GoldMiner", 200, 70);
		cvShowImage("GoldMiner", background);
		cvWaitKey(1);
		//判断是否有物体被抓住

		for (int i = 0;i <CalLim();i++) 
		{
			//如果距离足够近（误差值25）且物体存在
			if (IfGet(i,m_gold[i],end_hook)) 
			{
				AddScore(i);
				object[i] = 0;
				for (int j = p_gold[i].x;j < p_gold[i].x + m_gold[i]->width;j++) 
				{
					for (int k = p_gold[i].y;k < p_gold[i].y + m_gold[i]->height;k++) 
					{
						CV_IMAGE_ELEM(background, uchar, k, j * 3) = CV_IMAGE_ELEM(play_background_image, uchar, k, j * 3);
						CV_IMAGE_ELEM(background, uchar, k, j * 3 + 1) = CV_IMAGE_ELEM(play_background_image, uchar, k, j * 3 + 1);
						CV_IMAGE_ELEM(background, uchar, k, j * 3 + 2) = CV_IMAGE_ELEM(play_background_image, uchar, k, j * 3 + 2);
					}
				}
				while ((end_hook.x - start_hook.x)*(end_hook.x - start_hook.x) +
					(end_hook.y - start_hook.y)*(end_hook.y - start_hook.y) > 8){
					//flag_show = 1;
					//cvCopy
					cvCopy(play_background_image, background);
					for (int j = 0;j <CalLim();j++) 
					{
						if (object[j]) 
						{
							draw.DrawGold(background, m_gold[j], p_gold[j].x, p_gold[j].y);
						}
					}

					draw.DrawGold(background, m_gold[i], end_hook.x - m_gold[i]->width / 2, end_hook.y + 2);

					if (dir_cloud == 0)
					{
						p_cloud.x -= 1;
						draw.ShowCloud(background, cloud, p_cloud.x, p_cloud.y);
					}
					else
					{
						p_cloud.x += 1;
						draw.ShowCloud(background, cloud, p_cloud.x, p_cloud.y);
					}

					if (p_cloud.x >= 550) dir_cloud = 0;
					if (p_cloud.x <= 130) dir_cloud = 1;


					//plus可调控拉钩子速度
					if (get_stone)
						plus = 1;
					else
						plus = 2;
					//if(end_hook.y!=y0+plus)
					end_hook.y -= plus;
					//这里加减法写错了  debug半小时 QwQ
					//内存无法访问 && 除以0
					if (end_hook.x >= x0  )
						end_hook.x -= plus * (end_hook.x - x0) / (end_hook.y - y0 + plus);

					if (end_hook.x  <x0)
						end_hook.x  += plus * (x0 - end_hook.x ) / (end_hook.y - y0 + plus);

					//抓到物体后回缩的钩子 要慢一些
					cvLine(background, end_hook, start_hook, cvScalar(20, 40, 0), 2, 8, 0);
					//打印 钩子
					DrawHook();
					draw.DrawHook(background, hook[id_hook], hook_now.x, hook_now.y);

					draw.DrawObjects(background, car, start_hook.x - 25, start_hook.y - 10);
					draw.DrawObjects(background, person, p_person.x, p_person.y);

					//显示时间，得分
					draw.ShowLevel(background, level);
					draw.ShowScore(background, score, goal_score);
					finish = clock();
					int tmp = double(finish - start) / CLOCKS_PER_SEC;
					draw.ShowTimeLeft(background, time_limit-tmp);
					if (tmp >= time_limit) break;
					//if (time - time_add++/ 68 == 0) break;

					cvNamedWindow("GoldMiner", 1);
					cvMoveWindow("GoldMiner", 200, 70);
					cvShowImage("GoldMiner", background);
					cvWaitKey(1);
				}
				get = 1;
				//如果已经抓到 就完成这次判断。Debug 1h纪念
				return;
			}
		}
	}

		if (!get) 
		{

			while (sqrt((end_hook.x - start_hook.x)*(end_hook.x - start_hook.x) + (end_hook.y - start_hook.y)*(end_hook.y - start_hook.y)) >= 8
				&& end_hook.y >= 8) 
			{

				cvCopy(play_background_image, background);
				for (int j = 0;j < CalLim();j++) 
				{
					if (object[j]) 
					{
						draw.DrawGold(background, m_gold[j], p_gold[j].x, p_gold[j].y);
					}
				}
					end_hook.y -= 2;
				if (end_hook.x > x0)
					end_hook.x -= 2 * (end_hook.x - x0) / (end_hook.y - y0 + 2);
				if (end_hook.x < x0)
					end_hook.x += 2 * (x0 - end_hook.x) / (end_hook.y - y0 + 2);

				//往上回缩的绳子
				cvLine(background, end_hook, start_hook, cvScalar(20, 60, 0), 2, 8, 0);

				if (dir_cloud == 0)
				{
					p_cloud.x -= 1;
					draw.ShowCloud(background, cloud, p_cloud.x, p_cloud.y);
				}
				else
				{
					p_cloud.x += 1;
					draw.ShowCloud(background, cloud, p_cloud.x, p_cloud.y);
				}

				if (p_cloud.x >= 550) dir_cloud = 0;
				if (p_cloud.x <= 130) dir_cloud = 1;
	
				//显示钩子
				DrawHook();
				draw.DrawHook(background, hook[id_hook], hook_now.x, hook_now.y);

				draw.DrawObjects(background, car, start_hook.x - 25, start_hook.y - 10);
				draw.DrawObjects(background, person, p_person.x, p_person.y);

				//显示分数 时间
				draw.ShowLevel(background, level);
				draw.ShowScore(background, score, goal_score);
				finish = clock();
				int tmp = double(finish - start) / CLOCKS_PER_SEC;
				draw.ShowTimeLeft(background, time_limit-tmp);
				if (tmp >= time_limit) break;
				//if (time - time_add++/ 68 == 0) break;

				cvNamedWindow("GoldMiner", 1);
				cvMoveWindow("GoldMiner", 200, 70);
				cvShowImage("GoldMiner", background);
				cvWaitKey(1);
			}
		}
	return;
}

//安排
void CGamePlay::AddScore(int id) {
	/*
	s 0
	m 1 3	
	l 5
	s1 s2 2 4 6
	*/
	if (level == 1) 
	{
		if (id == 0) score += 100;
		if (id == 1 || id== 3) score += 250;
		if (id == 2 || id == 4 ) 
		{ 
			score += 50;
			get_stone = 1;
		}
		if (id == 5) score += 500;

		if (id == 6) 
		{
			//产生随机数
			int r_num = int(start + (end - start)*rand() / (RAND_MAX + 1.0));
			if (r_num % 4 == 1) 
			{
				//时间+=20s
				time_limit += 20;
				CDraw show;
				show.BagAddTime();
			}
			if (r_num % 4 == 2)
			{
				//结束游戏
				CEndPage w;
				w.ShowEndPage_2();
				time_limit = 5;
				end = 1;
			}
			if (r_num % 4 == 3)
			{
				//加分500
				score += 500;
				CDraw show;
				show.BagAddscore();
			}
			if (r_num % 4 == 0) 
			{
				//减分300
				score -= 300;
				CDraw show;
				show.BagMinusscore();
			}
		}
		if (id == 7) score += 1000;
	}
	/*
	s 0
	m 1 2 3
	l 5
	s1 s2 4 6
	c 7
	*/
	if (level == 2) 
	{
		if (id == 0)score += 100;
		else if (id == 1 || id == 2 || id == 3) score += 250;
		else if (id == 5) score += 500;
		else if (id == 4 || id == 6) 
		{ 
			score += 50; 
			get_stone = 1;
		}
		//bag
		else if (id == 7) {
				//产生随机数
				int r_num = int(start + (end - start)*rand() / (RAND_MAX + 1.0));
				if (r_num % 4 == 1)
				{
					//时间+=20s
					time_limit += 20;
					CDraw show;
					show.BagAddTime();
				}
				if (r_num % 4 == 2)
				{
					//结束游戏
					CEndPage w;
					w.ShowEndPage_2();
					time_limit = 5;
					end = 1;
				}
				if (r_num % 4 == 3)
				{
					//加分500
					score += 500;
					CDraw show;
					show.BagAddscore();
				}
				if (r_num % 4 == 0)
				{
					//减分300
					score -= 300;
					CDraw show;
					show.BagMinusscore();
				}
		}
		
		else if (id == 8) score += 800;
		else if (id == 9) score += 800;
	}
	/*
	s: 0
	m:1 2  8
	l:4
	c:3 7
	s1:5 6
	*/
	if (level == 3) 
	{
		if (id == 0)score += 100;
		else if (id == 2 || id == 1) score += 250;
		else if (id == 4) score += 500;
		else if (id == 3 || id == 7) score += 1000;
		else if (id == 5 || id == 6) 
		{ 
			score += 50;
			get_stone = 1;
		}
		else if (id == 9) score += 800;
		else if (id == 8) {
				//产生随机数
				int r_num = int(start + (end - start)*rand() / (RAND_MAX + 1.0));
				if (r_num % 4 == 1)
				{
					//时间+=20s
					time_limit += 20;
					CDraw show;
					show.BagAddTime();
				}
				if (r_num % 4 == 2)
				{
					//结束游戏
					CEndPage w;
					w.ShowEndPage_2();
					time_limit = 5;
					end = 1;
				}
				if (r_num % 4 == 3)
				{
					//加分500
					score += 500;
					CDraw show;
					show.BagAddscore();
				}
				if (r_num % 4 == 0)
				{
					//减分300
					score -= 300;
					CDraw show;
					show.BagMinusscore();
				}
		}
		else if (id == 10) score += 900;
	}
}

//安排金子出现位置
void CGamePlay::ArrangePosition() 
{

	if (level == 1) 
	{
		score = 0;
		//处理所有出现的位置
		p_gold[0] = CvPoint(130, 560);
		p_gold[1] = CvPoint(350, 500);
		p_gold[2] = CvPoint(245, 180);
		p_gold[3] = CvPoint(200, 300);
		p_gold[4] = CvPoint(700, 250);
		p_gold[5] = CvPoint(600, 400);
		p_gold[6] = CvPoint(238, 390);
		p_gold[7] = CvPoint(437, 456);
		p_gold[8] = CvPoint(543, 486);

		p_gold[9] = CvPoint(340, 340);

		//为所有位置安排物体
		m_gold[0] = cvCloneImage(gold[0]);
		m_gold[1] = cvCloneImage(gold[1]);
		m_gold[2] = cvCloneImage(gold[3]);
		m_gold[3] = cvCloneImage(gold[1]);
		m_gold[4] = cvCloneImage(gold[3]);
		m_gold[5] = cvCloneImage(gold[2]);
		m_gold[6] = cvCloneImage(gold[6]);
		m_gold[7] = cvCloneImage(gold[5]);
		m_gold[8] = cvCloneImage(gold[7]);
		//

		m_gold[9] = cvCloneImage(gold[8]);

	}
	if (level == 2) 
	{
		p_gold[0] = CvPoint(143, 388);
		p_gold[1] = CvPoint(150, 500);
		p_gold[2] = CvPoint(445, 380);
		p_gold[3] = CvPoint(59, 320);
		p_gold[4] = CvPoint(625, 255);
		p_gold[5] = CvPoint(660, 437);
		p_gold[6] = CvPoint(238, 399);
		p_gold[7] = CvPoint(600, 560);
		p_gold[8] = CvPoint(543, 486);
		p_gold[9] = CvPoint(340, 340);

		m_gold[0] = cvCloneImage(gold[0]);
		m_gold[1] = cvCloneImage(gold[1]);
		m_gold[2] = cvCloneImage(gold[1]);
		m_gold[3] = cvCloneImage(gold[1]);
		m_gold[4] = cvCloneImage(gold[3]);
		m_gold[5] = cvCloneImage(gold[2]);
		m_gold[6] = cvCloneImage(gold[4]);
		m_gold[7] = cvCloneImage(gold[6]);
		m_gold[8] = cvCloneImage(gold[7]);
		m_gold[9] = cvCloneImage(gold[8]);

	}
	if (level == 3) 
	{
		p_gold[0] = CvPoint(143, 388);
		p_gold[1] = CvPoint(450, 500);
		p_gold[2] = CvPoint(245, 280);
		p_gold[3] = CvPoint(209, 300);
		p_gold[4] = CvPoint(605, 350);
		p_gold[5] = CvPoint(400, 197);
		p_gold[6] = CvPoint(238, 399);
		p_gold[7] = CvPoint(500, 560);
		p_gold[8] = CvPoint(543, 486);
		p_gold[9] = CvPoint(340, 340);
		p_gold[10] = CvPoint(600, 190);

		m_gold[0] = cvCloneImage(gold[0]);
		m_gold[1] = cvCloneImage(gold[1]);
		m_gold[2] = cvCloneImage(gold[1]);
		m_gold[3] = cvCloneImage(gold[5]);
		m_gold[4] = cvCloneImage(gold[2]);
		m_gold[5] = cvCloneImage(gold[4]);
		m_gold[6] = cvCloneImage(gold[3]);
		m_gold[7] = cvCloneImage(gold[5]);
		m_gold[8] = cvCloneImage(gold[6]);
		m_gold[9] = cvCloneImage(gold[7]);
		m_gold[10] =cvCloneImage(gold[8]);
	}
}

//从本地加载参数
void CGamePlay::LoadObjects() 
{
	play_background_image = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\play_background.jpg", 1);
	gold[0] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\gold0.jpg", 1);
	gold[1] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\gold1.jpg", 1);
	gold[2] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\gold2.jpg", 1);

	gold[3] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\stone1.jpg", 1);
	gold[4] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\stone2.jpg", 1);

	gold[5] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\crystal.jpg", 1);
	gold[6] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\bag.jpg", 1);

	gold[7]= cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\gold3.jpg", 1);
	gold[8]=cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\gold4.jpg", 1);

	person = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\24.jpg", 1);
	car = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\car.jpg", 1);
	cloud = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\cloud.jpg", 1);

	hook[0] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook.png", 1);
	hook[1] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook-1.png", 1);
	hook[2] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook-2.png", 1);
	hook[3] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook-3.png", 1);
	hook[4] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook-4.png", 1);
	hook[5] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook-5.png", 1);
	hook[6] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook-6.png", 1);
	hook[7] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook+1.png", 1);
	hook[8] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook+2.png", 1);
	hook[9] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook+3.png", 1);
	hook[10] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook+4.png", 1);
	hook[11] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook+5.png", 1);
	hook[12] = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\hook+6.png", 1);
}

//释放内存防止泄露
void CGamePlay::ReleasePlayPage() 
{

	for (int i = 0;i < 10;i++)
		cvReleaseImage(&gold[i]);
	for (int i = 0;i < 15;i++)
	{
		cvReleaseImage(&hook[i]);
		cvReleaseImage(&m_gold[i]);
	}
	cvReleaseImage(&person);
	cvReleaseImage(&car);
	cvReleaseImage(&play_background_image);
	cvReleaseImage(&cloud);
	return;
}

//初始化参数
void CGamePlay::IniNumbers() 
{
	p_car = CvPoint(340, 56);
	p_person = CvPoint(345, 32);
	increase = 1;
	time_limit = 30;
	start = 0;finish = 0;
	start = clock();
	end_hook = cvPoint(327, 118);
	p_cloud.x = 130;
	p_cloud.y = 34;
	x0 = 417;y0 = 75;
	start_hook = cvPoint(x0, y0);
	for (int i = 0;i < 14;i++) 
		object[i] = 1;
	return;

}

//设置目标分数
void CGamePlay::SetGoal(int lev) 
{
	if (lev == 1) goal_score = 500;
	if (lev == 2) goal_score = 1000;
	if (lev == 3) goal_score = 3000;
	level = lev;
}

//画钩子，调整位置
void CGamePlay::DrawHook() 
{
	hook_now = end_hook;
	double angle;
	if (end_hook.y != y0) 
	{
		angle = 100 * abs(end_hook.x - x0) / (end_hook.y - y0);
		if (end_hook.x <= x0) 
		{
			if (angle < 5) id_hook = 0;
			else if (angle < 30) id_hook = 1;
			else if (angle < 70) id_hook = 2;
			else if (angle < 105) id_hook = 3;
			else if (angle < 139) id_hook = 4;
			else if (angle < 175) id_hook = 5;
			else if (angle < 210) id_hook = 6;
		}
		else 
		{
			if (angle < 5) id_hook = 0;
			else if (angle < 30) id_hook = 7;
			else if (angle < 105) id_hook = 8;
			else if (angle < 105) id_hook = 9;
			else if (angle < 139) id_hook = 10;
			else if (angle < 175) id_hook = 11;
			else if (angle < 210) id_hook = 12;
		}
	}
	else id_hook = 0;

	CDraw draw_hook;
	hook_now.x -= 20;
	if (id_hook == 0) {
		//hook_now.x += 6;
		hook_now.y -= 4;
	}
	if (id_hook == 1) 
	{
		hook_now.x -= 6;
		hook_now.y -= 6;
	}
	if (id_hook == 2) 
	{
		hook_now.x -= 7;
		hook_now.y -= 7;
	}
	if (id_hook == 3)
	{
		hook_now.x -= 10;
		hook_now.y -= 10;
	}
	if (id_hook == 4) 
	{
		hook_now.x -= 11;
		hook_now.y -= 12;
	}
	if (id_hook == 5) 
	{
		hook_now.x -= 10;
		hook_now.y -= 14;
	}
	if (id_hook == 6) 
	{
		hook_now.x -= 11;
		hook_now.y -= 16;
	}

	if (id_hook == 7) 
	{
		//hook_now.x -= 10;
		hook_now.y -= 5;
	}

	if (id_hook == 8) 
	{
		//hook_now.x -= 10;
		hook_now.y -= 8;
	}
	if (id_hook == 9) 
	{
		hook_now.x += 2;
		hook_now.y -= 10;
	}
	if (id_hook == 10) 
	{
		hook_now.x += 5;
		hook_now.y -= 13;
	}
	if (id_hook == 11) 
	{
		hook_now.x += 6;
		hook_now.y -= 13;
	}
	if (id_hook == 12) 
	{
		hook_now.x += 10;
		hook_now.y -= 15;
	}
}

int CGamePlay::CalLim()
{
	int lim;
	if (level == 1) lim = 8;
	if (level == 2) lim = 10;
	if (level == 3) lim = 11;
	return lim;
}

//可调控难度
bool CGamePlay::IfGet(int id, IplImage * gold, CvPoint hook)
{

	if (object[id] == 0) return 0;
	long long dis = (end_hook.x - (p_gold[id].x + m_gold[id]->width / 2))*(end_hook.x - (p_gold[id].x + m_gold[id]->width / 2))
		+ (end_hook.y - (p_gold[id].y + m_gold[id]->height / 2))*(end_hook.y - (p_gold[id].y + m_gold[id]->height / 2));
	if (level == 1)
	{
		//small
		if (id == 0) {
			if (dis <= 45 * 45) return 1;
			else return 0;
		}
		//mid
		if (id == 1 || id == 3) {
			if (dis <= 45 * 45) return 1;
			else return 0;
		}
		//stone
		if (id == 2 || id == 4 || id == 6)
		{
			if (dis <= 30 * 30) return 1;
			else return 0;
		}
		//bag
		if (id == 5) {
			if (dis <= 65 * 65) return 1;
			else return 0;
		}
		if (id == 6) {
			if (dis <= 45 * 45) return 1;
			else return 0;
		}
		if (id == 7) {
			if (dis <= 30 * 30) return 1;
			else return 0;
		}
	}

	if (level == 2)
	{
		//small
		if (id == 0) {
			if (dis <= 525) return 1;
			else return 0;
		}
		//mid
		else if (id == 1 || id == 2 || id == 3) {
			if (dis <= 45 * 45) return 1;
			else return 0;
		}
		//big
		else if (id == 5) {
			if (dis <= 65 * 65) return 1;
			else return 0;
		}
		//stone
		else if (id == 4 || id == 6)
		{
			if (dis <= 30 * 30) return 1;
			else return 0;
		}
		//bag
		else if (id == 7)
		{
			if (dis <= 60 * 60) return 1;
			else return 0;
		}

		else if (id == 8 || id == 9) {
			if (dis <= 45 * 45) return 1;
			else return 0;
		}
	}

	if (level == 3) 
	{
		//small
		if (id == 0) {
			if (dis <= 25*25) return 1;
			else return 0;
		}
		//mid
		else if (id == 2 || id == 1) {
			if (dis <= 45 * 45) return 1;
			else return 0;
		}
		//big
		else if (id == 4) 
		{
			if (dis <= 65 * 65) return 1;
			else return 0;
		}
		//stone
		else if (id == 3 || id == 7)
		{
			if (dis <= 35 * 35) return 1;
			else return 0;
		}
		//cristal
		else if(id == 5 || id == 6) 
		{
			if (dis <= 30 * 30) return 1;
			else return 0;
		}
		//bag
		else if (id == 8)
		{
			if (dis <= 30 * 30) return 1;
			else return 0;
		}
		else if (id == 9) 
		{
			if (dis <= 45 * 45) return 1;
			else return 0;
		}
		else if (id = 10)
		{
			if (dis <= 45 * 45) return 1;
			else return 0;
		}
	}
	return 0;
}