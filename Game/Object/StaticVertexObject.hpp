#pragma once

#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "Object.hpp"

namespace gd
{
	class StatucVertexObject : public Object
	{
		sgl::VertexBuffer2f vertbuf;
		sgl::ColorBuffer4f colbuf;
	public:
		StatucVertexObject();
		~StatucVertexObject();

		inline const sgl::VertexBuffer2f& vertBuf() const {
			return vertbuf;
		}
		inline const sgl::ColorBuffer4f& colBuf() const {
			return colbuf;
		}
		void setData()
	};
}