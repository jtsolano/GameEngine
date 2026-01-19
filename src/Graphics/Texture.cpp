#include <Texture.h>
#include <stb_image.h>
#include <string>

Texture::Texture()
{
	glGenTextures(1, &m_TextureId);

	glBindTexture(GL_TEXTURE_2D, m_TextureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	const string Path = string(PROJECT_ROOT) + string("textures/wall.jpg");
	unsigned char* data = stbi_load(Path.c_str(), &width, &height, &nrChannels, 0);

	if (data != nullptr)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(data);


}

Texture::~Texture()
{
	if (m_TextureId != 0)
	{
		glDeleteTextures(1, &m_TextureId);
		m_TextureId = 0;
	}

}
