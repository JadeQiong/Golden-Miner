#pragma once
#include<highgui.h>

class CEndPage 
{
public:
	IplImage *thank_page;
	IplImage *end_page;
	void ShowThankPage();
	void ShowEndPage(int);
	void ReleaseEndPage();
	void ShowEndPage_2();
	CEndPage();
	~CEndPage();

private:
protected:
};