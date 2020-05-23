#pragma once
#include<highgui.h>
class CDraw 
{
public:
	void ShowTimeLeft(IplImage *, int);
	void ShowScore(IplImage*, int, int);
	void ShowLevel(IplImage *, int);
	void ShowCloud(IplImage *,IplImage*, int ,int);

	void DrawObjects(IplImage*, IplImage*,int ,int );
	void DrawWhite(IplImage *, IplImage*, int, int);
	void DrawGold(IplImage *, IplImage*, int, int);
	void DrawHook(IplImage *, IplImage*, int, int);

	void BagAddscore();
	void BagMinusscore();
	void BagAddTime();

	CDraw();
	virtual ~CDraw();
private:
protected:
};