#pragma once

#include<string>

#include<glad/glad.h>
#include<glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader 
{
public:
	//state
	unsigned int ID;
	Shader() {}
	// sets the current shader as active
	Shader&	 Use();
	//Compiles the given shader from the given source code
	void	 Complile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr); //the geometry source is optimal
	//utility function
	void	 setFloat(const char* name, float value, bool useShader = false);
	void	 setInteger(const char* name, int value, bool useShader = false);
	void	 setVector2f(const char* name, float x, float y, bool useShader = false);
	void	 setVector2f(const char* name, const glm::vec2& value, bool useShader = false);
	void	 setVector3f(const char* name, float x, float y, float z, bool useShader = false);
	void	 setVector3f(const char* name, const glm::vec3& value, bool useShader = false);
	void	 setVector4f(const char* name, float x, float y, float z,float w, bool useShader = false);
	void	 setVector4f(const char* name, const glm::vec4& value, bool useShader = false);
	void	 setMatrix4(const char* name, const glm::mat4& matrix, bool useShader = false);
private:
	// checks if compilation or linking failed and if so, print the error logs
	void	 checkCompileErrors(unsigned int object, std::string type);
};