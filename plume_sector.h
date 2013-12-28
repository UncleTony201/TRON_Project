#ifndef PLUME_SECTOR_H
#define PLUME_SECTOR_H
#pragma once

#include "hge.h"
#include "hgevector.h"
#include "hgesprite.h"

//#define PLAYER_FRICTION 0.95

class plume_sector
{
protected:

private:	
	static HGE*		hge;
	hgeVector		Position;
	//hgeVector       Velocity;
	hgeSprite*		Sprite;
	hgeRect			BoundingBox;
	float           Speed;
public:
	plume_sector(hgeVector Position, HTEXTURE &Texture);
	plume_sector(plume_sector& x);
	~plume_sector();

	void Update(float delta);
	void Render();

	//void		SetVelocity(hgeVector velocity) { Velocity = velocity; };
	void		SetBoundingBox(hgeRect boundingbox) { BoundingBox = boundingbox; };
	void		SetPosition(hgeVector position) { Position = position; };
	hgeRect		GetBoundingBox() { return BoundingBox; };
	hgeVector	GetPosition() { return Position; };
	/*float	GetPosition_x() { return Position.x; };
	float	GetPosition_y() { return Position.y; };*/
	
	//hgeVector	GetPosition_x() {return Position.x; };
};

#endif