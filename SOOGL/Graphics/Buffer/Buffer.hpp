#pragma once

#include <vector>
#include "SOOGL/Other/opengl.h"

namespace sgl
{
	template <typename T>
	class Buffer
	{
	private:
		GLuint m_id;
		std::vector<T> m_data;

		void create() {
			if (not m_id)
				glCreateBuffers(1, &m_id);
		}
		void destroy() {
			if (m_id)
				glDeleteBuffers(1, &m_id);
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
			m_id = other.m_id;
			other.m_id = 0;
		}
		Buffer& operator=(Buffer&& other)
		{
			m_data = std::move(other.m_data);
			m_id = other.m_id;
			other.m_id = 0;
			return *this;
		}
		GLuint id() const {
			return m_id;
		}
		std::vector<T>& data() { 
			return m_data; 
		}
		const std::vector<T>& data() const {
			return m_data;
		}
		void loadToOGL(GLenum BUFFER_TYPE, size_t SIZE, GLenum MODE) const
		{
			glBindBuffer(BUFFER_TYPE, this->m_id);
			glBufferData(BUFFER_TYPE, SIZE * sizeof(T), &this->m_data[0], MODE);
		}
	};
}