#pragma once

#include "SOOGL/Graphics/Buffer/VertexBuffer.hpp"
#include "SOOGL/Graphics/Transform/Transform2D.hpp"
#include "SOOGL/Math/vec2.hpp"

namespace sgl
{
	using namespace vec;

	class Block : public Transformable2D
	{
		struct RoundedCorner
		{
			VertexBuffer2f corner;
			fvec2 raduis;
		};
		/*
		* Indexes of corners:
		* 0				1
		* 
		* 3				2
		*/
		RoundedCorner corners[4];
		VertexBuffer2f buffer;
		Block* border = nullptr;
	public:
		Block()
		{
			sizeof(Block);
		}
		~Block();
	};
}