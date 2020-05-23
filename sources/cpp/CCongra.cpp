#include"CCongra.h"
#include "opencv2/imgproc.hpp"

CCongra::CCongra() 
{
	;
}
CCongra::~CCongra() 
{
	;
}

void CCongra::IniCongra() 
{
	congra_page = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\endpage.jpg", 1);
	return;
}

void CCongra::ShowCongra(int score) 
{
	char s[30];
	sprintf_s(s, "%d", score);
	CvFont font, font_score;
	cvInitFont(&font_score, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvPutText(congra_page, "Congratulations!", CvPoint(100, 300), &font, CV_RGB(255, 150, 0));
	cvPutText(congra_page, "Current score is: ", CvPoint(100, 350), &font, CV_RGB(255, 150, 0));
	cvPutText(congra_page, s, CvPoint(525, 350), &font_score, CV_RGB(250, 150, 0));
	cvNamedWindow("GoldMiner", 1);
	cvShowImage("GoldMiner", congra_page);
	cvWaitKey(2000);
	return;
}


void CCongra::Work(int score) 
{
	IniCongra();
	ShowCongra(score);
	ReleaseCongra();
	return;
}

void CCongra::ReleaseCongra() 
{
	cvReleaseImage(&congra_page);
	return;
}