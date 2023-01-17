#include "ResourceManager.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <glad/stb_image.h>

//Instantiate static variables
std::map<std::string, Shader>		ResourceManager::Shaders;
std::map<std::string, Texture2D>	ResourceManager::Textures;

Shader ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name) 
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) 
{
	return Shaders[name];
}

Texture2D ResourceManager::loadTexture(const char* file, bool alpha, std::string name) 
{
	Textures[file] = loadTextureFromFile(file, alpha);
	return Textures[file];
}

Texture2D ResourceManager::getTexture(std::string name)
{
	return Textures[name];
}

void ResourceManager::clear() 
{
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	//1. retrieve the vertex/fragment source code from file path
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try 
	{
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		//read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		//close the file handler
		vertexShaderFile.close();
		fragmentShaderFile.close();
		//convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		//if geometry shader is present, also load a geometry shader
		if (gShaderFile) 
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "Error::Shader: Failed to read shader files" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();
	// 2. now create a shader object from source code
	Shader shader;
	shader.Complile(vShaderCode, fShaderCode, gShaderCode);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
	//create texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	//load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	// now generate texture
	texture.Generate(width, height, data);
	// and finally free image data
	stbi_image_free(data);
	return texture;
}


