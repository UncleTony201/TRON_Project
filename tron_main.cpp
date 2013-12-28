#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
//#include <fstream>
#include "hgegui.h"

#include <list>

#include "plume_sector.h"

using namespace std;

#define ITER 1

float x,y;

HGE *hge = 0;

// bool pause = 1;

int score = 0, score2 = 0;
int direction = 1, direction2 = 1;
float velocity = 0.1f, velocity2 = 0.1f, st, st2;
float new_pos_x = 0, new_pos_y = 0, new_pos_x2 = 0, new_pos_y2 = 0; 
bool increase = true, increase2 = true;

float time_s=0;

bool menu_check = true;
bool menu_update(float time);

void pause_func();
bool pause = false;

hgeSprite			*DFs,*PSs,*logo_s;
list<plume_sector*>	plume_drawed;
list<plume_sector*> plume_drawed2;

hgeFont		*fnt, *fnt2;
hgeGUI*		gui;

HTEXTURE	DFt		= 0;
HTEXTURE	PSt		= 0;
HTEXTURE	PSt2	= 0;
HTEXTURE	logo_t	= 0;

HEFFECT		bike_sound	= 0;
HEFFECT		menu_music  = 0;

bool FrameFunc()
{
	time_s+=hge->Timer_GetDelta();
	if(menu_check) {
		hge->Effect_PlayEx(menu_music,10,0,1,true);
		gui->Update(time_s);
		if(menu_update(time_s))
			return true;
	}
	else{
		hge->Effect_Free(menu_music);
		while(plume_drawed.size() == 0 && increase){
		plume_sector* start = new plume_sector(hgeVector(31,31),PSt);
		plume_drawed.push_front(start);}

		while(plume_drawed2.size() == 0 && increase2){
		plume_sector* start2 = new plume_sector(hgeVector(615,31),PSt2);
		plume_drawed2.push_front(start2);}


		switch(hge->Input_GetKey()) {
		case HGEK_W: if(direction != 1) direction = 0; break;
		case HGEK_S: if(direction != 0) direction = 1; break;
		case HGEK_A: if(direction != 3) direction = 2; break;
		case HGEK_D: if(direction != 2) direction = 3; break;
		}

		switch(hge->Input_GetKey()) {
		case HGEK_UP:	 if(direction2 != 1) direction2 = 0; break;
		case HGEK_DOWN:  if(direction2 != 0) direction2 = 1; break;
		case HGEK_LEFT:  if(direction2 != 3) direction2 = 2; break;
		case HGEK_RIGHT: if(direction2 != 2) direction2 = 3; break;
		}

		if(hge->Timer_GetTime()-st>velocity)
		{
			if(!pause)
			for(int i = 0; i < ITER; i++)
			{
				plume_sector* pSector = new plume_sector(hgeVector(plume_drawed.back()->GetPosition()+hgeVector(new_pos_x,new_pos_y)),PSt);
				plume_drawed.push_back(pSector);
				score+=10;
			}
			switch(direction){
		case 0:
			new_pos_x = 0;
			new_pos_y = -8;
			break;
		case 1:
			new_pos_x = 0;
			new_pos_y = 8;
			break;
		case 2:
			new_pos_x = -8;
			new_pos_y = 0;
			break;
		case 3:
			new_pos_x = 8;
			new_pos_y = 0;
			break;
			}
			st = hge->Timer_GetTime();
		}

		if(hge->Timer_GetTime()-st2>velocity2)
		{
			if(!pause)
			for(int i = 0; i < ITER; i++)
			{
				plume_sector* pSector2 = new plume_sector(hgeVector(plume_drawed2.back()->GetPosition()+hgeVector(new_pos_x2,new_pos_y2)),PSt2);
				plume_drawed2.push_back(pSector2);
				score+=10;
			}
			switch(direction2){
		case 0:
			new_pos_x2 = 0;
			new_pos_y2 = -8;
			break;
		case 1:
			new_pos_x2 = 0;
			new_pos_y2 = 8;
			break;
		case 2:
			new_pos_x2 = -8;
			new_pos_y2 = 0;
			break;
		case 3:
			new_pos_x2 = 8;
			new_pos_y2 = 0;
			break;
			}
			st2 = hge->Timer_GetTime();
		}

		if(plume_drawed.back()->GetPosition().x < 14
			|| plume_drawed.back()->GetPosition().x > 638 
			|| plume_drawed.back()->GetPosition().y < 14
			|| plume_drawed.back()->GetPosition().y > 430) {plume_drawed.pop_back();}

		if(plume_drawed2.back()->GetPosition().x < 14 
			|| plume_drawed2.back()->GetPosition().x > 638 
			|| plume_drawed2.back()->GetPosition().y < 14
			|| plume_drawed2.back()->GetPosition().y > 430) {plume_drawed2.pop_back();}


		for(list<plume_sector*>::iterator it = plume_drawed2.begin(); it != plume_drawed2.end();)
		{
			if(plume_drawed.back()->GetPosition()==(*it)->GetPosition())
			{
				increase = false;
				plume_drawed.clear();
				//for(list<plume_sector*>::iterator i = plume_drawed.begin(); i != plume_drawed.end(); /**/)
				//{
				//	delete (*i);
				//	i = plume_drawed.erase(i);
				//}
			}
			else it++;
		}
		for(list<plume_sector*>::iterator it = plume_drawed.begin(); it != plume_drawed.end();)
		{
			if(plume_drawed2.back()->GetPosition()==(*it)->GetPosition())
			{
				increase2 = false;
				plume_drawed.clear();
				//for(list<plume_sector*>::iterator i = plume_drawed2.begin(); i != plume_drawed2.end(); /**/)
				//{
				//	delete (*i);
				//	i = plume_drawed2.erase(i);
				//}
			}
			else it++;
		}
			
		for(int i = 0; i < ITER; i++) 
			if (hge->Input_GetKeyState(HGEK_SHIFT)) 
				velocity = 0.02f;
			else velocity = 0.1f;

		for(int i = 0; i < ITER; i++) 
			if (hge->Input_GetKeyState(HGEK_CTRL)) 
				velocity2 = 0.02f;
			else velocity2 = 0.1f;

		//if(plume_drawed.size() > 0 || plume_drawed.size() > 0) 
		//{
			//while(!pause)hge->Effect_PlayEx(bike_sound,10,0,0,true);
		//}
		if(!pause)hge->Effect_PlayEx(bike_sound,10,0,0,true);

		if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;

		if (hge->Input_GetKeyState(HGEK_SPACE))
			pause = 1;
		if (hge->Input_GetKeyState(HGEK_ENTER))
			pause = 0;
	}

	return false;
}

