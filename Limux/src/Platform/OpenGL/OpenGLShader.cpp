#include "lmxpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Limux/Core/AssetLoader.h"

namespace LMX
{
	void CreateOGLShader(const std::string& vertexSrc, const std::string& fragmentSrc, uint32_t& ID)
	{
		LMX_PROFILE_FUNCTION();
		uint32_t vertexShader, fragmentShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		{
			std::string version = "#version 460 core";
			std::string vertex = version + vertexSrc;
			std::string fragment = version + fragmentSrc;

			const GLchar* vertexCode = vertex.c_str();
			const GLchar* fragmentCode = fragment.c_str();
			glShaderSource(vertexShader, 1, &vertexCode, NULL);
			glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
			glCompileShader(vertexShader);
			glCompileShader(fragmentShader);
		}


		ID = glCreateProgram();

		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		LMX_PROFILE_FUNCTION();
		CreateOGLShader(vertexSrc, fragmentSrc, m_RendererID);
	}
	OpenGLShader::OpenGLShader(const std::string& shaderSrc)
	{
		LMX_PROFILE_FUNCTION();
		std::stringstream file;
		file << shaderSrc;
		std::string line, source[2];
		enum Mode
		{
			NONE = -1,
			VERTEX, FRAGMENT
		};
		Mode mode = NONE;
		const char* typeToken = "#shader";
		
		while (std::getline(file, line))
		{
			if (line.contains(typeToken))
			{
				if (line.contains("vertex"))
					mode = VERTEX;
				else if (line.contains("fragment"))
					mode = FRAGMENT;
				else
					mode = NONE;
			}
			else if (mode != NONE)
				source[mode] += line;
			source[VERTEX]   += '\n';
			source[FRAGMENT] += '\n';
		}
		CreateOGLShader(source[VERTEX], source[FRAGMENT], m_RendererID);
	}
	Ref<OpenGLShader> OpenGLShader::Load(const std::string& shaderPath)
	{
		LMX_PROFILE_FUNCTION();
		return CreateRef<OpenGLShader>(AssetLoader::LoadFile(shaderPath));
	}
	Ref<OpenGLShader> OpenGLShader::Load(const std::string& vertexPath, const std::string& fragmentPath)
	{
		LMX_PROFILE_FUNCTION();
		return CreateRef<OpenGLShader>(AssetLoader::LoadFile(vertexPath), AssetLoader::LoadFile(fragmentPath));
	}
	OpenGLShader::~OpenGLShader()
	{
		LMX_PROFILE_FUNCTION();
		glDeleteProgram(m_RendererID);
	}
	void OpenGLShader::Bind() const
	{
		LMX_PROFILE_FUNCTION();
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const
	{
		LMX_PROFILE_FUNCTION();
		glUseProgram(0);
	}
	uint32_t OpenGLShader::GetUni(const std::string & name) const
	{
		LMX_PROFILE_FUNCTION();
		return glGetUniformLocation(m_RendererID, name.c_str());
	}
	#define LMX_UNIFORMFUNCTION(func, name, ...) \
		LMX_PROFILE_FUNCTION();\
		uint32_t location = GetUni(name);\
		if(location == -1){\
			if(senderror){\
				LMX_ERROR("Unable to locate uniform: {0}", name);\
			}\
		}\
		else{\
			func(location, __VA_ARGS__);\
			}\
		return location;
	
	uint32_t OpenGLShader::setUniform(const std::string& name, const bool& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniform1i, name, (int)value);
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const int& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniform1i, name, value);
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const float& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniform1f, name, value);
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::vec2& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniform2f, name, value.x, value.y);
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::vec3& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniform3f, name, value.x, value.y, value.z);
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::vec4& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniform4f, name, value.x, value.y, value.z, value.w);
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::mat2& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniformMatrix3fv, name, 1, GL_FALSE, glm::value_ptr(value));
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::mat3& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniformMatrix3fv, name, 1, GL_FALSE, glm::value_ptr(value));
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::mat4& value, bool senderror) const
	{
		LMX_UNIFORMFUNCTION(glUniformMatrix4fv, name, 1, GL_FALSE, glm::value_ptr(value));
	}
}