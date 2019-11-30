#pragma once
#include "AllHeader.h"
#include "Sprite.h"
#include "Transformation.h"
#include "Vector3.h"
#include "Color.h"

class GameObject
{
private:
	bool m_ownSprite = false;
	Sprite* m_sprites = NULL;
	Vector3 m_position;
	float m_rotation;
	Scale m_scale;
	Color m_color;

public:
	GameObject();
	GameObject(Sprite* sprite);

	void SetPos(Vector3 pos);
	const Vector3& GetPos();

	void SetRotation(float rotate);
	const float& GetRotation();
	
	void SetScale(float scaleX, float scaleY);
	const Scale& GetScale();
	
	void SetSprite(Sprite* sprite);
	Sprite* GetSprite();
	
	void SetColor(Color& color);
	const Color& GetColor();
	
	virtual void Draw();
	virtual void Update();
};