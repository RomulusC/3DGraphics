#pragma once
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <glm/glm.hpp>

#include "Renderer.h"

class Shader
{
private:
	unsigned int m_RendererID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------

	struct ShaderProgramSource
	{
		const std::string VertexSource;
		const std::string FragmentSource;
	};

	static ShaderProgramSource ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line)) {
			if (line.find("#shader") != std::string::npos) {
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else {
				ss[(int)type] << line << "\n";
			}
		}

		return { ss[0].str(), ss[1].str() };
	}
	
public:
	Shader(const std::string& filepath)
	{		
		ShaderProgramSource source = ParseShader(filepath);

		const char* vShaderCode = source.VertexSource.c_str();
		const char* fShaderCode = source.FragmentSource.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		GLCall(vertex = glCreateShader(GL_VERTEX_SHADER));
		GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
		GLCall(glCompileShader(vertex));
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		GLCall(fragment = glCreateShader(GL_FRAGMENT_SHADER));
		GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
		GLCall(glCompileShader(fragment));
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		GLCall(m_RendererID = glCreateProgram());
		GLCall(glAttachShader(m_RendererID, vertex));
		GLCall(glAttachShader(m_RendererID, fragment));
		GLCall(glLinkProgram(m_RendererID));
		checkCompileErrors(m_RendererID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessery
		GLCall(glDeleteShader(vertex));
		GLCall(glDeleteShader(fragment));

	}
	// Return Renderer Shader ID
	// ------------------------------------------------------------------------
	unsigned int getID() const
	{
		return m_RendererID;
	}
	// activate the shader
	// ------------------------------------------------------------------------
	void use() const
	{
		GLCall(glUseProgram(m_RendererID));
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		GLCall(glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value));
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		GLCall(glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value));
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		GLCall(glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value));
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		GLCall(glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]));
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		GLCall(glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), x, y));
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		GLCall(glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]));
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		GLCall(glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z));
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		GLCall(glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]));
	}
	void setVec4(const std::string& name, float x, float y, float z, float w) const
	{
		GLCall(glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w));
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		GLCall(glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		GLCall(glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		GLCall(glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(GLuint shader, std::string type)
	{
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM")
		{
			GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
			if (!success)
			{
				GLCall(glGetShaderInfoLog(shader, 1024, NULL, infoLog));
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			GLCall(glGetProgramiv(shader, GL_LINK_STATUS, &success));
			if (!success)
			{
				GLCall(glGetProgramInfoLog(shader, 1024, NULL, infoLog));
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};