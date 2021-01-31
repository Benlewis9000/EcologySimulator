#include "Shader.h"

/**
* Create program and link compiled shaders of sources given.
*
* @param vertexPath path to vertex shader source
* @param fragmentPath path to fragment shader source
*/
Shader::Shader(const char* vertexPath, const char* fragmentPath) {

	// Create program
	this->ID = glCreateProgram();

	// Load shader sources and compile
	loadShader(vertexPath, GL_VERTEX_SHADER);
	loadShader(fragmentPath, GL_FRAGMENT_SHADER);
	// Link shaders to program
	buildShader();


}

/**
 * Get the program ID of this shader program.
 *
 * @return shader program ID
 */
unsigned int Shader::getID() {

	return this->ID;

}

/**
 * Load shader source, compile and attach to this program.
 *
 * @param path to shader source
 * @param shaderType type of shader
 */
void Shader::loadShader(const char* path, GLenum shaderType) {

	// Read in shader source code
	std::string source;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {

		// Open file
		shaderFile.open(path);
		std::stringstream shaderStream;
		// Stream file into stream
		shaderStream << shaderFile.rdbuf();
		// Close file
		shaderFile.close();
		source = shaderStream.str();

	}
	catch (std::ifstream::failure) {

		std::cerr << "Error: failed to read shader source file." << std::endl;

	}

	const char* sourceCstr = source.c_str();

	// Create shader
	unsigned int shader = glCreateShader(shaderType);
	// Attach and compile shader source
	glShaderSource(shader, 1, &sourceCstr, NULL);
	glCompileShader(shader);
	// Check compilation was successful
	int success;
	char log[1024];
	glGetShaderiv(shader, shaderType, &success);
	if (!success) {

		// Retrieve shader log
		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		std::cerr << "Error: failed to compile shader source:\n" << log << std::endl;

	}

	// Attach shader to program
	glAttachShader(this->ID, shader);

}

/**
 * Link attached shaders.
 */
void Shader::buildShader() {

	// Link program
	glLinkProgram(this->ID);
	// Check linking was successful
	int success;
	char log[1024];
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->ID, sizeof(log), NULL, log);
		std::cerr << "Error: failed to link shader program:\n" << log << std::endl;
	}

}

/**
* Activate shader on OpenGL context.
*/
void Shader::enable() const {

	glUseProgram(ID);

}