#pragma once

#include "SOOGL/Other/types.hpp"
#include "SOOGL/Math/vec3.hpp"
#include "SOOGL/Math/vec4.hpp"
#include "SOOGL/Math/mat3.hpp"
#include "SOOGL/Math/mat4.hpp"
#include "SOOGL/Graphics/Image/Texture.hpp"
#include <map>

namespace sgl
{
	class ShaderCompiler;
}

namespace sgl
{
	using namespace types;
	using namespace vec;
	using namespace mat;

	using Uniform = int;

	enum Inbuilt
	{
		Vert2b = 1 << 0,
		Vert3b = 1 << 1,
		Col3b = 1 << 2,
		Col4b = 1 << 3,
		UVb = 1 << 4,
		rUVb = 1 << 5,
		Col3u = 1 << 6,
		Col4u = 1 << 7
	};

	class Shader
	{
		friend class ShaderCompiler;

		static std::map<int, Shader> shaders;

		uint id = 0;

		void destroy();

		inline Shader(uint id)
			: id(id) {}
	public:
		inline Shader() = default;
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(Shader&&) noexcept;
		Shader& operator=(Shader&&) noexcept;
		~Shader();

		uint nativeHandle() const;
		inline bool isValid() const {
			return (bool)id;
		}

		Uniform location(const char* name) const; 
		void setUniform(Uniform location, float value) const;
		void setUniform(Uniform location, const fvec3& value) const;
		void setUniform(Uniform location, const fvec4& value) const;
		void setUniform(Uniform location, const mat3& value) const;
		void setUniform(Uniform location, const mat4& value) const;
		void setUniform(Uniform location, const Texture& texture) const;

		void activate() const; 
		
		enum Type
		{
			Vertex, Geometry, Fragment
		};

		static const Shader* get(int inbuilt);
	};
}