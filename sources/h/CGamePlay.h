#pragma once
#include<highgui.h>
#include<ctime>
class CGamePlay 
{
public:
	IplImage *play_background_image, *car, *person;
	IplImage *gold[15],*hook[15],*m_gold[15];
	IplImage * cloud;

	CvPoint p_car, p_person;
	CvPoint start_hook, end_hook, p_gold[15],hook_now;
	CvPoint p_cloud;

	int level, score, goal_score,increase;
	int plus;
	int time_limit;
	int x0, y0;
	int id_hook;
	long long start, finish;

	bool flag_show;
	bool get_stone;
	bool end = 0;
	bool dir = 0, get = 0, object[15];
	bool dir_cloud = 0;
	int mark = 0;
	void IniPlayPage(int);
	//void ShowPlayPage(IplImage *);
	void Hook();
	void judge(IplImage*);

	int CalLim();
	void IniNumbers();
	void AddScore(int);
	bool IfGet(int, IplImage*,CvPoint);
	void ArrangePosition();
	void LoadObjects();
	void SetGoal(int);
	void DrawHook();
	void ReleasePlayPage();

	CGamePlay();
	virtual ~CGamePlay();

private:
protected:
};