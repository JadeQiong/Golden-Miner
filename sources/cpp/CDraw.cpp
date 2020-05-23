#include"CDraw.h"
#include<highgui.h>
#include "opencv2\highgui\highgui.hpp"
#include "opencv2/imgproc.hpp"

CDraw::CDraw() {
	;
}

CDraw::~CDraw() {
	;
}

void CDraw::DrawObjects(IplImage *back,IplImage * obj,int x,int y) 
{
	//CV_IMAGE_ELEM是一个宏，用来读取像素
//这里读的是彩图 格式如下：#define CV_IMAGE_ELEM( image, elemtype, row, col) 
/*	CV_IMAGE_ELEM(image, uchar,y, 3*x)
	CV_IMAGE_ELEM(image, uchar,y, 3*x+1)
	CV_IMAGE_ELEM(image, uchar,y, 3*x+2)
	但要想正确的得到图像的坐标为(x,y)点的像素值，是应该这样写CV_IMAGE_ELEM(Image, uchar, y, x)
	要注意像素点的坐标xy和行列值的顺序是相反的
	以下所有CV_IMAGE_EKEM同理 和函数差不多用法
*/
	for (int i = 0;i < obj->width;i++) 
	{
		for (int j = 0;j < obj->height;j++) 
		{
			if (CV_IMAGE_ELEM(obj, uchar, j, i * 3)  <40 
			&&CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 1) < 40
			&& CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 2) < 40)
			continue;
			CV_IMAGE_ELEM(back,uchar,j + y,(i + x) * 3)=CV_IMAGE_ELEM(obj,uchar,j,i * 3);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 1) = CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 1);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 2) = CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 2);
		}
	}
}

void CDraw::DrawWhite(IplImage *back, IplImage *gold, int x, int y) {
	for (int i = 0;i < gold->width && (i + x) < back->width;i++)
		for (int j = 0;j < gold->height && (j + y) < back->height;j++)
		{
			if (i<gold->width/2 && CV_IMAGE_ELEM(gold, uchar, j, i * 3) > 200
				&& CV_IMAGE_ELEM(gold, uchar, j, i * 3 + 1) > 200
				&& CV_IMAGE_ELEM(gold, uchar, j, i * 3 + 2) > 200)
				continue;
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3) = CV_IMAGE_ELEM(gold, uchar, j, i * 3);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 1) = CV_IMAGE_ELEM(gold, uchar, j, i * 3 + 1);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 2) = CV_IMAGE_ELEM(gold, uchar, j, i * 3 + 2);
		}
	return;
}



void CDraw::DrawGold(IplImage *back, IplImage *gold, int x, int y) 
{
	for (int i = 0;i < gold->width && (i + x) < back->width;i++)
		for (int j = 0;j < gold->height && (j + y) < back->height;j++)
		{
			if (CV_IMAGE_ELEM(gold, uchar, j, i * 3) < 50 
				&& CV_IMAGE_ELEM(gold, uchar, j, i * 3 + 1) < 50 
				&& CV_IMAGE_ELEM(gold, uchar, j, i * 3 + 2) < 50)
				continue;
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3) = CV_IMAGE_ELEM(gold, uchar, j, i * 3);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 1) = CV_IMAGE_ELEM(gold, uchar, j, i * 3 + 1);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 2) = CV_IMAGE_ELEM(gold, uchar, j, i * 3 + 2);
		}
	return;
}

void CDraw::DrawHook(IplImage *back, IplImage * obj, int x, int y) 
{
	for (int i = 0;i < obj->width && (i + x) < back->width;i++) 
	{
		for (int j = 0;j < obj->height && (j + y) < back->height;j++) 
		{
			if (CV_IMAGE_ELEM(obj, uchar, j, i * 3) < 20
				&& CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 1) < 20
				&& CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 2) < 20)
				continue;
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3) = CV_IMAGE_ELEM(obj, uchar, j, i * 3);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 1) = CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 1);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 2) = CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 2);
		}
	}
}

