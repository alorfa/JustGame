#pragma once

#include "SOOGL/Other/types.hpp"
#include "Shader.hpp"
#include <string>
#include <filesystem>

namespace sgl
{
	using namespace types;

	class ShaderCompiler
	{
		uint vertex = 0, geometry = 0, fragment = 0;

		void deleteShaders();

		/* Returns ogl shader id.
		* Data is shader source
		* Type is GLenum that takes shader type
		* Message is the same that in method loadFromMemory
		*/
		uint compile(const char* shader_source, uint type, std::string* message = nullptr);
	public:
		inline ShaderCompiler() = default;
		inline ~ShaderCompiler() = default;

		/* ���� ������ �� ��������������, ����� ������ ���������� shader_error
		* � ���������� ������. ���� ������ �������������, �� ���� ��������������,
		* �� ��� ��������� � message, ���� ��� �� ����� nullptr
		*/
		void loadFromMemory(const char* data, Shader::Type type, std::string* message = nullptr);

		/* ���� ��������� ���� �� ������, ����� ������ ���������� file_not_found 
		* � ��������� �����. ����� ����� ������� \ref loadFromMemory � ���������� �����
		*/
		void loadFromFile(const std::filesystem::path& path, Shader::Type type, std::string* message = nullptr);

		/*
		* Links shaders to shader program. 
		* hlvl::shader_error � ���������� �� ������. ���� ������ ������� ���������, ��
		* ���� ��������������, ��� ��������� � message, ���� ��� �� ����� nullptr
		*/
		Shader link(std::string* message = nullptr);
	};
}