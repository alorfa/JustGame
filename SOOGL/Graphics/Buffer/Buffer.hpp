#pragma once

#include <vector>
#include "SOOGL/Other/opengl.h"

namespace sgl
{
	template <typename T>
	class Buffer
	{
	private:
		std::vector<T> m_data;
		GLuint id;

		void create() {
			if (not id)
				glCreateBuffers(1, &id);
		}
		void destroy() {
			if (id)
				glDeleteBuffers(1, &id);
		}
	public:
		Buffer() {
			create();
		}
		~Buffer() {
			destroy();
		}
		Buffer(const Buffer& other)
			: m_data(other.m_data)
		{
			create();
		}
		Buffer& operator=(const Buffer& other)
		{
			m_data = other.m_data;
			create();
			return *this;
		}
		Buffer(Buffer&& other)
			: m_data(std::move(other.m_data))
		{
			id = other.id;
			other.id = 0;
		}
		Buffer& operator=(Buffer&& other)
		{
			m_data = std::move(other.m_data);
			id = other.id;
			other.id = 0;
			return *this;
		}
		GLuint nativeHandle() const {
			return id;
		}
		std::vector<T>& data() { 
			return m_data; 
		}
		const std::vector<T>& data() const {
			return m_data;
		}
		void loadToOGL(GLenum BUFFER_TYPE, size_t SIZE, GLenum MODE) const
		{
			glBindBuffer(BUFFER_TYPE, this->id);
			glBufferData(BUFFER_TYPE, SIZE * sizeof(T), &this->m_data[0], MODE);
		}
	};
	namespace buffer
	{
		using sgl::Buffer;
	}
}