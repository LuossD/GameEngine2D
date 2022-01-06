#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>
#include <iostream>

namespace Bengine
{
	GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0)
	{
		std::cout << "GLSLProgram" << std::endl;
	}

	GLSLProgram::~GLSLProgram()
	{

	}

	void GLSLProgram::initShaderProgram()
	{
		createShaderProgram();
		compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
		addAttribute("vertexPosition");
		addAttribute("vertexColor");
		addAttribute("vertexUV");
		linkShaders();
	}

	void GLSLProgram::createShaderProgram()
	{
		//This func(glCreateProgram) can only be called after opengl has been initialized.Otherwise, an error will be reported.
		//create a GLSLProgram
		_programID = glCreateProgram();
	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (_vertexShaderID == 0)
		{
			fatalError("Vertex shader failed to be created!");
		}

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (_fragmentShaderID == 0)
		{
			fatalError("Fragment shader failed to be created!");
		}

		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);
	}

	void GLSLProgram::linkShaders()
	{
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		_programID = glCreateProgram();
		// Attach our shaders to our program
		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		// Link our program
		glLinkProgram(_programID);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(_programID);
			// Don't leak shaders either.
			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);

			// Use the infoLog as you see fit.

			// In this simple program, we'll just leave
			printf("%s\n", &infoLog[0]);
			fatalError("Shader program failed to link!");
		}

		// Always detach shaders after a successful link.
		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
	}

	void GLSLProgram::compileShader(const std::string& shaderFilePath, GLuint& shaderID)
	{
		std::ifstream vertexFile(shaderFilePath);
		if (vertexFile.fail())
		{
			perror(shaderFilePath.c_str());
			fatalError("Failed to open" + shaderFilePath);
		}

		std::string fileContents = "";
		std::string line;
		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}
		vertexFile.close();

		const char* shaderCode = fileContents.c_str();
		glShaderSource(shaderID, 1, &shaderCode, nullptr);
		glCompileShader(shaderID);

		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(_vertexShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(shaderID); // Don't leak the shader.

			printf("%s\n", &errorLog[0]);
			fatalError("Shader" + shaderFilePath + "failed to compile!");
		}
	}

	void GLSLProgram::addAttribute(const std::string& attributeName)
	{
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
		{
			fatalError("Uniform" + uniformName + "not found in shader!");
		}
		return location;
	}

	void GLSLProgram::useProgram()
	{
		glUseProgram(_programID);
		for (GLuint i = 0; i < _numAttributes; ++i)
		{
			glEnableVertexAttribArray(i);
		}
	}

	void GLSLProgram::unuseProgram()
	{
		glUseProgram(0);
		for (GLuint i = 0; i < _numAttributes; ++i)
		{
			glDisableVertexAttribArray(i);
		}
	}
}




