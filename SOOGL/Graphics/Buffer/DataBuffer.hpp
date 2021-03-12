#pragma once

#include "Buffer.hpp"
#include "SOOGL/Graphics/color.hpp"
#include "SOOGL/Math/vec2.hpp"
#include "SOOGL/Math/vec4.hpp"

namespace sgl
{
	enum class LoadMode
	{
		// The data is set only once and used many times
		Static = GL_STATIC_DRAW,
		// The data is changed a lot and used many times
		Dynamic = GL_DYNAMIC_DRAW,
		// The data is set only once and used by the GPU at most a few times
		Stream = GL_STREAM_DRAW
	};
	
	template <typename T, 
		uint COMPONENTS_COUNT, 
		GLenum DATA_TYPE,
		GLenum BUFFER_TYPE = GL_ARRAY_BUFFER>
	class DataBuffer
	{
	protected:
		Buffer<T> buf;
		mutable size_t data_size_in_ogl;
		mutable bool need_to_update = false;

		void updateData(LoadMode mode = LoadMode::Static) const
		{
			data_size_in_ogl = buf.data().size();
			buf.loadToOGL(BUFFER_TYPE, data_size_in_ogl, (GLenum)mode);
			need_to_update = false;
		}
	public:
		DataBuffer()
			: data_size_in_ogl(0) {}

		DataBuffer(const std::vector<T>& data) {
			changeData() = data;
		}
		DataBuffer(std::vector<T>&& data) {
			changeData() = std::move(data);
		}

		void activate(uint attribute, LoadMode mode = LoadMode::Static) const
		{
			if (this->need_to_update)
				this->updateData(mode);

			glEnableVertexAttribArray(attribute);
			glBindBuffer(BUFFER_TYPE, buf.nativeHandle());
			glVertexAttribPointer(attribute, COMPONENTS_COUNT, DATA_TYPE, GL_FALSE, 0, nullptr);
		}
		void deactivate(uint attribute) const
		{
			glDisableVertexAttribArray(attribute);
		}

		const std::vector<T>& data() const
		{
			return buf.data();
		}
		// returns non-const vector<T>&, you can change it(before first draw call)
		std::vector<T>& changeData()
		{
			this->need_to_update = true;
			return buf.data();
		}
		// clears the data from memory but the data won't be updated
		void clearFromMemory(LoadMode mode = LoadMode::Static)
		{
			this->updateData(mode);
			buf.data().clear();
		}
	};

	using ColorBuffer3f = DataBuffer<color3f, 3, GL_FLOAT>;
	using ColorBuffer4f = DataBuffer<color4f, 4, GL_FLOAT>;
	using UVBuffer = DataBuffer<fvec2, 2, GL_FLOAT>;
	/*
	const UVBuffer default_quad_UVs({
		{0.f, 0.f},
		{0.f, 1.f},
		{1.f, 1.f},
		{1.f, 0.f}
	});
	const UVBuffer default_rev_quad_UVs({
		{0.f, 1.f},
		{0.f, 0.f},
		{1.f, 0.f},
		{1.f, 1.f}
	});/**/

	namespace buffer
	{
		using sgl::LoadMode;
		using sgl::DataBuffer;
		using sgl::ColorBuffer3f;
		using sgl::ColorBuffer4f; 
		using sgl::UVBuffer;
	}
}