void CDraw::ShowTimeLeft(IplImage *background, int time)
{
	char t[40];
	sprintf_s(t, "%d",time);
	CvFont font_time;
	cvInitFont(&font_time, CV_FONT_HERSHEY_DUPLEX, 1, 1, 0, 2, 8);
	cvPutText(background, "Time: ", CvPoint(20,30), &font_time, CvScalar(20, 30, 0));
	if(time>=20)
	cvPutText(background, t, CvPoint(120, 30), &font_time, CvScalar(0, 30, 0));
	else
	cvPutText(background, t, CvPoint(120, 30), &font_time, CvScalar(0, 30, 250));
	cvPutText(background, "s ", CvPoint(167, 30), &font_time, CvScalar(20, 30, 0));
	//cvInitFont()
	return;
}

void CDraw::ShowCloud(IplImage * back,IplImage * obj, int x, int y) {
	for (int i = 0;i < obj->width;i++)
	{
		for (int j = 0;j < obj->height;j++)
		{
			if (CV_IMAGE_ELEM(obj, uchar, j, i * 3) < 20
				&& CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 1) < 20
				&& CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 2) < 20)
				continue;
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3) = CV_IMAGE_ELEM(obj, uchar, j, i * 3);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 1) = CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 1);
			CV_IMAGE_ELEM(back, uchar, j + y, (i + x) * 3 + 2) = CV_IMAGE_ELEM(obj, uchar, j, i * 3 + 2);
		}
	}
	return;
}

void CDraw::ShowScore(IplImage * background ,int score,int goal_score)
{
	char s[20], s_goal[20];
	sprintf_s(s, "%d", score);
	sprintf_s(s_goal, "%d", goal_score);
	CvFont font_s;
	cvInitFont(&font_s, CV_FONT_HERSHEY_DUPLEX, 1, 1, 0, 1, 8);
	cvPutText(background,"Your Score: ", CvPoint(600, 30), &font_s, CvScalar(50, 30, 0));
	cvPutText(background, s, CvPoint(795, 30), &font_s, CvScalar(20, 60, 0));
	cvPutText(background, "Goal Score:", CvPoint(600, 60), &font_s, CvScalar(50, 30, 0));
	cvPutText(background, s_goal, CvPoint(795, 60), &font_s, CvScalar(70, 90, 0));
	return;
}

void CDraw::ShowLevel(IplImage *background,int lev) 
{
	char s[10];
	sprintf_s(s, "%d", lev);
	CvFont font_s;
	cvInitFont(&font_s, CV_FONT_HERSHEY_DUPLEX, 1, 1, 0, 1, 8);
	cvPutText(background, "Level: ", CvPoint(25, 60), &font_s, CvScalar(50, 30, 0));
	cvPutText(background, s, CvPoint(120, 60), &font_s, CvScalar(50, 30, 0));
	return;
}


void CDraw::BagAddscore() {
	IplImage *page = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\endpage.jpg", 1);
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvPutText(page, "Score + 500 !", CvPoint(100, 300), &font, CV_RGB(255, 150, 0));
	cvNamedWindow("> w <", 1);
	cvMoveWindow("> w <", 250, 100);
	cvShowImage("> w <", page);
	cvWaitKey(900);
	cvDestroyWindow("> w <");
	cvReleaseImage(&page);
	return;
}

void CDraw::BagMinusscore() {
	IplImage *page = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\endpage.jpg", 1);
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvPutText(page, "Score - 300 ...", CvPoint(100, 300), &font, CV_RGB(255, 150, 0));
	cvNamedWindow("QAQ", 1);
	cvMoveWindow("QAQ", 250, 100);
	cvShowImage("QAQ", page);
	cvWaitKey(900);
	cvDestroyWindow("QAQ");
	cvReleaseImage(&page);
	return;
}


void CDraw::BagAddTime() {
	IplImage *page = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\endpage.jpg", 1);
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvPutText(page, "Time + 20 s !", CvPoint(100, 300), &font, CV_RGB(255, 150, 0));
	cvNamedWindow("`O v O`", 1);
	cvMoveWindow("`O v O`", 250, 100);
	cvShowImage("`O v O`", page);
	cvWaitKey(900);
	cvDestroyWindow("`O v O`");
	cvReleaseImage(&page);
	return;
}