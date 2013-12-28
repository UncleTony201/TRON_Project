#include "plume_sector.h"

HGE* plume_sector::hge = 0;
plume_sector::plume_sector(hgeVector position, HTEXTURE &Texture) : Position(position)
{
	hge = hgeCreate(HGE_VERSION);
	Sprite = new hgeSprite(Texture,0,0,7,7);

}
//plume_sector::plume_sector(plume_sector &x)
//{
//	Position=x.Position;
//	Sprite=x.Sprite;
//	BoundingBox=x.BoundingBox;
//}
plume_sector::~plume_sector()
{
	delete Sprite;
	hge->Release();
}
void plume_sector::Update(float delta)
{
	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
}
void plume_sector::Render()
{
	Sprite->Render(Position.x,Position.y);
}