#pragma once

#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "Object.hpp"

namespace gd
{
	class StatucVertexObject : public Object
	{
	public:
		StatucVertexObject();
		~StatucVertexObject();

		sgl::VertexBuffer2f vertbuf;
		sgl::ColorBuffer4f colbuf;


	};
}