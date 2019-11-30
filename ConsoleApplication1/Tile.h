#pragma once
#include "AllHeader.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Vector3.h"
#include "GLFW/glfw3.h"

enum class TileState
{
	NONE,
	SELECTED,
	RELEASED,
	HIGHLIGHT,
};

class Tile : public GameObject
{
private:
	Scale offsetScale;
	Scale scale;
public:
	float life;
	float maxLife;
	TileState tileState = TileState::NONE;
	Scale originScale;
	Scale curScale;
	Sprite* selectedSprite;
	Sprite* releasedSprite;
	bool doHighlight = false;

	Tile(Sprite* sprite) : GameObject(sprite){};
	Tile() {};
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool CheckBoxArea(float x, float y);
};