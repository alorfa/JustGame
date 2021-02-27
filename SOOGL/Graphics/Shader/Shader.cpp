#include "Shader.hpp"
#include "SOOGL/Other/opengl.h"
#include <map>
#include "ShaderCreater.hpp"
#include "ShaderCompiler.hpp"

namespace sgl
{
	void Shader::destroy()
	{
		if (id)
			glDeleteProgram(id);
		id = 0;
	}
	Shader::Shader(Shader&& other) noexcept
	{
		destroy();
		id = other.id;
		other.id = 0;
	}
	Shader& Shader::operator=(Shader&& other) noexcept
	{
		destroy();
		id = other.id;
		other.id = 0;

		return *this;
	}
	Shader::~Shader()
	{
		destroy();
	}

	uint Shader::nativeHandle() const
	{
		return id;
	}

	Uniform Shader::location(const char* name) const
	{
		return glGetUniformLocation(id, name);
	}
	void Shader::setUniform(Uniform location, float value) const
	{
		glUniform1f(location, value);
	}
	void Shader::setUniform(Uniform location, const fvec3& value) const
	{
		glUniform3f(location, value.x, value.y, value.z);
	}
	void Shader::setUniform(Uniform location, const fvec4& value) const
	{
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	void Shader::setUniform(Uniform location, const mat3& value) const
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, value.mat);
	}
	void Shader::setUniform(Uniform location, const mat4& value) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, value.mat);
	}

	void Shader::setUniform(Uniform location, const Texture& texture) const
	{
		texture.activate(); 
		glUniform1i(location, texture.nativeHandle());
	}

	void Shader::activate() const
	{
		glUseProgram(id);
	}
	const Shader* Shader::get(int inbuilt)
	{
		if (shaders.count(inbuilt) == 1) // shader was created yet
			return &shaders.at(inbuilt);

		auto vertex_source = ShaderCreater::createVertex(inbuilt);
		auto fragment_source = ShaderCreater::createFragment(inbuilt);

		if (vertex_source.empty() or fragment_source.empty())
			return nullptr;

		ShaderCompiler compiler;
		compiler.loadFromMemory(vertex_source.c_str(), Shader::Vertex);
		compiler.loadFromMemory(fragment_source.c_str(), Shader::Fragment);
		shaders.insert(std::pair(inbuilt, compiler.link()));
		return &shaders.at(inbuilt);
	}

	std::map<int, Shader> Shader::shaders;
}