bool RenderFunc()
{
   	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	if(menu_check) {
		gui->Render();
		fnt2->SetColor(ARGB(255,255,255,255));
		if(int(hge->Timer_GetTime())%2 == 0)
		fnt2->printf(200,280,HGETEXT_LEFT,"Press ENTER to start.");
		logo_s->Render(83,98);
	}
	else {
		DFs->Render(0,0);

		fnt->SetColor(ARGB(255,0,0,255));
		if(pause)if(int(hge->Timer_GetTime())%2 == 0)fnt2->printf(180,280,HGETEXT_LEFT,"Press ENTER to continue.");
		fnt->printf(5, 450, HGETEXT_LEFT, "Player 1\nScore:%d \nPress SPACE to pause or ESCAPE to exit the game.", score);
		fnt->printf(332, 450, HGETEXT_LEFT, "Player 2\nScore:%d ", score);

		for(list<plume_sector*>::iterator i = plume_drawed.begin(); i!= plume_drawed.end(); i++)
		{
			(*i)->Render();
		}

		for(list<plume_sector*>::iterator i = plume_drawed2.begin(); i!= plume_drawed2.end(); i++)
		{
			(*i)->Render();
		}
	}		
	hge->Gfx_EndScene();

	
	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "TRON: Light Cycles");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, true);
	hge->System_SetState(HGE_SCREENWIDTH, 653);
	hge->System_SetState(HGE_SCREENHEIGHT, 550);
	hge->System_SetState(HGE_SCREENBPP, 32);


	if(hge->System_Initiate())
	{
		DFt    = hge->Texture_Load("images/frontier.bmp");
		PSt    = hge->Texture_Load("images/sector.bmp");
		PSt2   = hge->Texture_Load("images/sector2.bmp");
		logo_t = hge->Texture_Load("images/tron_logo.png");

		fnt  = new hgeFont("font/font1.fnt");
		fnt2 = new hgeFont("font/font1.fnt");

		gui  = new hgeGUI();

		bike_sound = hge->Effect_Load("sounds/bike_sound.wav");
		menu_music = hge->Effect_Load("sounds/menu_music.mp3");

		if(!DFt || !PSt)
		{
			MessageBox(NULL, "Can't load BGt.BMP or PSt.BMP", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		DFs    = new hgeSprite(DFt,0,0,653,445);
		logo_s = new hgeSprite(logo_t,0,0,487,157);

		hge->System_Start();

		hge->Texture_Free(DFt);
		hge->Texture_Free(PSt);
		hge->Texture_Free(PSt2);
		hge->Texture_Free(logo_t);

		hge->Effect_Free(bike_sound);
		hge->Effect_Free(menu_music);

		delete gui;
		delete DFs;
		delete logo_s;
		delete fnt;

		for(list<plume_sector*>::iterator i = plume_drawed.begin(); i != plume_drawed.end(); /**/)
		{
			delete (*i);
			i = plume_drawed.erase(i);
		}

	}
	else
	{	
		MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
	}

	hge->System_Shutdown();
	hge->Release();

	return 0;
}

bool menu_update(float time){
	gui->Update(time);
	if(/*start->GetState()
		||*/hge->Input_GetKeyState(HGEK_ENTER))menu_check=false;
	return false;
}
