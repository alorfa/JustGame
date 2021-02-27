#include "ShaderCompiler.hpp"
#include "SOOGL/Other/opengl.h"
#include "SOOGL/Other/exceptions.hpp"
#include "SOOGL/System/File.hpp"

using namespace sgl::exceptions;

namespace sgl
{
	void ShaderCompiler::deleteShaders()
	{
		if (vertex)
			glDeleteShader(vertex);
		if (fragment)
			glDeleteShader(fragment);
		if (geometry)
			glDeleteShader(geometry);
		vertex = geometry = fragment = 0;
	}

	uint ShaderCompiler::compile(const char* shader_source, uint type, std::string* message)
	{
		GLuint shader_id = glCreateShader(type);

		glShaderSource(shader_id, 1, &shader_source, nullptr);
		glCompileShader(shader_id);

		GLint log_length = 0;
		GLint compile_status = GL_FALSE;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

		if (log_length > 0)
		{
			if (compile_status == GL_FALSE)
			{
				std::string shader_message;
				shader_message.resize(log_length);
				glGetShaderInfoLog(shader_id, log_length, nullptr, &shader_message[0]);
				throw shader_error(shader_message);
			}
			if (message)
			{
				message->resize(log_length);
				glGetShaderInfoLog(shader_id, log_length, nullptr, &(*message)[0]);
			}
		}
		return shader_id;
	}
	void ShaderCompiler::loadFromMemory(const char* data, Shader::Type type, std::string* message)
	{
		// need to free shader
		auto replaceShader = [](uint& shader_id, uint new_shader) 
		{
			if (shader_id)
				glDeleteShader(shader_id);
			shader_id = new_shader;
		};

		switch (type)
		{
		case Shader::Type::Vertex:
			replaceShader(vertex, compile(data, GL_VERTEX_SHADER, message));
			break;
		case Shader::Type::Geometry:
			replaceShader(geometry, compile(data, GL_GEOMETRY_SHADER, message));
			break;
		case Shader::Type::Fragment:
			replaceShader(fragment, compile(data, GL_FRAGMENT_SHADER, message));
			break;
		}
	}

	void ShaderCompiler::loadFromFile(const std::filesystem::path& path, Shader::Type type, std::string* message)
	{
		size_t length = 0;
		char* file_data = nullptr;

		File file;
		file.open(path, File::Read | File::Text).readAllBytes<char>(file_data, length);

		std::unique_ptr<char> cleaner(file_data);

		loadFromMemory(file_data, type, message);
	}
	Shader ShaderCompiler::link(std::string* message)
	{
		GLuint out_shader = glCreateProgram();

		if (vertex)
			glAttachShader(out_shader, vertex);
		if (fragment)
			glAttachShader(out_shader, fragment);
		if (geometry)
			glAttachShader(out_shader, geometry);
		glLinkProgram(out_shader);

		GLint log_length = 0;
		GLint link_status = GL_FALSE;
		glGetProgramiv(out_shader, GL_INFO_LOG_LENGTH, &log_length);
		glGetProgramiv(out_shader, GL_LINK_STATUS, &link_status);

		if (log_length > 0)
		{
			if (link_status == GL_FALSE)
			{
				std::string error;
				error.resize(log_length);
				glGetProgramInfoLog(out_shader, log_length, nullptr, &error[0]);
				throw shader_error(error.c_str());
			}
			if (message)
			{
				message->resize(log_length);
				glGetProgramInfoLog(out_shader, log_length, nullptr, &(*message)[0]);
			}
		}

		if (vertex)
			glDetachShader(out_shader, vertex);
		if (fragment)
			glDetachShader(out_shader, fragment);
		if (geometry)
			glDetachShader(out_shader, geometry);

		deleteShaders();

		return Shader(out_shader);
	}
}
