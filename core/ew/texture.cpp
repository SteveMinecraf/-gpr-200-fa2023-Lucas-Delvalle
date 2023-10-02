#include "texture.h"
#include "shader.h"
#include "../ew/ewMath/external/stb_image.h"
#include "../ew/ewMath/external/glad.h"

unsigned int loadTexture(const char* filePath, int wrapMode, int filterMode) {

	stbi_set_flip_vertically_on_load(true);

	int width, height, numComponents;
	unsigned char* data = stbi_load(filePath, &width, &height, &numComponents, 0);
	if (data == NULL) {
		printf("Failed to load image %s", filePath);
		stbi_image_free(data);
		return 0;
	}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 4, GL_RGBA, width, height, 4, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
		return texture;
	}

void clear() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void bindQuadVAO() 
{
	glBindVertexArray(quadVAO);
}
void bindBackgroundTextures() 
{
	glBindTexture(GL_TEXTURE_2D, brickTexture);
}
void setBackgroundShaderUniforms(Shader& shader) 
{
	ew:: shader.setFloat("brickUniform", 0.5f);
}
void bindCharacterTextures() 
{
	glBindTexture(GL_TEXTURE_2D, characterTexture);
}
void setCharacterShaderUniforms(Shader& shader) 
{
	ew:: shader.setFloat("characterUniform", 1.0f);
}
void swapBuffers() 
{
	glfwSwapBuffers(window);
}