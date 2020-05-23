#include<highgui.h>
#include<iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "CStartPage.h"

using namespace cv;

/*  函数
	void IniStartPage();
	void ShowStartPage();
	void ShowPerson(Mat *p, int x, int y);
	CStartPage();
	virtual ~CStartPage();
*/

//构造函数与析构函数
CStartPage::CStartPage() 
{
	;
}

CStartPage::~CStartPage() 
{
	;
}


void CStartPage::IniStartPage() 
{
	//cvLoadImage(path,1)
	back_ground_image = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\homepage.jpg", 1);
	person = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\person.jpg",1);
}


void CStartPage::ShowPerson(IplImage* p,int x,int y) {
	for (int i = 1;i < p->width ;i++) 
	{
		for (int j = 1;j < p->height; j++) 
		{
			if (CV_IMAGE_ELEM(p, uchar, j, i * 3) < 20
				&& CV_IMAGE_ELEM(p, uchar, j, i * 3 + 1) < 20
				&& CV_IMAGE_ELEM(p, uchar, j, i * 3 + 2) < 20)
				continue;
			//三个色彩通道 加载图片
			CV_IMAGE_ELEM(back_ground_image, uchar, j + y, (i + x) * 3) = CV_IMAGE_ELEM(p, uchar, j, i * 3);
			CV_IMAGE_ELEM(back_ground_image, uchar, j + y, (i + x) * 3 + 1) = CV_IMAGE_ELEM(p, uchar, j, i * 3 + 1);
			CV_IMAGE_ELEM(back_ground_image, uchar, j + y, (i + x) * 3 + 2) = CV_IMAGE_ELEM(p, uchar, j, i * 3 + 2);
		}
	}
}

void CStartPage::ShowStartPage() 
{
	CvFont font,fontHelp,fontTittle;
	cvInitFont(&fontTittle, CV_FONT_HERSHEY_SCRIPT_COMPLEX, 2, 2.5, 0.2, 2, 8);
	cvInitFont(&fontHelp, CV_FONT_HERSHEY_COMPLEX_SMALL,2,1,0.6,2,8);
	cvInitFont(&font, CV_FONT_HERSHEY_COMPLEX_SMALL, 2, 1, 0.6, 2, 8);
	cvPutText(back_ground_image, " Gold  Miner ", CvPoint(167, 157), &fontTittle, CV_RGB(250, 250, 0));
	cvPutText(back_ground_image, "Press keyboard to start", CvPoint(130, 400), &font,CV_RGB(250,250,250));
	cvPutText(back_ground_image, "Help", CvPoint(580, 50), &fontHelp,CV_RGB(290,200,0));
	ShowPerson(person, person_x, person_y);

	cvNamedWindow("GoldMiner", 1);
	cvShowImage("GoldMiner", back_ground_image);
	waitKey(0);
	return;
}

/*
void ShowHelpPage() {
	IplImage *HelpPage;
	//HelpPage = cvLoadImage(" ", 1);
//	cvNamedWindow("HelpPage", 1);
//	cvShowImage("HelpPage", HelpPage);
	//cvWaitKey(10);
	return;
}
*/
void CStartPage::ReleaseStartPage()
{
	cvReleaseImage(&back_ground_image);
	cvReleaseImage(&HelpPage);
	cvReleaseImage(&person);
	return;
}

void CStartPage::Work() 
{
	IniStartPage();
	ShowStartPage();
	ReleaseStartPage();
	return;
}