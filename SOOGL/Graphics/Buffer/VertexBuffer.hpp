#pragma once

#include "DataBuffer.hpp"
#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/Math/vec3.hpp"
#include "SOOGL/Render/RenderTarget.hpp"

namespace sgl
{
	template <typename T, uint COMPONENTS_COUNT, GLenum DATA_TYPE>
	class VertexBuffer;

	using VertexBuffer3f = VertexBuffer<fvec3, 3, GL_FLOAT>;
	using VertexBuffer2f = VertexBuffer<fvec2, 2, GL_FLOAT>;

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

		static const VertexBuffer2f& default_quad_verts()
		{
			static VertexBuffer2f b;
			b.changeData() = {
				{0.f, 0.f},
				{0.f, 1.f},
				{1.f, 1.f},
				{1.f, 0.f}
			};
			return b;
		}
	};

	namespace buffer
	{
		using sgl::VertexBuffer;
		using sgl::VertexBuffer2f;
		using sgl::VertexBuffer3f;
	}
}