#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	// Shader program ID
	unsigned int ID;

	void loadShader(const char* path, GLenum shaderType);

	void buildShader();
public:
	unsigned int getID();

	Shader(const char* vertexPath, const char* fragmentPath);

	void enable() const;

};
