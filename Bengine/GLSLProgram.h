#pragma once
#include <string>
#include <glad/glad.h>

namespace Bengine
{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();
		void initShaderProgram();
		
		GLint getUniformLocation(const std::string& uniformName);

		void useProgram();
		void unuseProgram();

	private:
		//Methods that are called internally by themselves should be private
		void compileShader(const std::string& shaderFilePath, GLuint& shaderID);
		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void linkShaders();

		void createShaderProgram();
		void addAttribute(const std::string& attributeName);

		GLuint _programID;
		GLuint _vertexShaderID;
		GLuint _fragmentShaderID;
		GLuint _numAttributes;
	};

}

