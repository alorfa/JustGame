#pragma once

#include "DataBuffer.hpp"

namespace sgl
{
	template <typename T>
	class Activator
	{
		const T* buffer = 0;
		uint attribute = 0;
	public:
		Activator() = default;
		Activator(const T& buffer, uint attribute, LoadMode mode = LoadMode::Static)
		{
			this->buffer = &buffer;
			this->attribute = attribute;
			buffer.activate(attribute, mode);
		}
		Activator(const Activator&) = delete;
		Activator& operator=(const Activator&) = delete;
		~Activator()
		{
			if (buffer)
				buffer->deactivate(attribute);
		}

		void activate(const T& buffer, uint attribute, LoadMode mode = LoadMode::Static)
		{
			this->buffer = &buffer;
			this->attribute = attribute;
			buffer.activate(attribute, mode);
		}
	};
}