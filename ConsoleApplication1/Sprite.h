#ifndef SPRITE_H_
#define SPRITE_H_

#include "AllHeader.h"
#include "Vector3.h"
#include "Transformation.h"
#include "Color.h"
#include "stb_image.h"


class Texture
{
public:

	int m_width;
	int m_height;
	int nrChannels;
	unsigned int m_textureID;

	Texture(const char* path)
	{
		glGenTextures(1, &m_textureID);
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

};

class Sprite
{
private:
    int m_width;
    int m_height;
	int nrChannels;
	unsigned int m_textureID;

	void LoadTexture(const char* path);
	void DrawSquare(float x, float y, float z, float rotation, float scaleX, float scaleY, Color& color);
public:
    Sprite();
    Sprite(const std::string& file);
    ~Sprite();
	void Draw(float x, float y, float z, float rotation, float scaleX, float scaleY, Color& color = Color::White);
	void DrawLine(Vector3 start, Vector3 end, float scaleX, float scaleY, Color& color = Color::White);
};




#endif // SPRITE_H_
