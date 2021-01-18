#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	// Shader program ID
	unsigned int ID;

	/**
	 * Load shader source, compile and attach to this program.
	 * 
	 * @param path to shader source
	 * @param shaderType type of shader
	 */
	void loadShader(const char* path, GLenum shaderType);

	/**
	 * Link attached shaders.
	 */
	void buildShader();
public:
	inline unsigned int getID();

	/**
	* Create program and link compiled shaders of sources given.
	* 
	* @param vertexPath path to vertex shader source
	* @param fragmentPath path to fragment shader source
	*/
	Shader(const char* vertexPath, const char* fragmentPath);

	/**
	* Activate shader on OpenGL context.
	*/
	void enable() const;

};

/**
 * Get the program ID of this shader program.
 * 
 * @return shader program ID
 */
inline unsigned int Shader::getID() {

	return this->ID;

}