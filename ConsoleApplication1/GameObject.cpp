#include "GameObject.h"

GameObject::GameObject()
{
	m_ownSprite = true;
	m_sprites = new Sprite();
}

GameObject::GameObject(Sprite* sprite)
{
	m_sprites = sprite;
}

void GameObject::SetPos(Vector3 pos)
{
	m_position = pos;
}

const Vector3& GameObject::GetPos()
{
	return m_position;
}

void GameObject::SetRotation(float rotate)
{
	m_rotation = rotate;
}

const float& GameObject::GetRotation()
{
	return m_rotation;
}

void GameObject::SetScale(float scaleX, float scaleY)
{
	m_scale.xScale = scaleX;
	m_scale.yScale = scaleY;
}

const Scale& GameObject::GetScale()
{
	return m_scale;
}

void GameObject::SetSprite(Sprite* sprite)
{
	m_sprites = sprite;
}

Sprite* GameObject::GetSprite()
{
	return m_sprites;
}

void GameObject::SetColor(Color& color)
{
	m_color = color;
}

const Color& GameObject::GetColor()
{
	return m_color;
}

void GameObject::Draw()
{
	if (m_sprites != NULL)
	{
		glEnable(GL_BLEND);
		//glBlendFunc(GL_ONE, GL_ONE);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glBlendFunc(GL_DST_COLOR, GL_ONE);
		//glBlendFunc(GL_DST_COLOR, GL_ZERO);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_sprites->Draw(m_position.x, m_position.y, m_position.z, m_rotation, m_scale.xScale, m_scale.yScale, m_color);
		glDisable(GL_BLEND);
	}
}

void GameObject::Update()
{
	
}
