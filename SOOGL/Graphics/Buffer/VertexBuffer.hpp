#pragma once

#include "DataBuffer.hpp"
#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/Math/vec3.hpp"

namespace sgl
{
	enum class DrawMode : GLenum
	{
		Points = GL_POINTS,
		Lines = GL_LINES,
		LineStrip = GL_LINE_STRIP,
		LineLoop = GL_LINE_LOOP,
		Triangles = GL_TRIANGLES,
		TriangleStrip = GL_TRIANGLE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN
	};

	template <typename T, uint COMPONENTS_COUNT, GLenum DATA_TYPE>
	class VertexBuffer : public DataBuffer<T, COMPONENTS_COUNT, DATA_TYPE>
	{
	public:
		void drawArrays(DrawMode type, int begin, int end) const
		{
			glDrawArrays(GLenum(type), begin, end);
		}
		void drawArrays(DrawMode type) const
		{
			glDrawArrays(GLenum(type), 0, (GLsizei)this->data_size_in_ogl);
		}
	};

	using VertexBuffer3f = VertexBuffer<fvec3, 3, GL_FLOAT>;
	using VertexBuffer2f = VertexBuffer<fvec2, 2, GL_FLOAT>;

	namespace buffer
	{
		using sgl::DrawMode;
		using sgl::VertexBuffer;
		using sgl::VertexBuffer2f;
		using sgl::VertexBuffer3f;
	}
}