#pragma once

#include "VertexBuffer.hpp"

namespace sgl
{
	template <typename T, GLenum DATA_TYPE>
	class IndexBufferTempl : public DataBuffer<T, 1, DATA_TYPE, GL_ELEMENT_ARRAY_BUFFER>
	{
		void activate(uint attribute, LoadMode mode = LoadMode::Static) const = delete;
		void deactivate(uint attribute) const = delete;
	public:
		void drawIndexes(PrimitiveType type, int count) const
		{
			if (this->need_to_update)
				this->updateData();

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
			glDrawElements((GLenum)type, count, DATA_TYPE, nullptr);
		}
		void drawIndexes(PrimitiveType type) const
		{
			this->drawIndexes(type, (int)this->data_size_in_ogl);
		}
	};
	using IndexBufferUint = IndexBufferTempl<unsigned, GL_UNSIGNED_INT>;
	using IndexBufferUshort = IndexBufferTempl<unsigned short, GL_UNSIGNED_SHORT>;
	using IndexBuffer = IndexBufferUint;
}