#include"CEndPage.h"
#include "opencv2/imgproc.hpp"

CEndPage::CEndPage()
{
	;
}

CEndPage::~CEndPage()
{
	;
}

void CEndPage::ShowEndPage(int s) 
{
	end_page = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\endpage.jpg", 1);
	char score[10];
	sprintf_s(score,"%d",s);
	CvFont font, font_score;
	cvInitFont(&font_score, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvPutText(end_page, "Final Score:", CvPoint(100, 300), &font, CV_RGB(255, 150, 0));
	cvPutText(end_page, score, CvPoint(450, 300), &font_score, CV_RGB(250,150 , 0));
	cvNamedWindow("EndPage", 1);
	cvMoveWindow("EndPage", 250, 100);
	cvShowImage("EndPage", end_page);
	cvWaitKey(3000);
	return;
}

void CEndPage::ShowEndPage_2() {

	end_page = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\endpage.jpg", 1);
	CvFont font, font_score;
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvPutText(end_page, "The bomb exploded QAQ ", CvPoint(100, 300), &font, CV_RGB(255, 150, 0));
	cvNamedWindow("EndPage", 1);
	cvMoveWindow("EndPage", 250, 100);
	cvShowImage("EndPage", end_page);
	cvWaitKey(1500);
	return;
}

void CEndPage::ReleaseEndPage()
{
	cvReleaseImage(&end_page);
	return;
}

void CEndPage::ShowThankPage()
{
	thank_page = cvLoadImage("C:\\Users\\87179\\Desktop\\pictures\\endpage.jpg", 1);
	CvFont font, font_score;
	cvInitFont(&font_score, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvInitFont(&font, CV_FONT_HERSHEY_DUPLEX, 2, 1, 0.2, 2, 8);
	cvPutText(end_page, "Thank You ! `OwO`", CvPoint(100, 390), &font, CV_RGB(255, 150, 0));
	cvNamedWindow("EndPage", 1);
	cvShowImage("EndPage", end_page);
	cvWaitKey(0);
	cvReleaseImage(&thank_page);
	return;
}
