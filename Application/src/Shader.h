#pragma once

#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>

#include "Renderer.h"

class Shader
{
private:
	unsigned int m_RendererID;
	// constructor generates shaders during runtime
	// ------------------------------------------------------------------------

	struct ShaderProgramSource
	{
		const std::string VertexSource;
		const std::string FragmentSource;
	};
	static ShaderProgramSource ParseShader(const std::string& filepath);
	

	public:
	Shader(const std::string& filepath);

	// Return Renderer Shader ID
	unsigned int getID() const;

	// activate the shader
	void use() const;

	// utility uniform functions
	void setBool(const std::string& name, bool value) const;

	void setInt(const std::string& name, int value) const;

	void setFloat(const std::string& name, float value) const;

	void setVec2(const std::string& name, const glm::vec2& value) const;

	void setVec2(const std::string& name, float x, float y) const;

	void setVec3(const std::string& name, const glm::vec3& value) const;

	void setVec3(const std::string& name, float x, float y, float z) const;

	void setVec4(const std::string& name, const glm::vec4& value) const;

	void setVec4(const std::string& name, float x, float y, float z, float w) const;

	void setMat2(const std::string& name, const glm::mat2& mat) const;

	void setMat3(const std::string& name, const glm::mat3& mat) const;

	void setMat4(const std::string& name, const glm::mat4& mat) const;

	private:

	// Utility function for checking shader compilation/linking errors.	
	void checkCompileErrors(GLuint shader, std::string type);

};