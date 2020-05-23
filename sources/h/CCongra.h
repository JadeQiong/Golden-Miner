#pragma once
#include<highgui.h>
class CCongra 
{
public:
	CCongra();
	virtual ~CCongra();
	IplImage *congra_page;
	void Work(int);
	void IniCongra();
	void ShowCongra(int);
	void ReleaseCongra();
private:
protected:
};