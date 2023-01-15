#pragma once

#include<map>

#include <glad/glad.h>

#include "Texture.hpp"
#include "Shader.hpp"

class ResourceManager
{
public:
	//resource storage
	static std::map<std::string, Shader>	Shaders;
	static std::map<std::string, Texture2D> Textures;
	//loads (and generates) a shader program from file loadding vertex, fragment (and geometry) shader's source code. If gShaderFile is not nullptr, it also loads a geometry shader
	static Shader		loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	//retrieves a stored shader
	static Texture2D	GetShader(std::string name);
	//loads(and generates) a texture from file
	static Texture2D	loadTexture(const char* file, bool alpha, std::string name);
	//retrieves a stored texture
	static Texture2D	getTexture(std::string name);
	//properly deallocates all loaded resources.
	static void			clear();
private:
	//private constructor, that is we do not want any actual resource manager object. Its members and functions should be publicly available(static).
	ResourceManager();
	//loads and generates a shader from a file
	static Shader		loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	//loads a single texture from file
	static Texture2D	loadTextureFromFile(const char* file, bool alpha);
};