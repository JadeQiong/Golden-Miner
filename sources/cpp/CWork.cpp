#include"CWork.h"
#include"CStartPage.h"
#include"CGamePlay.h"
#include"CEndPage.h"
#include"CCongra.h"

using namespace std;


CWork::CWork() {
	;
}
CWork::~CWork() {
	;
}
void CWork::Play() {

	CStartPage start;
	CEndPage end;
	CGamePlay play;
	CCongra con;
	lev = 1;
//	PlaySound(TEXT("C:\\Users\\87179\\Desktop\\pictures\\back.wav"), NULL, SND_FILENAME | SND_ASYNC);
	start.Work();
	//start.ShowHelpPage();
	//if (::GetAsyncKeyState(VK_ESCAPE) && 0x8000)  exit(0);
	char key = cvWaitKey(0);
	if (key == '1' || key == 'h') 
	{
//		start.ShowHelpPage();
		key = cvWaitKey(0);
		start.ShowStartPage();
	}
	else 
	{
		while (1) 
		{
			if (lev <= 3) 
			{
				play.IniPlayPage(lev);
				play.Hook();
				if (play.score >= play.goal_score) 
				{
					lev++;
					if (lev < 3) 
					{
						con.Work(play.score);
					}
					continue;
				}
				if (play.end == 1) break;
			}
			end.ShowEndPage(play.score);
			end.ShowThankPage();
			end.ReleaseEndPage();
			cvWaitKey(0);
			break;
		}
		cvDestroyAllWindows();
	}
	return;
}