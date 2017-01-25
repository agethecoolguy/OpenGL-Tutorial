#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL) {
		std::cerr << "Texture loading failed for: " << fileName << std::endl;
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// For too small of a texture
	std::cout << "whoop" << std::endl;
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // width
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // height
	std::cout << "whoop" << std::endl;

	// For too many (MAG) or too little (MIN) pixels (useful for rotation, distance)
	// GL_LINEAR --> linear interpolation
	// GL_NEAREST --> direct pixel sample (pixelated effect at distance)
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::bind(unsigned int unit) {
	assert(unit >= 0 && unit <= 31); // force valid unit

	glActiveTexture(GL_TEXTURE0 + unit); // + unit because constants are ordered sequentially
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
