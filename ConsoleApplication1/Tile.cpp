#include "Tile.h"

void Tile::Update()
{
	GameObject::Update();
	if (tileState == TileState::SELECTED)
	{
		SetSprite(selectedSprite);
		life = 1.0f;
		maxLife = 1.0f;
		offsetScale.xScale = originScale.xScale * 0.7f;
		offsetScale.yScale = originScale.yScale * 0.7f;
		SetScale(offsetScale.xScale, offsetScale.yScale);
		tileState = TileState::RELEASED;
	}

	if (life > 0.0f && tileState == TileState::RELEASED)
	{
		float time = 1.0f - (life / maxLife);
		scale.xScale = Lerp(offsetScale.xScale, curScale.xScale, time);
		scale.yScale = Lerp(offsetScale.yScale, curScale.yScale, time);
		SetScale(scale.xScale, scale.yScale);
		life-=0.1f;
	}

	if (life <= 0.0f && tileState == TileState::RELEASED)
	{
		SetSprite(releasedSprite);
		life -= 0.1f;
		if (doHighlight == true && life <= -1.0f)
		{
			life = 1.0f;
			offsetScale.xScale = originScale.xScale * 1.2f;
			offsetScale.yScale = originScale.yScale * 1.2f;
			tileState = TileState::HIGHLIGHT;
		}
	}
	
	if (tileState == TileState::HIGHLIGHT)
	{
		static bool reverse = false;
		float time = 1.0f - (life / maxLife);
		
		if (life <= 0.0f)
		{
			reverse = true;
		}
		else if (life >= 1.0f)
		{
			reverse = false;
		}


		scale.xScale = Lerp(offsetScale.xScale, curScale.xScale, time);
		scale.yScale = Lerp(offsetScale.yScale, curScale.yScale, time);
		SetScale(scale.xScale, scale.yScale);
		
		if (reverse == false)
		{
			life -= 0.1f;
		}
		else if (reverse == true)
		{
			life += 0.1f;
		}
	}
	
}

void Tile::Draw()
{
	GameObject::Draw();
}

bool Tile::CheckBoxArea(float x, float y)
{
	float xMin = GetPos().x - curScale.xScale;
	float xMax = GetPos().x + curScale.xScale;

	float yMin = GetPos().y - curScale.yScale;
	float yMax = GetPos().y + curScale.yScale;
	if (x >= xMin && x <= xMax && y >= yMin && y <= yMax)
	{
		return true;
	}

	return false;
}
