#include "Sprite.h"


Sprite::Sprite()
{
    
}

Sprite::Sprite(const std::string& file)
{
    const char* texturePath = file.c_str();
	glGenTextures(1, &m_textureID);
	LoadTexture(texturePath);
}

Sprite::~Sprite()
{

}

void Sprite::LoadTexture(const char* path)
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &m_width, &m_height, &nrChannels, STBI_rgb_alpha); //0 - Auto or 4 - RGBA
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);

}

void Sprite::Draw(float x, float y, float z, float rotation, float scaleX, float scaleY, Color& color)
{
	glPushMatrix();
	glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, m_textureID);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLES);

	DrawSquare(x, y, z, rotation, scaleX, scaleY, color);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}

void Sprite::DrawLine(Vector3 start, Vector3 end, float scaleX, float scaleY, Color & color)
{
}

void Sprite::DrawSquare(float x, float y, float z, float rotation, float scaleX, float scaleY, Color& color)
{
	glColor4f(color.r, color.g, color.b, color.a);

	glTexCoord2f(0.0f, 0.0f);  glVertex3f(xCoord(-1.0f, -1.0f, rotation, scaleX, x), yCoord(-1.0f, -1.0f, rotation, scaleY, y), z);
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(xCoord(-1.0f, 1.0f, rotation, scaleX, x), yCoord(-1.0f, 1.0f, rotation, scaleY, y), z);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(xCoord(1.0f, 1.0f, rotation, scaleX, x), yCoord(1.0f, 1.0f, rotation, scaleY, y), z);

	glTexCoord2f(1.0f, 1.0f);  glVertex3f(xCoord(1.0f, 1.0f, rotation, scaleX, x), yCoord(1.0f, 1.0f, rotation, scaleY, y), z);
	glTexCoord2f(1.0f, 0.0f);  glVertex3f(xCoord(1.0f, -1.0f, rotation, scaleX, x), yCoord(1.0f, -1.0f, rotation, scaleY, y), z);
	glTexCoord2f(0.0f, 0.0f);  glVertex3f(xCoord(-1.0f, -1.0f, rotation, scaleX, x), yCoord(-1.0f, -1.0f, rotation, scaleY, y), z);
}