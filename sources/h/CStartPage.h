#pragma once

#include<highgui.h>
using namespace cv;
class CStartPage
{
public:
	IplImage* back_ground_image, *person,*HelpPage;
	int person_x=270, person_y=200;
	void IniStartPage();
	void ShowStartPage();
	void ShowPerson(IplImage*,int, int);
	//void ShowHelpPage();
	void ReleaseStartPage();
	void Work();
	CStartPage();
	virtual ~CStartPage();
private:
protected:
};